/*
 * [CCBL]
 *
 * menu.c
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


extern void rspCreate(void);
extern void rdpCreate(void);
extern void viCreate(void);
extern void miscCreate(void);

void mbCreate(void );

void
menuInit(void)
{
  mbCreate();
}

CW_ID
__create_win(MENU *mnp)
{
  CW_ID id;

  id = cwCreateWindow();
  cwSetEventFunc(id,mnp->evt);
  cwSetDispFunc(id,mnp->dsp);
  cwSetDeleteFunc(id,mnp->dlt);
  cwSetGeometry(id,mnp->x,mnp->y,mnp->w,mnp->h);
  cwSetAttr(id,CW_ATTR_MODAL);
  return id;
}

CW_ID
__create_win_nomode(MENU *mnp)
{
  CW_ID id;

  id = cwCreateWindow();
  cwSetEventFunc(id,mnp->evt);
  cwSetDispFunc(id,mnp->dsp);
  cwSetDeleteFunc(id,mnp->dlt);
  cwSetGeometry(id,mnp->x,mnp->y,mnp->w,mnp->h);
  cwSetAttr(id,CW_ATTR_MODELESS);
  return id;
}



/* Menu Bar ---------------- */
void mbEvent(CW_ID wid);
void mbDisp(CW_ID wid);
void mbDelete(CW_ID wid);

MENU mbMENU = {
  0,0,BASE_CW_WIN_W,1,
  mbEvent,
  mbDisp,
  NULL
};

#define MB_LABEL_MAX 4

void
mbCreate(void)
{
  __create_win_nomode(&mbMENU);
}



static LABEL mbLabel[MB_LABEL_MAX] = {
  {2,0,"RSP"},
  {7,0,"RDP"},
  {12,0,"VI"},
  {16,0,"MISC"}
};
  



static int mbPos = 0;

void
mbEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  static createfunc vf[MB_LABEL_MAX] = {
    rspCreate,
    rdpCreate,
    viCreate,
    miscCreate};

 if(pd->trigger & PAD_A){
    vf[mbPos]();
  }else{
    if(pd->trigger & PAD_R){
      mbPos++;
      if(mbPos >= MB_LABEL_MAX) mbPos = (MB_LABEL_MAX - 1);
    }
    if(pd->trigger & PAD_L){
      mbPos--;
      if(mbPos < 0 ) mbPos = 0;
    }
  }
}

void
mbDisp(CW_ID wid)
{
  static String l =
    "------------------------------------";
    /*012345678901234567890123456789012345*/
  static String ka = "[";
  static String ko = "]";

  int i;
  LABEL *lp;

  cwPutBuffer(wid,l,0,0);

  for(i = 0,lp = mbLabel;i < MB_LABEL_MAX;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
  }
  lp = &mbLabel[mbPos];
  cwPutBuffer(wid,ka,
	      lp->x-1,
	      lp->y);
  cwPutBuffer(wid,ko,
	      lp->x+strlen(lp->str),
	      lp->y);

}

/* == Menu Components ============================ */
/* scroll list box */
void slbEvent(CW_ID wid);
void slbDisp(CW_ID wid);

MENU slbMenu = {
  0,0,0,0,
  slbEvent,
  slbDisp,
  NULL
};

/*
  LABEL lbl[] = {
  :
  :
  :
  {-1,-1,NULL}
  };
*/

int slbPosC;
int slbPosL;
LABEL *slbLabel;
int slbLabelMax;
slbsetfunc slbSetFunc;


void
slbCreate(LABEL *lbl,int lpos,int x,int y,int w,int h,slbsetfunc fnc)
{
  int it,i;

  slbLabel = lbl;
  slbMenu.x = x;
  slbMenu.y = y;

  if(w == 0){
    for(i = 0;;i++){
      if(lbl[i].str == NULL) break;
      it = strlen(lbl[i].str);
      if(it > w) w = it;
    }
  }

  for(slbLabelMax = 0;;slbLabelMax++){
    if(lbl[slbLabelMax].str == NULL) break;
  }
  h = (h)?h:slbLabelMax;

  slbMenu.w = w;
  slbMenu.h = h;

  slbPosL = lpos;
  if((slbLabelMax - lpos) < h){
    slbPosC = slbLabelMax - h;
    if(slbPosL < 0) slbPosC = 0;
  }else{
    slbPosC = lpos;
  }

  slbSetFunc = fnc;
  __create_win(&slbMenu);
}

void
slbEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      slbSetFunc(slbPosL);
      cwDeleteWindow(wid);
    }else{
      if(pd->repeat & PAD_U){
	slbPosL--;
	if(slbPosL < 0) slbPosL++;
	if((slbPosL-slbPosC) < 0) slbPosC--;
      }
      if(pd->repeat & PAD_D){
	slbPosL++;
	if(slbPosL >= slbLabelMax) slbPosL--;
	if((slbPosL-slbPosC) >= slbMenu.h){
	  slbPosC++;
	}
      }
    }
  }
}

void
slbDisp(CW_ID wid)
{
  int i;
  LABEL *lbp;

  cwPutWindowFrame(wid,3,NULL);
  
  i = slbPosC;
  lbp = &slbLabel[i];
  for(i = 0;i < slbMenu.h;i++,lbp++){
    if(lbp->str == NULL) break;
    cwPutBuffer(wid,lbp->str,0,i);
  }
  cwPutCursorMB(wid,slbPosL-slbPosC,1);
}


/* Two OK panels cannot exist at the same time. */

static MENU okpMenu;
static int *okpRes;
static String okpStr;

void okpCreate(MENU *mn);
void okpEvent(CW_ID wid);
void okpDisp(CW_ID wid);
void okpDelete(CW_ID wid);

#define OK_PANEL_FALSE 0
#define OK_PANEL_TRUE 1

int
ok_panel(String str,int *rslt)
{
  int len;

  okpRes = rslt;
  okpStr = str;

  len = strlen(str);

  okpMenu.x = (BASE_CW_WIN_W / 2) - (len+2)/2;
  okpMenu.y = 8;
  okpMenu.w = len + 2;
  okpMenu.h = 4;
  okpMenu.evt = okpEvent;
  okpMenu.dsp = okpDisp;
  okpMenu.dlt = okpDelete;
  okpCreate(&okpMenu);
  return 0;
}


void
okpCreate(MENU *mn)
{
  __create_win(mn);
}

void
okpEvent(CW_ID wid)
{

}

void
okpDisp(CW_ID wid)
{

}

void
okpDelete(CW_ID wid)
{


}

int
touch_u8_val(u8 *val)
{
  Pad_D *pd = &Mpad[0];
  int rval;

  rval = *val;
  if(pd->trigger & PAD_CUNIT){
    if(pd->button & PAD_LT){
      if(pd->trigger & PAD_CR){
	rval = 255;
      }else if(pd->trigger & PAD_CL) rval = 0;
    }else{
      if(pd->trigger &(PAD_CL|PAD_CU)){
	rval -= (pd->trigger&PAD_CL)?1:16;
	if(rval < 0) rval = *val;
      }else{
	rval += (pd->trigger&PAD_CR)?1:16;
	if(rval > 255) rval = *val;
      }
    }


    *val = rval;
  }else{
    return 0;
  }
  return 1;
}


#if 0
void Event(CW_ID wid);
void Disp(CW_ID wid);
void Delete(CW_ID wid);

MENU Menu = {
  0,0,0,0,
  Event,
  Disp,
  Delete
};

void
Create(void)
{
  __create_win(& Menu);
}

void
Event(CW_ID wid)
{

}
void
Disp(CW_ID wid)
{

}
void
Delete(CW_ID wid)
{

}

#endif



