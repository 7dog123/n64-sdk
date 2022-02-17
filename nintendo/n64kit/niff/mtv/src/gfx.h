/*
 *	gfx.h
 *
 *	initializes drawings
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#ifndef _GFX_H
#define	_GFX_H

#include	<ultra64.h>
#include	"main.h"
#include	"game.h"

static	Vp vp = {
	DEF_WIDTH*2, DEF_HEIGHT*2, G_MAXZ/2, 0,	/* Magnification */
	DEF_WIDTH*2, DEF_HEIGHT*2, G_MAXZ/2, 0,	/* Movement */
};

static	Gfx	setup_RCP_dl[] =
{
	gsSPViewport(&vp),
	gsSPClearGeometryMode( G_CULL_BOTH|G_TEXTURE_GEN|G_TEXTURE_GEN_LINEAR
						  |G_LIGHTING|G_FOG|G_LOD ),
	gsSPSetGeometryMode( G_SHADE|G_SHADING_SMOOTH|G_ZBUFFER|G_CULL_BACK ),
	gsSPTexture( 0,0,0,0,G_OFF ),
	gsSPFogPosition( 982 , 1000 ),
	gsSPClipRatio( FRUSTRATIO_1 ),

	gsDPSetCombineKey( G_CK_NONE ),

	gsDPPipeSync(),
	gsDPSetCycleType( G_CYC_1CYCLE ),
	gsDPSetCombineMode( G_CC_SHADE , G_CC_SHADE ),
	gsDPSetRenderMode( G_RM_OPA_SURF , G_RM_OPA_SURF2 ),
	gsDPSetColorDither( G_CD_BAYER ),
	gsDPSetAlphaCompare( G_AC_NONE ),
	gsDPSetAlphaDither( G_AD_DISABLE ),
	gsDPPipelineMode( G_PM_NPRIMITIVE ),

	gsSPEndDisplayList(),
};

static	Gfx	setup_texture_dl[] =
{
	gsSPTexture(0x8000,0x8000,0,G_TX_RENDERTILE,G_ON),
	gsDPSetTextureConvert( G_TC_FILT ),
	gsDPSetTextureDetail( G_TD_CLAMP ),
	gsDPSetTextureFilter( G_TF_POINT ),
	gsDPSetTextureLOD( G_TL_TILE ),
	gsDPSetTexturePersp( G_TP_PERSP ),
	gsDPSetTextureLUT( G_TT_NONE ),
	gsDPSetTile( G_IM_FMT_RGBA ,
				 G_IM_SIZ_16b ,
				 GS_TB_TLINE( 64 , G_IM_SIZ_16b ) ,
				 GS_PIX2TMEM( 0 , G_IM_SIZ_16b ) ,
				 0 , 0 ,
				 G_TX_NOMIRROR , G_TX_NOMASK , 0 ,
				 G_TX_NOMIRROR , G_TX_NOMASK , 0 ),
	gsDPSetTile( G_IM_FMT_RGBA ,
				 G_IM_SIZ_16b ,
				 GS_TB_TLINE( 64 , G_IM_SIZ_16b ) ,
				 GS_PIX2TMEM( 64*16 , G_IM_SIZ_16b ) ,
				 1 , 0 ,
				 G_TX_NOMIRROR , G_TX_NOMASK , 0 ,
				 G_TX_NOMIRROR , G_TX_NOMASK , 0 ),
	gsDPSetTileSize( 0, 0,0, 63,15 ),
	gsDPSetTileSize( 1, 0,16, 63,31 ),

	gsSPEndDisplayList(),
};

Gfx *gfxInit(Gfx *gp);
Gfx *gfxClearCfb(Gfx *gp,RGBA32);
Gfx *gfxTexInit(Gfx *gp);

#endif	/* _GFX_H */
