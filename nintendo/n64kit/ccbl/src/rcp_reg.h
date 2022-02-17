/*
 * [CCBL]
 *
 * rcp_reg.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _RCP_REG_H_
#define _RCP_REG_H_
#include "common_include.h"

enum swval {
  RCP_OFF = 0,
  RCP_ON
};

/*-- RDP Cycle Type --*/
enum cycletype {
  RDP_1_CYCLE = 0,
  RDP_2_CYCLE,
  RDP_COPY_CYCLE,
  RDP_FILL_CYCLE
};

typedef struct CYCLE_TYPE_s {
  u8 cycleType;		/* 0: 1cycle 1:2cycle */
} CYCLE_TYPE;

/*-- Geometry Mode --*/
enum rcpGEO {
  GEO_SHADE = 0,
  GEO_LIGHTING,
  GEO_SHADING_SMOOTH,
  GEO_ZBUFFER,
  GEO_TEXTURE_GEN,
  GEO_TEXTURE_GEN_LINEAR,
  GEO_CULL_FRONT,
  GEO_CULL_BACK,
  GEO_FOG,
  REFLECT_ENABLE,
  GEO_MODE_LEN
};

typedef struct GEO_MODE_s {
  /* geometry mode */
  u8 gm_regs[GEO_MODE_LEN];
    /*Ignore G_TEXTURE_ENABLE G_CLIPING G_LOD */
} GEO_MODE;

/*--- CC AC ---*/
enum ccreg_no {
  CC_A = 0,
  CC_B,
  CC_C,
  CC_D,
  AC_A,
  AC_B,
  AC_C,
  AC_D,
  CC_END
};

typedef struct CC_REG_s {
  /* color combiner */
  u8 ccac1[CC_END];
  u8 ccac2[CC_END];
  u8 mcro[2];
  u8 touch[2];
} CC_REG;


/*-- Primitive Color ---*/
enum prim_col_no {
  PRIM_COL_R = 0,
  PRIM_COL_G,
  PRIM_COL_B,
  PRIM_COL_A,
  PRIM_COL_M,
  PRIM_COL_L,
  PRIM_COL_LEN
};

typedef struct PRIM_COL_s {
    /* primitive color */
  u8 prim_col[PRIM_COL_LEN];
} PRIM_COL;
/* -- Env Color ---*/
enum env_col_no {
  ENV_COL_R = 0,
  ENV_COL_G,
  ENV_COL_B,
  ENV_COL_A,
  ENV_COL_LEN
};

typedef struct ENV_COL_s {
  u8 env_col[ENV_COL_LEN];
} ENV_COL;

/*-- Render Mode ---*/
enum __rm_switch {
  BL_AA_EN = 0,
  BL_Z_CMP,
  BL_Z_UPD,
  BL_IM_RD,
  BL_CLR_ON_CVG,
  BL_CVG_X_ALPHA,
  BL_ALPHA_CVG_SEL,
  BL_FORCE_BL,
  BL_SWITCH_LEN	
  /* The Programming Manual says the BL_TEX_EDGE appears unnecessary. */
};

enum __rm_cvg {
  BL_CVG_DST_CLAMP = 0,
  BL_CVG_DST_WRAP,
  BL_CVG_DST_FULL,
  BL_CVG_DST_SAVE,
  BL_CVG_DST_MAX
};

enum __rm_zmode {
  BL_ZMODE_OPA = 0,
  BL_ZMODE_INTER,
  BL_ZMODE_XLU,
  BL_ZMODE_DEC,
  BL_ZMODE_MAX
};

enum __blmux {
  BL_MUX_P = 0,
  BL_MUX_A,
  BL_MUX_M,
  BL_MUX_B,
  BL_MUX_LEN
};

typedef struct RENDER_MODE_s {
  u8 rndr[BL_SWITCH_LEN];	/* Switches */
  u8 cvg;
  u8 zmode;
  u8 mux1[BL_MUX_LEN];		/* cycle 1 */
  u8 mux2[BL_MUX_LEN];		/* cycle 2 */
  u8 cd;			/* color dither */
  u8 ad;			/* dither alpha */
  u8 ac;			/* alpha compare */
  u8 mcro[2];			/* macro index */
  u8 touch[2];
} RENDER_MODE;

/* -- Blend Color ---*/
enum blend_col_no {
  BLEND_COL_R = 0,
  BLEND_COL_G,
  BLEND_COL_B,
  BLEND_COL_A,
  BLEND_COL_LEN
};

typedef struct BLEND_COL_s {
  u8 blend_col[BLEND_COL_LEN];
} BLEND_COL;

/* -- fog Color ---*/
enum fog_col_no {
  FOG_COL_R = 0,
  FOG_COL_G,
  FOG_COL_B,
  FOG_COL_A,
  FOG_COL_LEN
};

typedef struct FOG_COL_s {
  u8 fog_col[FOG_COL_LEN];
} FOG_COL;

/* color dither */
enum color_dither_no {
  CD_MAGICSQ = 0,
  CD_BAYER,
  CD_NOISE,
  CD_DISABLE,
  COLOR_DITHER_LEN
};
typedef struct COLOR_DITHER_s {
  u8 col_d;
} COLOR_DITHER;

/* alpha dither */
enum alpha_dither_no {
  AD_PATTERN = 0,
  AD_NOTPATTERN,
  AD_NOISE,
  AD_DISABLE,
  ALPHA_DITHER_LEN
};

typedef struct ALPHA_DITHER_s {
  u8 alp_d;
} ALPHA_DITHER;

/* alpha compare */

enum alpha_compare_no {		/* No 1-for-1 correspondence with gbi.h.*/
  AC_NONE = 0,
  AC_THRESHOLD,
  AC_DITHER,
  ALPHA_COMPARE_LEN
};

typedef struct ALPHA_COMPARE_s {
  u8 alp_c;
} ALPHA_COMPARE;


/* Light Color */

enum lc_col_no {
  LC_R = 0,
  LC_G,
  LC_B,
  LC_LEN
};
enum light_col_no {
  DIFFUSE1 = 0,
  DIFFUSE2 = (DIFFUSE1 + LC_LEN),
  DIFFUSE3 = (DIFFUSE2 + LC_LEN),
  DIFFUSE4 = (DIFFUSE3 + LC_LEN),
  DIFFUSE5 = (DIFFUSE4 + LC_LEN),
  DIFFUSE6 = (DIFFUSE5 + LC_LEN),
  DIFFUSE7 = (DIFFUSE6 + LC_LEN),
  AMBIENT = (DIFFUSE7 + LC_LEN),
  LIGHT_COL_LEN = (AMBIENT + LC_LEN)
};
#define LIGHT_COL_NUM (LIGHT_COL_LEN/LC_LEN)

typedef struct LIGHT_COL_s {
  u8 light_col[LIGHT_COL_LEN];
} LIGHT_COL;

/* VI Special Feature */
enum vsf_no {
  VSF_GAMMA = 0,
  VSF_GAMMA_DITHER,
  VSF_DIVOT,
  VSF_DITHER_FILTER,
  VSF_LEN
};

typedef struct VSF_s {
  u8 vsfs[VSF_LEN];
} VSF;

/* Fog Position */

enum fog_pos_no {
  FOG_POS_MIN_L = 0,
  FOG_POS_MIN_H,
  FOG_POS_MAX_L,
  FOG_POS_MAX_H,
  FOG_POS_LEN
};
#define FOG_POS_MAX (FOG_POS_LEN/2)

typedef struct FOG_POS_s {
  u8 minmax[FOG_POS_LEN];
} FOG_POS;

/* Texture Filter */
enum tex_filt_no {
  TEX_FILT_POINT = 0,
  TEX_FILT_AVERAGE,
  TEX_FILT_BILERP,
  TEX_FILT_LEN
};

typedef struct TEX_FILT_s {
  u8 texfilt;
} TEX_FILT;

/* --------- */
typedef struct RCP_MODULE_s {
  CYCLE_TYPE *cycl;
  GEO_MODE *gm;
  CC_REG *ccac;
  PRIM_COL *prm;
  ENV_COL *env;
  RENDER_MODE *rm;
  BLEND_COL *blnd;
  FOG_COL *fog;
  COLOR_DITHER *cd;
  ALPHA_DITHER *ad;
  ALPHA_COMPARE *ac;
  LIGHT_COL *lc;
  VSF *vsf;
  FOG_POS *fp;
  TEX_FILT *tf;
} RCP_MODULE;

typedef struct RM_MACRO_s {
  u8 *sw,*mux;
}  RM_MACRO;


/* misc parameter */
enum bgc_no {
  BG_COLOR_BLACK = 0,
  BG_COLOR_GRAY,
  BG_COLOR_WHITE,
  BG_COLOR_BLUE,
  BG_COLOR_RED,
  BG_COLOR_GREEN,
  BG_COLOR_IMG0,
  BG_COLOR_IMG1,
  BG_COLOR_MAX
};

/* print uty */
typedef struct PRNT_s {
  u32 len;
  char dt[2048];
} PRNT;


/* ------------- */
extern RCP_MODULE rcp_regs;
extern u8 *ccm1_idx[];
extern u8 *ccm2_idx[];
extern RM_MACRO rmm1_idx[];
extern RM_MACRO rmm2_idx[];

/* ------------- */

extern void init_rcpreg(RCP_MODULE *);
extern void set_rcp_default(RCP_MODULE *);

/*---*/
extern u32 makeGeometryModeVal(RCP_MODULE *);
extern void toggleGeometryModeVal(int reg);
extern int getGeometryModeVal(int reg);
extern void printGeometryModeVal(int mode);
/*---*/
extern u32 makeCycleTypeVal(RCP_MODULE *);
/* extern void toggleCycleModeVal(void); */
extern void setCycleModeVal(int ctval);
extern int getCycleModeVal(void);
extern void printCycleTypeVal(int mode);
/*---*/
extern u32 makeCCMUX1Val(RCP_MODULE *);
extern u32 makeCCMUX2Val(RCP_MODULE *);
extern int getCCACVal(int cycl,int regno);
extern void setCCACVal(int cycl,int regno,int val);
extern void printCombineModeVal(int mode);
extern void setMacroCombineModeVal(int cycl);
extern int getCCACMacroVal(int cycl);
extern void setCCACMacroVal(int cycl,int mval);
extern void setCCACTouch(int cycle,int val);
extern int getCCACTouch(int cycle);
/*---*/
extern u32 makeRMVal(RCP_MODULE *);

extern int getRMSwitchVal(int sw_no);
extern void toggleRMSwitchVal(int sw_no);

extern int getRMCvgVal(void);
extern void setRMCvgVal(int val);

extern int getRMZmodeVal(void);
extern void setRMZmodeVal(int val);

extern int getRMMuxVal(int cycle,int regno);
extern void setRMMuxVal(int cycle,int regno,int val);
extern void printRenderModeDefine(int mode);

extern void setMacroRMVal(int cycl);
extern int getRenderModeMacroVal(int cycl);
extern void setRenderModeMacroVal(int cycl,int mval);
extern void setRMTouch(int cycle,int val);
extern int getRMTouch(int cycle);

extern int getAlphaDVal(void);
extern int getDitherAVal(void );
extern int getZSourceVal(void );

/*---*/
extern int getPrimColVal(int regno);
extern void setPrimColVal(int regno,int val);

/*---*/
extern int getEnvColVal(int regno);
extern void setEnvColVal(int regno,int val);

/*---*/
extern int getBlendColVal(int regno);
extern void setBlendColVal(int regno,int val);

/*---*/
extern int getFogColVal(int regno);
extern void setFogColVal(int regno,int val);

/*---*/
extern int getColorDitherVal(void );
extern u32 makeColorDitherVal(void );
extern void setColorDitherVal(int val);
/*---*/
extern int getAlphaDitherVal(void );
extern u32 makeAlphaDitherVal(void );
extern void setAlphaDitherVal(int val);
/*---*/
extern int getAlphaCompareVal(void );
extern u32 makeAlphaCompareVal(void );
extern void setAlphaCompareVal(int val);
/*---*/
extern int getLightColorVal(int creg);
extern void setLightColorVal(int creg,int val);
extern u32 makeLightColorVal(int lno);
/*---*/
extern void toggleVSFVal(int rno);
extern int getVSFVal(int rno);
extern u32 makeVSFVal(void );
/*---*/
extern int getFogPositionVal(int minmax);
extern void setFogPositionVal(int minmax,int val);
extern int makeFogPositionVal(int minmax);
/*---*/
extern int getTexFiltVal(void);
extern void setTexFiltVal(int no);
extern int makeTexFiltVal(void);
/*---*/
extern int getBgColorVal(void);
extern void setBgColorVal(int colno);
extern int makeBgColorVal(void);
/*---*/
extern int getModelNoVal(void);
extern void setModelNoVal(int colno);
extern int makeModelNoVal(void);
/*---*/
extern int getTextureNoVal(void);
extern void setTextureNoVal(int texno);
extern int makeTextureNoVal(void);
/*---*/
extern int getBgModelNoVal(void);
extern void setBgModelNoVal(int bgno);
/*---*/
extern PRNT *printRCP_REG(int mode);
#endif /* !_RCP_REG_H_ */

