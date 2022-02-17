/*
 * [CCBL]
 *
 * menu.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _MENU_H_
#define _MENU_H_
#include "window.h"

typedef struct MENU_s {
  int x,y,w,h;
  cwEventfunc evt;
  cwDispfunc dsp;
  cwDeletefunc dlt;
} MENU;


typedef struct LABEL_s {
  int x,y;
  String str;
} LABEL;

typedef void (*createfunc)(void);
typedef void (*slbsetfunc)(int val);
/*-----*/
extern void menuInit(void);

extern int ok_panel(String str,int *rslt);

/*----*/
extern void slbCreate(LABEL *lbl,int lpos,int x,int y,int w,int h,slbsetfunc fnc);
/*---*/
int touch_u8_val(u8 *val);

/*-menu internal---*/
extern CW_ID __create_win(MENU *mnp);
extern CW_ID __create_win_nomode(MENU *mnp);

#endif /* !_NEMU_H_ */
