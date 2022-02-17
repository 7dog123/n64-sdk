/*
  mrn/BlenderMode.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 22, 1998.
*/

#ifndef _mrn_BlenderMode_h
#define _mrn_BlenderMode_h 1

#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_BLENDER_MODE_CYCLE_TYPE_FILL	(0)
#define MRN_BLENDER_MODE_CYCLE_TYPE_1_CYCLE	(1)
#define MRN_BLENDER_MODE_CYCLE_TYPE_2_CYCLE	(2)
#define MRN_BLENDER_MODE_CYCLE_TYPE_COPY	(3)
/* Constant value 'blender' */
#define MRN_BLENDER_MODE_P_IN_COLOR		(0)
#define MRN_BLENDER_MODE_P_MEM_COLOR		(1)
#define MRN_BLENDER_MODE_P_BLEND_COLOR		(2)
#define MRN_BLENDER_MODE_P_FOG_COLOR		(3)
#define MRN_BLENDER_MODE_M_IN_COLOR		(0)
#define MRN_BLENDER_MODE_M_MEM_COLOR		(1)
#define MRN_BLENDER_MODE_M_BLEND_COLOR		(2)
#define MRN_BLENDER_MODE_M_FOG_COLOR		(3)
#define MRN_BLENDER_MODE_A_IN_ALPHA		(0)
#define MRN_BLENDER_MODE_A_FOG_ALPHA		(1)
#define MRN_BLENDER_MODE_A_SHADE_ALPHA		(2)
#define MRN_BLENDER_MODE_A_0			(3)
#define MRN_BLENDER_MODE_B_1_MINUS_A		(0)
#define MRN_BLENDER_MODE_B_MEM_ALPHA		(1)
#define MRN_BLENDER_MODE_B_1			(2)
#define MRN_BLENDER_MODE_B_0			(3)
/* Constant 'blender mode' */
#define MRN_BLENDER_MODE_AA_EN			(8)
#define MRN_BLENDER_MODE_Z_CMP			(0x10)
#define MRN_BLENDER_MODE_Z_UPD			(0x20)
#define MRN_BLENDER_MODE_IM_RD			(0x40)
#define MRN_BLENDER_MODE_CLR_ON_CVG		(0x80)
#define MRN_BLENDER_MODE_CVG_DST_MASK		(0x300)
#define MRN_BLENDER_MODE_CVG_DST_CLAMP		(0)
#define MRN_BLENDER_MODE_CVG_DST_WRAP		(0x100)
#define MRN_BLENDER_MODE_CVG_DST_FULL		(0x200)
#define MRN_BLENDER_MODE_CVG_DST_SAVE		(0x300)
#define MRN_BLENDER_MODE_ZMODE_MASK		(0xC00)
#define MRN_BLENDER_MODE_ZMODE_OPA		(0)
#define MRN_BLENDER_MODE_ZMODE_INTER		(0x400)
#define MRN_BLENDER_MODE_ZMODE_XLU		(0x800)
#define MRN_BLENDER_MODE_ZMODE_DEC		(0xC00)
#define MRN_BLENDER_MODE_CVG_X_ALPHA		(0x1000)
#define MRN_BLENDER_MODE_ALPHA_CVG_SEL		(0x2000)
#define MRN_BLENDER_MODE_FORCE_BL		(0x4000)

#define MRN_BLENDER_MODE_BL1_SHIFT		(18)
#define MRN_BLENDER_MODE_BL2_SHIFT		(16)
#define MRN_BLENDER_MODE_RENDER_MODE_SHIFT	(0)
#define MRN_BLENDER_MODE_P_SHIFT		(12)
#define MRN_BLENDER_MODE_M_SHIFT		(4)
#define MRN_BLENDER_MODE_A_SHIFT		(8)
#define MRN_BLENDER_MODE_B_SHIFT		(0)

/* Declare a structure */
typedef struct _MrnBlenderMode
{
    u8			cycle_type;
    u32			blender_code;
    MvmColor4c		blend_color;
    u32			alpha_compare_mode;
    Gfx			render_mode_gfx[ 5 ];
	/* Should reflect 'blender_code', etc.. */
} MrnBlenderMode;

/* Declare functions */
extern void mrnBlenderModeSet( MrnBlenderMode *mode_ptr, const u8 cycle_type,
			const u8 p1, const u8 m1, const u8 a1, const u8 b1,
			const u8 p2, const u8 m2, const u8 a2, const u8 b2,
			const u16 render_mode_flags );
extern void mrnBlenderModeSetAlphaCompare( MrnBlenderMode *mode_ptr,
	const u32 blend_color, const u8 alpha_compare, const u8 dither );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_BlenderMode_h */
