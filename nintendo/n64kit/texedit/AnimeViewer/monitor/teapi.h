/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/

#ifndef __TEAPI_H__
#define	__TEAPI_H__

#ifndef	_GBI_H_

/*
 * G_SETIMG fmt: set image formats
 */
#define G_IM_FMT_RGBA	0
#define G_IM_FMT_YUV	1
#define G_IM_FMT_CI		2
#define G_IM_FMT_IA		3
#define G_IM_FMT_I		4

/*
 * G_SETIMG siz: set image pixel size
 */
#define G_IM_SIZ_4b		0
#define G_IM_SIZ_8b		1
#define G_IM_SIZ_16b	2
#define G_IM_SIZ_32b	3

#endif

#ifndef	_ULTRATYPES_H_
typedef unsigned char			u8;	/* unsigned  8-bit */
typedef unsigned short			u16;	/* unsigned 16-bit */
typedef unsigned long			u32;	/* unsigned 32-bit */

typedef signed char			s8;	/* signed  8-bit */
typedef short				s16;	/* signed 16-bit */
typedef long				s32;	/* signed 32-bit */
#endif

typedef struct {
	u32	timg;	/* Texture image position.  64 bit boundary */
	u32	fmt;	/* G_IM_FMT_RGBA, G_IM_FMT_YUV, G_IM_FMT_CI, G_IM_FMT_IA, G_IM_FMT_I */
	u32	siz;	/* G_IM_SIZ_4b, G_IM_SIZ_8b, G_IM_SIZ_16b, G_IM_SIZ_32b */
	u32	width;	/* Width*/
	u32	height;	/* Height*/
	u32	pal;	/* Palette number */
	u32	dram;	/* DRAM with TULT. 64 bit boundary */
} TeInfo;

#define	teAPI_info		((TeInfo*) 0xb0200000L)	/* teInfo */
#define	teAPI_dram		((u32) 0xb0200200L)	/* palette max 512bytes */
#define	teAPI_timg		((u32) 0xb0200400L)	/* texture image data (size:1024(w)x1024(h)x8(bit)=0x100000) */

#ifdef	_GBI_H_
/* Display texture in specified coordinates using texture image information */
//extern Gfx* teDrawTexture(Gfx*, s16 x, s16 y);

Gfx* teDrawTexture(Gfx* glp, u32 x, u32 y, u32 nPicFormat, u32 nPicBits,
                   u32 nXSize, u32 nYSize, 
                   u32 nAdrsPal, u32 nNumberPal, u32 nAdrsTex);
#endif

#endif

