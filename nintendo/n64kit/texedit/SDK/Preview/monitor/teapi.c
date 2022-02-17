/*
 * TextureEditor preview plugin API
 *   Copyright 1998 (c) MONEGI CORP.
 *
 * Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
 */
#include <nusys.h>
#include "graphic.h"
#include "teapi.h"

#define	fabs(f)	((f) < 0 ? -(f) : (f))

#define	RGBA16(r,g,b,a)	(u16)((((r)&31)<<11)|(((g)&31)<<6)|(((b)&31)<<1)|((a)&1))

/* Rectangle data structure */
/* <<< 矩形データ構造体 >>> */
typedef struct {
	s16		left;
	s16		top;
	s16		right;
	s16		bottom;
} RECT;

typedef	struct {
	s16	x;
	s16	y;
} POINT;

typedef	struct {
	s16	cx;
	s16	cy;
} SIZE;

enum teMenuItemType {
	MIT_U32,
	MIT_S32,
	MIT_U8,
	MIT_SWITCH,	// U8 (0=OFF/1=ON)
};

typedef struct teMenuItem_t {
	enum teMenuItemType type;	// Type
	s16 title_x, title_y;	// Title coordinates
	char* title;			// Title string
	u32 title_attr;			// Title attribute (color)
	u32 attr;				// Value attribute (color)
	s16 x, y, h, v;			// Value's coordinates, and length and height
	s32 nDefault;			// Initial value
	s32 nMin;				// Minimum value
	s32 nMax;				// Maximum value
	s32 nStep;				// Number of steps for changing
	s32 nAccel;				// Step acceleration
	void* pValue;			// Pointer to where number is stored
} teMenuItem;

#define	RGBA32(r, g, b, a)	((((r) & 255) << 24) | (((g) & 255) << 16) | (((b) & 255) << 8) | ((a) & 255))
#define	RBGA32_RED(a)		RGBA32(255,0,0,a)
#define	RBGA32_GREEN(a)		RGBA32(0,255,0,a)
#define	RGBA32_BLUE(a)		RGBA32(0,0,255,a)
#define	RGBA32_YELLOW(a)	RGBA32(255,255,0,a)
#define	RGBA32_CYAN(a)		RGBA32(255,0,255,a)
#define	RGBA32_TURQUOISE(a)	RGBA32(0,255,255,a)
#define	RGBA32_WHITE(a)		RGBA32(255,255,255,a)
#define	RGBA32_GetRValue(rgba)	(u8)((rgba) >> 24)
#define	RGBA32_GetGValue(rgba)	(u8)((rgba) >> 16)
#define	RGBA32_GetBValue(rgba)	(u8)((rgba) >> 8)
#define	RGBA32_GetAValue(rgba)	(u8)(rgba)
#define	elements(array)	(sizeof array / sizeof array[0])

struct teMenuPage_t;
typedef Gfx * (teMenuDrawFunc)(Gfx *, const struct teMenuPage_t *, int, u32, s16, s16);
typedef void (teMenuCtrlFunc)(const struct teMenuPage_t *, int, NUContData *);

typedef struct teMenuPage_t {
	int	x, y, h, v;	// shade region
	char* title;	// title
	teMenuItem* pItems;	// menu items
	int	items;		// menu item count
	teMenuDrawFunc*	draw;
	teMenuCtrlFunc*	ctrl;
} teMenuPage;

/* Global variables */
static RECT aaSci = { 0, 0, SCREEN_WD, SCREEN_HT};	/* Scissoring area */
u16 teControl_repeat = 0;	// Button repeat (Number of times teControl_repeatCheck() is called)
s16 te_no = 0;	// Picture number

//// Texture information
#ifndef	__GNUC__
static Gfx texture_teInfo_dummy_aligner1[] = { gsSPEndDisplayList() };
#endif
static TeInfo teInfo[teSEGMENT_INFO_COUNT]
#ifdef	__GNUC__
__attribute__((aligned (8)))
#endif
;

//// Texture image
#ifndef	__GNUC__
static Gfx texture_C_dummy_aligner1[] = { gsSPEndDisplayList() };
#endif
static u8 teTexture[teSEGMENT_TIMG_COUNT * teSEGMENT_TIMG_SIZE]
#ifdef	__GNUC__
__attribute__((aligned (8)))
#endif
;
//// Texture look up table
#ifndef	__GNUC__
static Gfx texturetlut_dummy_aligner1[] = { gsSPEndDisplayList() };
#endif
static u16 tePalette[teSEGMENT_TLUT_COUNT * teSEGMENT_TLUT_SIZE / sizeof (u16)]
#ifdef	__GNUC__
__attribute__((aligned (8)))
#endif
;

//#define	_DEBUG

int teLoadInfo(int no)
{
#ifdef	_DEBUG
char buf[128];
#endif
	//osPiRawReadIo((u32) teSEGMENT_INFO(no), &teInfo[no].update);
	osPiReadIo((u32) teSEGMENT_INFO(no), &teInfo[no].update);
	osPiWriteIo((u32) teSEGMENT_INFO(no), 0);

#ifdef	_DEBUG
sprintf(buf, "teLoadInfo() ... \n");
osSyncPrintf(buf);
sprintf(buf, "teInfo.update=%d\n", teInfo[no].update);
osSyncPrintf(buf);
#endif

	if (teInfo[no].update == 0) return 0;
#ifdef	_DEBUG
sprintf(buf, "nuPiReadRom(0x%x, 0x%x, %d)\n", (u32) teSEGMENT_INFO(no), (u32) &teInfo[no], teSEGMENT_INFO_SIZE_CORE);
osSyncPrintf(buf);
#endif
	nuPiReadRom((u32) teSEGMENT_INFO(no), &teInfo[no], teSEGMENT_INFO_SIZE_CORE);
#ifdef	_DEBUG
sprintf(buf, "nuPiReadRom(0x%x, 0x%x, %d)\n", (u32) teSEGMENT_TLUT(teInfo[no].dram), (u32) &tePalette[no * 0x100], teSEGMENT_TLUT_SIZE);
osSyncPrintf(buf);
#endif
	nuPiReadRom(teSEGMENT_TLUT(teInfo[no].dram) , &tePalette[no * 0x100], teSEGMENT_TLUT_SIZE);
	{
		double bytesPerPixel = ((double)(4 << teInfo[no].siz) / 8);
		u32 xSize = (u32)(teInfo[no].width * bytesPerPixel + (teInfo[no].siz == G_IM_SIZ_4b ? teInfo[no].width & 1 : 0));
		u32 size = teInfo[no].height * xSize;
		if (size > teSEGMENT_TIMG_SIZE) size = teSEGMENT_TIMG_SIZE;
#ifdef	_DEBUG
sprintf(buf, "nuPiReadRom(0x%x, 0x%x, %d)\n", (u32) teSEGMENT_TIMG(teInfo[no].timg), (u32) &teTexture[no * teSEGMENT_TIMG_SIZE], size);
osSyncPrintf(buf);
#endif
		nuPiReadRom((u32) teSEGMENT_TIMG(teInfo[no].timg), &teTexture[no * teSEGMENT_TIMG_SIZE], size);
	}
	//osPiRawWriteIo((u32) teSEGMENT_INFO(no), 0);
	return 1;
}

//// Variable for menu appearance
// General
static s32 te_xOffset;	// Texture X coordinate
static s32 te_yOffset;	// Texture Y coordinate
static u32 te_xScale;	// Texture's X scale (1/100)
static u32 te_yScale;	// Texture's Y scale (1/100)
static u32 te_xyScale;	// Texture's XY scale (1/100)
static u8 te_rBackground;	// (R) Background color
static u8 te_gBackground;	// (G)
static u8 te_bBackground;	// (B)
static u8 te_aBackground;	// (A)
// Filter
static s32 te_typeFilter;	// Texture Filter (G_TF_POINT | G_TF_AVERAGE | G_TF_BILERP)
// Blender
static s32 te_modeRender;	// Rendering mode
// Color Combiner
static s32 te_modeCombine;	// Combine mode
static u8 te_rPrimitive;	// (R) Primitive color
static u8 te_gPrimitive;	// (G)
static u8 te_bPrimitive;	// (B)
static u8 te_aPrimitive;	// (A)
static u8 te_rEnvironment;	// (R) Environment color
static u8 te_gEnvironment;	// (G)
static u8 te_bEnvironment;	// (B)
static u8 te_aEnvironment;	// (A)
#ifndef	NU_DEB_CON_TEXT_LIGHTBLUE
#define	NU_DEB_CON_TEXT_LIGHTBLUE	 NU_DEB_CON_TEXT_LIGTHBLUE	// for Spell miss
#endif
#define	teMenuTitleColor	NU_DEB_CON_TEXT_CYAN
#define	teMenuValueColor	NU_DEB_CON_TEXT_LIGHTWHITE

static u8 te_osVISF_GAMMA;	// 0=OFF/1=ON
static u8 te_osVISF_GAMMA_DITHER;
static u8 te_osVISF_DIVOT;
static u8 te_osVISF_DITHER_FILTER;

static const teMenuItem teMenu_itemsGeneral[] = {
	{MIT_S32, 1, 2, "Offset X,Y", teMenuTitleColor, teMenuValueColor, 13, 2, 5, 1, 0, -640, +640, 1, 2, &te_xOffset},
	{MIT_S32, 13+5, 2, ",", teMenuTitleColor, teMenuValueColor, 13+6, 2, 5, 1, 0, -480, +480, 1, 2, &te_yOffset},
	{MIT_U32, 1, 3, "Scale  X,Y", teMenuTitleColor, teMenuValueColor, 13, 3, 5, 1, 100, 10, 1000, 10, 2, &te_xScale},
	{MIT_U32, 13+5, 3, ",", teMenuTitleColor, teMenuValueColor, 13+6, 3, 5, 1, 100, 10, 1000, 10, 2, &te_yScale},
	{MIT_U32, 1, 4, "Scale  X&Y", teMenuTitleColor, teMenuValueColor, 13, 4, 5, 1, 100, 10, 1000, 10, 2, &te_xyScale},
	{MIT_U8, 1, 5, "Back Ground", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTRED, 13, 5, 3, 1, 0x40, 0, 255, 1, 2, &te_rBackground},
	{MIT_U8, 1, 5, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTGREEN, 13+4, 5, 3, 1, 0x80, 0, 255, 1, 2, &te_gBackground},
	{MIT_U8, 1, 5, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTBLUE, 13+4+4, 5, 3, 1, 0x50, 0, 255, 1, 2, &te_bBackground},
	{MIT_U8, 1, 5, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTWHITE, 13+4+4+4, 5, 3, 1, 0xb0, 0, 255, 1, 2, &te_aBackground},
};
static const teMenuItem teMenu_itemsFilter[] = {
	{MIT_S32, 1, 2, "Filter", teMenuTitleColor, teMenuValueColor, 8, 2, 12, 1, 0, 0, 2, 1, 0, &te_typeFilter},
};
static const teMenuItem teMenu_itemsCombiner[] = {
	{MIT_S32, 1, 2, "Mode", teMenuTitleColor, teMenuValueColor, 13, 2, 15, 1, 0, 0, 2, 1, 0, &te_modeCombine},
	{MIT_U8, 1, 3, "Primitive", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTRED, 13, 3, 3, 1, 255, 0, 255, 1, 2, &te_rPrimitive},
	{MIT_U8, 1, 3, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTGREEN, 13+4, 3, 3, 1, 255, 0, 255, 1, 2, &te_gPrimitive},
	{MIT_U8, 1, 3, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTBLUE, 13+4+4, 3, 3, 1, 255, 0, 255, 1, 2, &te_bPrimitive},
	{MIT_U8, 1, 3, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTWHITE, 13+4+4+4, 3, 3, 1, 255, 0, 255, 1, 2, &te_aPrimitive},
	{MIT_U8, 1, 4, "Environment", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTRED, 13, 4, 3, 1, 0, 0, 255, 1, 2, &te_rEnvironment},
	{MIT_U8, 1, 4, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTGREEN, 13+4, 4, 3, 1, 0, 0, 255, 1, 2, &te_gEnvironment},
	{MIT_U8, 1, 4, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTBLUE, 13+4+4, 4, 3, 1, 0, 0, 255, 1, 2, &te_bEnvironment},
	{MIT_U8, 1, 4, "", teMenuTitleColor, NU_DEB_CON_TEXT_LIGHTWHITE, 13+4+4+4, 4, 3, 1, 0, 0, 255, 1, 2, &te_aEnvironment},
};
static const teMenuItem teMenu_itemsBlender[] = {
	{MIT_S32, 1, 2, "Render Mode", teMenuTitleColor, teMenuValueColor, 13, 2, 20, 1, 0, 0, 2, 1, 0, &te_modeRender},
};
static const teMenuItem teMenu_itemsVISF[] = {
	{MIT_SWITCH, 1, 2, "GAMMA        ", teMenuTitleColor, teMenuValueColor, 16, 2, 3, 1, 0, 0, 1, 1, 0, &te_osVISF_GAMMA},
	{MIT_SWITCH, 1, 3, "GAMMA DITHER ", teMenuTitleColor, teMenuValueColor, 16, 3, 3, 1, 0, 0, 1, 1, 0, &te_osVISF_GAMMA_DITHER},
	{MIT_SWITCH, 1, 4, "DIVOT        ", teMenuTitleColor, teMenuValueColor, 16, 4, 3, 1, 0, 0, 1, 1, 0, &te_osVISF_DIVOT},
	{MIT_SWITCH, 1, 5, "DITHER FILTER", teMenuTitleColor, teMenuValueColor, 16, 5, 3, 1, 0, 0, 1, 1, 0, &te_osVISF_DITHER_FILTER},
};

// Default function of changing menu's value
// <<< メニュー数値変更のデフォルト処理関数 >>>
void teMenu_ctrlValues(const teMenuPage* page, int item_no, NUContData* contdata);
// Default function of drawing menu's value
// <<< メニュー数値表示のデフォルト処理関数 >>>
Gfx* teMenu_drawValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y);

Gfx* teMenu_drawGeneralValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y);
Gfx* teMenu_drawFilterValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y);
Gfx* teMenu_drawCombinerValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y);
Gfx* teMenu_drawBlenderValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y);

static const teMenuPage teMenu_pages[] = {
	{0, 0, 29, 7, "General", (teMenuItem*) teMenu_itemsGeneral, elements(teMenu_itemsGeneral), teMenu_drawGeneralValues, teMenu_ctrlValues},
	{0, 0, 21, 4, "Filter", (teMenuItem*) teMenu_itemsFilter, elements(teMenu_itemsFilter), teMenu_drawFilterValues, teMenu_ctrlValues},
	{0, 0, 29, 6, "Combiner", (teMenuItem*) teMenu_itemsCombiner, elements(teMenu_itemsCombiner), teMenu_drawCombinerValues, teMenu_ctrlValues},
	{0, 0, 34, 4, "Blender", (teMenuItem*) teMenu_itemsBlender, elements(teMenu_itemsBlender), teMenu_drawBlenderValues, teMenu_ctrlValues},
	{0, 0, 29, 7, "osViSetSpecialFeautures", (teMenuItem*) teMenu_itemsVISF, elements(teMenu_itemsVISF), teMenu_drawValues, teMenu_ctrlValues},
};

#define	teMenu_maxPage	elements(teMenu_pages)
static int teMenu_page = 0;
static int teMenu_cursor[teMenu_maxPage];
int teMenu_disp = !0;


//// Draw semi-transparent rectangle
//// <<< 半透明の矩形を描画する >>>
Gfx* teDrawFillRectangle(Gfx* glp, s16 x, s16 y, s16 h, s16 v, u32 rgba32)
{
	u32 r = (rgba32 >> 24) & 255;
	u32 g = (rgba32 >> 16) & 255;
	u32 b = (rgba32 >> 8) & 255;
	u32 a = (rgba32 >> 0) & 255;
	gDPPipeSync(glp++);

	gDPSetCycleType(glp++, G_CYC_1CYCLE);
	gDPSetColorDither(glp++, G_CD_DISABLE);
	gDPSetAlphaDither(glp++, G_AD_DISABLE);
	gDPSetAlphaCompare(glp++, G_AC_NONE);
	gDPSetRenderMode(glp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
	gDPSetCombineMode (glp++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
	gDPSetCombineKey(glp++, G_CK_NONE);
	gDPSetScissor(glp++, G_SC_NON_INTERLACE, 0, 0, 320, 240);

	gDPSetPrimColor(glp++, 0, 0, r, g, b, a);

	gDPFillRectangle(glp++, x, y, x + h - 1, y + v - 1);

	gDPPipeSync(glp++);
	return glp;
}

//// Mask background with Shade
//// <<< 背景をShadeでマスク >>>
Gfx* teDrawShadeRectangle(Gfx* glp, s16 x, s16 y, s16 h, s16 v)
{
	return teDrawFillRectangle(glp, x, y, h, v, 0x000000a0);
}

//// Mask background with Hilight
//// <<< 背景をHilightでマスク >>>
Gfx* teDrawHilightRectangle(Gfx* glp, s16 x, s16 y, s16 h, s16 v)
{
	return teDrawFillRectangle(glp, x, y, h, v, 0xa0a0a0a0);
}

//// Mask background with Smooth Blink Hilight
//// <<< 背景をスムースブリンクなハイライトでマスクする >>>
Gfx* teDrawSmoothBlinkHilightRectangle(Gfx* glp, s16 x, s16 y, s16 h, s16 v)
{
	const int max = 128;
	const int speed = 4;
	const int limit = max / speed;
	static s16 blink = 0;
	u8 a;
	if (++blink >= limit) blink = 0;
	a = blink >= (limit / 2) ? limit - blink : blink;
	return teDrawFillRectangle(glp, x, y, h, v, 0xa0a0a080 + a * speed);
}

//// Display general menu values
//// <<< 一般メニューの値の表示 >>>
Gfx* teMenu_drawGeneralValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y)
{
	if (item_no == 2 || item_no == 3 || item_no == 4) {
		const teMenuItem* pItem = &page->pItems[item_no];
		char buf[32];
		buf[0] = '\0';
		if (item_no == 2 || item_no == 3 || item_no == 4) {
			// Display decimal point
			// <<< 小数点表示 >>>
			sprintf(buf, "%02d.%02d", (*(u32*) pItem->pValue) / 100, (*(u32*) pItem->pValue) % 100);
		}
		nuDebConTextPos(wnd, x + page->x + pItem->x, y + page->y + pItem->y);
		nuDebConTextColor(wnd, pItem->attr);
		nuDebConCPuts(wnd, buf);
	} else {
		glp = teMenu_drawValues(glp, page, item_no, wnd, x, y);	// Default process
	}
	return glp;
}

//// Display filter menu values
//// <<< フィルタメニューの値の表示 >>>
Gfx* teMenu_drawFilterValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y)
{
	const teMenuItem* pItem = &page->pItems[item_no];
	char buf[32];
	buf[0] = '\0';
	if (item_no == 0) {
		static const char* teFilterTypeStrings[] = {
			"G_TF_POINT",
			"G_TF_AVERAGE",
			"G_TF_BILERP",
		};
		sprintf(buf, "%s", teFilterTypeStrings[te_typeFilter]);
	} else {
		return teMenu_drawValues(glp, page, item_no, wnd, x, y);
	}
	if (*buf) {
		nuDebConTextPos(wnd, x + page->x + pItem->x, y + page->y + pItem->y);
		nuDebConTextColor(wnd, pItem->attr);
		nuDebConCPuts(wnd, buf);
	}
	return glp;
}

//// Display combiner menu values
//// <<< コンバイナメニューの値の表示 >>>
Gfx* teMenu_drawCombinerValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y)
{
	const teMenuItem* pItem = &page->pItems[item_no];
	char buf[32];
	buf[0] = '\0';
	if (item_no == 0) {
		static const char* teCombineModeStrings[] = {
			"G_CC_DECALRGBA",
			"G_CC_PRIMITIVE",
			"G_CC_BLENDPE",
		};
		sprintf(buf, "%s", teCombineModeStrings[te_modeCombine]);
	} else {
		return teMenu_drawValues(glp, page, item_no, wnd, x, y);
	}
	if (*buf) {
		nuDebConTextPos(wnd, x + page->x + pItem->x, y + page->y + pItem->y);
		nuDebConTextColor(wnd, pItem->attr);
		nuDebConCPuts(wnd, buf);
	}
	return glp;
}

//// Display blender menu values
//// <<< ブレンダーメニューの値の表示 >>>
Gfx* teMenu_drawBlenderValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y)
{
	const teMenuItem* pItem = &page->pItems[item_no];
	char buf[32];
	buf[0] = '\0';
	if (item_no == 0) {
		static const char* teRenderModeStrings[] = {
			"G_RM_AA_ZB_OPA_SURF",
			"G_RM_AA_ZB_XLU_SURF",
			"G_RM_AA_ZB_TEX_EDGE",
		};
		sprintf(buf, "%s", teRenderModeStrings[te_modeRender]);
	} else {
		return teMenu_drawValues(glp, page, item_no, wnd, x, y);
	}
	if (*buf) {
		nuDebConTextPos(wnd, x + page->x + pItem->x, y + page->y + pItem->y);
		nuDebConTextColor(wnd, pItem->attr);
		nuDebConCPuts(wnd, buf);
	}
	return glp;
}

//// Default process for displaying menu's numeric values
//// <<< メニューの数値表示のデフォルト処理 >>>
Gfx* teMenu_drawValues(Gfx* glp, const teMenuPage* page, int item_no, u32 wnd, s16 x, s16 y)
{
	teMenuItem* pItem = &page->pItems[item_no];
	char buf[32];
	char form[32];
	buf[0] = '\0';
	if (pItem->type == MIT_U32) {
		u32 value = *(u32*) pItem->pValue;
		sprintf(form, "%%%du", pItem->h);
		sprintf(buf, form, value);
	} else if (pItem->type == MIT_S32) {
		s32 value = *(s32*) pItem->pValue;
		sprintf(form, "%%%dd", pItem->h);
		sprintf(buf, form, value);
	} else if (pItem->type == MIT_U8) {
		u8 value = *(u8*) pItem->pValue;
		sprintf(form, "%%0%dd", pItem->h);
		sprintf(buf, form, value);
	} else if (pItem->type == MIT_SWITCH) {
		u8 value = *(u8*) pItem->pValue;
		sprintf(buf, "%s", value ? "ON" : "OFF");
	}
	if (*buf) {
		nuDebConTextPos(wnd, x + page->x + pItem->x, y + page->y + pItem->y);
		nuDebConTextColor(wnd, pItem->attr);
		nuDebConCPuts(wnd, buf);
	}
	return glp;
}

//// Default process for changing numeric values with key input
//// <<< キー入力による数値変更のデフォルト処理 >>>
void teMenu_ctrlValues(const teMenuPage* page, int item_no, NUContData* contdata)
{
	teMenuItem* pItem = &page->pItems[item_no];
	static u32 timer = 0;
	float stick_y = (float) contdata->stick_y / 80;	// -1.00～+1.00
//	osSyncPrintf("stick_y = %f\n", stick_y);
	timer++;
	if (pItem->type == MIT_U32) {
		u32* p = (u32*) pItem->pValue;
		if (teControl_repeat & START_BUTTON) {
			(*p) = (u32) pItem->nDefault;
		} else if (teControl_repeat & A_BUTTON) {
			(*p) += pItem->nStep;
		} else if (teControl_repeat & B_BUTTON) {
			(*p) -= pItem->nStep;
		} else if (teControl_repeat & U_CBUTTONS) {
			(*p) = (u32) pItem->nMax;
		} else if (teControl_repeat & D_CBUTTONS) {
			(*p) = (u32) pItem->nMin;
		} else if (fabs(stick_y) >= 0.25f) {
			// Count from above 25.0%
			// <<< 25.0%以上からカウント >>>
			if (pItem->nAccel == 0 && (timer % 10) == 0) {
				(*p) += (s32)(stick_y < 0 ? -pItem->nStep : +pItem->nStep);
			} else {
				(*p) += (s32)(pItem->nAccel * stick_y) * pItem->nStep;
			}
		}
		if ((s32) *p < (s32) pItem->nMin) *p = pItem->nMin;
		if (*p > (u32) pItem->nMax) *p = pItem->nMax;
	} else if (pItem->type == MIT_S32) {
		s32* p = (s32*) pItem->pValue;
		if (teControl_repeat & START_BUTTON) {
			(*p) = (s32) pItem->nDefault;
		} else if (teControl_repeat & A_BUTTON) {
			(*p) += pItem->nStep;
		} else if (teControl_repeat & B_BUTTON) {
			(*p) -= pItem->nStep;
		} else if (teControl_repeat & U_CBUTTONS) {
			(*p) = (s32) pItem->nMax;
		} else if (teControl_repeat & D_CBUTTONS) {
			(*p) = (s32) pItem->nMin;
		} else  if (fabs(stick_y) >= 0.25f) {
			if (pItem->nAccel == 0 && (timer % 10) == 0) {
				(*p) += (s32)(stick_y < 0 ? -pItem->nStep : +pItem->nStep);
			} else {
				(*p) += (s32)(pItem->nAccel * stick_y) * pItem->nStep;
			}
		}
		if (*p < (s32) pItem->nMin) *p = pItem->nMin;
		if (*p > (s32) pItem->nMax) *p = pItem->nMax;
	} else if (pItem->type == MIT_U8) {
		u8* p = (u8*) pItem->pValue;
		if (teControl_repeat & START_BUTTON) {
			(*p) = (u8) pItem->nDefault;
		} else if (teControl_repeat & A_BUTTON) {
			(*p) += pItem->nStep;
		} else if (teControl_repeat & B_BUTTON) {
			(*p) -= pItem->nStep;
		} else if (teControl_repeat & U_CBUTTONS) {
			(*p) = (u8) pItem->nMax;
		} else if (teControl_repeat & D_CBUTTONS) {
			(*p) = (u8) pItem->nMin;
		} else if (fabs(stick_y) >= 0.25f) {
			s32 value;
			if (pItem->nAccel == 0 && (timer % 10) == 0) {
				value = *p + (s32)(stick_y < 0 ? -pItem->nStep : +pItem->nStep);
			} else {
				value = *p + (s32)(pItem->nAccel * stick_y) * pItem->nStep;
			}
			if (value < (s32) pItem->nMin) *p = (u8) pItem->nMin;
			else if (value > (s32) pItem->nMax) *p = (u8) pItem->nMax;
			else *p = (u8) value;
		}
	} else if (pItem->type == MIT_SWITCH) {
		u8* p = (u8*) pItem->pValue;
		if (teControl_repeat & START_BUTTON) {
			(*p) = (u8) pItem->nDefault;
		} else if (teControl_repeat & (A_BUTTON | B_BUTTON)) {
			(*p) = (*p) ? 0 : 1;
		} else if ((teControl_repeat & U_CBUTTONS) || stick_y < -0.25f) {
			(*p) = 1;
		} else if ((teControl_repeat & D_CBUTTONS) || stick_y > +0.25f) {
			(*p) = 0;
		}
	}
}


/* メニューの内容をINFOにコピーする */
void teCopyMenuToInfo(u16 no)
{
	teInfo[no].x = te_xOffset;
	teInfo[no].y = te_yOffset;
	teInfo[no].xScale = te_xScale;
	teInfo[no].yScale = te_yScale;
	teInfo[no].filter = te_typeFilter;
	teInfo[no].combiner = te_modeCombine;
	teInfo[no].render = te_modeRender;
	teInfo[no].rgbaP = RGBA32(te_rPrimitive, te_gPrimitive, te_bPrimitive, te_aPrimitive);
	teInfo[no].rgbaE = RGBA32(te_rEnvironment, te_gEnvironment, te_bEnvironment, te_aEnvironment);
}

/* Copy teInfo[no] to menu */
/* <<< INFOの内容をメニューにコピーする >>> */
void teCopyInfoToMenu(u16 no)
{
	te_xOffset = teInfo[no].x;
	te_yOffset = teInfo[no].y;
	te_xScale = teInfo[no].xScale;
	te_yScale = teInfo[no].yScale;
	te_typeFilter = teInfo[no].filter;
	te_modeCombine = teInfo[no].combiner;
	te_modeRender = teInfo[no].render;
	te_rPrimitive = RGBA32_GetRValue(teInfo[no].rgbaP);
	te_gPrimitive = RGBA32_GetGValue(teInfo[no].rgbaP);
	te_bPrimitive = RGBA32_GetBValue(teInfo[no].rgbaP);
	te_aPrimitive = RGBA32_GetAValue(teInfo[no].rgbaP);
	te_rEnvironment = RGBA32_GetRValue(teInfo[no].rgbaE);
	te_gEnvironment = RGBA32_GetGValue(teInfo[no].rgbaE);
	te_bEnvironment = RGBA32_GetBValue(teInfo[no].rgbaE);
	te_aEnvironment = RGBA32_GetAValue(teInfo[no].rgbaE);
}

/* Draw menu */
/* <<< メニューを描画 >>> */
Gfx* teDrawMenu(Gfx* glp, s16 x, s16 y)
{
	int i;
	const u32 wnd = NU_DEB_CON_WINDOW0;
	const teMenuPage* page = &teMenu_pages[teMenu_page];
	nuDebConClear(wnd);
	nuDebConTextColor(wnd, NU_DEB_CON_TEXT_LIGHTYELLOW);
	nuDebConTextAttr(wnd, NU_DEB_CON_ATTR_NORMAL);

	if (!teMenu_disp) return glp;

	nuDebConTextPos(wnd, x + page->x, y + page->y);
	nuDebConCPuts(wnd, page->title);
	{
		// Draw picture number
		// <<< ピクチャー番号の表示 >>>
		char buf[8];
		nuDebConTextPos(wnd, x + page->x + page->h - 2, y + page->y);
		sprintf(buf, "%d", te_no);
		nuDebConCPuts(wnd, buf);
	}
	glp = teDrawShadeRectangle(glp, (x + page->x) * 8, (y + page->y) * 8, page->h * 8, page->v * 8);

	for (i = 0; i < page->items; i++) {
		const teMenuItem* item = &page->pItems[i];
		if (teMenu_cursor[teMenu_page] == i) {
			glp = teDrawSmoothBlinkHilightRectangle(glp, (x + page->x + item->x) * 8, (y + page->y + item->y) * 8, item->h * 8, item->v * 8);
		}
		nuDebConTextPos(wnd, x + page->x + item->title_x, y + page->y + item->title_y);
		nuDebConTextColor(wnd, item->title_attr);
		nuDebConCPuts(wnd, item->title);
		if (page->draw) glp = page->draw(glp, page, i, wnd, x, y);
	}
	return glp;
}


u16 teControl_repeatCheck(NUContData* contdata)
{
	static u16 repeat = 0xffff;
	static u32 counter = 0;
	const int repeat_start = 30;
	const int repeat_loop = 3;
	if (contdata[0].button != repeat) {
		counter = 0;
		repeat = contdata[0].trigger;
		return repeat;
	} else {
		++counter;
		if (counter == repeat_start) return repeat;
		if (counter >= (repeat_start + repeat_loop)) counter = repeat_start - 1;
	}
	return 0;
}

void teControl(NUContData* contdata)
{
	// Make key repeat
	// <<< キーリピートを作る >>>
	teControl_repeat = teControl_repeatCheck(contdata);
	if (contdata[0].trigger & Z_TRIG) {
		teMenu_disp = !teMenu_disp;
	}
	if (!teMenu_disp) return;
	if (teControl_repeat & L_TRIG) {
		if (--teMenu_page < 0) teMenu_page = teMenu_maxPage - 1;
	}
	if (teControl_repeat & R_TRIG) {
		if (++teMenu_page >= teMenu_maxPage) teMenu_page = 0;
	}
	{
		const teMenuPage* page = &teMenu_pages[teMenu_page];
		const teMenuItem* pItems = page->pItems;
		int items = page->items;
		int cursor = teMenu_cursor[teMenu_page];
		if (teControl_repeat & U_JPAD) {
			int i, item_no = cursor, yKeep = pItems[cursor].y, xKeep = pItems[cursor].x;
			// Search for end of line in previous step
			// <<< 一段前の行の末尾を検索 >>>
			for (i = 1; i <= items; i++) {
				item_no = (items + cursor - i) % items;
				if (pItems[item_no].y != yKeep) break;
			}
			// Search for same X coordinate in same line
			// <<< 同じ行の同じＸ座標を検索 >>>
			cursor = item_no;
			yKeep = pItems[cursor].y;
			for (i = 0; i < items; i++) {
				item_no = (items + cursor - i) % items;
				if (pItems[item_no].y == yKeep && pItems[item_no].x == xKeep) {
					cursor = item_no;
					break;
				}
			}
			teMenu_cursor[teMenu_page] = cursor;
		}
		if (teControl_repeat & D_JPAD) {
			int i, item_no = cursor, yKeep = pItems[cursor].y, xKeep = pItems[cursor].x;
			// Search for end of line in previous step
			// <<< 一段前の行の末尾を検索 >>>
			for (i = 1; i <= items; i++) {
				item_no = (cursor + i) % items;
				if (pItems[item_no].y != yKeep) break;
			}
			// Search for same X coordinate in same line
			// <<< 同じ行の同じＸ座標を検索 >>>
			cursor = item_no;
			yKeep = pItems[cursor].y;
			for (i = 0; i < items; i++) {
				item_no = (items + cursor - i) % items;
				if (pItems[item_no].y == yKeep && pItems[item_no].x == xKeep) {
					cursor = item_no;
					break;
				}
			}
			teMenu_cursor[teMenu_page] = cursor;
		}
		if (teControl_repeat & L_JPAD) {
			int i, item_no = cursor, yKeep = pItems[cursor].y;
			for (i = 1; i <= items; i++) {
				item_no = (items + cursor - i) % items;
				if (pItems[item_no].y == yKeep) break;
			}
			teMenu_cursor[teMenu_page] = item_no;
		}
		if (teControl_repeat & R_JPAD) {
			int i, item_no = cursor, yKeep = pItems[cursor].y;
			for (i = 1; i <= items; i++) {
				item_no = (cursor + i) % items;
				if (pItems[item_no].y == yKeep) break;
			}
			teMenu_cursor[teMenu_page] = item_no;
		}
		/* change picture on C button */
		/* <<< Cボタンの←→でピクチャー切り替え >>> */
		if (teControl_repeat & L_CBUTTONS) {
			if (--te_no < 0) te_no = teSEGMENT_INFO_COUNT - 1;
			/* copy teInfo[te_no] information to menu */
			/* <<< INFOの内容をメニューにコピーする >>> */
			teCopyInfoToMenu(te_no);
		}
		if (teControl_repeat & R_CBUTTONS) {
			if (++te_no >= teSEGMENT_INFO_COUNT) te_no = 0;
			/* copy teInfo[te_no] information to menu */
			/* <<< INFOの内容をメニューにコピーする >>> */
			teCopyInfoToMenu(te_no);
		}
		if (page->ctrl) page->ctrl(page, teMenu_cursor[teMenu_page], contdata);
		/* copy menu status to teInfo[te_no] */
		/* <<< メニューの内容をINFOにコピーする >>> */
		teCopyMenuToInfo(te_no);
	}
}

void teInit()
{
	int i, j;
	teMenu_disp = !0;
	teMenu_page = 0;
	for (i = 0; i < teMenu_maxPage; i++) {
		// Initialize cursor position
		// <<< カーソル位置の初期化 >>>
		teMenu_cursor[i] = 0;
		// Initialize menu values
		// <<< メニュー値の初期化 >>>
		for (j = 0; j < teMenu_pages[i].items; j++) {
			teMenuItem* pItem = &teMenu_pages[i].pItems[j];
			switch (pItem->type) {
			case MIT_U32: *(u32*) pItem->pValue = (u32) pItem->nDefault; break;
			case MIT_S32: *(s32*) pItem->pValue = (s32) pItem->nDefault; break;
			case MIT_SWITCH:
			case MIT_U8: *(u8*) pItem->pValue = (u8) pItem->nDefault; break;
			}
		}
	}
	// Initialize display texture number
	// <<< 初期選択画像 >>>
	te_no = 0;
	for (i = 0; i < teSEGMENT_INFO_COUNT; i++) {
		// Initialize teInfo[i] from menu
		// INFO情報もメニューに合わせて初期化
		teCopyMenuToInfo(i);
	}
	nuDebConWindowSet(NU_DEB_CON_WINDOW0, 0, 0, 40, 30);
	nuDebConClear(NU_DEB_CON_WINDOW0);
//	osSyncPrintf("teInit()...done\n");
}

// Draw background
// <<< 背景の描画 >>>
Gfx* teDrawBackground(Gfx* glp)
{
	u32 bgcol = te_rBackground << 24 | te_gBackground << 16 | te_bBackground << 8 | te_aBackground;
	glp = teDrawFillRectangle(glp, 0, 0, 320, 240, bgcol);
//	glp = teDrawFillRectangle(glp, 0, 0, 320, 240, 0x408050b0);
	return glp;
}

/* Draw texture from number */
/* <<< テクスチャイメージを表示する >>> */
Gfx* teDrawTexture(Gfx* glp, int no)
{
	float xyScale, xScale, yScale, widthScaled, heightScaled;
	s16 x = 0, y = 0;
//	s16 vx = 0, vy = 0;
	TeInfo* pInfo = &teInfo[no];
	teLoadInfo(no);
	if ((pInfo->width * pInfo->height) == 0) return glp;
	xyScale = (float) te_xyScale / 100;
	xScale = ((float) pInfo->xScale / 100) * xyScale;
	yScale = ((float) pInfo->yScale / 100) * xyScale;
	widthScaled = pInfo->width * xScale;
	heightScaled = pInfo->height * yScale;
	x += pInfo->x;
	y += pInfo->y;
#if 0
	if (widthScaled < 320) {
		x += vx * ((widthScaled / 2) + (320 - (int) widthScaled)) / 128;
	} else {
		x += vx * (int) widthScaled / 128;
	}
	if (heightScaled < 240) {
		y += vy * ((heightScaled / 2) + (240 - (int) heightScaled)) / 128;
	} else {
		y += vy * (int) heightScaled / 128;
	}
#endif
	x += (320 - (int) widthScaled) / 2;
	y += (240 - (int) heightScaled) / 2;
	x += pInfo->ox * xScale;
	y += pInfo->oy * yScale;
	{
		u32 flag = (te_osVISF_GAMMA) ? OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF;
		flag |= (te_osVISF_GAMMA_DITHER) ? OS_VI_GAMMA_DITHER_ON : OS_VI_GAMMA_DITHER_OFF;
		flag |= (te_osVISF_DIVOT) ? OS_VI_DIVOT_ON : OS_VI_DIVOT_OFF;
		flag |= (te_osVISF_DITHER_FILTER) ? OS_VI_DITHER_FILTER_ON : OS_VI_DITHER_FILTER_OFF;
		osViSetSpecialFeatures(flag);
	}
	gDPPipeSync(glp++);
	gDPSetCycleType(glp++, G_CYC_1CYCLE);
//	gDPSetCycleType(glp++, G_CYC_COPY);
	{
		static const u32 teRenderModeValues[] = {
			G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_TEX_EDGE,
		};
		static const u32 teRenderModeValues2[] = {
			G_RM_AA_ZB_OPA_SURF2, G_RM_AA_ZB_XLU_SURF2, G_RM_AA_ZB_TEX_EDGE2,
		};
		if (pInfo->render >= 0 && pInfo->render < 3) {
			gDPSetRenderMode(glp++, teRenderModeValues[pInfo->render], teRenderModeValues2[pInfo->render]);
		} else {
		//	gDPSetRenderMode(glp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
			gDPSetRenderMode(glp++, G_RM_NOOP, G_RM_NOOP2);
		}
	}
	gDPSetTexturePersp(glp++, G_TP_NONE);
	{
		/* Setting combine mode */
		/* <<< コンバインモードの設定 >>> */
#define	teCombine_c0(a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0)	{\
	GCCc0w0(G_CCMUX_##a0, G_CCMUX_##c0,	G_ACMUX_##Aa0, G_ACMUX_##Ac0),\
	GCCc0w1(G_CCMUX_##b0, G_CCMUX_##d0,	G_ACMUX_##Ab0, G_ACMUX_##Ad0)\
}
#define	teCombine_c1(a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)	{\
	GCCc1w0(G_CCMUX_##a1, G_CCMUX_##c1),\
	GCCc1w1(G_CCMUX_##b1, G_ACMUX_##Aa1, G_ACMUX_##Ac1, G_CCMUX_##d1, G_ACMUX_##Ab1, G_ACMUX_##Ad1)\
}
#define	teCombineMode_c0(cc)	teCombine_c0(cc)
#define	teCombineMode_c1(cc)	teCombine_c1(cc)
		struct teCombineMode { u32 w0, w1; };
		static const struct teCombineMode teCombineModeValues[] = {
			teCombineMode_c0(G_CC_DECALRGBA),
			teCombineMode_c0(G_CC_PRIMITIVE),
			teCombineMode_c0(G_CC_BLENDPE),
		};
		static const struct teCombineMode teCombineModeValues2[] = {
			teCombineMode_c1(G_CC_DECALRGBA),
			teCombineMode_c1(G_CC_PRIMITIVE),
			teCombineMode_c1(G_CC_BLENDPE),
		};
		if (pInfo->combiner >= 0 && pInfo->combiner < 3) {
//			gDPSetCombineMode(glp++, teCombineModeValues[pInfo->combiner], teCombineModeValues[pInfo->combiner]);
			gDPSetCombine(glp++,
				teCombineModeValues[pInfo->combiner].w0 |
				teCombineModeValues2[pInfo->combiner].w0,
				teCombineModeValues[pInfo->combiner].w1 |
				teCombineModeValues2[pInfo->combiner].w1);
		} else {
			gDPSetCombineMode(glp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
		}
		/* Primitive color settings */
		/* <<< プリミティブカラーの設定 >>> */
		gDPSetPrimColor(glp++, 1 << 8, 1 << 8,
			RGBA32_GetRValue(pInfo->rgbaP),
			RGBA32_GetGValue(pInfo->rgbaP),
			RGBA32_GetBValue(pInfo->rgbaP),
			RGBA32_GetAValue(pInfo->rgbaP));
		/* Environment color settings */
		/* <<< 環境カラーの設定 >>> */
		gDPSetEnvColor(glp++,
			RGBA32_GetRValue(pInfo->rgbaE),
			RGBA32_GetGValue(pInfo->rgbaE),
			RGBA32_GetBValue(pInfo->rgbaE),
			RGBA32_GetAValue(pInfo->rgbaE));
	}
	{
		/* Texture filter type settings */
		/* <<< テクスチャフィルタのタイプを設定 >>> */
		static const u32 teFilterTypeValues[] = {
			G_TF_POINT, G_TF_AVERAGE, G_TF_BILERP,
		};
		if (pInfo->filter >= 0 && pInfo->filter < 3) {
			gDPSetTextureFilter(glp++, teFilterTypeValues[pInfo->filter]);
		} else {
			gDPSetTextureFilter(glp++, G_TF_POINT);
		}
	}
	/* Texture filter settings */
	/* <<< ディテールタイプを設定 >>> */
	gDPSetTextureDetail(glp++, G_TD_CLAMP);
	/* Color space convert mode settings */
	/* <<< カラー空間の変換モードを設定 >>> */
	gDPSetTextureConvert(glp++, G_TC_FILT);
	/* Alpha value compare mode settings */
	/* <<< アルファ値の比較モードを設定 >>> */
	gDPSetAlphaCompare(glp++, G_AC_NONE);
	/* Color data dithering mode settings */
	/* <<< カラーデータのディザリングモードを設定 >>> */
	gDPSetColorDither(glp++, G_CD_DISABLE);
	/* Alpha value dithering mode settings */
	/* <<< アルファ値のディザリングモードを設定 >>> */
	gDPSetAlphaDither(glp++, G_AD_DISABLE);
	/* Palette settings */
	/* <<< パレットの設定 >>> */
	if (pInfo->fmt == G_IM_FMT_CI) {
		u16 *pTlut = &tePalette[no * (teSEGMENT_TLUT_SIZE / sizeof(u16))];
		if (pInfo->type == 0) {
			gDPSetTextureLUT(glp++, G_TT_RGBA16);	/* TLUT is 16bitRGBA */
		} else if (pInfo->type == 1) {
			gDPSetTextureLUT(glp++, G_TT_IA16);	/* TLUT is 16bitIA */
		}
		if (pInfo->siz == G_IM_SIZ_8b) {
			gDPLoadTLUT_pal256(glp++, pTlut);
		} else if (pInfo->siz == G_IM_SIZ_4b) {
			gDPLoadTLUT_pal16(glp++, pInfo->pal, &pTlut[pInfo->pal * 16]);
		}
	}
	{
		// Position to scan texture data
		// <<< テクスチャデータをスキャンする位置 >>>
		POINT pt;
		// Sizes of cut texture data and all texture data
		// <<< 切り出したテクスチャデータのサイズと全テクスチャデータのサイズ >>>
		SIZE size, max;
		// Draw position and size
		// <<< 描画位置とサイズ >>>
		float xDraw, yDraw, widthDraw, heightDraw;
		RECT rectRead, rectDraw;
		u8* pImg = &teTexture[no * teSEGMENT_TIMG_SIZE];
		max.cy   = pInfo->height;
		for (pt.y = 0, yDraw = 0.0; pt.y < max.cy; pt.y += size.cy, yDraw += heightDraw) {
			size.cy = (max.cy - pt.y) < 32 ? (max.cy - pt.y) : 32;
			heightDraw = size.cy * yScale;
			rectDraw.top = (int)((y + yDraw) * 4);
			rectDraw.bottom = (int)((y + yDraw + heightDraw) * 4);
			if (aaSci.top > (rectDraw.bottom / 4)) continue;
			if (aaSci.bottom < (rectDraw.top / 4)) break;
			max.cx = pInfo->width;
			for (pt.x = 0, xDraw = 0.0; pt.x < max.cx; pt.x += size.cx, xDraw += widthDraw) {
				size.cx = (max.cx - pt.x) < 32 ? (max.cx - pt.x) : 32;
				widthDraw = size.cx * xScale;
				rectDraw.left = (int)((x + xDraw) * 4);
				rectDraw.right = (int)((x + xDraw + widthDraw) * 4);
				if (aaSci.left > (rectDraw.right / 4)) continue;
				if (aaSci.right < (rectDraw.left / 4)) break;
				rectRead.left = pt.x;
				rectRead.top = pt.y;
				rectRead.right = pt.x + size.cx - 1;
				rectRead.bottom = pt.y + size.cy - 1;
				if (pInfo->siz == G_IM_SIZ_4b) {
					gDPLoadTextureTile_4b(glp++, pImg, pInfo->fmt,
						pInfo->width + (pInfo->width & 1), pInfo->height,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						pInfo->pal, G_TX_NOMIRROR, G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (pInfo->siz == G_IM_SIZ_8b) {
					gDPLoadTextureTile(glp++, pImg, pInfo->fmt, G_IM_SIZ_8b,
						pInfo->width, pInfo->height,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_NOMIRROR, G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (pInfo->siz == G_IM_SIZ_16b) {
					gDPLoadTextureTile(glp++, pImg, pInfo->fmt, G_IM_SIZ_16b,
						pInfo->width, pInfo->height,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_NOMIRROR, G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				} else if (pInfo->siz == G_IM_SIZ_32b) {
					gDPLoadTextureTile(glp++, pImg, pInfo->fmt, G_IM_SIZ_32b,
						pInfo->width, pInfo->height,
						rectRead.left, rectRead.top, rectRead.right, rectRead.bottom,
						0, G_TX_NOMIRROR, G_TX_NOMIRROR,
						G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
				}
				gSPScisTextureRectangle(glp++,
					rectDraw.left, rectDraw.top,
					rectDraw.right, rectDraw.bottom,
					G_TX_RENDERTILE,
					pt.x << 5, pt.y << 5,	/* Upper-left coordinates inside TMEM */
					(int)((1 << 10) / xScale), (int)((1 << 10) / yScale));	/* Scale */
			}
		}
	}
	gDPPipeSync(glp++);
	return glp;
}


/* Display registered textures */
/* <<< 登録されているすべてのテクスチャイメージを表示する >>> */
Gfx* teDrawTextures(Gfx* glp)
{
	int i;
	for (i = 0; i < teSEGMENT_INFO_COUNT; i++) {
		glp = teDrawTexture(glp, i);
	}
	return glp;
}

