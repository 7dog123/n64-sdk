/*
 *	main.h
 *
 *	prepare and run app, such as initializing mode
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */
#ifndef	_MAIN
#define	_MAIN

#include	<ultra64.h>
#include	"nusys.h"
#include	"mesh.h"
#include	"meshglobal.h"

/* Functions */
void	mainproc(void);
void	mesh_LoadResource(void);
int		get_tv_header(texture_viewer_header*,u32);
void	get_texture_info(texture_info*,u8**);
void	get_setup_info(setup_info*,u8**);
void	getByte(u8* data,u8** ppBuf);
void	getChar(s8* data,u8** ppBuf);
void	getWord(u16* data,u8** ppBuf);
void	getShort(s16* data,u8** ppBuf);
void	getDword(u32* data,u8** ppBuf);
void	getLong(s32* data,u8** ppBuf);
void	tv_memcpy(void*,void*,unsigned int);

static	setup_info	start_set_inf =
{
	{		/*	Texture	*/
		G_TP_PERSP,
		G_TD_CLAMP,
		G_TF_POINT,
		G_TC_FILT
	},
	{		/*	Color Combiner	*/
		CC_USE_GLOBAL,
		0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		{0,0,0,0},
	},
	{		/*	Blender	*/
		RENDER_ZB_ON,
		RENDER_AA_ON,
		RENDER_OPA_SURF,
		G_AC_NONE,
		G_CD_DISABLE,
		G_AD_DISABLE
	},
	{		/*	Fog	*/
		FOG_NOUSE,
		900,
		1000,
		0xffffffff,
	},
	{		/*	Light	*/
		0xffffffff,
		{
			0xffffffff,
			0xffffffff,
			0xffffffff,
			0xffffffff,
			0xffffffff,
			0xffffffff,
			0xffffffff,
		},
		{
			{0,0,0,0,},
			{0,0,0,0,},
			{0,0,0,0,},
			{0,0,0,0,},
			{0,0,0,0,},
			{0,0,0,0,},
			{0,0,0,0,},
		},
		0,
	},
	{		/*	Vertex Color	*/
		0xffffffff,
		0xffffffff,
		0xffffffff,
		0xffffffff,
	},
	{		/*	Etc	*/
		CULL_NONE,
		0x000000ff,
		0xffffffff,
		0x808080ff,
	}
};

#endif	/* _MAIN */
