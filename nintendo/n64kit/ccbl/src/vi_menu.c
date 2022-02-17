/*
 * [CCBL]
 *
 * vi_menu.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include <string.h>
#include "window.h"
#include "pad.h"
#include "menu.h"
#include "rcp_reg.h"


/* VI */
void viEvent(CW_ID wid);
void viDisp(CW_ID wid);
void viDelete(CW_ID wid);

MENU viMENU = {
  12,2,16,1,
  viEvent,
  viDisp,
  NULL
};


void
viCreate(void )
{
  __create_win_nomode(&viMENU);
}


void
viEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
 
  void vsfCreate(void);

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A)
      vsfCreate();
  }
}

void
viDisp(CW_ID wid)
{
  cwPutWindowFrame(wid,1,NULL);
  cwPutBuffer(wid,"SPECIAL FEATURES",0,0);
  cwPutCursorMB(wid,0,0);
}

/* Vi Special Features */
void vsfEvent(CW_ID wid);
void vsfDisp(CW_ID wid);

MENU vsfMenu = {
  10,8,17,6,
  vsfEvent,
  vsfDisp,
  NULL
};

static int vsfPos = 0;

void
vsfCreate(void)
{
  __create_win(&vsfMenu);
}

void
vsfEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_CD){
      toggleVSFVal(vsfPos);
    }else{
      if(pd->repeat & PAD_U){
	vsfPos--;
	if(vsfPos < 0) vsfPos++;
      }
      if(pd->repeat & PAD_D){
	vsfPos++;
	if(vsfPos >= VSF_LEN) vsfPos--;
      }
    }
  }

}

static LABEL vsfl[VSF_LEN] = {
  {1,1,"GAMMA"},
  {1,2,"GAMMA_DITHER"},
  {1,3,"DIVOT"},
  {1,4,"DITHER_FILTER"},
};

void
vsfDisp(CW_ID wid)
{
  int i;
  LABEL *lp;

  cwPutWindowFrame(wid,0,"VI SPECIAL...");

  for(i = 0,lp = vsfl;i < VSF_LEN;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",14,lp->y);
    cwPutBuffer(wid,(getVSFVal(i))?"O":"x",15,lp->y);
  }
  cwPutCursorLabel(wid,1,vsfl[vsfPos].y,13,1);
}

