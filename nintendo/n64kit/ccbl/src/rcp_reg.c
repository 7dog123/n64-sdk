/*
 * [CCBL]
 *
 * rcp_reg.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */

/* !!! This program relies greatly on the F3DEX gbi.h file !!! */

#include "common_include.h"
#include "rcp_reg.h"
#include <PR/mbi.h>
#include "window.h"
#include "pad.h"
#include <malloc.h>
#include "model_load.h"
#include "texture.h"
#include "bg_model.h"

/* startup default parameter */
static const struct CYCLE_TYPE_s d_cycle = {RDP_1_CYCLE};

static const struct GEO_MODE_s d_geomode = {
  RCP_ON,  /* G_SHADE */
  RCP_OFF, /* G_LIGHTING */
  RCP_OFF, /* G_SHADING_SMOOTH*/
  RCP_ON,  /* G_ZBUFFER */
  RCP_OFF, /* G_TEXTURE_GEN */
  RCP_OFF, /* G_TEXTURE_GEN_LINEAR */
  RCP_OFF, /* G_CULL_FRONT */
  RCP_ON,  /* G_CULL_BACK */
  RCP_OFF, /* G_FOG */
  RCP_OFF, /* Normally G_LOD but that has no significance here, so used as reflection flag. */
};

static const struct CC_REG_s d_ccac = {
  /* cycle 1*/
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_SHADE /*PRIMITIVE*/,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE, /*PRIMITIVE*/
  /* cycle2 */
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_COMBINED, /*PRIMITIVE*/
  /* macro */
  1,0,
  /* touch */
  0,0
};


static struct RENDER_MODE_s d_rendermode = { /* G_RM_AA_ZB_OPA_SURF */
  RCP_ON,   /* AA_EN */
  RCP_ON,   /* Z_CMP */
  RCP_ON,   /* Z_UPD */
  RCP_ON,   /* IM_RD */
  RCP_OFF,  /* CLR_ON_CVG */
  RCP_OFF,  /* CVG_X_ALPHA */
  RCP_ON,   /* ALPHA_CVG_SEL */
  RCP_OFF,  /* FORCE_BL */
  /* cvg */
  BL_CVG_DST_CLAMP,
  /* zmode*/
  BL_ZMODE_OPA,
  /* mux cycle1 */
  G_BL_CLR_IN,
  G_BL_A_IN,
  G_BL_CLR_MEM,
  G_BL_A_MEM,
  /* mux cycle2 */
  G_BL_CLR_IN,
  G_BL_A_IN,
  G_BL_CLR_MEM,
  G_BL_A_MEM,
  /* cd ad ac */
  0,0,0,
  /* macro */
  0,0,
  /* touch */
  0,0
};

PRIM_COL d_primcol = {
  128,128,128,128,128,128};

ENV_COL d_envcol = {
  128,128,128,128 };

BLEND_COL d_blendcol = {
  128,128,128,128 };

FOG_COL d_fogcol = {
  128,128,128,128 };

COLOR_DITHER d_coldith = {CD_MAGICSQ};
ALPHA_DITHER d_alpdith = {AD_NOTPATTERN};
ALPHA_COMPARE d_alpcmp = {AC_NONE};

LIGHT_COL d_lightcolor = {
  0x80,0x00,0x00,		/* Front */
  0x00,0x00,0x00,		/* Top */
  0x00,0x00,0x00,		/* Right */
  0x00,0x00,0x00,		/* Bottom */
  0x00,0x00,0x00,		/* Left */
  0x00,0x00,0x00,		/* Left Upper */
  0xff,0xff,0xff,		/* orbiter */
  0x50,0x50,0x50,		/* Ambient */
};

VSF d_vispecialfeature = {
  RCP_ON,			/* GAMMA */
  RCP_OFF,			/* GAMMA DITHER*/
  RCP_OFF,			/* DIVOT */
  RCP_ON,			/* DITHER FILTER */
};

FOG_POS d_fogposition = {
  0,				/* Min Low */
  0,				/* Min high */
  1000 & 255,			/* Max Low */
  1000 >> 8			/* Max high */
};

TEX_FILT d_texturefilter = {
  TEX_FILT_BILERP
};
/* ----------------------------------------------*/

/* Master data */
RCP_MODULE rcp_regs;		/* Data table */
static CYCLE_TYPE cycle;
static GEO_MODE geomode;
static CC_REG combinemode;
static RENDER_MODE rendermode;
static PRIM_COL primcol;
static ENV_COL envcol;
static BLEND_COL blendcol;
static FOG_COL fogcol;
static COLOR_DITHER coldith;
static ALPHA_DITHER alpdith;
static ALPHA_COMPARE alpcmp;
static LIGHT_COL lightcolor;
static VSF vispecialfeature;
static FOG_POS fogposition;
static TEX_FILT texturefilter;

/* misc menu */
static int bg_color;
static int model_no;
static int texture_no;
static int bgmodel_no;

/* ---- local uty ----- */
void __init_print_uty(void);
void __start_print_uty(void);
PRNT *__end_print_uty(void);
void __put_tab(int c);
void __put_lf(void);
void __put_gSP(int mode);
void __put_gDP(int mode);
void __put_glist(int mode);
void __put_glist_1(int mode);
void __put_end(int mode);
void __put_string(const char *str);

static char nul_str[] = ""; 
static char *p_buf;

/* ------------------------- */

void
init_rcpreg(RCP_MODULE *rcp)
{
  rcp->cycl = &cycle;
  rcp->gm = &geomode;
  rcp->ccac = &combinemode;
  rcp->rm = &rendermode;
  rcp->prm = &primcol;
  rcp->env = &envcol;
  rcp->blnd = &blendcol;
  rcp->fog = &fogcol;
  rcp->cd = &coldith;
  rcp->ad = &alpdith;
  rcp->ac = &alpcmp;
  rcp->lc = &lightcolor;
  rcp->vsf = &vispecialfeature;
  rcp->fp = &fogposition;
  rcp->tf = &texturefilter;
  set_rcp_default(rcp);
 
  p_buf = malloc(256);
  __init_print_uty();
  //  load_model_data(MDL_SPHERE);
}

void
set_rcp_default(RCP_MODULE *rcp)
{
  /* Set default values. */
  bcopy(&d_cycle,rcp->cycl,sizeof(CYCLE_TYPE));
  bcopy(&d_geomode,rcp->gm,sizeof(GEO_MODE));
  bcopy(&d_ccac,rcp->ccac,sizeof(CC_REG));
  bcopy(&d_rendermode,rcp->rm,sizeof(RENDER_MODE));
  bcopy(&d_primcol,rcp->prm,sizeof(PRIM_COL));
  bcopy(&d_envcol,rcp->env,sizeof(ENV_COL));
  bcopy(&d_blendcol,rcp->blnd,sizeof(BLEND_COL));
  bcopy(&d_fogcol,rcp->fog,sizeof(FOG_COL));
  bcopy(&d_coldith,rcp->cd,sizeof(COLOR_DITHER));
  bcopy(&d_alpdith,rcp->ad,sizeof(ALPHA_DITHER));
  bcopy(&d_alpcmp,rcp->ac,sizeof(ALPHA_COMPARE));
  bcopy(&d_lightcolor,rcp->lc,sizeof(LIGHT_COL));
  bcopy(&d_vispecialfeature,rcp->vsf,sizeof(VSF));
  bcopy(&d_fogposition,rcp->fp,sizeof(FOG_POS));
  bcopy(&d_texturefilter,rcp->tf,sizeof(TEX_FILT));
  bg_color = BG_COLOR_BLUE;
  model_no = MDL_CUBE;
  texture_no = TX_RGBA16_TREE;
  bgmodel_no = BG_MODEL_NULL;
  user_model_init();
}


/* Geometry Mode --------------------------------------------*/

void
toggleGeometryModeVal(int reg)
{

  rcp_regs.gm->gm_regs[reg] = 
    (rcp_regs.gm->gm_regs[reg] == RCP_OFF)? RCP_ON:RCP_OFF; 
}

int
getGeometryModeVal(int reg)
{
  return(rcp_regs.gm->gm_regs[reg]);
}


/* Create parameters for gDPSetGeometryMode(). */
u32
makeGeometryModeVal(RCP_MODULE *rcp_p)
{
  static u32 geo_tmpl[GEO_MODE_LEN] = {
    G_SHADE,
    G_LIGHTING,
    G_SHADING_SMOOTH,
    G_ZBUFFER,
    G_TEXTURE_GEN,
    G_TEXTURE_GEN_LINEAR,
    G_CULL_FRONT,
    G_CULL_BACK,
    G_FOG,
    0		/* G_LOD invalid. */
  };

  int i;
  u32 rslt;

  for(i = 0,rslt=0;i < GEO_MODE_LEN;i++){
    rslt |= (rcp_p->gm->gm_regs[i])?geo_tmpl[i]:0;
  }
  return rslt;
}
/* GoemetryMode console output */
void
printGeometryModeVal(int mode)
{ /* mode 0:dynamic, 1:static */
  int i,pcnt;
  u8 *gmp;
  static String geostr[GEO_MODE_LEN-1] = {
    "G_SHADE",
    "G_LIGHTING",
    "G_SHADING_SMOOTH",
    "G_ZBUFFER",
    "G_TEXTURE_GEN",
    "G_TEXTURE_GEN_LINEAR",
    "G_CULL_FRONT",
    "G_CULL_BACK",
    "G_FOG", /*"G_LOD"*/};

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetGeometryMode -- */");
  __put_lf();
  __put_tab(4);
  __put_gSP(mode);
  __put_string("SetGeometryMode");
  __put_glist(mode);
  for(i = 0,pcnt=0,gmp=&rcp_regs.gm->gm_regs[0];i < GEO_MODE_LEN-1;i++,gmp++){
    if(*gmp == RCP_ON){
      __put_string((pcnt)?"| ":"");
      sprintf(p_buf,"%s ",geostr[i]);
      __put_string(p_buf);
      pcnt++;
    }
  }
  if(pcnt==0) __put_string("0 ");
  __put_end(mode);
}


/* Cycle Type --------------------------------------------*/
#if 0
void
toggleCycleModeVal(void)
{

  rcp_regs.cycl->cycleType = 
    ( rcp_regs.cycl->cycleType == RDP_1_CYCLE)?RDP_2_CYCLE:RDP_1_CYCLE;

}
#endif
void
setCycleModeVal(int ctval)
{
  rcp_regs.cycl->cycleType = ctval;

}


int
getCycleModeVal(void)
{
  return(rcp_regs.cycl->cycleType);
}


/* Create parameters for gDPSetCycletype(). */
u32
makeCycleTypeVal(RCP_MODULE *rcp_p)
{
  /* G_CYC_COPY and G_CYC_FILL not handled. */
  return((rcp_p->cycl->cycleType == RDP_1_CYCLE)?
	 G_CYC_1CYCLE : G_CYC_2CYCLE);
}

void
printCycleTypeVal(int mode)
{
  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetCycleType -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetCycleType");
  __put_glist(mode);
  sprintf(p_buf,"%s ",(rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
	    "G_CYC_1CYCLE":"G_CYC_2CYCLE");
  __put_string(p_buf);
  __put_end(mode);
}

/* Combine Mode --------------------------------------------*/

int
getCCACVal(int cycl,int regno)
{
  u8 *ccp;

  ccp = (cycl)? rcp_regs.ccac->ccac2:rcp_regs.ccac->ccac1;
  return(ccp[regno]);
}

void
setCCACVal(int cycl,int regno,int val)
{
  u8  *ccp;

  ccp = (cycl == RDP_2_CYCLE)? rcp_regs.ccac->ccac2:rcp_regs.ccac->ccac1;
  ccp[regno] = val;
}

/* Create muxs0 for gDPSetCombine(). */
u32
makeCCMUX1Val(RCP_MODULE *rcp_p)
{
  struct CC_REG_s *p = rcp_p->ccac;
  u32 aaa;

  aaa = _SHIFTL(GCCc0w0(p->ccac1[CC_A],p->ccac1[CC_C],
			p->ccac1[AC_A],p->ccac1[AC_C]) |
		((rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
		GCCc1w0(p->ccac1[CC_A],p->ccac1[CC_C]):
		GCCc1w0(p->ccac2[CC_A],p->ccac2[CC_C])),
		0, 24);
  return aaa;
}

/* Create muxs1 for gDPSetCombine(). */
u32
makeCCMUX2Val(RCP_MODULE *rcp_p)
{
  struct CC_REG_s *p = rcp_p->ccac;
  u32 aaa;

  aaa = 
    GCCc0w1(p->ccac1[CC_B],
	    p->ccac1[CC_D],
	    p->ccac1[AC_B],
	    p->ccac1[AC_D]) |
    ((rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
    GCCc1w1(p->ccac1[CC_B],
	    p->ccac1[AC_A],
	    p->ccac1[AC_C],
	    p->ccac1[CC_D],
	    p->ccac1[AC_B],
	    p->ccac1[AC_D]):
    GCCc1w1(p->ccac2[CC_B],
	    p->ccac2[AC_A],
	    p->ccac2[AC_C],
	    p->ccac2[CC_D],
	    p->ccac2[AC_B],
	    p->ccac2[AC_D]));
  return aaa;
}

typedef struct PCM_L_s {
  String str;
  int val;
} PCM_L;

static PCM_L ccA[] = {
  {"COMBINED",G_CCMUX_COMBINED},
  {"TEXEL0",G_CCMUX_TEXEL0},
  {"TEXEL1",G_CCMUX_TEXEL1},
  {"PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE",G_CCMUX_SHADE},
  {"ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"NOISE",G_CCMUX_NOISE},
  {"1",G_CCMUX_1},
  {"0",G_CCMUX_0},
  {NULL,0}
};

static PCM_L ccB[] = {
  {"COMBINED",G_CCMUX_COMBINED},
  {"TEXEL0",G_CCMUX_TEXEL0},
  {"TEXEL1",G_CCMUX_TEXEL1},
  {"PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE",G_CCMUX_SHADE},
  {"ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"CENTER",G_CCMUX_CENTER},
  {"K4",G_CCMUX_K4},
  {"0",G_CCMUX_0},
  {NULL,0}
};

static PCM_L ccC[] = {
  {"COMBINED",G_CCMUX_COMBINED},
  {"TEXEL0",G_CCMUX_TEXEL0},
  {"TEXEL1",G_CCMUX_TEXEL1},
  {"PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE",G_CCMUX_SHADE},
  {"ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"SCALE",G_CCMUX_SCALE},
  {"COMBINED_ALPHA",G_CCMUX_COMBINED_ALPHA},
  {"TEXEL0_ALPHA",G_CCMUX_TEXEL0_ALPHA},
  {"TEXEL1_ALPHA",G_CCMUX_TEXEL1_ALPHA},
  {"PRIMITIVE_ALPHA",G_CCMUX_PRIMITIVE_ALPHA},
  {"SHADE_ALPHA",G_CCMUX_SHADE_ALPHA},
  {"ENV_ALPHA",G_CCMUX_ENV_ALPHA},
  {"LOD_FRACTION",G_CCMUX_LOD_FRACTION},
  {"PRIM_LOD_FRAC",G_CCMUX_PRIM_LOD_FRAC},
  {"K5",G_CCMUX_K5},
  {"0",G_CCMUX_0},
  {NULL,0}
};

static PCM_L ccD[] = {
  {"COMBINED",G_CCMUX_COMBINED},
  {"TEXEL0",G_CCMUX_TEXEL0},
  {"TEXEL1",G_CCMUX_TEXEL1},
  {"PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE",G_CCMUX_SHADE},
  {"ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"1",G_CCMUX_1},
  {"0",G_CCMUX_0},
  {NULL,0}
};
static PCM_L acABD[] = {
  {"COMBINED",G_ACMUX_COMBINED},
  {"TEXEL0",G_ACMUX_TEXEL0},
  {"TEXEL1",G_ACMUX_TEXEL1},
  {"PRIMITIVE",G_ACMUX_PRIMITIVE},
  {"SHADE",G_ACMUX_SHADE},
  {"ENVIRONMENT",G_ACMUX_ENVIRONMENT},
  {"1",G_ACMUX_1},
  {"0",G_ACMUX_0},
  {NULL,0}
};
static PCM_L acC[] = {
  {"TEXEL0",G_ACMUX_TEXEL0},
  {"TEXEL1",G_ACMUX_TEXEL1},
  {"PRIMITIVE",G_ACMUX_PRIMITIVE},
  {"SHADE",G_ACMUX_SHADE},
  {"ENVIRONMENT",G_ACMUX_ENVIRONMENT},
  {"LOD_FRACTION",G_ACMUX_LOD_FRACTION},
  {"PRIM_LOD_FRAC",G_ACMUX_PRIM_LOD_FRAC},
  {"0",G_ACMUX_0},
  {NULL,0}
};

static String unknown = "UNKNOWN";

String
__s_pcm_l(int rno,int ccval)
{
  PCM_L *pp;
  static PCM_L *plt[] = {
    ccA,ccB,ccC,ccD,acABD,acABD,acC,acABD};

  for(pp = plt[rno];pp->str != NULL;pp++){
    if(pp->val == ccval) return pp->str;
  }
  return unknown;
}

void
printCombineModeVal(int mode)
{
  u8 *ccp;
  int c,i;
  static String md_str[] = {
    "DPTEST_G_CC_1",
    "DPTEST_G_CC_2"};

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetCombineMode -- */");
  __put_lf();
  for(c = 0;c < getCycleModeVal()+1;c++){

    __put_string("#define ");
    __put_string(md_str[c]);
    __put_string("    \\");
    __put_lf();
    __put_tab(8);
    ccp = 
      (c ==  0)? &rcp_regs.ccac->ccac1[0]:&rcp_regs.ccac->ccac2[0];
    for(i = 0;i < CC_END;i++,ccp++){
      if(i) __put_string(", ");
      __put_string(__s_pcm_l(i,*ccp));
    }
    __put_lf();
    __put_lf();
  }
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetCombineMode");
  __put_glist(mode);
  __put_string(md_str[0]);
  __put_string(", ");
  __put_string((rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
	       md_str[0]:md_str[1]);
  __put_end(mode);
}


int
getCCACMacroVal(int cycl)
{
  return rcp_regs.ccac->mcro[cycl];
}

void
setCCACMacroVal(int cycl,int mval)
{
  rcp_regs.ccac->mcro[cycl] = mval;
}


void
setMacroCombineModeVal(int cycl)
{
  u8 *m_dt,*cc_dt;
  int mcro;
  
  mcro = getCCACMacroVal(cycl);
  m_dt = (cycl == RDP_1_CYCLE)?
    ccm1_idx[mcro]:ccm2_idx[mcro];
  cc_dt = (cycl == RDP_1_CYCLE)?
    &rcp_regs.ccac->ccac1[0]:&rcp_regs.ccac->ccac2[0];
  bcopy(m_dt,cc_dt,CC_END);
}

void
setCCACTouch(int cycle,int val)
{
  rcp_regs.ccac->touch[cycle] = val;
}

int
getCCACTouch(int cycle)
{
  return rcp_regs.ccac->touch[cycle];

}

/* Render Mode --------------------------------------------*/

int
getRMSwitchVal(int sw_no)
{
  return(rcp_regs.rm->rndr[sw_no]);
}

void
toggleRMSwitchVal(int sw_no)
{
  rcp_regs.rm->rndr[sw_no] ^= 1;
}

int
getRMCvgVal(void)
{
  return(rcp_regs.rm->cvg);
}
void
setRMCvgVal(int val)
{
  rcp_regs.rm->cvg = val & 3;
}

int
getRMZmodeVal(void)
{
  return(rcp_regs.rm->zmode);

}
void
setRMZmodeVal(int val)
{
  rcp_regs.rm->zmode = val & 3;
}



int
getRMMuxVal(int cycle,int regno)
{
  u8 *mux_p;

  mux_p = (cycle == RDP_1_CYCLE)?rcp_regs.rm->mux1:rcp_regs.rm->mux2;
  return mux_p[regno];
}
void
setRMMuxVal(int cycle,int regno,int val)
{
  u8 *mux_p;

  mux_p = (cycle == RDP_1_CYCLE)?rcp_regs.rm->mux1:rcp_regs.rm->mux2;
  mux_p[regno] = val;

}



/* 
 * Normally create gDPSetRenderMode() parameters, but here create parameters
 * that can be used to call gSPSetOtherMode(pkt,G_SETOTHERMODE_L,
 * G_MDSFT_RENDERMODE,29...) directly.
 * 
 * Also necessary to set alphacompare, alphadither, and depthsource. 
 */
u32
makeRMVal(RCP_MODULE *rcp_p)
{
  static u32 rmval[BL_SWITCH_LEN] = {
    /* Provide parameters in this order ! */
    AA_EN,
    Z_CMP,
    Z_UPD,
    IM_RD,
    CLR_ON_CVG,
    CVG_X_ALPHA,
    ALPHA_CVG_SEL,
    FORCE_BL,			/* TEX_EDGE appears unnecessary. */
  };
  static u32 cvgval[BL_CVG_DST_MAX] = {
    CVG_DST_CLAMP,
    CVG_DST_WRAP,
    CVG_DST_FULL,
    CVG_DST_SAVE,
  };
  static u32 zmodeval[BL_ZMODE_MAX] = {
    ZMODE_OPA,
    ZMODE_INTER,
    ZMODE_XLU,
    ZMODE_DEC,
  };

  int i;
  u32 rslt;
  struct RENDER_MODE_s *rmp = rcp_p->rm;

  for(i = 0,rslt = 0;i < BL_SWITCH_LEN;i++){
    rslt |= (rmp->rndr[i])? rmval[i]:0;
  }

  rslt |= (cvgval[rmp->cvg] | zmodeval[rmp->zmode]);

  rslt |= 
    GBL_c1((u32)(rmp->mux1[0] & 3),	/* Mask as a precaution. */
	   (u32)(rmp->mux1[1] & 3),
	   (u32)(rmp->mux1[2] & 3),
	   (u32)(rmp->mux1[3] & 3)) |
    ((rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
     GBL_c2((u32)(rmp->mux1[0] & 3),
	    (u32)(rmp->mux1[1] & 3),
	    (u32)(rmp->mux1[2] & 3),
	    (u32)(rmp->mux1[3] & 3)):
     GBL_c2((u32)(rmp->mux2[0] & 3),
	    (u32)(rmp->mux2[1] & 3),
	    (u32)(rmp->mux2[2] & 3),
	    (u32)(rmp->mux2[3] & 3)));
  return rslt;
}

void
printRenderModeDefine(int mode)
{
  int i,c;
  u8 *rmp;

  static String rmsw_str[] = {
    "AA_EN",
    "Z_CMP",
    "Z_UPD",
    "IM_RD",
    "CLR_ON_CVG",
    "CVG_X_ALPHA",
    "ALPHA_CVG_SEL",
    "FORCE_BL",
  };
  static String rmcvg_str[] = {
    "CVG_DST_CLAMP",
    "CVG_DST_WRAP",
    "CVG_DST_FULL",
    "CVG_DST_SAVE",
  };
  static String rmzmode_str[] = {
    "ZMODE_OPA",
    "ZMODE_INTER",
    "ZMODE_XLU",
    "ZMODE_DEC"
  };

  static String muxpm_str[] = {
    "G_BL_CLR_IN",
    "G_BL_CLR_MEM",
    "G_BL_CLR_BL",
    "G_BL_CLR_FOG",
  };
  static String muxa_str[] = {
    "G_BL_A_IN",
    "G_BL_A_FOG",
    "G_BL_A_SHADE",
    "G_BL_0",
  };
  static String muxb_str[] = {
    "G_BL_1MA",
    "G_BL_A_MEM",
    "G_BL_1",
    "G_BL_0",
  };
  static String *mux_str_p[] = {
    muxpm_str,
    muxa_str,
    muxpm_str,
    muxb_str
  };
  static String rmd_str[] = {
    "DPTEST_RM____1",
    "DPTEST_RM____2"};


  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetRenderMode -- */");
  for(c = 0;c < getCycleModeVal()+1;c++){
    __put_lf();
    __put_string("#define ");
    __put_string(rmd_str[c]);
    __put_string("   \\");
    __put_lf();
    __put_tab(8);
    rmp = &rcp_regs.rm->rndr[0];
    for(i = 0;i < BL_SWITCH_LEN;i++,rmp++){
      if(*rmp == RCP_ON){
	sprintf(p_buf,"%s",rmsw_str[i]);
	__put_string(p_buf);
	__put_string(" | ");
      }
      if(i == 4){
	__put_string("    \\");
	__put_lf();
	__put_tab(8);
      }
    }
    __put_string("    \\");
    __put_lf();
    __put_tab(8);
    sprintf(p_buf,"%s | %s |   \\",
	    rmcvg_str[rcp_regs.rm->cvg],
	    rmzmode_str[rcp_regs.rm->zmode]);
    __put_string(p_buf);
    __put_lf();
    __put_tab(8);
    sprintf(p_buf,"GBL_c%d(",c);
    __put_string(p_buf);
    rmp = (c)?&rcp_regs.rm->mux2[0]:&rcp_regs.rm->mux1[0];
    for(i = 0;i < BL_MUX_LEN;i++,rmp++){
      sprintf(p_buf,"%s%s",(i)?", ":nul_str,*(mux_str_p[i]+(*rmp)) );
      __put_string(p_buf);
    }
    __put_string(")");
    __put_lf();
  }
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetRenderMode");
  __put_glist(mode);
  __put_string(rmd_str[0]);
  __put_string(", ");
  __put_string((rcp_regs.cycl->cycleType == RDP_1_CYCLE)?
	       rmd_str[0]:rmd_str[1]);
  __put_end(mode);
}


int
getRenderModeMacroVal(int cycl)
{
  return rcp_regs.rm->mcro[cycl];
}

void
setRenderModeMacroVal(int cycl,int mval)
{
  rcp_regs.rm->mcro[cycl] = mval;
}


void
setMacroRMVal(int cycl)
{
  RM_MACRO *rmm;
  RENDER_MODE *rmr = rcp_regs.rm;
  u8 *muxp;
  int mcr;

  mcr = getRenderModeMacroVal(cycl);
  rmm = (cycl == RDP_1_CYCLE)?
    &rmm1_idx[mcr]:&rmm2_idx[mcr];
  if(rmm->sw != NULL){
    bcopy(rmm->sw,rmr->rndr,BL_SWITCH_LEN);
    rmr->cvg = rmm->sw[BL_SWITCH_LEN]; 
    rmr->zmode = rmm->sw[BL_SWITCH_LEN+1]; 
  }
  if(rmm->mux != NULL){
    muxp = (cycl == RDP_1_CYCLE)?
      rmr->mux1:rmr->mux2;
    bcopy(rmm->mux,muxp,BL_MUX_LEN);
  }
}

void
setRMTouch(int cycle,int val)
{
  rcp_regs.rm->touch[cycle] = val;
}

int
getRMTouch(int cycle)
{
  return rcp_regs.rm->touch[cycle];
}
/* Primitive color */
int
getPrimColVal(int regno)
{
  return rcp_regs.prm->prim_col[regno];
}

void
setPrimColVal(int regno,int val)
{
  rcp_regs.prm->prim_col[regno] = val;
}

void
printPrimColVal(int mode)
{
  int i;

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetPrimColor -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetPrimColor");
  __put_glist(mode);
  
  for(i = 0;i < PRIM_COL_LEN;i++){
    sprintf(p_buf,"%s%3d",
	    (i)?", ":nul_str,
	    rcp_regs.prm->prim_col[i]);
    __put_string(p_buf);
  }
  __put_end(mode);
}


/* Env color */
int
getEnvColVal(int regno)
{
  return rcp_regs.env->env_col[regno];
}

void
setEnvColVal(int regno,int val)
{
  rcp_regs.env->env_col[regno] = val;
}

void
printEnvColVal(int mode)
{
  int i;

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetEnvColor -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetEnvColor");
  __put_glist(mode);
  
  for(i = 0;i < ENV_COL_LEN;i++){
    sprintf(p_buf,"%s%3d",
	    (i)?", ":nul_str,
	    rcp_regs.env->env_col[i]);
    __put_string(p_buf);
  }
  __put_end(mode);
}

/* Blend color */
int
getBlendColVal(int regno)
{
  return rcp_regs.blnd->blend_col[regno];
}

void
setBlendColVal(int regno,int val)
{
  rcp_regs.blnd->blend_col[regno] = val;
}

void
printBlendColVal(int mode)
{
  int i;

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetBlendColor -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetBlendColor");
  __put_glist(mode);
  
  for(i = 0;i < BLEND_COL_LEN;i++){
    sprintf(p_buf,"%s%3d",
	    (i)?", ":nul_str,
	    rcp_regs.blnd->blend_col[i]);
    __put_string(p_buf);
  }
  __put_end(mode);
}

/* Fog color */
int
getFogColVal(int regno)
{
  return rcp_regs.fog->fog_col[regno];
}

void
setFogColVal(int regno,int val)
{
  rcp_regs.fog->fog_col[regno] = val;
}

void
printFogColVal(int mode)
{
  int i;

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetFogColor -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetFogColor");
  __put_glist(mode);
  
  for(i = 0;i < FOG_COL_LEN;i++){
    sprintf(p_buf,"%s%3d",
	    (i)?", ":nul_str,
	    rcp_regs.fog->fog_col[i]);
    __put_string(p_buf);
  }
  __put_end(mode);
}
/* color dither */
int
getColorDitherVal(void)
{
  return rcp_regs.cd->col_d;
}

void
setColorDitherVal(int val)
{
  rcp_regs.cd->col_d = val;
}

u32
makeColorDitherVal(void)
{
  static u32 cdt[COLOR_DITHER_LEN] = {
    G_CD_MAGICSQ,
    G_CD_BAYER,
    G_CD_NOISE,
    G_CD_DISABLE
  };

  return cdt[getColorDitherVal()];
}

void
printColorDitherVal(int mode)
{
  static String cd_l[COLOR_DITHER_LEN] = {
    "G_CD_MAGICSQ",
    "G_CD_BAYER",
    "G_CD_NOISE",
    "G_CD_DISABLE"
  };

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetColorDither -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetColorDither");
  __put_glist(mode);
  __put_string(cd_l[rcp_regs.cd->col_d]);
  __put_end(mode);

}

/* alpha dither */
int
getAlphaDitherVal(void)
{
  return rcp_regs.ad->alp_d;
}

void
setAlphaDitherVal(int val)
{
  rcp_regs.ad->alp_d = val;
}

u32
makeAlphaDitherVal(void)
{
  static u32 adt[ALPHA_DITHER_LEN] = {
    G_AD_PATTERN,
    G_AD_NOTPATTERN,
    G_AD_NOISE,
    G_AD_DISABLE
  };

  return adt[getAlphaDitherVal()];
}

void
printAlphaDitherVal(int mode)
{
  static String ad_l[ALPHA_DITHER_LEN] = {
    "G_AD_PATTERN",
    "G_AD_NOTPATTERN",
    "G_AD_NOISE",
    "G_AD_DISABLE"
  };

  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetAlphaDither -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetAlphaDither");
  __put_glist(mode);
  __put_string(ad_l[rcp_regs.ad->alp_d]);
  __put_end(mode);

}

/* alpha compare */
int
getAlphaCompareVal(void)
{
  return rcp_regs.ac->alp_c;
}

void
setAlphaCompareVal(int val)
{
  rcp_regs.ac->alp_c = val;
}

u32
makeAlphaCompareVal(void)
{
  static u32 ac_d[ALPHA_COMPARE_LEN] = {
    G_AC_NONE,G_AC_THRESHOLD,G_AC_DITHER};

  return ac_d[getAlphaCompareVal()];
}

void
printAlphaCompareVal(int mode)
{
  static String ac_l[ALPHA_COMPARE_LEN] = {
    "G_AC_NONE",
    "G_AC_THRESHOLD",
    "G_AC_DITHER"
  };
  __put_lf();
  __put_tab(4);
  __put_string("/* -- SetAlphaCompare -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetAlphaCompare");
  __put_glist(mode);
  __put_string(ac_l[rcp_regs.ac->alp_c]);
  __put_end(mode);

}

/* light color */
int
getLightColorVal(int creg)
{
  return rcp_regs.lc->light_col[creg];
}

void
setLightColorVal(int creg,int val)
{
  rcp_regs.lc->light_col[creg] = val;
}


u32
makeLightColorVal(int lno){
  int i;
  u32 rslt;

  for(i = 0,rslt = 0;i < LC_LEN;i++){
    rslt = (rslt << 8) | rcp_regs.lc->light_col[lno+i];
  }
  return (rslt << 8);
}

/* ViSpecialFeature */
void
toggleVSFVal(int rno)
{
  rcp_regs.vsf->vsfs[rno] ^= RCP_ON;
}

int
getVSFVal(int rno)
{
  return rcp_regs.vsf->vsfs[rno];
}


u32
makeVSFVal(void )
{
  int i;
  u32 rslt;
  static u32 vsf_rv[8] = {
    OS_VI_GAMMA_OFF,
    OS_VI_GAMMA_ON,
    OS_VI_GAMMA_DITHER_OFF,
    OS_VI_GAMMA_DITHER_ON,
    OS_VI_DIVOT_OFF,
    OS_VI_DIVOT_ON,
    OS_VI_DITHER_FILTER_OFF,
    OS_VI_DITHER_FILTER_ON,
  };

  rslt = 0;
  for(i = 0;i < VSF_LEN;i++){
    rslt |= vsf_rv[i*2+getVSFVal(i)];
  }
  return rslt;
}


/* FogPosition */
int
getFogPositionVal(int minmax)
{
  return rcp_regs.fp->minmax[minmax+1]*256+
	 rcp_regs.fp->minmax[minmax];
}

void
setFogPositionVal(int minmax,int val)
{
  rcp_regs.fp->minmax[minmax+1] = val / 256;
  rcp_regs.fp->minmax[minmax] = val % 256;
}
  
int
makeFogPositionVal(int minmax)
{
  return getFogPositionVal(minmax);
}

void
printFogPositionVal(int mode)
{

  __put_lf();
  __put_tab(4);
  __put_string("/* -- FogPosition -- */");
  __put_lf();
  __put_tab(4);
  __put_gSP(mode);
  __put_string("FogPosition");
  __put_glist(mode);

  sprintf(p_buf,"%d , %d",
	  makeFogPositionVal(FOG_POS_MIN_L),
	  makeFogPositionVal(FOG_POS_MAX_L));
  __put_string(p_buf);
  __put_end(mode);
}

/* TextureFilter */
int
getTexFiltVal(void )
{
  return rcp_regs.tf->texfilt;
}

void
setTexFiltVal(int no)
{
  rcp_regs.tf->texfilt = no;
}

int
makeTexFiltVal(void)
{
  static int tf_t[] = {
    G_TF_POINT,G_TF_AVERAGE,G_TF_BILERP
  };

  return tf_t[getTexFiltVal()];
}

void
printTexFiltVal(int mode)
{
  static String tf_str[TEX_FILT_LEN] = {
    "G_TF_POINT",
    "G_TF_AVERAGE",
    "G_TF_BILERP"};

  __put_lf();
  __put_tab(4);
  __put_string("/* -- TextureFilter -- */");
  __put_lf();
  __put_tab(4);
  __put_gDP(mode);
  __put_string("SetTextureFilter");
  __put_glist(mode);

  __put_string(tf_str[getTexFiltVal()]);
  __put_end(mode);
}


/* bg color */
int
getBgColorVal(void)
{
  return bg_color;
}

void
setBgColorVal(int colno)
{
  bg_color = colno;
}

int
makeBgColorVal(void)
{
  return getBgColorVal();
}

/* model data */
int
getModelNoVal(void)
{
  return model_no;
}

void
setModelNoVal(int no)
{
  model_no = no;
}

int
makeModelNoVal(void)
{
  return getModelNoVal();
}

/* texture data */

int
getTextureNoVal(void)
{
  return texture_no;
}

void
setTextureNoVal(int texno)
{
  texture_no = texno;
}

int
makeTextureNoVal(void)
{
  return getTextureNoVal();
}

/* BG Model */
int
getBgModelNoVal(void)
{
  return bgmodel_no;
}

void
setBgModelNoVal(int bgno)
{
  bgmodel_no = bgno;
}


/* ====================================================== */
PRNT *
printRCP_REG(int mode)
{
  void __put_pipesync(int mode);
  static String dlmt = "/*========================================*/";

  __start_print_uty();
  __put_string(dlmt);
  __put_lf();
  __put_pipesync(mode);
  printCycleTypeVal(mode);

  printCombineModeVal(mode);
  printPrimColVal(mode);
  printEnvColVal(mode);

  printRenderModeDefine(mode);
  printBlendColVal(mode);
  printFogColVal(mode);
  printColorDitherVal(mode);
  printAlphaDitherVal(mode);
  printAlphaCompareVal(mode);
  printTexFiltVal(mode);

  printGeometryModeVal(mode);
  printFogPositionVal(mode);
  __put_string(dlmt);
  __put_lf();
  __put_lf();
  return __end_print_uty();
}

/* --- PRINT UTY------ */

static PRNT *print_buf;

void
__init_print_uty(void)
{
  print_buf = malloc(sizeof(PRNT));
}

void
__start_print_uty(void)
{
  bzero(print_buf,sizeof(PRNT));
  print_buf->len = 0;
}

PRNT *
__end_print_uty(void)
{
#ifndef DPTEST

  osSyncPrintf("%s",print_buf->dt);

#endif /* !DPTEST */
  return print_buf;
}

void
__put_string(const char *str)
{
  for(;;){
    if(*str == '\0') break;
    print_buf->dt[print_buf->len++] = *str++;
  }

}



void
__put_tab(int c)
{
  for(;c > 0;c--){
    __put_string(" ");
  }
}

void
__put_lf(void)
{
  __put_string("\n");
}

void
__put_gSP(int mode)
{
  sprintf(p_buf,"g%sSP",(mode)?"s":"");
  __put_string(p_buf);
}

void
__put_gDP(int mode)
{
  sprintf(p_buf,"g%sDP",(mode)?"s":"");
  __put_string(p_buf);
}

void
__put_glist(int mode)
{
  sprintf(p_buf,"(%s",(mode)?"":"DPTEST_GP++, ");
  __put_string(p_buf);
}
void
__put_glist_1(int mode)
{
  sprintf(p_buf,"(%s",(mode)?"":"DPTEST_GP++ ");
  __put_string(p_buf);
}

void
__put_end(int mode)
{
  sprintf(p_buf,")%s\n",(mode)?",":";");
  __put_string(p_buf);
}


void
__put_pipesync(int mode)
{
  __put_tab(4);
  __put_gDP(mode);
  __put_string("PipeSync");
  __put_glist_1(mode);
  __put_end(mode);
}


