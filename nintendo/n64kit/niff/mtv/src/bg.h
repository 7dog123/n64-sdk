/*
 *	bg.h
 *
 *	Displays a background.
 *	
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */
#ifndef	_BG_H_
#define	_BG_H_

#include	"main.h"

extern	u16	bg_pixel[];

/***********************************************************
				static display list
************************************************************/
static	Gfx	bg_setup_RCP_dl[] =
{
	gsSPClearGeometryMode( 0xffffffff ),
	gsSPSetGeometryMode( G_SHADE|G_SHADING_SMOOTH|G_TEXTURE_ENABLE ),

	gsDPPipeSync(),

	gsDPSetCycleType( G_CYC_1CYCLE),

	gsDPSetColorDither( G_CD_DISABLE ),
	gsDPSetAlphaCompare( G_AC_NONE ),
	gsDPSetAlphaDither( G_AD_DISABLE ),
	gsDPSetBlendColor( 0,0,0,1),
	gsDPSetFogColor( 0,0,0,127 ),
	gsDPPipelineMode( G_PM_NPRIMITIVE ),

	gsSPTexture(0x8000,0x8000,0,G_TX_RENDERTILE,G_ON),
	gsDPSetTextureConvert( G_TC_FILT ),
	gsDPSetTextureDetail( G_TD_CLAMP ),
	gsDPSetTextureFilter( G_TF_POINT ),
	gsDPSetTexturePersp( G_TP_NONE ),
	gsDPSetTextureLOD( G_TL_TILE ),
	gsDPSetTextureLUT( G_TT_NONE ),

	gsDPSetRenderMode( G_RM_OPA_SURF,G_RM_OPA_SURF2 ),
	gsDPSetCombineLERP( 0,0,0,TEXEL0, 0,0,0,1, 0,0,0,TEXEL0, 0,0,0,1 ),
	gsSPEndDisplayList(),
};

/***********************************************************
						functions
************************************************************/
Gfx *bg_disp(Gfx*,texture_data*);
Gfx *tex_rect(Gfx *gp,unsigned int,unsigned int,unsigned int,
					  s16,s16,s16,s16,u16,u16,u16,u16);

#endif	/*_BG_H_*/
