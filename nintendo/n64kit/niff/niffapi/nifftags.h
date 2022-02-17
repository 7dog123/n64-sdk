#ifndef _NIFFTAGS_H_
#define _NIFFTAGS_H_
/* $Id: nifftags.h,v 0.8 1999/01/06 05:33:26 yoshino Exp $ */
/**************************************************************************
 *	NIFF TAG Definitions 			 			  *
 *									  *
 *		Copyright (C) 1998, NINTENDO Co.,Ltd.			  *
 *		Copyright (C) 1998, MONEGI CORPORATION			  *
 *									  *
 **************************************************************************/
#define TAG_HEADER	    0x00000000
#define TAG_SCENE_LIST      0x00010000
#define TAG_SCENE_HEADER    0x00010000
#define TAG_OBJ_LIST	    0x00020000
#define TAG_OBJ		    0x00020100
#define TAG_SHAPE_LIST	    0x00030000
#define TAG_SHAPE	    0x00030100
#define TAG_VTX_LIST	    0x00040000
#define TAG_VTX_GROUP	    0x00040100
#define TAG_COLOR_LIST	    0x00050000
#define TAG_TRI_COLOR_GROUP 0x00050100
#define TAG_VTX_COLOR_GROUP 0x00050200
#define TAG_VECTOR_LIST	    0x00060000
#define TAG_TRI_NV_GROUP    0x00060100
#define TAG_VTX_NV_GROUP    0x00060200
#define TAG_ST_LIST	    0x00070000
#define TAG_ST_GROUP	    0x00070100
#define TAG_TRI_LIST	    0x00080000
#define TAG_TRI_GROUP	    0x00080100
#define TAG_TRI		    0x00080101
#define TAG_PART_LIST	    0x00090000
#define TAG_PART	    0x00090100
#define TAG_MAT_LIST	    0x000a0000
#define TAG_MAT		    0x000a0100
#define TAG_TEX_LIST	    0x000b0000
#define TAG_TEX		    0x000b0100
#define TAG_TEX_IMG_LIST    0x00120000
#define TAG_TEX_IMG	    0x00120100
#define TAG_ANIM_LIST	    0x000c0000
#define TAG_ANIM_GROUP	    0x000c0100
#define TAG_ANIM_STATIC	    0x000c0101
#define TAG_ANIM_CONST	    0x000c0102
#define TAG_ANIM_FULL	    0x000c0103
#define TAG_ANIM_KEY	    0x000c0104
#define TAG_ANIM_BILLBOARD_OBJ	0x000c0105
#define TAG_COLL_LIST	    0x000d0000
#define TAG_COLL_GROUP	    0x000d1000
#define TAG_COLL	    0x000d0100
#define TAG_COLL_DATA_TERRAIN	0x000d0101
#define TAG_COLL_DATA_POINT 0x000d0102
#define TAG_COLL_DATA_CIRCLE	0x000d0103
#define TAG_COLL_DATA_SPHERE	0x000d0104
#define TAG_COLL_DATA_CYLINDER	0x000d0105
#define TAG_COLL_DATA_BOX   0x000d0106
#define TAG_CAM_LIST	    0x000e0000
#define TAG_CAM		    0x000e0100
#define TAG_LIGHT_LIST	    0x000f0000
#define TAG_LIGHT	    0x000f0100
#define TAG_DIR_LIGHT_DIRECTION 0x000f0101
#define TAG_DIR_LIGHT_POSITION	0x000f0102
#define TAG_ENV_LIST	    0x00100000
#define TAG_ENV		    0x00100100
#define TAG_SWITCH_LIST	    0x00130000
#define TAG_SWITCH	    0x00130100
#define TAG_NAME_LIST	    0x00110000
#define TAG_NAME	    0x00110100

/*--------------------------------------
 * Constants, flags, ... 
 *--------------------------------------*/
/* in SceneList */
enum{
    SCENE_CFG_VIDEO_NTSC = 0x00000000,
    SCENE_CFG_VIDEO_PAL  = 0x00000001,
    SCENE_CFG_VIDEO_MPAL = 0x00000002,
    SCENE_CFG_GAMMA	 = 0x00000004,
    SCENE_CFG_DITHER     = 0x00000008,
    SCENE_CFG_DIVOT	 = 0x00000010
};

/* in CamList */
enum{
    CAM_TYPE_PERSP = 0x00000000,
    CAM_TYPE_ORTHO = 0x00000001
};

/* in EnvList */
enum{
    ENV_FOG_NONE = 0x00000000,
    ENV_FOG_USE  = 0x00000001
};

#define FILL_COLOR_NONE	    0xffffffff
#define FILL_DEPTH_NONE	    0xffffffff
#define BG_COLOR_IMG_NONE   0xffffffff
#define	BG_DEPTH_IMG_NONE   0xffffffff

/* in LightList */
enum {
    LIGHT_TYPE_DIRECTION = 0x00000000,
    LIGHT_TYPE_POSITION  = 0x00000001
};

/* in ObjList */
enum{
    OBJ_STATE_CLEAR  = 0x00000000,
    OBJ_STATE_ACTIVE = 0x00000001
};

enum{
    OBJ_TYPE_NULL      = 0x00000000,
    OBJ_TYPE_3D	       = 0x00000001,
    OBJ_TYPE_BILLBOARD = 0x00000002
};

#define	OBJ_GROUP_NONE	0x00000000
#define OBJ_PRI_NONE    0x00000000

enum{
    OBJ_RENDER_CYC_1CYC = 0x00000000,
    OBJ_RENDER_CYC_2CYC = 0x00000001
};

enum{
    OBJ_RENDER_NIFF_OPA_SURF  = 0x00d00000,
    OBJ_RENDER_NIFF_OPA_INTER = 0x00b00000,
    OBJ_RENDER_NIFF_OPA_DECAL = 0x00900000,
    OBJ_RENDER_NIFF_TEX_EDGE  = 0x00700000,
    OBJ_RENDER_NIFF_XLU_SURF  = 0x00500000,
    OBJ_RENDER_NIFF_XLU_INTER = 0x00300000,
    OBJ_RENDER_NIFF_XLU_DECAL = 0x00100000
};

#define ANY_LINK_BILLBOARD  0x00000001
#define OBJ_NOLOD	    0x00000000
#define	OBJ_NOSHAPE	    0xffffffff
#define	OBJ_MAT_NOLINK	    0xffffffff
#define	OBJ_ANIM_NOLINK	    0xffffffff

/* in ShapeList */
enum {
    SHAPE_TYPE_CLEAR      = 0x00000000,
    SHAPE_TYPE_AA         = 0x00000001,
    SHAPE_TYPE_RA         = 0x00000002,
    SHAPE_TYPE_ZB         = 0x00000004,
    SHAPE_TYPE_CULL_BACK  = 0x00000010,
    SHAPE_TYPE_CULL_FRONT = 0x00000020,
    SHAPE_TYPE_CULL_BOTH  = 0x00000030,
    SHAPE_TYPE_USE_VTX_ALPHA_FOR_FOG = 0x00000100   /* NIFF2.0 */
};

#define	SHAPE_MAT_NOLINK    0xffffffff

/* in TriList */
enum{
    TRI_ANIM_NONE	    = 0x00000000,
    TRI_ANIM_VTX_MASK	    = 0x0000000f,
    TRI_ANIM_VTX_FULL	    = 0x00000001,
    TRI_ANIM_VTX_KEY	    = 0x00000002,
    TRI_ANIM_TRI_COLOR_MASK = 0x000000f0,
    TRI_ANIM_TRI_COLOR_FULL = 0x00000010,
    TRI_ANIM_TRI_COLOR_KEY  = 0x00000020,
    TRI_ANIM_VTX_COLOR_MASK = 0x00000f00,
    TRI_ANIM_VTX_COLOR_FULL = 0x00000100,
    TRI_ANIM_VTX_COLOR_KEY  = 0x00000200,
    TRI_ANIM_TRI_NV_MASK    = 0x0000f000,
    TRI_ANIM_TRI_NV_FULL    = 0x00001000,
    TRI_ANIM_TRI_NV_KEY	    = 0x00002000,
    TRI_ANIM_VTX_NV_MASK    = 0x000f0000,
    TRI_ANIM_VTX_NV_FULL    = 0x00010000,
    TRI_ANIM_VTX_NV_KEY	    = 0x00020000,
    TRI_ANIM_ST_MASK	    = 0x00f00000,
    TRI_ANIM_ST_FULL	    = 0x00100000,
    TRI_ANIM_ST_KEY	    = 0x00200000
};

/* in PartList */
#define USE_SHAPE_MAT	0x80000000

/* in MatList */
enum{
    MAT_TYPE_NIFF = 0x0000000,
    MAT_TYPE_N64  = 0x01010101
};

enum{
    MAT_CC_NIFF_VTX        = 0x00000001,
    MAT_CC_NIFF_TRI        = 0x00000002,
    MAT_CC_NIFF_PRIM       = 0x00000004,
    MAT_CC_NIFF_TEX0	   = 0x00000008,
    MAT_CC_NIFF_TEX1       = 0x00000010,
    MAT_CC_NIFF_VTX_ALPHA  = 0x00010000,
    MAT_CC_NIFF_TRI_ALPHA  = 0x00020000,
    MAT_CC_NIFF_PRIM_ALPHA = 0x00040000,
    MAT_CC_NIFF_TEX0_ALPHA = 0x00080000,
    MAT_CC_NIFF_TEX1_ALPHA = 0x00100000,
    MAT_CC_NIFF_NONE	   = 0xffffffff
};

enum{
    MAT_SHADE_LIGHT_OFF    = 0x00000000,
    MAT_SHADE_LIGHT_LOCAL  = 0x00000001,
    MAT_SHADE_LIGHT_GLOBAL = 0x00000002,
    MAT_SHADE_FLAT         = 0x00000000,
    MAT_SHADE_SMOOTH       = 0x00000010,
    MAT_SHADE_USE_HILIGHT  = 0x00000100,
    MAT_SHADE_USE_REFLECT  = 0x00000200
};

enum{
    MAT_CC_N64_COMBINED   = 0x00,
    MAT_CC_N64_TEX0       = 0x01,
    MAT_CC_N64_TEX1       = 0x02,
    MAT_CC_N64_PRIMITIVE  = 0x03,
    MAT_CC_N64_SHADE      = 0x04,
    MAT_CC_N64_ENV        = 0x05,
    MAT_CC_N64_KEY_CENTER = 0x10,
    MAT_CC_N64_KEY_SCALE       = 0x11,
    MAT_CC_N64_COMBINED_ALPHA  = 0x06,
    MAT_CC_N64_TEX0_ALPHA      = 0x07,
    MAT_CC_N64_TEX1_ALPHA      = 0x08,
    MAT_CC_N64_PRIMITIVE_ALPHA = 0x09,
    MAT_CC_N64_SHADE_ALPHA     = 0x0a,
    MAT_CC_N64_ENV_ALPHA       = 0x0b,
    MAT_CC_N64_LOD             = 0x0c,
    MAT_CC_N64_PRIM_LOD        = 0x0d,
    MAT_CC_N64_NOISE           = 0x12,
    MAT_CC_N64_K4              = 0x14,
    MAT_CC_N64_K5              = 0x15,
    MAT_CC_N64_1               = 0x0e,
    MAT_CC_N64_0               = 0x0f,
    MAT_CC_N64_NONE = 0xffffffff
};

/* in  TexList */
enum{
    TEX_FORM_I = 0x00000000,
    TEX_FORM_IA = 0x00000001,
    TEX_FORM_CI = 0x00000002,
    TEX_FORM_YUV = 0x00000003,
    TEX_FORM_RGB = 0x00000004,
    TEX_FORM_RGBA = 0x00000005,
    TEX_FORM_MASK = 0x000000ff
};

enum{
    TEX_DEPTH_4 = 0x00000000,
    TEX_DEPTH_8 = 0x00000100,
    TEX_DEPTH_16 = 0x00000200,
    TEX_DEPTH_32 = 0x00000400,
    TEX_DEPTH_MASK = 0x00000f00
};

enum{
    TEX_WRAP_S = 0x00000000,
    TEX_CLAMP_S = 0x00000001,
    TEX_MIRROR_S = 0x00000002,
    TEX_WRAP_T = 0x00000000,
    TEX_CLAMP_T = 0x00000100,
    TEX_MIRROR_T = 0x00000200
};

enum{
    TEX_ANIM_OFF = 0x00000000,
    TEX_ANIM_FLIPBOOK = 0x00000001,
    TEX_ANIM_FLIPBOOK_KEY = 0x00000002,
    TEX_ANIM_SCROLL_OFFSET = 0x00000010,
    TEX_ANIM_SCROLL_OFFSET_KEY = 0x00000020,
    TEX_ANIM_SCROLL_SCALE = 0x00000100,
    TEX_ANIM_SCROLL_SCALE_KEY = 0x00000200
};

/* in AnimList */
enum{
    ANIM_TYPE_STATIC        = 0x00000000,
    ANIM_TYPE_FULL          = 0x00000002,
    ANIM_TYPE_KEY           = 0x00000003,
    ANIM_TYPE_BILLBOARD_OBJ = 0x00000004
};

#define	ANIM_LOOP_ENDLESS   0x0

/* in CollList */
enum{
    COLL_TYPE_NONE       = 0x00000000,
    COLL_TYPE_TERRAIN    = 0x00000010,
    COLL_TYPE_POINT      = 0x00000020,
    COLL_TYPE_CIRCLE     = 0x00000021,
    COLL_TYPE_SPHERE     = 0x00000022,
    COLL_TYPE_CYLINDER   = 0x00000023,
    COLL_TYPE_BOX        = 0x00000024
};
#endif /* ! _NIFFTAGS_H_ */
