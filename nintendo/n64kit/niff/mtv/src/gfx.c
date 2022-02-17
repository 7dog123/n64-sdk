/*
 *	gfx.c
 *
 *	Initializes drawing related parts
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	<ultra64.h>
#include	"nusys.h"
#include	"gfx.h"
#include	"main.h"
#include	"bg.h"

extern	tvModeData	tvmd;
extern	texture_data	td[];

/***********************************************************************************
 *	gfxInit
 *
 *	Initializing RCP
 **********************************************************************************/
Gfx *gfxInit(Gfx *gp)
{
	gSPSegment( gp++ , 0 , 0x0 );
	gSPDisplayList(gp++, OS_K0_TO_PHYSICAL(setup_RCP_dl));

	return	gp;
}

/***********************************************************************************
 *	gfxTexInit
 *
 *	Initializing RCP when displaying texture.
 **********************************************************************************/
Gfx *gfxTexInit( Gfx *gp )
{
	gSPDisplayList(gp++, OS_K0_TO_PHYSICAL(setup_texture_dl) );
	return	gp;
}

/**********************************************************************************
 *	gfxClearCfb
 *
 *	Clearing Z buffer and frame buffer.
 **********************************************************************************/
Gfx *gfxClearCfb(Gfx *gp , RGBA32 rgba)
{
	int	i;
	u16* pfb;
	u16	BackColor = (u16)((u8)(rgba.rgba.r) & 0xf8)<<8
				| ((u16)(u8)((rgba.rgba.g) & 0xf8))<<3
				| (u16)((u8)rgba.rgba.b & 0xf8)>>2
				| (u16)((u8)rgba.rgba.a & 0x80)>>7 ;
		/* Clearing Z buffer */
	gDPSetDepthImage(gp++, OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	gDPSetCycleType(gp++, G_CYC_FILL);
	gDPSetColorImage(gp++, G_IM_FMT_RGBA, G_IM_SIZ_16b,DEF_WIDTH,
		   OS_K0_TO_PHYSICAL(nuGfxZBuffer));
	gDPSetFillColor(gp++,(GPACK_ZDZ(G_MAXFBZ,0) << 16 |
			       GPACK_ZDZ(G_MAXFBZ,0)));
	gDPFillRectangle(gp++, 0, 0, DEF_WIDTH-1, DEF_HEIGHT-1);
	gDPPipeSync(gp++);
		/* Clearing frame buffer */
	gDPSetColorImage(gp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, DEF_WIDTH,
		   osVirtualToPhysical(nuGfxCfb_ptr));
	gDPSetFillColor(gp++, BackColor<<16|BackColor);
	gDPFillRectangle(gp++, 0, 0, DEF_WIDTH-1, DEF_HEIGHT-1);
	gDPPipeSync(gp++);
	if( 0 != tvmd.bg_number ){
		gp = bg_disp(gp,&td[tvmd.bg_number-1]);
	}
	return	gp;
}
