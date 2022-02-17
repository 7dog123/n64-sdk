/*
  gfxinit.c
   
  Display list for initialization of graphics
  <<<グラフィック初期化のためのディスプレイリスト>>>

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#include <nusys.h>
#include "graphic.h"

/*
  Viewport structure
  Conversion from (-1,-1,-1)-(1,1,1).  Decimal part is 2 bits.
  <<<ビューポート構造体>>>
  <<<(-1,-1,-1)-(1,1,1)よりの変換。小数部２ビット。>>>
 */
static Vp vp = {
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* Scaling */
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* Moving */
};

/*
  Initialize RDP
*/
Gfx setup_rdpstate[] = {
  gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
  gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0,0, SCREEN_WD,SCREEN_HT),
  gsDPSetColorDither(G_CD_BAYER),
  gsSPEndDisplayList(),
};

/*
  Initialize RSP
*/
Gfx setup_rspstate[] = {
  gsSPViewport(&vp),
  gsSPClearGeometryMode(0xFFFFFFFF),
  gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK),
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsSPEndDisplayList(),
};
