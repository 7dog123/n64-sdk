/*
 * [CCBL]
 *
 * bl_macro.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "rcp_reg.h"

/* ---------------------------------------------------- */
static u8 rmsw_AA_ZB_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_ZB_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_XLU_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_ON,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_XLU,	/* zmode*/
};
static u8 rmmux_AA_ZB_XLU_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_OPA_DECAL[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_AA_ZB_OPA_DECAL[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_XLU_DECAL[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_ON,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_AA_ZB_XLU_DECAL[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_OPA_INTER[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_INTER,	/* zmode*/
};
static u8 rmmux_AA_ZB_OPA_INTER[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_XLU_INTER[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_ON,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_INTER,	/* zmode*/
};
static u8 rmmux_AA_ZB_XLU_INTER[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_XLU_LINE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_XLU,	/* zmode*/
};
static u8 rmmux_AA_ZB_XLU_LINE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_DEC_LINE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_SAVE,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_AA_ZB_DEC_LINE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_TEX_EDGE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_AA_ZB_TEX_EDGE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_TEX_INTER[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_INTER,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_AA_ZB_TEX_INTER[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_SUB_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_ZB_SUB_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_ZB_PCL_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www G_AC_DITHER */
};
static u8 rmmux_AA_ZB_PCL_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_OPA_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_ZB_OPA_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_TEX_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_AA_ZB_TEX_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_ZB_SUB_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_ZB_SUB_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_RA_ZB_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_RA_ZB_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_RA_ZB_OPA_DECAL[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_RA_ZB_OPA_DECAL[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_RA_ZB_OPA_INTER[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_INTER,	/* zmode*/
};
static u8 rmmux_RA_ZB_OPA_INTER[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_XLU_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_ON,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_WRAP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_XLU_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_XLU_LINE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_XLU_LINE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_DEC_LINE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_DEC_LINE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_TEX_EDGE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_AA_TEX_EDGE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_SUB_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_SUB_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_AA_PCL_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www G_AC_DITHER */
};
static u8 rmmux_AA_PCL_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_OPA_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_OPA_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_TEX_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_AA_TEX_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_AA_SUB_TERR[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_AA_SUB_TERR[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_RA_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_RA_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_ZB_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_ZB_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_ZB_XLU_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_XLU,	/* zmode*/
};
static u8 rmmux_ZB_XLU_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_ZB_OPA_DECAL[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_ZB_OPA_DECAL[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_A_MEM
};
static u8 rmsw_ZB_XLU_DECAL[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_ZB_XLU_DECAL[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_ZB_CLD_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_SAVE,	/* cvg */
    BL_ZMODE_XLU,	/* zmode*/
};
static u8 rmmux_ZB_CLD_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_ZB_OVL_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_SAVE,	/* cvg */
    BL_ZMODE_DEC,	/* zmode*/
};
static u8 rmmux_ZB_OVL_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_ZB_PCL_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_ON,		/* Z_CMP */
    RCP_ON,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/*  www G_AC_DITHER */
};
static u8 rmmux_ZB_PCL_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_0,
    G_BL_CLR_IN,
    G_BL_1
};
static u8 rmsw_OPA_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_OPA_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_0,
    G_BL_CLR_IN,
    G_BL_1
};
static u8 rmsw_XLU_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_XLU_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_CLD_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_SAVE,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_CLD_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_IN,
    G_BL_CLR_MEM,
    G_BL_1MA
};
static u8 rmsw_TEX_EDGE[BL_SWITCH_LEN+2] = {
    RCP_ON,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_ON,		/* CVG_X_ALPHA */
    RCP_ON,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www TEX_EDGE */
};
static u8 rmmux_TEX_EDGE[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_0,
    G_BL_CLR_IN,
    G_BL_1
};
static u8 rmsw_PCL_SURF[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_FULL,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
/* www G_AC_DITHER */
};
static u8 rmmux_PCL_SURF[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_0,
    G_BL_CLR_IN,
    G_BL_1
};
static u8 rmsw_G_RM_ADD[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_ON,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_ON,		/* FORCE_BL */
    BL_CVG_DST_SAVE,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_G_RM_ADD[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_A_FOG,
    G_BL_CLR_MEM,
    G_BL_1
};
static u8 rmsw_FOG_SHADE_A[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_FOG_SHADE_A[BL_MUX_LEN] = {
    G_BL_CLR_FOG,
    G_BL_A_SHADE,
    G_BL_CLR_IN,
    G_BL_1MA
};
static u8 rmsw_FOG_PRIM_A[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_FOG_PRIM_A[BL_MUX_LEN] = {
    G_BL_CLR_FOG,
    G_BL_A_FOG,
    G_BL_CLR_IN,
    G_BL_1MA
};
static u8 rmsw_PASS[BL_SWITCH_LEN+2] = {
    RCP_OFF,		/* AA_EN */
    RCP_OFF,		/* Z_CMP */
    RCP_OFF,		/* Z_UPD */
    RCP_OFF,		/* IM_RD */
    RCP_OFF,		/* CLR_ON_CVG */
    RCP_OFF,		/* CVG_X_ALPHA */
    RCP_OFF,		/* ALPHA_CVG_SEL */
    RCP_OFF,		/* FORCE_BL */
    BL_CVG_DST_CLAMP,	/* cvg */
    BL_ZMODE_OPA,	/* zmode*/
};
static u8 rmmux_PASS[BL_MUX_LEN] = {
    G_BL_CLR_IN,
    G_BL_0,
    G_BL_CLR_IN,
    G_BL_1
};

/* =============================== */


RM_MACRO rmm1_idx[] = {
  {rmsw_AA_ZB_OPA_SURF,rmmux_AA_ZB_OPA_SURF},
  {rmsw_AA_ZB_XLU_SURF,rmmux_AA_ZB_XLU_SURF},
  {rmsw_AA_ZB_OPA_DECAL,rmmux_AA_ZB_OPA_DECAL},
  {rmsw_AA_ZB_XLU_DECAL,rmmux_AA_ZB_XLU_DECAL},
  {rmsw_AA_ZB_OPA_INTER,rmmux_AA_ZB_OPA_INTER},
  {rmsw_AA_ZB_XLU_INTER,rmmux_AA_ZB_XLU_INTER},
  {rmsw_AA_ZB_XLU_LINE,rmmux_AA_ZB_XLU_LINE},
  {rmsw_AA_ZB_DEC_LINE,rmmux_AA_ZB_DEC_LINE},
  {rmsw_AA_ZB_TEX_EDGE,rmmux_AA_ZB_TEX_EDGE},
  {rmsw_AA_ZB_TEX_INTER,rmmux_AA_ZB_TEX_INTER},
  {rmsw_AA_ZB_SUB_SURF,rmmux_AA_ZB_SUB_SURF},
  {rmsw_AA_ZB_PCL_SURF,rmmux_AA_ZB_PCL_SURF},
  {rmsw_AA_ZB_OPA_TERR,rmmux_AA_ZB_OPA_TERR},
  {rmsw_AA_ZB_TEX_TERR,rmmux_AA_ZB_TEX_TERR},
  {rmsw_AA_ZB_SUB_TERR,rmmux_AA_ZB_SUB_TERR},
  {rmsw_RA_ZB_OPA_SURF,rmmux_RA_ZB_OPA_SURF},
  {rmsw_RA_ZB_OPA_DECAL,rmmux_RA_ZB_OPA_DECAL},
  {rmsw_RA_ZB_OPA_INTER,rmmux_RA_ZB_OPA_INTER},
  {rmsw_AA_OPA_SURF,rmmux_AA_OPA_SURF},
  {rmsw_AA_XLU_SURF,rmmux_AA_XLU_SURF},
  {rmsw_AA_XLU_LINE,rmmux_AA_XLU_LINE},
  {rmsw_AA_DEC_LINE,rmmux_AA_DEC_LINE},
  {rmsw_AA_TEX_EDGE,rmmux_AA_TEX_EDGE},
  {rmsw_AA_SUB_SURF,rmmux_AA_SUB_SURF},
  {rmsw_AA_PCL_SURF,rmmux_AA_PCL_SURF},
  {rmsw_AA_OPA_TERR,rmmux_AA_OPA_TERR},
  {rmsw_AA_TEX_TERR,rmmux_AA_TEX_TERR},
  {rmsw_AA_SUB_TERR,rmmux_AA_SUB_TERR},
  {rmsw_RA_OPA_SURF,rmmux_RA_OPA_SURF},
  {rmsw_ZB_OPA_SURF,rmmux_ZB_OPA_SURF},
  {rmsw_ZB_XLU_SURF,rmmux_ZB_XLU_SURF},
  {rmsw_ZB_OPA_DECAL,rmmux_ZB_OPA_DECAL},
  {rmsw_ZB_XLU_DECAL,rmmux_ZB_XLU_DECAL},
  {rmsw_ZB_CLD_SURF,rmmux_ZB_CLD_SURF},
  {rmsw_ZB_OVL_SURF,rmmux_ZB_OVL_SURF},
  {rmsw_ZB_PCL_SURF,rmmux_ZB_PCL_SURF},
  {rmsw_OPA_SURF,rmmux_OPA_SURF},
  {rmsw_XLU_SURF,rmmux_XLU_SURF},
  {rmsw_CLD_SURF,rmmux_CLD_SURF},
  {rmsw_TEX_EDGE,rmmux_TEX_EDGE},
  {rmsw_PCL_SURF,rmmux_PCL_SURF},
  {rmsw_G_RM_ADD,rmmux_G_RM_ADD},
  {NULL,rmmux_FOG_SHADE_A},
  {NULL,rmmux_FOG_PRIM_A},
  {NULL,rmmux_PASS},
};


RM_MACRO rmm2_idx[] = {
  {rmsw_AA_ZB_OPA_SURF,rmmux_AA_ZB_OPA_SURF},
  {rmsw_AA_ZB_XLU_SURF,rmmux_AA_ZB_XLU_SURF},
  {rmsw_AA_ZB_OPA_DECAL,rmmux_AA_ZB_OPA_DECAL},
  {rmsw_AA_ZB_XLU_DECAL,rmmux_AA_ZB_XLU_DECAL},
  {rmsw_AA_ZB_OPA_INTER,rmmux_AA_ZB_OPA_INTER},
  {rmsw_AA_ZB_XLU_INTER,rmmux_AA_ZB_XLU_INTER},
  {rmsw_AA_ZB_XLU_LINE,rmmux_AA_ZB_XLU_LINE},
  {rmsw_AA_ZB_DEC_LINE,rmmux_AA_ZB_DEC_LINE},
  {rmsw_AA_ZB_TEX_EDGE,rmmux_AA_ZB_TEX_EDGE},
  {rmsw_AA_ZB_TEX_INTER,rmmux_AA_ZB_TEX_INTER},
  {rmsw_AA_ZB_SUB_SURF,rmmux_AA_ZB_SUB_SURF},
  {rmsw_AA_ZB_PCL_SURF,rmmux_AA_ZB_PCL_SURF},
  {rmsw_AA_ZB_OPA_TERR,rmmux_AA_ZB_OPA_TERR},
  {rmsw_AA_ZB_TEX_TERR,rmmux_AA_ZB_TEX_TERR},
  {rmsw_AA_ZB_SUB_TERR,rmmux_AA_ZB_SUB_TERR},
  {rmsw_RA_ZB_OPA_SURF,rmmux_RA_ZB_OPA_SURF},
  {rmsw_RA_ZB_OPA_DECAL,rmmux_RA_ZB_OPA_DECAL},
  {rmsw_RA_ZB_OPA_INTER,rmmux_RA_ZB_OPA_INTER},
  {rmsw_AA_OPA_SURF,rmmux_AA_OPA_SURF},
  {rmsw_AA_XLU_SURF,rmmux_AA_XLU_SURF},
  {rmsw_AA_XLU_LINE,rmmux_AA_XLU_LINE},
  {rmsw_AA_DEC_LINE,rmmux_AA_DEC_LINE},
  {rmsw_AA_TEX_EDGE,rmmux_AA_TEX_EDGE},
  {rmsw_AA_SUB_SURF,rmmux_AA_SUB_SURF},
  {rmsw_AA_PCL_SURF,rmmux_AA_PCL_SURF},
  {rmsw_AA_OPA_TERR,rmmux_AA_OPA_TERR},
  {rmsw_AA_TEX_TERR,rmmux_AA_TEX_TERR},
  {rmsw_AA_SUB_TERR,rmmux_AA_SUB_TERR},
  {rmsw_RA_OPA_SURF,rmmux_RA_OPA_SURF},
  {rmsw_ZB_OPA_SURF,rmmux_ZB_OPA_SURF},
  {rmsw_ZB_XLU_SURF,rmmux_ZB_XLU_SURF},
  {rmsw_ZB_OPA_DECAL,rmmux_ZB_OPA_DECAL},
  {rmsw_ZB_XLU_DECAL,rmmux_ZB_XLU_DECAL},
  {rmsw_ZB_CLD_SURF,rmmux_ZB_CLD_SURF},
  {rmsw_ZB_OVL_SURF,rmmux_ZB_OVL_SURF},
  {rmsw_ZB_PCL_SURF,rmmux_ZB_PCL_SURF},
  {rmsw_OPA_SURF,rmmux_OPA_SURF},
  {rmsw_XLU_SURF,rmmux_XLU_SURF},
  {rmsw_CLD_SURF,rmmux_CLD_SURF},
  {rmsw_TEX_EDGE,rmmux_TEX_EDGE},
  {rmsw_PCL_SURF,rmmux_PCL_SURF},
  {rmsw_G_RM_ADD,rmmux_G_RM_ADD},
};


