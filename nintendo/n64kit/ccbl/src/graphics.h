/*
 * [CCBL]
 *
 * graphics.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_



#define SCREEN_HT 240
#define SCREEN_WD 320

#define GFX_GLIST_LEN 16384


typedef struct {
  Mtx	projection;
  Mtx	modeling;
  Mtx	viewing;
  Mtx    identity;
  LookAt lat;
} Dynamic;


extern Dynamic dynamic[];
extern Gfx* glistp;
extern Gfx gfx_glist[2][GFX_GLIST_LEN];

extern int console_f;
extern int setup_frame_no;
extern int draw_frame_no;


void gfxSetupFirst(void);

enum clear_cfb_col {
  CLR_BLACK = 0,
  CLR_GRAY,
  CLR_WHITE,
  CLR_BLUE,
  CLR_RED,
  CLR_GREEN,
  CLR_IMG0,
  CLR_IMG1
};
void gfxClearCfb(int type);

extern void init_gtask(void );
extern void start_gtask(int );
//extern void wait_gtask(void );
extern void request_gtask(void );

#endif /* !_GRAPHICS_H_ */
