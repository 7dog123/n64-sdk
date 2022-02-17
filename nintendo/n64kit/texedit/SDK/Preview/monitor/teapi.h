/*
 * TextureEditor preview plugin API
 *   Copyright 1998 (c) MONEGI CORP.
 */
#ifndef __TEAPI_H__
#define	__TEAPI_H__

#define	teSEGMENT_INFO_OFFSET	0xb0200000
#define	teSEGMENT_INFO_COUNT	2
#define	teSEGMENT_INFO_SIZE		0x80
#define	teSEGMENT_INFO(n)		(teSEGMENT_INFO_OFFSET + (n) * teSEGMENT_INFO_SIZE)
#define	teSEGMENT_TLUT_OFFSET	teSEGMENT_INFO(teSEGMENT_INFO_COUNT)	// 0xb0200100
#define	teSEGMENT_TLUT_COUNT	2
#define	teSEGMENT_TLUT_SIZE		0x200
#define	teSEGMENT_TLUT(n)		(teSEGMENT_TLUT_OFFSET + (n) * teSEGMENT_TLUT_SIZE)
#define	teSEGMENT_TIMG_OFFSET	teSEGMENT_TLUT(teSEGMENT_TLUT_COUNT)	// 0xb0200500
#define	teSEGMENT_TIMG_COUNT	2
#define	teSEGMENT_TIMG_SIZE		0x4b000
#define	teSEGMENT_TIMG(n)		(teSEGMENT_TIMG_OFFSET + (n) * teSEGMENT_TIMG_SIZE)
#define	teSEGMENT_TIMG_END		teSEGMENT_TIMG(teSEGMENT_TIMG_COUNT)	// 0xb0240500
#define	te_MAXSIZE	0x80000	/* Maximum size of texture buffer */

#if defined(_LANGUAGE_C) || defined(__cplusplus)

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

#ifdef _MSC_VER
#pragma	pack(4)
#endif

typedef struct {
	u32 update;	/* Update flag */
	u32	timg;	/* TIMG number */
	u32	fmt;	/* G_IM_FMT_RGBA, G_IM_FMT_YUV, G_IM_FMT_CI, G_IM_FMT_IA, G_IM_FMT_I */
	u32	siz;	/* G_IM_SIZ_4b, G_IM_SIZ_8b, G_IM_SIZ_16b, G_IM_SIZ_32b */
	u32	width;	/* Width */
	u32	height;	/* Height */
	u32	pal;	/* Palette number */
	u32	dram;	/* TULT number*/
	u32 type;	/* Palette type */
	s32 ox;		/* x position offset */
	s32 oy;		/* y position offset */
	u32 reserved_for_pc[16-11];	/* reserved for comunicate to PC */
#define	teSEGMENT_INFO_SIZE_CORE	(16*sizeof(u32))	/* end of copy from ROM */
	s32 x;		/* x position */
	s32 y;		/* y position */
	u32 xScale;	/* x scaling */
	u32 yScale;	/* y scaling */
	u32 filter;	/* Filter type */
	u32 combiner;	/* Combiner mode */
	u32 rgbaP;	/* Primitive color */
	u32 rgbaE;	/* Environment color */
	u32 render;	/* render mode */
	u32 reserved_for_nu64[16-9];	/* reserved for save status of NU64 */
} TeInfo;	// 32 * 4 = 128byte

#define	teAPI_info		((TeInfo*) teSEGMENT_INFO_OFFSET)	/* teInfo */
#define	teAPI_dram		((u32) teSEGMENT_TLUT_OFFSET)	/* palette max 512bytes */
#define	teAPI_timg		((u32) teSEGMENT_TIMG_OFFSET)	/* texture image data (size:1024(w)x512(h)x8(bit)=0x80000) */

#ifdef	_GBI_H_
extern int teMenu_disp;	/* Menu ON/OFF flag */
/* Initialize */
extern void teInit();
/* Draw background */
extern Gfx* teDrawBackground(Gfx*);
/* Draw texture */
extern Gfx* teDrawTextures(Gfx*);
/* Draw menu */
extern Gfx* teDrawMenu(Gfx*, s16 x, s16 y);
/* Menu control */
extern void teControl(NUContData* contdata);
#endif

typedef struct {
	u32 timg_update;	/* update */
	u32	timg;	/* TIMG offset */
	u32	fmt;	/* G_IM_FMT_RGBA, G_IM_FMT_YUV, (G_IM_FMT_CI, G_IM_FMT_IA), G_IM_FMT_I */
	u32	siz;	/* G_IM_SIZ_4b, G_IM_SIZ_8b, G_IM_SIZ_16b, G_IM_SIZ_32b */
	u32	width;	/* Width */
	u32	height;	/* Height */
	u32 reserved[8-6];	/* reserved */
} n64_tmfInfo;	/* 8 * 4 = 32byte */

typedef struct {
	u32 tlut_update;	/* update */
	u32	tlut;	/* TULT offset */
	u32 type;	/* Palette type */
	u32 reserved[8-3];	/* reserved */
} n64_tlfInfo;	/* 8 * 4 = 32byte */

typedef struct {
	u32 tmf;	/* tmfInfo offset(offset/32=number) */
	u32 tlf;	/* tlfInfo offset(offset/32=number) */
	u32	pal;	/* Palette number */
	u32 reserved[8-3];
} n64_picInfo;	/* 8 * 4 = 32byte */

typedef struct {
	u32 type;	/* 0=end/1=relative jump/2=display picture with wait */
	union {
		struct {
			u32 no;		/* picture number */
			s32 x;		/* add x position */
			s32 y;		/* add y position */
			u32 time;	/* wait timer */
		} pic;
		struct {
			s32 no;	/* jump relative number(-n .. +n) */
		} jump;
		u32 reserved[8-1];
	};
} n64_seqInfo;	/* 8 * 4 = 32byte */

typedef struct {
	u32 seqInfo_update;
	u32 seqInfo_adrs;
	u32 seqInfo_cnt;
	s32 x;
	s32 y;
	u32 reserved[8-4];
} n64_anmInfo;	/* 8 * 4 = 32byte */

typedef struct {
	u32	update;	/* b0=busy/b1=picInfo/b2=tmfInfo/b3=tlfInfo/b4=anmInfo */

	u32 picInfo_adrs;
	u32 picInfo_cnt;
	u32 tmfInfo_adrs;
	u32 tmfInfo_cnt;
	u32 tlfInfo_adrs;
	u32 tlfInfo_cnt;
	u32 tmfData_adrs;
	u32 tmfData_len;
	u32 tlfData_adrs;
	u32 tlfData_len;
	u32 anmInfo_adrs;
	u32 anmInfo_cnt;
	u32 reserved[32-13];
} n64_previewInfo;	/* 32 * 4 = 128byte */

#ifdef	_MSC_VER
#pragma pack()
#endif

#endif	// _LANGUAGE_C or __cplusplus

#endif

