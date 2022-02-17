
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)
        
        $RCSfile: block.c,v $
        $Revision: 1.9 $
        $Date: 1998/09/30 13:29:58 $
 *---------------------------------------------------------------------*/

/*
 * File:	block.c
 * Create Date:	Tue Sep 19 16:20:26 PDT 1995
 * Creator:     Kevin Luster, kluster@sgi.com
 *
 */

#include <ultra64.h>
#include <PR/ramrom.h>	/* needed for argument passing into the app */
#include <assert.h>
#include <os.h>

#include "controller.h"
#include "block.h"
#include "static.h"
#include "subcube.h"
#include "subplane.h"
#include "timer.h"

#include "mario-small.h"

/*
 * Symbol genererated by "makerom" to indicate the end of the code segment
 * in virtual (and physical) memory
 */
extern char _codeSegmentEnd[];

/*
 * Symbols generated by "makerom" to tell us where the static segment is
 * in ROM.
 */

/*
 * Stacks for the threads as well as message queues for synchronization
 * This stack is ridiculously large, and could also be reclaimed once
 * the main thread is started.
 */
u64	bootStack[STACKSIZE/sizeof(u64)];

static void	idle(void *);
static void	main(void *);

static OSThread	idleThread;
static u64	idleThreadStack[STACKSIZE/sizeof(u64)];

static OSThread	mainThread;
static u64	mainThreadStack[STACKSIZE/sizeof(u64)];

/* this number (the depth of the message queue) needs to be equal
 * to the maximum number of possible overlapping PI requests.
 * For this app, 1 or 2 is probably plenty, other apps might
 * require a lot more.
 */
#define NUM_PI_MSGS     8

static OSMesg PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;

OSMesgQueue     dmaMessageQ, rspMessageQ, rdpMessageQ, retraceMessageQ;
OSMesg          dmaMessageBuf, rspMessageBuf, rdpMessageBuf, retraceMessageBuf;
OSMesg          dummyMessage;
OSIoMesg        dmaIOMessageBuf;

OSMesg		dummyMesg;
OSTask		*tlistp;
Dynamic		*dynamicp;

int             ActiveController;
int             ControllerInput     =  1;
int             CreateNewCubes      =  1;
int             CreateNewPlanes     =  1;
int             UseAAMode           =  0;
int             UseZMode            =  0;
int             SelfScaleTimer      =  1;
int             EyeZPosition        =  0;
int             TranslateHorizontal =  0;
int             TranslateVertical   =  0;
int             RotateGlobalXAxis   =  0;
int             RotateGlobalYAxis   =  0;
int             ClipRatio           =  1;
int             TimerTicks          =  7;
int             UseTextureMode      =  0;
int             UseGlobalTransforms =  1;

int             UseViModeX          =  0;
int             ScreenWidth         =  SCREEN_WD_320;
int             ScreenWidthDelta    =  0;

float           TimePerFrame        =  0;
float           TicksPerSec;

OSTime          t1, t2;

/*
 * Dynamic data.
 */
Dynamic dynamic;

/*
 * Turbo data.
 */

/* init dp state, clear screen: */
Gfx	dpGlobDPBlock[] =
{
	gsDPPipeSync(),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

	gsDPPipeSync(),
	gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, cfb_16_a),
	gsDPSetFillColor((GPACK_RGBA5551(64,0,64,1) << 16 |
			  GPACK_RGBA5551(64,0,64,1))),
	gsDPFillRectangle(0, 0, SCREEN_WD, SCREEN_HT-1),

	gsDPPipeSync(),
	gsDPEndDisplayList(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
	gsDPNoOp(),
};

/* global data */
gtGlobState	dpGlobObjState =
{
    0xffff,						/* perspNorm */
    0x0, 0x0,						/* pad0, pad1 */
    gsDPClearOtherMode(),				/* rdpOthermode */
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 	/* segBases */
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
    },
    {	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,		/* viewport */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,
    },
    &(dpGlobDPBlock[0])
};
gtGlobState	*ggsp = &(dpGlobObjState);


/*
 * necessary for RSP tasks:
 */
u64 dram_stack[SP_DRAM_STACK_SIZE64];	/* used for matrix stack */
    
/*
 * Task descriptor.
 */
OSTask	tlist =
{
    M_GFXTASK,			/* task type */
    OS_TASK_DP_WAIT,		/* task flags */
    NULL,			/* boot ucode pointer (fill in later) */
    0,				/* boot ucode size (fill in later) */
    NULL,			/* task ucode pointer (fill in later) */
    SP_UCODE_SIZE,		/* task ucode size */
    NULL,			/* task ucode data pointer (fill in later) */
    SP_UCODE_DATA_SIZE,		/* task ucode data size */
    &(dram_stack[0]),		/* task dram stack pointer */
    SP_DRAM_STACK_SIZE8,	/* task dram stack size */
    NULL,		        /* task output buffer ptr (not always used) */
    NULL,		        /* task output buffer size ptr */
    NULL,			/* task data pointer (fill in later) */
    0,				/* task data size (fill in later) */
    NULL,			/* task yield buffer ptr (not used here) */
    0				/* task yield buffer size (not used here) */
};

gtGfx		*gtlistp;
Gfx		*glistp;	/* global for test case procs */
    
/*
 * global variables
 */

int      draw_buffer        = 0;

void    *cfb_ptrs[2];

#ifdef DEBUG
void parse_args(char *);
#endif

OSViMode viModeXpn1;	/* Structure for test Vi mode Xpn1 
				   which is based on Lpn1 */

OSPiHandle	*handler;

void boot(void)
{

#ifdef DEBUG
    int i;
    u32 *argp;
    u32 argbuf[16];
#endif

    /* notice that you can't call osSyncPrintf() until you have
     * an idle thread.
     */
    
    osInitialize();

    handler = osCartRomInit();

#ifdef DEBUG
    argp = (u32 *)RAMROM_APP_WRITE_ADDR;
    for (i=0; i<sizeof(argbuf)/4; i++, argp++) 
      {
	osEPiReadIo(handler, (u32)argp, &argbuf[i]); /* Assume no DMA */
      }

    parse_args((char *) argbuf);
#endif
    
    osCreateThread(&idleThread, 1, idle, (void *)0,
		   idleThreadStack+STACKSIZE/sizeof(u64), 10);
    osStartThread(&idleThread);

    /* never reached */
}

#ifdef DEBUG
void parse_args(char *argstring)
{
  int		argc = 1;
  char	*arglist[32], **argv = arglist;	/* max 32 args */
  char	*ptr;

  if (argstring == NULL || argstring[0] == '\0')
    return;

  /* re-organize argstring to be like main(argv,argc) */

  ptr = argstring;
  while (*ptr != '\0') {
    while (*ptr != '\0' && (*ptr == ' ')) 
      {
	*ptr = '\0';
	ptr++;
      }
    if (*ptr != '\0')
      arglist[argc++] = ptr;
    while (*ptr != '\0' && (*ptr != ' ')) 
      {
	ptr++;
      }
  }

  /* process the arguments: */
  while ((argc > 1) && (argv[1][0] == '-')) 
    {
      switch(argv[1][1]) 
	{
	case 's':
	  SelfScaleTimer = 0;
	  break;

	default:
	  break;
	}
      
      argc--;
      argv++;
    }
}
#endif


static void idle(void *arg)
{
  /* Initialize video */
  osCreateViManager(OS_PRIORITY_VIMGR);
  
  if (UseAAMode)
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
  else
    osViSetMode(&osViModeTable[OS_VI_NTSC_LPN1]);

  ScreenWidth = SCREEN_WD_320;
  /*
   * Replicate Lpn1 mode to Xpn1
   */
  bcopy((char *)&osViModeNtscLpn1, (char *)&viModeXpn1,
	sizeof(osViModeNtscLpn1));
  
  osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON);
  
  /*
   * Start PI Mgr for access to cartridge
   */
  osCreatePiManager((OSPri)OS_PRIORITY_PIMGR, &PiMessageQ, PiMessages, 
		    NUM_PI_MSGS);
  
  /*
   * Create main thread
   */
  osCreateThread(&mainThread, 3, main, arg,
		 mainThreadStack+STACKSIZE/sizeof(u64), 10);
  
  osStartThread(&mainThread);
  
  /*
   * Become the idle thread
   */
  osSetThreadPri(0, 0);
  
  for (;;);
}

void CreateMessageQueues(void)
{
  osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);
  
  osCreateMesgQueue(&rspMessageQ, &rspMessageBuf, 1);
  osSetEventMesg(OS_EVENT_SP, &rspMessageQ, dummyMessage);
  
  osCreateMesgQueue(&rdpMessageQ, &rdpMessageBuf, 1);
  osSetEventMesg(OS_EVENT_DP, &rdpMessageQ, dummyMessage);
  
  osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf, 1);
  osViSetEvent(&retraceMessageQ, dummyMessage, 1);  
}

void CreateTaskStructure(void)
{
  /* Build graphics task */

  tlistp->t.ucode_boot = (u64 *) rspbootTextStart;
  tlistp->t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;

  /* choose which ucode to run */

  tlistp->t.ucode      = (u64 *) gspTurbo3DTextStart;
  tlistp->t.ucode_data = (u64 *) gspTurbo3DDataStart;
  
  /* initial display list: */
  tlistp->t.data_ptr = (u64 *) &(dynamicp->gtlist[0]);
}

static void SwapViBuffer(void)
{
  /* setup to swap buffers */
  osViSwapBuffer(cfb_ptrs[draw_buffer]); 
  
  /* Make sure there isn't an old retrace in queue */
  if (MQ_IS_FULL(&retraceMessageQ))
    (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
  
  /* Wait for Vertical retrace to finish swap buffers */
  (void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);
  draw_buffer ^= 1;
}

void ApplyGlobalTransformations(void)
{
  guTranslate(&dynamicp->Translation,  
	      TranslateHorizontal/320.0 * ScreenWidth, 
	      TranslateVertical/240.0 * SCREEN_HT,
	      0.0);
  guRotate(&dynamicp->RotationX, RotateGlobalXAxis, 1.0F, 0.0F, 0.0F); 
  guRotate(&dynamicp->RotationY, RotateGlobalYAxis, 0.0F, 1.0F, 0.0F); 
  guTranslate(&dynamicp->TranslateOut,  
	      +(XMAX+XMIN)/2.0, 
	      +(YMAX+YMIN)/2.0,
	      -(ZMAX+ZMIN)/2.0);
  guTranslate(&dynamicp->TranslateIn,  
	      -(XMAX+XMIN)/2.0,
	      -(YMAX+YMIN)/2.0,
	      +(ZMAX+ZMIN)/2.0);
  
  guMtxCatL(&dynamicp->TranslateOut, &dynamicp->Translation,
	    &dynamicp->AA);
  guMtxCatL(&dynamicp->RotationX, &dynamicp->AA,
	    &dynamicp->BB);
  guMtxCatL(&dynamicp->RotationY, &dynamicp->BB,
	    &dynamicp->AA);
  guMtxCatL(&dynamicp->TranslateIn, &dynamicp->AA,
	    &dynamicp->BB);
  guMtxCatL(&dynamicp->BB, &dynamicp->viewing,
	    &dynamicp->viewing);
}

static void SetupViewing(void)
{
	/* compute single model-view-projection matrix: */
	guPerspective(&dynamicp->projection, &(ggsp->sp.perspNorm),
		      33, 320.0/240.0, 1, 2000, 1.0);
	guLookAt(&dynamicp->viewing, 
		 160, 120, 400 - EyeZPosition,
		 160, 120, -EyeZPosition,
		 0, 1, 0);
	guMtxCatL(&dynamicp->viewing, &dynamicp->projection,
		  &dynamicp->viewing);
}

unsigned int xseed = (7789<<16)+13399;	

unsigned int xrand(void)
{
    unsigned int x;
    
    x = (xseed<<2) + 2;
    
    x *= (x+1);
    x = x >> 2;

    xseed = x;

    return( x );
}

float frand(void)
{
  return((xrand()%32767) / 32768.0);
}

static void doPolyFuncs(void)
{
  /* Setup display modes antialiased in 1 cycle */

  SetupViewing();

  if (UseGlobalTransforms)
    ApplyGlobalTransformations();
      
/*
  CreatePlanes();
*/
  CreateBlocks();
}

static void InitRsp(int clearScreen)
{
  static Vp vp;
  Gfx	*gptr;

  vp.vp.vscale[0] = ScreenWidth*2;
  vp.vp.vscale[1] = SCREEN_HT*2;
  vp.vp.vscale[2] = G_MAXZ/2;
  vp.vp.vscale[3] = 0;
  vp.vp.vtrans[0] = ScreenWidth*2;
  vp.vp.vtrans[1] = SCREEN_HT*2;
  vp.vp.vtrans[2] = G_MAXZ/2;
  vp.vp.vtrans[3] = 0;

  /* handle variable viewport based on screen size: */
  bcopy((char *)&(vp.vp), (char *)&(ggsp->sp.viewport), sizeof(Vp_t));

  /* init global state: */
  ggsp->sp.segBases[0] = 0x0;	/* physical mapping */

  /* set rendermode and cycletype for clear object: */
  gtStateSetOthermode(&(ggsp->sp.rdpOthermode), GT_RENDERMODE,
		      (G_RM_OPA_SURF | G_RM_OPA_SURF2));
  gtStateSetOthermode(&(ggsp->sp.rdpOthermode), GT_CYCLETYPE, 
		      G_CYC_FILL);

  gptr = (Gfx *) &(ggsp->sp.rdpCmds[0]);
  gDPPipeSync(gptr++);
  if (clearScreen) {
      gDPSetScissor(gptr++, G_SC_NON_INTERLACE, 0, 0, ScreenWidth, SCREEN_HT);
      gDPSetCombineMode(gptr++, G_CC_SHADE, G_CC_SHADE);
      gDPPipeSync(gptr++);
      gDPSetColorImage(gptr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ScreenWidth,
		       cfb_ptrs[draw_buffer]);
      gDPSetFillColor(gptr++, (GPACK_RGBA5551(64,0,64,1) << 16 |
			       GPACK_RGBA5551(64,0,64,1)));
      gDPFillRectangle(gptr++, 0, 0, ScreenWidth, SCREEN_HT-1);
      if (UseTextureMode) {
	  gDPLoadTextureBlock(gptr++, mario_small, G_IM_FMT_RGBA, G_IM_SIZ_16b,
			    32, 32, 0,
			    G_TX_WRAP | G_TX_NOMIRROR, 
			    G_TX_WRAP | G_TX_NOMIRROR,
			    G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
	  gDPSetCombineMode(gptr++, G_CC_DECALRGB, G_CC_DECALRGB);
      }
      gDPPipeSync(gptr++);
  }
  gDPEndDisplayList(gptr++);
}

static void UpdateViMode(void)
{
  u32 xScale;
  OSIntMask im;

  ScreenWidth = SCREEN_WD_MIN+ScreenWidthDelta;
  if (ScreenWidth < SCREEN_WD_MIN)
      ScreenWidth = SCREEN_WD_MIN;
  if (ScreenWidth > SCREEN_WD_MAX)
      ScreenWidth = SCREEN_WD_MAX;
  xScale = (u32)((ScreenWidth * XSCALE_MAX) / SCREEN_WD_MAX);

  /* Change width, xScale, and origin */
  im = osSetIntMask(OS_IM_VI);
  viModeXpn1.comRegs.width     = ScreenWidth;
  viModeXpn1.comRegs.xScale    = xScale;
  viModeXpn1.fldRegs[0].origin = ScreenWidth*2;
  viModeXpn1.fldRegs[1].origin = ScreenWidth*2;
  (void)osSetIntMask(im);

  if (!UseViModeX)
    {
      if (UseAAMode)
        osViSetMode(&osViModeNtscLan1);
      else
        osViSetMode(&osViModeNtscLpn1);
      ScreenWidth = SCREEN_WD_320;
    }
  else 
    {
      osViSetMode(&viModeXpn1);
    }
}


static void InitDisplayLists(int clearScreen)
{
  /* pointers to build the display list */
  glistp = dynamicp->glist;
  gtlistp = &(dynamicp->gtlist[0]);
  
  /* Initialize RSP state */
  InitRsp(clearScreen);

}

static void CleanupAndSendDisplayList(void)
{
    /* global state: */
  gtlistp->obj.gstatep = (gtGlobState *) NULL;
  gtlistp->obj.statep = &dpFinalObj;
  gtlistp->obj.vtxp = (Vtx *) NULL;
  gtlistp->obj.trip = (gtTriN *) NULL;
  gtlistp++;
  
  gtlistp->obj.gstatep = (gtGlobState *) NULL;
  gtlistp->obj.statep = (gtState *) NULL;	/* signal end of object list */
  gtlistp->obj.vtxp = (Vtx *) NULL;
  gtlistp->obj.trip = (gtTriN *) NULL;
  gtlistp++;
  
  tlistp->t.data_size = (u32)((gtlistp - dynamicp->gtlist) * sizeof(gtGfx));
	
  /* Write back dirty cache lines that need to be read by the RCP */
  osWritebackDCache(&dynamic, sizeof(dynamic));
	
  /* start up the RSP task */
  CreateTaskStructure();
  
  osSpTaskLoad(tlistp);
  t1 = osGetTime(); 
  osSpTaskStartGo(tlistp);
	
  (void)osRecvMesg(&rdpMessageQ, NULL, OS_MESG_BLOCK);
  t2 = osGetTime();
}


#ifdef DEBUG

static void PrintStatNumbers(int DisplayListLength)
{
  NumCubePolys  = 12 * NumSubCubes * NumCubesPerAxis * NumCubesPerAxis * NumCubesPerAxis;
  NumPlanePolys =  2 * NumSubPlanes;
  
  osSyncPrintf("AA %3s ZB %3s\t\t", 
	     UseAAMode ? "on" : "off",
	     UseZMode  ? "on" : "off");
  
  osSyncPrintf("Cubes Per Row %d\tCube Divisions {%d,%d,%d} \n",
	     NumCubesPerAxis,
	     CubeDivisions[0], CubeDivisions[1], CubeDivisions[2]);
  
  osSyncPrintf("Cube Width %3d\t\tCube tris %d\t\tPlane tris %d\n\n",
	     BlockWidth, NumCubePolys, NumPlanePolys);
  
  osSyncPrintf("Plane Dimensions X -> {%4d,%4d} \n",
	     (int) PlaneMinMax[0][0], (int) PlaneMinMax[0][1]);
  
  osSyncPrintf("Plane Dimensions Z -> {%4d,%3d} \n",
	     (int) PlaneMinMax[1][0], (int) PlaneMinMax[1][1]);
  
  osSyncPrintf("Plane Divisions    -> {%d, %d} \n",
	     PlaneDivisions[0], PlaneDivisions[1]);
  
  osSyncPrintf("Current Vi Mode    -> ");
  if (UseViModeX) {
      osSyncPrintf("Xpn1 (%dx240)      \n", viModeXpn1.comRegs.width);
  }
  else {
      osSyncPrintf("Lpn1/Lan1 (320x240)\n");
  }
  osSyncPrintf(
      "    Xpn1: (%dx240), width=0x%x, x_scale=0x%x, origin=0x%x\n",
      viModeXpn1.comRegs.width,
      viModeXpn1.comRegs.width,
      viModeXpn1.comRegs.xScale,
      viModeXpn1.fldRegs[0].origin);

  osSyncPrintf("\nDisplay List Length %d\t\t\tClip Ratio %d \n", 
	     DisplayListLength, ClipRatio);      

  osSyncPrintf("Controller Mode %d\tGlobal Transforms %3s \tTexture %3s\n", 
	     ControllerMode,
	     UseGlobalTransforms ? "on" : "off",
	     UseTextureMode ? "on" : "off");
}


static void PrintController0Instructions(void)
{
  osSyncPrintf("----------------------------------------------------------  \n");
  osSyncPrintf("Up Pad       -> blockwidths     ++                   \n");
  osSyncPrintf("Down Pad     -> blockwidths     --                   \n");
  osSyncPrintf("Right Pad    -> planesize       ++                   \n");
  osSyncPrintf("Left Pad     -> planesize       --                   \n");
  osSyncPrintf("A Button     -> toggle AA                            \n");
  osSyncPrintf("B Button     -> toggle ZB                            \n");
  osSyncPrintf("Arrow Right  -> Cube Divisions  ++                   \n");
  osSyncPrintf("Arrow Left   -> Cube Divisions  --                   \n");
  osSyncPrintf("Arrow Up     -> Plane Divisions ++                   \n");
  osSyncPrintf("Arrow Down   -> Plane Divisions --                   \n");
  osSyncPrintf("Right        -> Cubes Per Axis  ++                   \n");
  osSyncPrintf("Left         -> Cubes Per Axis  --                   \n");
  osSyncPrintf("G button     -> toggle mode (0,1,2)                  \n");
  osSyncPrintf("START button -> reset parameters                     \n");
}

static void PrintController1Instructions(void)
{
  osSyncPrintf("----------------------------------------------------------  \n");

  osSyncPrintf("stick        -> translate objects (%s)               \n",
	     UseGlobalTransforms ? "Enabled" : "Disabled");

  osSyncPrintf("Up Pad       -> move eye in                          \n");
  osSyncPrintf("Down Pad     -> move eye out                         \n");
  osSyncPrintf("A Button     -> toggle global transformations        \n");
  osSyncPrintf("B Button     -> toggle texture                       \n");

  osSyncPrintf("Arrow Right  -> positive rotation about Y axis (%s)  \n",
	     UseGlobalTransforms ? "Enabled" : "Disabled");

  osSyncPrintf("Arrow Left   -> negative rotation about Y axis (%s)  \n",
	     UseGlobalTransforms ? "Enabled" : "Disabled");

  osSyncPrintf("Arrow Up     -> positive rotation about X axis (%s)  \n",
	     UseGlobalTransforms ? "Enabled" : "Disabled");

  osSyncPrintf("Arrow Down   -> negative rotation about X axis (%s)  \n",
	     UseGlobalTransforms ? "Enabled" : "Disabled");

  osSyncPrintf("Right        -> clip ratio ++                        \n");
  osSyncPrintf("Left         -> clip ratio --                        \n");
  osSyncPrintf("G button     -> toggle mode (0,1,2)                  \n");
  osSyncPrintf("START button -> reset parameters                     \n");
}

static void PrintController2Instructions(void)
{
  osSyncPrintf("----------------------------------------------------------  \n");

  osSyncPrintf("Up           -> toggle VI mode (Lpn1 and Xpn1)       \n");
  osSyncPrintf("Right        -> Xpn1 screen width +4                 \n");
  osSyncPrintf("Left         -> Xpn1 screen width -4                 \n");
  osSyncPrintf("G button     -> toggle mode (0,1,2)                  \n");
  osSyncPrintf("START button -> reset parameters                     \n");
}

static void PrintStats(int DisplayListLength)
{
  osSyncPrintf("%c%c%c%c%c%c\n", 27, 91, 72, 27, 91, 74);

  PrintStatNumbers(DisplayListLength);
      
  if (ControllerMode == 0)
    PrintController0Instructions();
  else if (ControllerMode == 1)
    PrintController1Instructions();
  else 
    PrintController2Instructions();

  ControllerInput = 0;
}

#endif

static void doPoly(void *arg)
{
  /* Main game loop */
  
  ActiveController = initControllers();

  while (1) 
    {
      int DisplayListLength;

      osContStartReadData(&controllerMsgQ);
      
      ReadController();

      UpdateViMode();

      if (CreateNewCubes)
	{
	  CreateSubCubes();
	  CreateNewCubes = 0;
	}

/*
      if (CreateNewPlanes)
	{
	  CreateSubPlanes();
	  CreateNewPlanes = 0;
	}
*/


      InitDisplayLists(1);

      /* create/send objects */
      gtlistp->obj.gstatep = ggsp;
      gtlistp->obj.statep = &dpInitClearObj;
      gtlistp->obj.vtxp = (Vtx *) NULL;
      gtlistp->obj.trip = (gtTriN *) NULL;
      gtlistp++;

      doPolyFuncs(); 

      CleanupAndSendDisplayList();	

      DisplayListLength = glistp - dynamicp->glist;

      TimePerFrame = 1000.0 * (float) (t2 - t1) / ((OSTime) (TicksPerSec));
 
      /* Now write out timer bar */

      InitDisplayLists(0);
      WriteTimerBar();
      CleanupAndSendDisplayList();		

      if (ControllerInput)
#ifdef DEBUG	
	PrintStats(DisplayListLength);
#else
        ;
#endif
      
      SwapViBuffer();
    }
}

static void ComputeClockSpeed(void)
{
  u32 count0, count1;

  /* wait for a few */
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);

  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  count0 = osGetCount();
  osRecvMesg(&retraceMessageQ, 0, OS_MESG_BLOCK);
  count1 = osGetCount();

  TicksPerSec = ((osTvType == 0) ? 50.0 : 60.0) * (count1 - count0);
}


static void main(void *arg)
{
  tlistp = &tlist;
  dynamicp = &dynamic;
  cfb_ptrs[0] = cfb_16_a; 
  cfb_ptrs[1] = cfb_16_b; 

  CreateMessageQueues();
  InitCubeRotations();

  ComputeClockSpeed();

  doPoly(arg);
}
