/*
 * [CCBL]
 *
 * model_out.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "graphics.h"
#include "mysys.h"
#include "mdl.h"
#include "model_out.h"
#include "rcp_reg.h"
#include "cam.h"
#include "pad.h"
#include "light.h"
#include "model_load.h"
#include "texture.h"
#include "bg_model.h"
#include "window_out.h"


int cvg_view_f = 0;

static Vp mvp = {
  SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,
  SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,
};

/* initialize the RSP state: */
static Gfx rsp_first_dl[] = {
  gsSPViewport(&mvp),
  gsSPClearGeometryMode(G_SHADE |
			G_SHADING_SMOOTH |
			G_CULL_BOTH |
			G_FOG |
			G_LIGHTING |
			G_TEXTURE_GEN |
			G_TEXTURE_GEN_LINEAR |
			G_LOD),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};

/* initialize the RDP state: */
static Gfx rdp_first_dl[] = {
  gsDPPipeSync(),
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPPipelineMode(G_PM_1PRIMITIVE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_NONE),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTexturePersp(G_TP_PERSP),
  gsDPSetTextureFilter(G_TF_BILERP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetCombineKey(G_CK_NONE),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetColorDither(G_CD_DISABLE),
  gsDPPipeSync(),
  gsSPEndDisplayList(),
};

#define	MDL_gDPLoadMultiBlock(pkt, timg, tmem, rtile, fmt, siz, width, \
		height, pal, cms, cmt, masks, maskt, shifts, shiftt)	\
{									\
	gDPSetTextureImage(pkt, fmt, _lblk[siz], 1, timg);	\
	gDPSetTile(pkt, fmt, _lblk[siz], 0, tmem, G_TX_LOADTILE, 0,\
		cmt, maskt, shiftt, cms, masks, shifts);		\
	gDPLoadSync(pkt);						\
	gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, 				\
		(((width)*(height) + _incr[siz]) >> _lsft[siz])-1,	\
		CALC_DXT(width, _byts[siz])); 				\
	gDPPipeSync(pkt);						\
	gDPSetTile(pkt, fmt, siz, (((width) * _lbyt[siz])+7)>>3,	\
		tmem, rtile, pal, cmt,					\
		maskt, shiftt, cms, masks, shifts);			\
	gDPSetTileSize(pkt, rtile, 0, 0,				\
		((width)-1) << G_TEXTURE_IMAGE_FRAC,			\
		((height)-1) << G_TEXTURE_IMAGE_FRAC)			\
	gDPSetTile(pkt, fmt, siz, (((width) * _lbyt[siz])+7)>>3,	\
		tmem,(rtile+1), pal, cmt,				\
		maskt, shiftt, cms, masks, shifts);			\
	gDPSetTileSize(pkt,(rtile+1), 0, 0,				\
		((width)-1) << G_TEXTURE_IMAGE_FRAC,			\
		((height)-1) << G_TEXTURE_IMAGE_FRAC)			\
}

static u32 _lblk[] = {
  G_IM_SIZ_4b_LOAD_BLOCK,
  G_IM_SIZ_8b_LOAD_BLOCK,
  G_IM_SIZ_16b_LOAD_BLOCK,
  G_IM_SIZ_32b_LOAD_BLOCK
};
static u32 _incr[] = {
  G_IM_SIZ_4b_INCR,
  G_IM_SIZ_8b_INCR,
  G_IM_SIZ_16b_INCR,
  G_IM_SIZ_32b_INCR
};
static u32 _lbyt[] = {
  G_IM_SIZ_4b_LINE_BYTES,
  G_IM_SIZ_8b_LINE_BYTES,
  G_IM_SIZ_16b_LINE_BYTES,
  G_IM_SIZ_32b_LINE_BYTES
};
static u32 _byts[] = {
  G_IM_SIZ_4b_BYTES,
  G_IM_SIZ_8b_BYTES,
  G_IM_SIZ_16b_BYTES,
  G_IM_SIZ_32b_BYTES
};
static u32 _lsft[] = {
  G_IM_SIZ_4b_SHIFT,
  G_IM_SIZ_8b_SHIFT,
  G_IM_SIZ_16b_SHIFT,
  G_IM_SIZ_32b_SHIFT
};

#define MDL_gSPLightColor(pkt,n,col) \
{ \
    gMoveWd(pkt, G_MW_LIGHTCOL,(_mwo_a[n]),col); \
    gMoveWd(pkt, G_MW_LIGHTCOL,(_mwo_b[n]),col); \
}

static u32 _mwo_a[] = {
  G_MWO_aLIGHT_1,
  G_MWO_aLIGHT_2,
  G_MWO_aLIGHT_3,
  G_MWO_aLIGHT_4,
  G_MWO_aLIGHT_5,
  G_MWO_aLIGHT_6,
  G_MWO_aLIGHT_7,
  G_MWO_aLIGHT_8,
};
static u32 _mwo_b[] = {
  G_MWO_bLIGHT_1,
  G_MWO_bLIGHT_2,
  G_MWO_bLIGHT_3,
  G_MWO_bLIGHT_4,
  G_MWO_bLIGHT_5,
  G_MWO_bLIGHT_6,
  G_MWO_bLIGHT_7,
  G_MWO_bLIGHT_8,
};

void
model_out(void )
{
  Dynamic *dyp = &dynamic[setup_frame_no];
  int i;
  int use_mdl;
  MDL_TEX *tx;

  NDR_SHAPE *shape_p;
  NDR_RESINFO *ndr_p;
  NDR_RESINFO *bg_p;
  
  use_mdl = makeModelNoVal();
  load_model_data(use_mdl);
  ndr_p = *ndrs;

  /* VI Specail Feature */
  osViSetSpecialFeatures(makeVSFVal());
  /*---------------------------------------------------------*/
  /* Set RSP segment register. */
  gSPSegment(glistp++, 0, 0x0);  /* For CPU virtual address */
  /* Clear frame buffer. */
  gfxClearCfb(makeBgColorVal());
  /*
   * Register RDP state initialization Gfx
   */
  gSPDisplayList(glistp++, rdp_first_dl);
  /*
   * Register RDP state initialization Gfx 
   */
  gSPDisplayList(glistp++, rsp_first_dl);
  /* --- Camera settings ----------------------------------- */
  makeCam(dyp);			/* Set camera. */
  /* Build matrix. */
  gSPMatrix(glistp++,
	    &dyp->projection,
	    G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
  gSPMatrix(glistp++,
	    &dyp->viewing,
	    G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);
  gSPMatrix(glistp++,
	    &dyp->modeling,
	    G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
  
  /*  -- BG MODEL display --------------  */
  bg_p = bg_models[getBgModelNoVal()];
  if(bg_p != NULL){
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++,G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPSetGeometryMode(glistp++,G_ZBUFFER);
    for(i = 0;i < bg_p->nshape;i++){
      shape_p = bg_p->shape[i];
      gSPSegment(glistp++, shape_p->vtxsegno,shape_p->vtx);
      gSPDisplayList(glistp++, shape_p->gfx);
    }
    gDPPipeSync(glistp++);
    gSPClearGeometryMode(glistp++,G_SHADE |
			 G_SHADING_SMOOTH |
			 G_CULL_BOTH |
			 G_FOG |
			 G_LIGHTING |
			 G_TEXTURE_GEN |
			 G_TEXTURE_GEN_LINEAR |
			 G_LOD);
  }
  /* ---RDP settings  ----------------------------------- */
  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,makeCycleTypeVal(&rcp_regs));
  /* CC processing */
  gDPSetCombine(glistp++,
		makeCCMUX1Val(&rcp_regs),
		makeCCMUX2Val(&rcp_regs));
  gDPSetPrimColor(glistp++,
		getPrimColVal(PRIM_COL_M),getPrimColVal(PRIM_COL_L),
		getPrimColVal(PRIM_COL_R),getPrimColVal(PRIM_COL_G),
		getPrimColVal(PRIM_COL_B),getPrimColVal(PRIM_COL_A));
  gDPSetEnvColor(glistp++,
		getEnvColVal(ENV_COL_R),getEnvColVal(ENV_COL_G),
		getEnvColVal(ENV_COL_B),getEnvColVal(ENV_COL_A));

  /* Blender processing */
  gSPSetOtherMode(glistp++,
		  G_SETOTHERMODE_L, G_MDSFT_RENDERMODE,29,
		  makeRMVal(&rcp_regs)); /* RenderMode set by OtherMode.*/
  gDPSetBlendColor(glistp++,
		getBlendColVal(BLEND_COL_R),getBlendColVal(BLEND_COL_G),
		getBlendColVal(BLEND_COL_B),getBlendColVal(BLEND_COL_A));
  gDPSetFogColor(glistp++,
		getFogColVal(FOG_COL_R),getFogColVal(FOG_COL_G),
		getFogColVal(FOG_COL_B),getFogColVal(FOG_COL_A));
  gDPSetColorDither(glistp++,makeColorDitherVal());
  gDPSetAlphaDither(glistp++,makeAlphaDitherVal());
  gDPSetAlphaCompare(glistp++,makeAlphaCompareVal());

  /* --- RSP state settings ------------------------------- */
  gSPSetGeometryMode(glistp++,makeGeometryModeVal(&rcp_regs));
  gSPFogPosition(glistp++,
		 makeFogPositionVal(FOG_POS_MIN_L),	
		 makeFogPositionVal(FOG_POS_MAX_L));
  if(getGeometryModeVal(REFLECT_ENABLE))
    gSPLookAt(glistp++,&dyp->lat); /* Set reflection LookAt */
  /* --- Texture loading --------------------------- */
  /* Enable texture selection. */
  tx = &textures[makeTextureNoVal()];
  if(tx->w+tx->h){
    MDL_gDPLoadMultiBlock( glistp++,
			   tx->img, 0, 0,
			   tx->fmt, tx->size,tx->w,tx->h, 0,
			   0, 0, 5, 5, 0, 0 );
    if(getGeometryModeVal(REFLECT_ENABLE)){
      /* When reflection mapping used */
      gSPTexture(glistp++,(32<<6),(32 <<6), 0, G_TX_RENDERTILE, G_ON);
    }else{
      gSPTexture(glistp++,0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
  }else{
    gDPLoadSync(glistp++);
    gSPDisplayList(glistp++, tx->img);
    gDPPipeSync(glistp++);
    gDPSetTextureLOD(glistp++,G_TL_LOD);

    if(getGeometryModeVal(REFLECT_ENABLE)){
      /* When reflection mapping used */
      gSPTexture(glistp++,(32<<6),(32 <<6), 0, G_TX_RENDERTILE, G_ON);
    }else{
      gSPTexture(glistp++,0x8000, 0x8000, 5, G_TX_RENDERTILE, G_ON);
    }
  }
  /* Tex1 test code -- start */
#if 0
  tx = &textures[0];
  MDL_gDPLoadMultiBlock( glistp++,
			 tx->img, 0, 1,
			 tx->fmt, tx->size,tx->w,tx->h, 0,
			 0, 0, 5, 5, 0, 0 );
  /* Tex1 test code -- end */
#endif
  gDPSetTextureFilter(glistp++,makeTexFiltVal());
  /* --- Light settings ----------------------------------- */
  orbiter_light_move();
  { /* gSPSetLight() */
    Lights7 *l7;
    int i;
    l7 = make_ccbl_light(0 /*setup_frame_no*/);
    gSPNumLights(glistp++,NUMLIGHTS_7);
    for(i = 0;i < NUMLIGHTS_7;i++)
          gSPLight(glistp++,&l7->l[i],i+1);
    gSPLight(glistp++,&l7->a,8);
  }
  /* Light color settings */
  for(i = 0;i < 8;i++){
    MDL_gSPLightColor(glistp++,i,
		      makeLightColorVal(i*LC_LEN));
  }
  /* --- Geometry registration ------------------------------ */
  for(i = 0;i < ndr_p->nshape;i++){
    shape_p = ndr_p->shape[i];
    gSPSegment(glistp++, shape_p->vtxsegno,shape_p->vtx);
    gSPDisplayList(glistp++, shape_p->gfx);
  }
  /* --- cvg visualization ------------------------------------- */
  if(Mpad[1].trigger & PAD_RT) 
    cvg_view_f ^= 1;		/* Set this here. */
  if(cvg_view_f){
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++,G_CYC_1CYCLE);
    gDPSetBlendColor(glistp++,255,255,255,255);
    gDPSetPrimDepth(glistp++,0xffff,0xffff);
    gDPSetDepthSource(glistp++,G_ZS_PRIM);
    gDPSetRenderMode(glistp++,G_RM_VISCVG,G_RM_VISCVG2);
    gDPSetAlphaCompare(glistp++,G_AC_NONE);
    gDPSetColorDither(glistp++,G_CD_DISABLE);
    gDPFillRectangle(glistp++,0,0,SCREEN_WD-1,SCREEN_HT-1);
  }
  /* Display menu window. */
  glistp = window_disp(glistp);

  /* --- Terminate building of display list -------------------- */
  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);
}

extern char _modelsSegmentRomStart[],_modelsSegmentRomEnd[];
extern char _modelsSegmentDataStart[],_modelsSegmentDataEnd[];

void
load_modelseg(void)
{
  nuPiReadRom((u32)_modelsSegmentRomStart,
	      _modelsSegmentDataStart,
	      _modelsSegmentRomEnd-_modelsSegmentRomStart);
#if 0
  osSyncPrintf("Model START:%x\nModel END:%x\nModel Length:%x\n",
	       _modelsSegmentDataStart,
	       _modelsSegmentDataEnd,
	       _modelsSegmentRomEnd-_modelsSegmentRomStart);
#endif
}


