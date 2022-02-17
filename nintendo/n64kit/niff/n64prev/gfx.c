/*======================================================================*/
/*		NIFFprev						*/
/*		gfx.c							*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/ 3	Set Debug console valid          			*/
/*		Set to reference Process mode, mode.h    		*/
/*  1998/ 6/ 8	Revised position of PerfBar to 8-pixel			*/
/*  1998/ 6/24	Revised position of PerfBar t0 4-pixel    		*/
/*======================================================================*/
#define __GFX_C__

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	Display list manager
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

#include "pack.h"
#include "nusys.h"
#include "mode.h"

/* ===========================================================================
	defines
 =========================================================================== */

/* ===========================================================================
	variables
 =========================================================================== */

extern MODE gMode;

#define MAX_GFXBUF 2

typedef enum{
    GFXSTAT_FREE = 0,
    GFXSTAT_BUILDING,
    GFXSTAT_DRAWING
} GFXSTAT;

typedef struct {
    Gfx gfx[GFXLEN_GLIST];
    Mtx mtx[GFXLEN_MTX];
    Light light[GFXLEN_LIGHT];
    GFXSTAT stat;
} GFXBUF;

static u16 *gfxZBUF;

static GFXBUF gfxbuf[MAX_GFXBUF];
static u32 building_gfxlen;
static Mtx *mtxp;
static Light *lightp;

u32 v_count;

int building_gb;
int drawing_gb;

/* ===========================================================================
	functions
 =========================================================================== */

/* ---------------------------------------------------------------------------
	Frame buffer swap callback
	Note: called from a separate thread
 --------------------------------------------------------------------------- */
void gfxBufferSwap(void *p)
{
    /* Annul GFXBUF */
    gfxbuf[drawing_gb].stat = GFXSTAT_FREE;
    drawing_gb = -1;

    /* Swap frame buggers */
    nuGfxSwapCfb(p);

    nuGfxDisplayOn();
}

/* ----------------------------------------------------------------------------
name:
    gfxInit
synopsis:
    void gfxInit(void);
description:
    gfx driver initialization
parameter:
return:
notes:
 --------------------------------------------------------------------------- */
void gfxInit(void)
{
    int i;

    /* Graphic library initialization */
    nuGfxInit();

    /* Set VI mode */
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAF1]);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF|OS_VI_GAMMA_DITHER_ON|OS_VI_DITHER_FILTER_ON);
    /* Display OFF */
    nuGfxDisplayOff();
    gfxZBUF = (u16*)(NU_GFX_ZBUFFER_ADDR);

    /* Initialize Gfx & Mtx buffers */
    for(i=0; i<MAX_GFXBUF; ++i)
      gfxbuf[i].stat = GFXSTAT_FREE;

    building_gb = -1;
    drawing_gb = -1;
    v_count = 0;
    gMode.perfmon_enable = 1;

    /* Set frame buffer swap call back function */
    nuGfxSwapCfbFuncSet(gfxBufferSwap);
    nuDebConClear(0);
    nuDebConTextPos(0, 0, 0);
    nuDebConCPuts(0, "NIFF");
}

/* ----------------------------------------------------------------------------
name:
    gfxBegin
synopsis:
    Gfx *gfxBegin( void );
description:
    Begin drawing DL creation
parameter:
return:
    Gfx *;
	Display list pointer. If Null, ti shows that the buffer for drawing             couldn't be provided.
notes:
    Sometimes it isn't reservd    , so please process that also.
 --------------------------------------------------------------------------- */
Gfx *gfxBegin( void )
{
    Gfx *gp;
    int i;

    /* Use vacant buffer */
    for(i = 0; i < MAX_GFXBUF; ++i)
      if(gfxbuf[i].stat == GFXSTAT_FREE)
	break;

    if(i<MAX_GFXBUF){

	/* Use buffer */
	gfxbuf[i].stat = GFXSTAT_BUILDING;
	building_gb = i;

	gp = gfxbuf[i].gfx;
	mtxp = gfxbuf[i].mtx;
	lightp = &gfxbuf[i].light[0];

	/* Assign frame buffer, Zbuffer addresses to segments */
	gSPSegment(gp++, PHISICAL_SEGMENT, 0);
	gSPSegment(gp++, CFB_SEGMENT, nuGfxCfb_ptr);
	gSPSegment(gp++, ZBUF_SEGMENT, gfxZBUF);

	return gp;
    }

    return NULL;
}

/* ----------------------------------------------------------------------------
name:
    gfxEnd
synopsis:
    void gfxEnd(Gfx *gfx);
description:
    End drawing DL creation
parameter:
    Gfx *;
	Display list pointer
return:
notes:
    After building two gfx, gDPFullSync() and gSPEndDisplayList().
 --------------------------------------------------------------------------- */
void gfxEnd(Gfx *gfx)
{
    void *vp;
    u32 len;

    gDPFullSync(gfx++);
    gSPEndDisplayList(gfx++);

    vp = gfxbuf[building_gb].gfx;
    building_gfxlen = len = (u32)gfx - (u32)vp;

    osWritebackDCache(vp, len);
#if 0
    osWritebackDCacheAll();
#endif
}

/* ----------------------------------------------------------------------------
name:
    gfxFlush
synopsis:
    void gfxFlush(void);
description:
    Excute drawing task
parameter:
return:
notes:
    Excute display list that is done with building by gfxEnd() right before,
    by making it into RCP task.  Currently, performance meter is displayed on 
    the model display, for debug use.
 --------------------------------------------------------------------------- */
void gfxFlush(void)
{
    int i;

    /* Entry of pending bugger as task */
    if(nuGfxTaskSpool == 0){
	drawing_gb = i = building_gb;
	gfxbuf[i].stat = GFXSTAT_DRAWING;
	if(gMode.perfmon_enable){
	    /* Performance meter exists */
	    nuGfxTaskStart(gfxbuf[i].gfx, building_gfxlen,
	      NU_GFX_UCODE_F3DEX_NON, NU_SC_NOSWAPBUFFER);
	    nuDebTaskPerfBar1( 3, 212, NU_SC_NOSWAPBUFFER );
	}else{
	    /* Only model display */
	    nuGfxTaskStart(gfxbuf[i].gfx, building_gfxlen,
	      NU_GFX_UCODE_F3DEX_NON, NU_SC_NOSWAPBUFFER);
	}
	nuDebConDisp(NU_SC_SWAPBUFFER);
    }else{
	/* If the preceding drawing seems not to be complete, discard it,
	   even with newly created buffers */
	gfxbuf[building_gb].stat = GFXSTAT_FREE;
    }
}

/* ----------------------------------------------------------------------------
name:
    gfxWaitSync
synopsis:
    void gfxWaitSync(void);
description:
    Wait for retrace
parameter:
return:
notes:
 --------------------------------------------------------------------------- */
void gfxWaitSync(void)
{
    /* Wait for retrace */
    nuGfxRetraceWait(1);

    /* ++V counter */
    ++v_count;
}

/* ----------------------------------------------------------------------------
name:
    gfxMatrix
synopsis:
    Gfx *gfxMatrix( Gfx *gp, Mtx *m, u32 flag );
description:
    Operate matrix
parameter:
    Gfx *gp;
	Display list pointer
    Mtx *m;
	Matrix structure for RSP
    u32 flag;
	Set-up flag
return:
notes:
    Argument m is copied and written in Gfx; Mtx, that is a copu destination,
    is prepared as a set of Gfx buffer.  It's maintained, not to be written
    over until drawing is complete.
 --------------------------------------------------------------------------- */
Gfx *gfxMatrix( Gfx *gp, Mtx *m, u32 flag )
{
    memcpy(mtxp, m, sizeof(Mtx));
    gSPMatrix(gp++, OS_K0_TO_PHYSICAL(mtxp), flag);

    mtxp++;

    return gp;
}

/* ---------------------------------------------------------------------------
	Substitution of projection conversion matrix
 --------------------------------------------------------------------------- */
Gfx *gfxPerspective( Gfx *gp, float fovy, float aspect, float near, float far, float scale )
{
    Mtx m;
    u16 perspNorm;

    guPerspective( &m, &perspNorm, fovy, aspect, near, far, scale);
    gSPPerspNormalize(gp++, perspNorm);
    return gfxMatrix( gp, &m, G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
}

/* ---------------------------------------------------------------------------
	Setting the perspective projection matrix with multiplication of input          matrix
---------------------------------------------------------------------------- */
Gfx *gfxMulPerspective( Gfx *gp, float fovy, float aspect, float near, float far, float scale, float mul[4][4] )
{
    Mtx m;

    float mf[4][4];
    float ans[4][4];
    u16 perspNorm;

    guPerspectiveF( mf, &perspNorm, fovy, aspect, near, far, scale );
    guMtxCatF( mul, mf, ans );
    guMtxF2L( ans, &m );
    gSPPerspNormalize( gp++, perspNorm );
    return gfxMatrix( gp, &m, G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH );
}

/* ---------------------------------------------------------------------------
	Substitution of parallel projection matrix
 --------------------------------------------------------------------------- */
Gfx *gfxOrtho( Gfx *gp, float left, float right, float bottom, float top, float near, float far, float scale )
{
    Mtx m;

    guOrtho( &m, left, right, bottom, top, near, far, scale);
    return gfxMatrix( gp, &m, G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
}

/* ---------------------------------------------------------------------------
	Create and substitute model matrix from the three values of viewpoint,          point of attention, and upward
 --------------------------------------------------------------------------- */
Gfx *gfxLookAtReflect( Gfx *gp, s8 *right, s8 *upper)
{
    Light *lkp;
    static s8 _s8_a[]={0,0,0,0};
    static s8 _s8_b[]={0,0x80,0,0};

    lkp = lightp;

    memcpy(&lightp->l.col[0], _s8_a, 4);
    memcpy(&lightp->l.colc[0], _s8_a, 4);
    memcpy(&lightp->l.dir[0], right, 3);
    ++lightp;
    memcpy(&lightp->l.col[0], _s8_b, 4);
    memcpy(&lightp->l.colc[0], _s8_b, 4);
    memcpy(&lightp->l.dir[0], upper, 3);
    ++lightp;
    gSPLookAt(gp++, lkp);

    return gp;
}

/* ---------------------------------------------------------------------------
	Set model matrix overwrite
 --------------------------------------------------------------------------- */
Gfx *gfxLoadMatrix( Gfx *gp, Mtx *m )
{
    return gfxMatrix( gp, m, G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
}

/* ---------------------------------------------------------------------------
	Overlay model matrices
 --------------------------------------------------------------------------- */
Gfx *gfxMultiMatrix( Gfx *gp, Mtx *m )
{
    return gfxMatrix( gp, m, G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
}

/* ---------------------------------------------------------------------------
	Overlay model matrices while pushing one step further
 --------------------------------------------------------------------------- */
Gfx *gfxPushMatrix( Gfx *gp, Mtx *m )
{
    return gfxMatrix( gp, m, G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
}

/* ---------------------------------------------------------------------------
	Pop model matrices one step further
 --------------------------------------------------------------------------- */
Gfx *gfxPopMatrix( Gfx *gp )
{
    gSPPopMatrix(gp++, G_MTX_MODELVIEW);
    return gp;
}

/* ---------------------------------------------------------------------------
	Absorb macro
 --------------------------------------------------------------------------- */
Gfx *ndgSPLightColor(Gfx *gp, int lnum, u32 color)
{
    switch(lnum){
      case 0: {gSPLightColor( gp++, LIGHT_1, color );} break;
      case 1: {gSPLightColor( gp++, LIGHT_2, color );} break;
      case 2: {gSPLightColor( gp++, LIGHT_3, color );} break;
      case 3: {gSPLightColor( gp++, LIGHT_4, color );} break;
      case 4: {gSPLightColor( gp++, LIGHT_5, color );} break;
      case 5: {gSPLightColor( gp++, LIGHT_6, color );} break;
      case 6: {gSPLightColor( gp++, LIGHT_7, color );} break;
      case 7: {gSPLightColor( gp++, LIGHT_8, color );} break;
    }
    return gp;
}

/* ---------------------------------------------------------------------------
	Transmit one write
 --------------------------------------------------------------------------- */
Gfx *gfxSetLight( Gfx *gp, int num, u32 color, s8 *normal )
{
    if(normal){
	/* When normal is specified, make a definition using heap */
	memcpy(&lightp->l.col[0], &color, 3);
	memcpy(&lightp->l.colc[0], &color, 3);
	lightp->l.dir[0] = normal[0];
	lightp->l.dir[1] = normal[1];
	lightp->l.dir[2] = normal[2];
	gSPLight(gp++, lightp++, num);
    }else{
	/* When there is no normal, MODIFY transfer only the color value */
	gp = ndgSPLightColor( gp, num, color );
    }

    return gp;
}

/* ---------------------------------------------------------------------------
	Transfer environment light
 --------------------------------------------------------------------------- */
Gfx *gfxSetAmbient( Gfx *gp, int num, u32 color )
{
    static s8 dummy_normal[]={ 0, 0, 127 };

    return gfxSetLight( gp, num, color, dummy_normal );
}

