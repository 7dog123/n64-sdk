/*
 * [CCBL]
 *
 * graphics.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "graphics.h"

Dynamic dynamic[2];
Gfx gfx_glist[2][GFX_GLIST_LEN];
Gfx *glistp,*glist_top;
static int gfxTaskReq = 0;

int console_f = 0;

void allend_gtask(NUScTask * );

extern void makeScreen(void );

int micro_code = 0;
int setup_frame_no;
static int gfx_draw_stat;


void
gfxSetupFirst(void)
{
  glistp = glist_top = gfx_glist[setup_frame_no]; /* Be sure to do this. */
}


void
gfxClearCfb(int type)
{
  extern u16 bgimg1[],bgimg2[];

  static u16 ccl[] = {
    1,
    0x7bdf,
    0xffff,
    0x3f,
    0xf801,
    0xfc1
  };
  int i;
  static u16 *img[] = {bgimg1,bgimg2};

  /* Clear the Z buffer. */
  gDPSetDepthImage(glistp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetRenderMode(glistp++, G_RM_NOOP, G_RM_NOOP2);
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b,SCREEN_WD,
		   OS_K0_TO_PHYSICAL(nuGfxZBuffer));
  gDPSetFillColor(glistp++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 |
			       GPACK_ZDZ(G_MAXFBZ,0)));
  gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
  gDPPipeSync(glistp++);
   
 /* Clear the frame buffer. */
  gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
		   osVirtualToPhysical(nuGfxCfb_ptr));
  if(type < CLR_IMG0){
    gDPSetFillColor(glistp++,ccl[type] << 16 | ccl[type]);
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
    gDPPipeSync(glistp++);
  }else{
    gDPSetTexturePersp(glistp++,G_TP_NONE);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPSetRenderMode(glistp++, G_RM_NOOP, G_RM_NOOP2);
    for(i = 0;i < 240;i += 1){
      gDPLoadTextureBlock(glistp++,img[type-CLR_IMG0]+i*320,
			  G_IM_FMT_RGBA,
			  G_IM_SIZ_16b,
			  320,1,0,
			  G_TX_WRAP | G_TX_NOMIRROR,
			  G_TX_WRAP | G_TX_NOMIRROR,
			  G_TX_NOMASK, G_TX_NOMASK,
			  G_TX_NOLOD, G_TX_NOLOD);
      gSPTextureRectangle(glistp++,
			  0 << 2,i << 2,
			  320 << 2,i<< 2,
			  G_TX_RENDERTILE,
			  0,0,
			  4 << 10,4 << 10);
    }
    gDPPipeSync(glistp++);
  }
}

/*------------------------------------------------------------------*/

/* --------- */

void
init_gtask(void )
{
  gfxTaskReq = 0;
  setup_frame_no = 0;
  /* Callback registration. */
  nuGfxSwapCfbFuncSet((NUGfxSwapCfbFunc)allend_gtask);
}

/* --------- */

void
start_gtask(int pendingGfx)
{
  /*  Start the RSP task.  When finished, swap the display buffer . . . */
  nuGfxTaskStart(glist_top,
		 (s32)(glistp - glist_top) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX,
		 NU_SC_NOSWAPBUFFER);

#if 0
  nuDebTaskPerfBar0(2,210,NU_SC_SWAPBUFFER);
#else
  nuDebTaskPerfBar1(1,210,NU_SC_SWAPBUFFER);
#endif
}


/* CFB SWAP CALLBACK */
void
allend_gtask(NUScTask *gfxTask)
{
  nuGfxSwapCfb(gfxTask);
  nuGfxDisplayOn();
  gfx_draw_stat = 0;
}


/* --------- */


void
request_gtask(void )
{
  gfx_draw_stat = -1;
  start_gtask(0);
  for(;;){
    nuGfxRetraceWait(1);
    if(gfx_draw_stat == 0) break; /* Wait for write to cfb to end.  */
  }
  setup_frame_no ^= 1;
}



