/*
  graphic.h

  Graphic-related definitions
  <<< グラフィックまわりの定義 >>>

  Notice: <<<...>>> is same comment in Japanese (SHIFT JIS code).
*/

#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

/* Screen size */
/* <<< スクリーンサイズ >>> */
#define SCREEN_HT        240
#define SCREEN_WD        320

/* Maximum length of display vlist for one stack */
/* <<< 一つのタスクのディスプレイリストの長さの最大値 >>> */
#define GFX_GLIST_LEN     2048
/* Length of display list for use in clearing the buffer */
/* <<< バッファクリア専用のディスプレイリストの長さ >>> */
#define GFX_CLEAR_GLIST_LEN     512

/*-------------------------- define structure ------------------------------ */
/* Projection matrix structure */
/* <<< 投影マトリクス行列構造体 >>> */
typedef struct {
  Mtx     projection;
  Mtx     modeling;
  Mtx     translate;
} Dynamic;

/*-------------------------------- parameter---------------------------------*/
extern Dynamic gfx_dynamic[];
extern Gfx* glistp;
extern Gfx gfx_glist[][GFX_GLIST_LEN];
extern Gfx gfx_clear_glist[][GFX_CLEAR_GLIST_LEN];
extern u32 gfx_gtask_no;
/*-------------------------------- function ---------------------------------*/
extern void gfxRCPInit(void);
extern void gfxClearCfb(void);
/*------------------------------- other extern define -----------------------*/
extern Gfx setup_rdpstate[];
extern Gfx setup_rspstate[];

#endif /* _GRAPHIC_H_ */



