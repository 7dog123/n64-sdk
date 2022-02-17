/*======================================================================*/
/*		NuSYS							*/
/*		nugfxsetcfb.c						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*----------------------------------------------------------------------*/    
/* Ver 1.0	97/10/9		Created by Kensaku Ohki(SLANP)		*/
/*======================================================================*/  
#include <nusys.h>

/*----------------------------------------------------------------------*/
/*	Frame buffer Settings						*/
/*	IN:	**framebuf Pointer to an array of pointers to frame buffers*/
/*		framebufnum Number of frame buffers			*/
/*----------------------------------------------------------------------*/
void nuGfxSetCfb(u16** framebuf, u32 framebufnum)
{
    s32	cnt;
    
    nuGfxCfb	= framebuf;
    nuGfxCfbNum	= framebufnum;
    nuGfxCfbCounter = 0;
    nuGfxCfb_ptr = nuGfxCfb[ 0 ];
    osViSwapBuffer( nuGfxCfb[ 0 ] );

#if 0
    nuScSetFrameBufferNum(framebufnum);

    /* Check whether frame buffer addresses are the same. */
    if(framebufnum > 1){
	for(cnt = 0; cnt < framebufnum - 1; cnt++){
	    if(nuGfxCfb[cnt] != nuGfxCfb[cnt+1]){
		return;
	    }
	}
	nuScSetFrameBufferNum(1);
    }
#endif
}
