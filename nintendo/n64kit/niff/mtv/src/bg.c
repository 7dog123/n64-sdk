/*
 *	bg.c
 *
 *	displays background pictures
 *
 *	Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  	Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#include	"bg.h"

/**********************************************************************************
 *	bg_disp
 *
 *	displays background pictures
***********************************************************************************/
Gfx	*bg_disp(Gfx* gfxp,texture_data* ptxdata)
{
	int	i,j;
	Gfx*	gp = gfxp;
	texture_info*	pti = ptxdata->pti;

	u16	width = pti->image.imageW;
	u16	height = pti->image.imageH;
	s16	startX,startY;
	s16	startS,startT;
	u16	lastW,lastH;
	u16	dispW = 320;
	u16	dispH = 240;
	u16	gridW = 64;
	u16	gridH = 64;
	unsigned int	fmt = (unsigned int)pti->image.imageFmt;
	unsigned int	siz = (unsigned int)pti->image.imageSiz;
	unsigned int	timg = (unsigned int)ptxdata->ppixel[0];

	switch(siz){
		case G_IM_SIZ_4b :
			if( fmt == G_IM_FMT_CI )
				gridH = 32;
			else
				gridW = 128;
			width = (width+1)&-2;
			break;
		case G_IM_SIZ_8b :
			if( fmt == G_IM_FMT_CI )
				gridH = 32;
			break;
		case G_IM_SIZ_16b :
			if( fmt == G_IM_FMT_YUV )
				gridH = 16;
			else
				gridH = 32;
			break;
		case G_IM_SIZ_32b :
			gridH = 16;
			break;
		default :
			break;
	}
	startX = (320-width)/2;
	startY = (240-height)/2;
	if( startX < 0 ){
		startS = -startX;
		startX = 0;
	} else {
		startS = 0;
		dispW = width;
	}
	lastW = dispW % gridW;
	if( startY < 0 ){
		startT = -startY;
		startY = 0;
	} else {
		startT = 0;
		dispH = height;
	}
	lastH = dispH % gridH;
		/*    Initializing RCP	*/
	gSPDisplayList( gp++ ,bg_setup_RCP_dl );
	if( G_IM_FMT_YUV == fmt ){
		gSPSetGeometryMode( gp++ , G_LOD );
	}
	if( G_IM_FMT_CI == fmt ){
		gDPSetTextureLUT( gp++ , ptxdata->pti->image.tlutMode );
		switch(siz){
			case G_IM_SIZ_4b :
			case G_IM_SIZ_8b :
				gDPLoadSync(gp++);
				gDPLoadTLUT_pal256(gp++ ,ptxdata->ppal );
				break;
			default :
				gDPSetTextureLUT(gp++ , G_TT_NONE );
				break;
		}
	} else {
		gDPSetTextureLUT(gp++ , G_TT_NONE );
	}
	gDPPipeSync(gp++);
		/*	Loop which displays a background picture.	*/
	for( i=0;i<=(signed)(dispH-gridH);i+=gridH )
	{
		for( j=0;j<=(signed)(dispW-gridW);j+=gridW )
			gp = tex_rect(gp,timg,fmt,siz,startX+j,startY+i,startS+j,startT+i,
							width,height,gridW,gridH);
		if( lastW ){
			gp = tex_rect(gp,timg,fmt,siz,startX+j,startY+i,startS+j,startT+i,
							width,height,lastW,gridH);
		}
	}
	if( lastH ){
		for( j=0;j<=(signed)(dispW-gridW);j+=gridW )
			gp = tex_rect(gp,timg,fmt,siz,startX+j,startY+i,startS+j,startT+i,
							width,height,gridW,lastH);
		if( lastW )
			gp = tex_rect(gp,timg,fmt,siz,startX+j,startY+i,startS+j,startT+i,
							width,height,lastW,lastH);
	}
	gDPPipeSync(gp++);
	return	gp;
}

/**************************************************************************************
 *	tex_rect
 *
 *	Reading and displaying a picture
*************************************************************************************/
Gfx *tex_rect(Gfx *gp,unsigned int timg,unsigned int fmt,unsigned int siz,
					 s16 startX,s16 startY,s16 startS,s16 startT,
					 u16 width,u16 height,u16 rectW,u16 rectH)
{
	gDPLoadSync( gp++ );
	switch(siz){
		case G_IM_SIZ_4b :
			gDPLoadTextureTile_4b(gp++,timg,fmt,
								(unsigned int)width,(unsigned int)height,(unsigned int)startS,(unsigned int)startT,
								(unsigned int)(startS+rectW-1),(unsigned int)(startT+rectH-1),
								0,
								G_TX_WRAP ,G_TX_WRAP,
								G_TX_NOMASK ,G_TX_NOMASK,
								G_TX_NOLOD , G_TX_NOLOD
								);
			break;
		case G_IM_SIZ_8b :
			gDPLoadTextureTile( gp++,timg,fmt,G_IM_SIZ_8b,
								(unsigned int)width,(unsigned int)height,
								(unsigned int)startS,(unsigned int)startT,
								(unsigned int)(startS+rectW-1),(unsigned int)(startT+rectH-1),
								0,
								G_TX_WRAP ,G_TX_WRAP,
								G_TX_NOMASK ,G_TX_NOMASK,
								G_TX_NOLOD , G_TX_NOLOD
								);
			break;
		case G_IM_SIZ_16b :
			gDPLoadTextureTile( gp++,timg,fmt,G_IM_SIZ_16b,
								(unsigned int)width,(unsigned int)height,
								(unsigned int)startS,(unsigned int)startT,
								(unsigned int)(startS+rectW-1),(unsigned int)(startT+rectH-1),
								0,
								G_TX_WRAP ,G_TX_WRAP ,
								G_TX_NOMASK ,G_TX_NOMASK,
								G_TX_NOLOD , G_TX_NOLOD
								);
			break;
		case G_IM_SIZ_32b :
			gDPLoadTextureTile( gp++,timg,fmt,G_IM_SIZ_32b,
								(unsigned int)width,(unsigned int)height,
								(unsigned int)startS,(unsigned int)startT,
								(unsigned int)(startS+rectW-1),(unsigned int)(startT+rectH-1),
								0,
								G_TX_WRAP ,G_TX_WRAP,
								G_TX_NOMASK ,G_TX_NOMASK,
								G_TX_NOLOD , G_TX_NOLOD
								);
			break;
		default :
			break;
	}
		/*	Display a picture	*/
	gSPTextureRectangle(gp++ ,startX<<2,startY<<2,
						(startX+rectW)<<2,(startY+rectH)<<2,
						G_TX_RENDERTILE,startS<<5,startT<<5,1<<10,1<<10 );
	gDPPipeSync(gp++);
	return	gp;
}

