/*
 * [CCBL]
 *
 * window_out.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include <malloc.h>
#include "mysys.h"
#include "graphics.h"
#include "window_out.h"

#include "pal.h"

#define WIN_OUT_W 40
#define WIN_OUT_H 30

static u8 *wd_buff;
static int wd_cur_cx;
static int wd_cur_cy;
static int wd_cw;
static int wd_ch;
static int wd_sx;
static int wd_sy;
static u32 *letters_img;

extern u8 _lettersSegmentRomStart[];
extern u8 _lettersSegmentRomEnd[];

void
window_disp_init(int x,int y,int w,int h)
{
  wd_buff = malloc(WIN_OUT_W * WIN_OUT_H);
  wd_sx = x;
  wd_sy = y;
  wd_cw = w;
  wd_ch = h;
  window_disp_cls();
  letters_img = malloc(_lettersSegmentRomEnd - _lettersSegmentRomStart);
  nuPiReadRom((u32)_lettersSegmentRomStart,
	      letters_img,
	      _lettersSegmentRomEnd - _lettersSegmentRomStart);
 
}

void
window_disp_cls(void)
{
  wd_cur_cx = wd_cur_cy = 0;
  bzero(wd_buff,WIN_OUT_W * WIN_OUT_H);
}

void
window_disp_put(u8 val)
{
  u8 *put_p;

  put_p = wd_buff + (wd_cur_cy * WIN_OUT_W + wd_cur_cx);
  *put_p = val;
  wd_cur_cx++;
  if(wd_cur_cx >= wd_cw){
    wd_cur_cx = 0;
    wd_cur_cy++;
    if(wd_cur_cy >= wd_ch) wd_cur_cy--;

  }
}



static Gfx wd_initDL[] = {
  gsDPPipeSync(),
  gsSPSegment(0,0),
  gsDPSetCycleType(G_CYC_1CYCLE),
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
  gsDPSetTextureFilter(G_TF_POINT),
  gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
  gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF),
  gsDPSetTexturePersp(G_TP_NONE),
  gsDPSetTextureLOD(G_TL_TILE),
  gsDPSetTextureLUT(G_TT_IA16),
  gsDPSetTextureDetail(G_TD_CLAMP),
  gsDPSetTextureConvert(G_TC_FILT),
  gsDPSetAlphaCompare(G_AC_NONE),
  gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),
  gsDPSetPrimColor(0, 0, 255, 255, 255, 0),
  gsSPClearGeometryMode(0xffffffff),
  gsDPLoadTLUT_pal16(0,letters_pal),
  gsDPPipeSync(),
  gsSPEndDisplayList()
};


Gfx *
window_disp(Gfx *gp)
{
  int i,j;
  u8 *wp;
  u32 tx,ty;
  u32 ts,tt;
  int out_char;



  gSPDisplayList(gp++,&wd_initDL);
  /* character drawing in the former half */
  gDPLoadTextureBlock_4b(gp++,letters_img, G_IM_FMT_CI,
			  128, 32,			    
			  0,
			  G_TX_WRAP , G_TX_WRAP,
			  G_TX_NOMASK, G_TX_NOMASK,
			  G_TX_NOLOD, G_TX_NOLOD);
  wp = wd_buff;
  for(i = 0;i < WIN_OUT_H;i++){
    for(j = 0;j < WIN_OUT_W;j++){
      out_char =  *wp - 0x20;
      if((out_char >= 0) && (out_char < 0x40)){ 
	ts = ((out_char & 0xf) * 8) << 5;
	tt = (((out_char & 0xf0)>>4)*8) << 5;
	tx = j*8+wd_sx;
	ty = i*8+wd_sy;
	gSPTextureRectangle(gp++,
			    tx << 2,ty << 2,
			    (tx + 8) << 2,(ty + 8) << 2,
			    G_TX_RENDERTILE,
			    ts,tt,
			    1 << 10,1 << 10);
      }
      wp++;
    }
  }

  /* character drwaing in latter half */
  gDPLoadTextureBlock_4b(gp++,(int)letters_img+(128*32/2), G_IM_FMT_CI,
			  128, 32,			    
			  0,
			  G_TX_WRAP , G_TX_WRAP,
			  G_TX_NOMASK, G_TX_NOMASK,
			  G_TX_NOLOD, G_TX_NOLOD);
  wp = wd_buff;
  for(i = 0;i < WIN_OUT_H;i++){
    for(j = 0;j < WIN_OUT_W;j++){
      out_char =  *wp - 0x60;
      if((out_char >= 0) && (out_char < 0x40)){ 
	ts = ((out_char & 0xf) * 8) << 5;
	tt = (((out_char & 0xf0)>>4)*8) << 5;
	tx = j*8+wd_sx;
	ty = i*8+wd_sy;
	gSPTextureRectangle(gp++,
			    tx << 2,ty << 2,
			    (tx + 8) << 2,(ty + 8) << 2,
			    G_TX_RENDERTILE,
			    ts,tt,
			    1 << 10,1 << 10);
      }
      wp++;
    }
  }

  return gp;
}


