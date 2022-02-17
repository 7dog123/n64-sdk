/*
 * [CCBL]
 *
 * misc_menu.c
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
#include "model_load.h"
#include "texture.h"
#include "bg_model.h"

void miscEvent(CW_ID wid);
void miscDisp(CW_ID wid);


#define MISC_LABEL_MAX 4

MENU miscMENU = {
  16,2,8,MISC_LABEL_MAX,
  miscEvent,
  miscDisp,
  NULL
};

static int miscPos = 0;

static String miscStr[MISC_LABEL_MAX] = {
  "MODEL",
  "TEXTURE",
  "BG_COLOR",
  "BG_MODEL"
};

void
miscCreate(void )
{
  __create_win_nomode(&miscMENU);

}

void
miscEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  void bgcCreate(void);
  void mdlCreate(void);
  void txCreate(void );
  void bgmCreate(void);
  static createfunc crf[MISC_LABEL_MAX] = {
    mdlCreate,
    txCreate,
    bgcCreate,
    bgmCreate,
  };

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      crf[miscPos]();
    }else{
      if(pd->trigger & PAD_U){
	miscPos--;
	if(miscPos < 0) miscPos++;
      }
      if(pd->trigger & PAD_D){
	miscPos++;
	if(miscPos >= MISC_LABEL_MAX) miscPos--;
      }
    }
  }
}

void
miscDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,1,NULL);
  for(i = 0;i < MISC_LABEL_MAX;i++){
    cwPutBuffer(wid,miscStr[i],0,i);
  }
  cwPutCursorMB(wid,miscPos,0);
}

/* BG COLOR */
void bgcEvent(CW_ID wid);
void bgcDisp(CW_ID wid);


#define BGC_LABEL_MAX 8

MENU bgcMENU = {
  14,8,12,BGC_LABEL_MAX,
  bgcEvent,
  bgcDisp,
  NULL
};

static int bgcPos = 0;

static String bgcStr[BGC_LABEL_MAX] = {
  "BLACK",
  "GRAY",
  "WHITE",
  "BLUE",
  "RED",
  "GREEN",
  "IMAGE1",
  "IMAGE2"
};

void
bgcCreate(void )
{
  __create_win(&bgcMENU);
  bgcPos = getBgColorVal();
}


void
bgcEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
 
  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setBgColorVal(bgcPos);
    }else{
      if(pd->trigger & PAD_U){
	bgcPos--;
	if(bgcPos < 0) bgcPos++;
      }
      if(pd->trigger & PAD_D){
	bgcPos++;
	if(bgcPos >= BGC_LABEL_MAX) bgcPos--;
      }
    }
  }
}

void
bgcDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,0,"BG COLOR");
  for(i = 0;i < BGC_LABEL_MAX;i++){
    cwPutBuffer(wid,bgcStr[i],2,i);
  }
  cwPutCursorLabel(wid,2,bgcPos,6,0);
}


/* model data */

void mdlEvent(CW_ID wid);
void mdlDisp(CW_ID wid);

#define MDL_LABEL_MAX MDL_NO_MAX

MENU mdlMenu = {
  10,6,10,MDL_LABEL_MAX+3,
  mdlEvent,
  mdlDisp,
  NULL
};

static int mdlPos;

void
mdlCreate(void)
{
  __create_win(&mdlMenu);
  mdlPos = getModelNoVal();
}

void
mdlEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setModelNoVal((mdlPos < MDL_LABEL_MAX)?mdlPos:MDL_USER);
    }else{
      if(pd->repeat & PAD_U){
	mdlPos--;
	if(mdlPos < 0) mdlPos++;
      }
      if(pd->repeat & PAD_D){
	mdlPos++;
	if(mdlPos >= (MDL_LABEL_MAX+get_user_model_sw())) mdlPos--;
      }
    }
  }
}

static String mdlLabel[MDL_LABEL_MAX] = {
  "TETRA",
  "CUBE",
  "SPHERE",
  "XY-YZ",
  "MOUNTAIN",
  "TRIANGLE",
  "   A    ",
  "MIZO   ",
  "TORUS2",
};

void
mdlDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,0,"MODEL");
  for(i = 0;i < MDL_LABEL_MAX;i++){
    cwPutBuffer(wid,mdlLabel[i],1,i+1);
  }
  if(get_user_model_sw()) cwPutBuffer(wid,"DPTEST",1,i+1);

  cwPutCursorLabel(wid,1,mdlPos+1,8,0);
}

/* texture */

void txEvent(CW_ID wid);
void txDisp(CW_ID wid);


#define TX_LABEL_MAX TX_ITEM_LEN

MENU txMenu = {
  10,4,18,TX_LABEL_MAX+2,
  txEvent,
  txDisp,
  NULL,
};

static String txLabel[TX_LABEL_MAX] = {
 //01234567890123456
  "RGBA16 MARIO",
  "RGBA16 TREE",
  "RGBA16 BRICK",
  "RGBA16 CHECKER",
  "RGBA16 BRICK_MM",
  "RGBA32 GRADIENT",
  "IA16   GRADIENT",
  "RGBA16 REFLECT",
  "I8     HIGHLIGHT",
};

static int txPos;

void
txCreate(void)
{
  __create_win(&txMenu);
  txPos = getTextureNoVal();
}

void
txEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setTextureNoVal(txPos);
    }else{
      if(pd->repeat & PAD_U){
	txPos--;
	if(txPos < 0) txPos++;
      }
      if(pd->repeat & PAD_D){
	txPos++;
	if(txPos >= TX_LABEL_MAX) txPos--;
      }
    }
  }

}

void
txDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,0,"TEXTURE");
  for(i = 0;i < TX_LABEL_MAX;i++){
    cwPutBuffer(wid,txLabel[i],1,i+1);
  }
  cwPutCursorLabel(wid,1,txPos+1,16,0);
}

/* bg model */
void bgmEvent(CW_ID wid);
void bgmDisp(CW_ID wid);

#define BGM_LABEL_MAX BG_MODEL_LEN

MENU bgmMenu = {
  10,4,10,BGM_LABEL_MAX+2,
  bgmEvent,
  bgmDisp,
  NULL,
};

static String bgmLabel[BGM_LABEL_MAX] = {
 //01234567890123456
  "DISABLE",
  "PLANE",
  "STARS"
};

static int bgmPos;

void
bgmCreate(void)
{
  __create_win(&bgmMenu);
  bgmPos = getBgModelNoVal();
}

void
bgmEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setBgModelNoVal(bgmPos);
    }else{
      if(pd->repeat & PAD_U){
	bgmPos--;
	if(bgmPos < 0) bgmPos++;
      }
      if(pd->repeat & PAD_D){
	bgmPos++;
	if(bgmPos >= BGM_LABEL_MAX) bgmPos--;
      }
    }
  }

}

void
bgmDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,0,"BG MODEL");
  for(i = 0;i < BGM_LABEL_MAX;i++){
    cwPutBuffer(wid,bgmLabel[i],1,i+1);
  }
  cwPutCursorLabel(wid,1,bgmPos+1,8,0);
}
