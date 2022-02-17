/*
  Copyright(C) 1998, NINTENDO Co., Ltd.
  Texture Editor Anime Viewer Converter
*/

#include <nusys.h>
#include "graphic.h"
#include "teapi.h"

/* Rectangle data structure */
typedef struct {
	s16		left;					// Left-end coordinates
	s16		top;					// Upper coordinates
	s16		right;					// Right-end coordinates
	s16		bottom;					// Lower coordinates
} RECT;

typedef	struct {
	s16	x;
	s16	y;
} POINT;

typedef	struct {
	s16	cx;
	s16	cy;
} SIZE;

/* Global variables */
static RECT aaSci = { 0, 0, SCREEN_WD, SCREEN_HT};	/* Scissoring area */

#define	RGBA16(r,g,b,a)	(u16)((((r)&31)<<11)|(((g)&31)<<6)|(((b)&31)<<1)|((a)&1))

//#define	te_MAXSIZE	0x80000
//#include "tedata.c"

#if 0

static TeInfo teInfo __attribute__((aligned (8))) = { teAPI_timg, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 32, 0, teAPI_dram };

void nuPiRomRead(u32 rom, void* ram, u32 size)
{
	u32 i, cnt = size / 4;
	u32* pROM = (u32*) rom;
	u32* pRAM = (u32*) ram;
	for (i = 0; i < cnt; i++) {
		osPiRawReadIo((u32) pROM, pRAM);
		pROM++;
		pRAM++;
	}
}

void teLoadInfo()
{
	nuPiRomRead((u32) teAPI_info, &teInfo, sizeof teInfo);
	nuPiRomRead(teInfo.dram, tePalette, sizeof tePalette);
	{
		u32 xSize = (u32)(teInfo.width * ((double)(4 << teInfo.siz) / 8));
		u32 size = teInfo.height * xSize;
		if (size > te_MAXSIZE) size = te_MAXSIZE;
		nuPiRomRead(teInfo.timg, teTexture, size);
	}
}
#endif


/* Display texture in specified coordinates using texture image information */

Gfx* teDrawTexture(Gfx* glp, u32 x, u32 y, 
                   u32 nPicFormat, u32 nPicBits,
                   u32 nWidth, u32 nHeight, 
                   u32 nAdrsPal, u32 nPalIndex, u32 nAdrsTex)
{
//	TeInfo* pInfo = &teInfo;

//	teLoadInfo();
	x += (320 - nWidth) / 2;
	y += (240 - nHeight) / 2;

	gDPPipeSync(glp++);
	gDPSetCycleType(glp++, G_CYC_1CYCLE);
	gDPSetRenderMode(glp++, G_RM_NOOP, G_RM_NOOP2);
	gDPSetTexturePersp(glp++, G_TP_NONE);
	gDPSetCombineMode(glp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
	/* Set texture filter type */
	gDPSetTextureFilter(glp++, G_TF_POINT);
	/* Set detailed type */
	gDPSetTextureDetail(glp++, G_TD_CLAMP);
	/* Set color space conversion mode */
	gDPSetTextureConvert(glp++, G_TC_FILT);
	/* Set alpha value compare mode*/
	gDPSetAlphaCompare(glp++, G_AC_NONE);
	/* Set color data dithering mode */
	gDPSetColorDither(glp++, G_CD_DISABLE);
	/* Set alpha value dithering mode */
	gDPSetAlphaDither(glp++, G_AD_DISABLE);

	/* Palette settings */
	if (nPicFormat == G_IM_FMT_CI) {
		gDPSetTextureLUT(glp++, G_TT_RGBA16);
		if (nPicBits == G_IM_SIZ_8b) {
			gDPLoadTLUT_pal256(glp++, nAdrsPal);
		} else if (nPicBits == G_IM_SIZ_4b) {
			gDPLoadTLUT_pal16(glp++, 0, nAdrsPal);
		}
	}
	{
		s16 ix, iy;
		SIZE sizeRect;
		s16 sx = aaSci.left > x ? aaSci.left - x : 0;
		s16 sy = aaSci.top > y ? aaSci.top - y : 0;
		iy = sy;
		sizeRect.cx = nWidth;
		sizeRect.cy = nHeight;
		while (iy < sizeRect.cy) {
			SIZE size;
			ix = sx;
			size.cy = 32;
			if ((iy + size.cy) > sizeRect.cy) {
				size.cy = sizeRect.cy - iy;
			}
			while (ix < sizeRect.cx) {
				RECT rectRead, rectDraw;
				size.cx = 32;
				if ((ix + size.cx) > sizeRect.cx) {
					size.cx = sizeRect.cx - ix;
				}
				rectRead.left = ix;
				rectRead.top = iy;
				rectRead.right = rectRead.left + size.cx - 1;
				rectRead.bottom = rectRead.top + size.cy - 1;
				rectDraw.left = x + ix;
				rectDraw.top = y + iy;
				rectDraw.right = rectDraw.left + size.cx;
				rectDraw.bottom = rectDraw.top + size.cy;
				if (nPicBits == G_IM_SIZ_4b) {
					gDPLoadTextureTile_4b(glp++, nAdrsTex, nPicFormat,
						nWidth, nHeight,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						nPalIndex, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (nPicBits == G_IM_SIZ_8b) {
					gDPLoadTextureTile(glp++, nAdrsTex, nPicFormat, G_IM_SIZ_8b,
						nWidth, nHeight,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (nPicBits == G_IM_SIZ_16b) {
					gDPLoadTextureTile(glp++, nAdrsTex, nPicFormat, G_IM_SIZ_16b,
						nWidth, nHeight,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (nPicBits == G_IM_SIZ_32b) {
					gDPLoadTextureTile(glp++, nAdrsTex, nPicFormat, G_IM_SIZ_32b,
						nWidth, nHeight,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				}
				gSPTextureRectangle(glp++,
					rectDraw.left << 2, rectDraw.top << 2,		/* Upper left coordinates */
					rectDraw.right << 2, rectDraw.bottom << 2,	/* Lower right coordinates */
					G_TX_RENDERTILE,							/* Tile number */
					ix << 5, iy << 5,						/* Upper left coordinates in TMEM */
					1 << 10, 1 << 10);							/* Scale */
				ix += size.cx;
			}
			iy += size.cy;
		}
	}
	return glp;
}

