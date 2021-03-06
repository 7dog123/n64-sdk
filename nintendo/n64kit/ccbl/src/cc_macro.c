/*
 * [CCBL]
 *
 * cc_macro.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "rcp_reg.h"

/* color combiner cycle1 */
static u8 ccmPRIMITIVE[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE,
};
static u8 ccmSHADE[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
};
static u8 ccmMODULATEI[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
};
static u8 ccmMODULATEIA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0,
};
static u8 ccmMODULATEIDECALA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
/*  same as G_CC_MODULATEI */
static u8 ccmMODULATERGB[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
};
/*  same as G_CC_MODULATEIA */
static u8 ccmMODULATERGBA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0,
};
/*  same as G_CC_MODULATEIDECALA */
static u8 ccmMODULATERGBDECALA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmMODULATEI_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE
};
static u8 ccmMODULATEIA_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE,
  G_ACMUX_0
};
static u8 ccmMODULATEIDECALA_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0,
};
/*  same as G_CC_MODULATEI_PRIM */
static u8 ccmMODULATERGB_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE
};
/*  same as G_CC_MODULATEIA_PRIM */
static u8 ccmMODULATERGBA_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE,
  G_ACMUX_0
};
/*  same as G_CC_MODULATEIDECALA_PRIM */
static u8 ccmMODULATERGBDECALA_PRIM[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0,
};
static u8 ccmDECALRGB[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmDECALRGBA[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmBLENDI[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmBLENDIA[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0
};
static u8 ccmBLENDIDECALA[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmBLENDRGBA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0_ALPHA,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmBLENDRGBDECALA[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0_ALPHA,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmADDRGB[CC_END] = {
  G_CCMUX_1,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmADDRGBDECALA[CC_END] = {
  G_CCMUX_1,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmREFLECTRGB[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmREFLECTRGBDECALA[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_0,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmHILITERGB[CC_END] = {
  G_CCMUX_PRIMITIVE,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmHILITERGBA[CC_END] = {
  G_CCMUX_PRIMITIVE,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_PRIMITIVE,
  G_ACMUX_SHADE,
  G_ACMUX_TEXEL0,
  G_ACMUX_SHADE
};
static u8 ccmHILITERGBDECALA[CC_END] = {
  G_CCMUX_PRIMITIVE,
  G_CCMUX_SHADE,
  G_CCMUX_TEXEL0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmSHADEDECALA[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmBLENDPE[CC_END] = {
  G_CCMUX_PRIMITIVE,
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_TEXEL0,
  G_CCMUX_ENVIRONMENT,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0
};
static u8 ccmBLENDPEDECALA[CC_END] = {
  G_CCMUX_PRIMITIVE,
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_TEXEL0,
  G_CCMUX_ENVIRONMENT,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmTRILERP[CC_END] = {
  G_CCMUX_TEXEL1,
  G_CCMUX_TEXEL0,
  G_CCMUX_LOD_FRACTION,
  G_CCMUX_TEXEL0,
  G_ACMUX_TEXEL1,
  G_ACMUX_TEXEL0,
  G_ACMUX_LOD_FRACTION,
  G_ACMUX_TEXEL0
};
static u8 ccmINTERFERENCE[CC_END] = {
  G_CCMUX_TEXEL0,
  G_CCMUX_0,
  G_CCMUX_TEXEL1,
  G_CCMUX_0,
  G_ACMUX_TEXEL0,
  G_ACMUX_0,
  G_ACMUX_TEXEL1,
  G_ACMUX_0
};
/* color combiner cycle2 */
static u8 ccmPASS2[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_COMBINED
};
static u8 ccmMODULATEI2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmMODULATEIA2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0
};
/*  same as G_CC_MODULATEI2 */
static u8 ccmMODULATERGB2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
/*  same as G_CC_MODULATEIA2 */
static u8 ccmMODULATERGBA2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_SHADE,
  G_CCMUX_0,
  G_ACMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0
};
static u8 ccmMODULATEI_PRIM2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE
};
static u8 ccmMODULATEIA_PRIM2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE,
  G_ACMUX_0
};
/*  same as G_CC_MODULATEI_PRIM2 */
static u8 ccmMODULATERGB_PRIM2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE
};
/*  same as G_CC_MODULATEIA_PRIM2 */
static u8 ccmMODULATERGBA_PRIM2[CC_END] = {
  G_CCMUX_COMBINED,
  G_CCMUX_0,
  G_CCMUX_PRIMITIVE,
  G_CCMUX_0,
  G_ACMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_PRIMITIVE,
  G_ACMUX_0
};
static u8 ccmDECALRGB2[CC_END] = {
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmBLENDI2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_SHADE,
  G_CCMUX_COMBINED,
  G_CCMUX_SHADE,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmBLENDIA2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_SHADE,
  G_CCMUX_COMBINED,
  G_CCMUX_SHADE,
  G_ACMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_SHADE,
  G_ACMUX_0
};
static u8 ccmHILITERGB2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_COMBINED,
  G_CCMUX_TEXEL0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_SHADE
};
static u8 ccmHILITERGBA2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_COMBINED,
  G_CCMUX_TEXEL0,
  G_CCMUX_COMBINED,
  G_ACMUX_ENVIRONMENT,
  G_ACMUX_COMBINED,
  G_ACMUX_TEXEL0,
  G_ACMUX_COMBINED
};
static u8 ccmHILITERGBDECALA2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_COMBINED,
  G_CCMUX_TEXEL0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_TEXEL0
};
static u8 ccmHILITERGBPASSA2[CC_END] = {
  G_CCMUX_ENVIRONMENT,
  G_CCMUX_COMBINED,
  G_CCMUX_TEXEL0,
  G_CCMUX_COMBINED,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_0,
  G_ACMUX_COMBINED
};
/*==================================*/
u8 *ccm1_idx[] = {
  ccmPRIMITIVE,
  ccmSHADE,
  ccmMODULATEI,
  ccmMODULATEIA,
  ccmMODULATEIDECALA,
  ccmMODULATERGB,
  ccmMODULATERGBA,
  ccmMODULATERGBDECALA,
  ccmMODULATEI_PRIM,
  ccmMODULATEIA_PRIM,
  ccmMODULATEIDECALA_PRIM,
  ccmMODULATERGB_PRIM,
  ccmMODULATERGBA_PRIM,
  ccmMODULATERGBDECALA_PRIM,
  ccmDECALRGB,
  ccmDECALRGBA,
  ccmBLENDI,
  ccmBLENDIA,
  ccmBLENDIDECALA,
  ccmBLENDRGBA,
  ccmBLENDRGBDECALA,
  ccmADDRGB,
  ccmADDRGBDECALA,
  ccmREFLECTRGB,
  ccmREFLECTRGBDECALA,
  ccmHILITERGB,
  ccmHILITERGBA,
  ccmHILITERGBDECALA,
  ccmSHADEDECALA,
  ccmBLENDPE,
  ccmBLENDPEDECALA,
  ccmTRILERP,
  ccmINTERFERENCE,
};
u8 *ccm2_idx[] = {
  ccmPASS2,
  ccmMODULATEI2,
  ccmMODULATEIA2,
  ccmMODULATERGB2,
  ccmMODULATERGBA2,
  ccmMODULATEI_PRIM2,
  ccmMODULATEIA_PRIM2,
  ccmMODULATERGB_PRIM2,
  ccmMODULATERGBA_PRIM2,
  ccmDECALRGB2,
  ccmBLENDI2,
  ccmBLENDIA2,
  ccmHILITERGB2,
  ccmHILITERGBA2,
  ccmHILITERGBDECALA2,
  ccmHILITERGBPASSA2,
};
