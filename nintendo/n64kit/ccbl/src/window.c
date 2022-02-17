/*
 * [CCBL]
 *
 * window.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */

/* Simple menu manager */

#include "common_include.h"
#include <string.h>
#include "malloc.h"
#include "window.h"
#include "pad.h"
#include "rcp_reg.h"
#include "window_out.h"

#define USE_CON_FRONT NU_DEB_CON_WINDOW1
#define USE_CON_BACK NU_DEB_CON_WINDOW0
#define BASE_CON_X (8*2)
#define BASE_CON_Y (8*2)

static unsigned char *base_win_c;		/* Characters */
static unsigned char *base_win_a;		/* Attributes */

static CW_ID nwid;
static CW_WINDOW cwBase;
static int cw_real_f;
static int cw_mode_count;

static void 
__clear_cw_fb(void)
{
  memset(base_win_c,
	 0x0,
	 BASE_CW_WIN_W*BASE_CW_WIN_H*sizeof(unsigned char));
}

void
cwInitWindowSystem(void )
{
  cw_real_f = 1;

  nwid = CW_ROOT_WINDOW;
  base_win_c = calloc(BASE_CW_WIN_W*BASE_CW_WIN_H,sizeof(unsigned char));
  base_win_a = calloc(BASE_CW_WIN_W*BASE_CW_WIN_H,sizeof(unsigned char));
  __clear_cw_fb(); 
  cwBase.wid = nwid++;		/*!!No specific limit on assigned ID!!*/
  cwBase.prvwin = NULL;
  cwBase.nxtwin = NULL;

  window_disp_init(BASE_CON_X+1,BASE_CON_Y+1,BASE_CW_WIN_W,BASE_CW_WIN_H);
 
#if 0
  nuDebConWindowSet(USE_CON_FRONT,
		    BASE_CON_X,BASE_CON_Y,BASE_CW_WIN_W,BASE_CW_WIN_H);
  nuDebConScroll(USE_CON_FRONT,NU_DEB_CON_SCROLL_OFF);
  nuDebConWindowSet(USE_CON_BACK,
		    BASE_CON_X+1,BASE_CON_Y+1,BASE_CW_WIN_W,BASE_CW_WIN_H);
  nuDebConScroll(USE_CON_BACK,NU_DEB_CON_SCROLL_OFF);
  nuDebConTextColor(USE_CON_BACK,0 /*8*/);
#endif

  cw_mode_count = 0;
}


CW_WINDOW *
cwSearchWindowID(CW_ID wid)
{
  CW_WINDOW *cwp = &cwBase;
  int i;
  
  for(i = 0;;i++){
    if(cwp->wid == wid) return cwp;
    if(cwp->nxtwin == NULL) break;
    cwp = cwp->nxtwin;
  }
  return NULL;
}

int
cwCreateWindow(void )
{
  CW_WINDOW *cwp = &cwBase;
  CW_WINDOW *cwin;

  if(nwid > 65536*256){	/* That said, a maximum is provided for id generation. */
    osSyncPrintf("!! Window ID Limit !!\nPlese Restart me.\n");
    return (-1);
  }
  cwin = calloc(1,sizeof(CW_WINDOW)); /* That provided by malloc is somewhat unstable. */
  if(cwin == NULL) return (-1);

  for(;;){			/* Search for window registered last. */
    if(cwp->nxtwin == NULL )break;
    cwp = cwp->nxtwin;
  }
  cwp->nxtwin = cwin;
  cwin->prvwin = cwp;
  cwin->nxtwin = NULL;

  cwin->wid = nwid++;
  cwin->stat = CW_ST_IDLE;
  cwin->event = NULL;
  cwin->disp = NULL;
  cwin->del = NULL;
  cwin->geo.x = cwin->geo.y = 0;
  cwin->geo.w = cwin->geo.h = 0;
  cwin->atr = 0;
  return cwin->wid;
}

int
cwDeleteWindow(CW_ID wid)
{
  CW_WINDOW *cwp;

  if(wid == CW_ROOT_WINDOW) return(-1);
  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->stat = CW_ST_DEATH;	/* You're already dead. */
  return cwp->stat;
}


int
__delete_window(CW_ID wid)
{
  CW_WINDOW *cwp,*cprv,*cnxt;

  if(wid == CW_ROOT_WINDOW) return(-1);
  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);

  /* Join previous and next. */
  cprv = cwp->prvwin;
  cnxt = cwp->nxtwin;
  cprv->nxtwin = cnxt;
  if(cnxt != NULL)		/* If not the last */
    cnxt->prvwin = cprv;
  free(cwp);			/* Nullify CW_WINDOW.*/
  return 0;
}

int
cwSetEventFunc(CW_ID wid,cwEventfunc evt)
{
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->event = evt;
  return 0;
}

int
cwSetDispFunc(CW_ID wid,cwDispfunc dpf)
{
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->disp = dpf;
  return 0;
}

int
cwSetDeleteFunc(CW_ID wid,cwDispfunc dlt)
{
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->del = dlt;
  return 0;
}

int
cwSetGeometry(CW_ID wid,int x,int y,int w,int h)
{
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->geo.x = x;
  cwp->geo.y = y;
  cwp->geo.w = w;
  cwp->geo.h = h;
  return 0;
}

int
cwSetAttr(CW_ID wid,unsigned long atr)
{
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  if(cwp == NULL) return (-1);
  cwp->atr = atr;
  return 0;
}


void
cwWindowMain(void)
{
  CW_WINDOW *cwp,*nwp;
  int a;

  if(Mpad[0].trigger & PAD_RT) 
    cw_real_f ^= 1;

  if(cw_real_f){
    cwp=&cwBase;
    for(;;){
      if((cwp->event != NULL) && 
	 (cwp->nxtwin == NULL) && 
	 (cwp->stat == CW_ST_LIVE))
	cwp->event(cwp->wid);	/* Execute only last in list. */
      
      a = 1;
      if((cw_mode_count) && (cwp->wid > CW_ROOT_WINDOW+1))
	if((cwp->atr & 1) == 0) a = 0;
      if((cwp->disp != NULL) && (cwp->stat == CW_ST_LIVE) && (a))
	  cwp->disp(cwp->wid);

      if(cwp->nxtwin == NULL) break;
      cwp = cwp->nxtwin;
    }
  }

  cwFlushWindow();
  /* Dispose of the dead and wake the sleeping. */
  cwp = &cwBase;
  for(;;){
    nwp = cwp->nxtwin;
    if(cwp->stat == CW_ST_DEATH){
      if(cwp->del != NULL)
	cwp->del(cwp->wid);
      if(cwp->atr & CW_ATTR_MODAL){
	cw_mode_count--;
	if(cw_mode_count < 0) cw_mode_count = 0;
      }
      /*cwp used to this point cannot be used subsequently. */
      __delete_window(cwp->wid);
    }else{
      if(cwp->stat == CW_ST_IDLE){
	cwp->stat = CW_ST_LIVE;
	if(cwp->atr & CW_ATTR_MODAL) cw_mode_count++;
      }
    }
    /* Prepare new cwp. */
    if(nwp == NULL) break;
    cwp = nwp;
  }
  if(Mpad[1].trigger & (PAD_A|PAD_B))
    printRCP_REG((Mpad[1].trigger & PAD_A)?0:1);
}


void
cwFlushWindow(void)
{
  int x,y;
  unsigned char *ch;
  int c;
  static char cadj[0x20] = {
  /* 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F */
    ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>','<',' ',' ',' ',' ',
    '+','+','+','+','|','|','-','-',' ',' ',' ',' ',' ',' ',' ',' ',
  };
  window_disp_cls();

  ch = base_win_c;
  for(y = 0;y < BASE_CW_WIN_H;y++)
    for(x = 0;x < BASE_CW_WIN_W;x++){
      window_disp_put(*ch);
      //nuDebConPutc(USE_CON_FRONT,*ch);
      //nuDebConPutc(USE_CON_BACK,*ch);
      ch++;
    }
  /* make screen snap shot */
#ifndef DPTEST
  if(Mpad[1].trigger & PAD_LT){
    ch = base_win_c;
    for(y = 0;y < BASE_CW_WIN_H;y++){
      for(x = 0;x < BASE_CW_WIN_W;x++){
	c = *ch++;
	if(c < 0x20){
	  c = ' ';
	}else if(c >=0x80){
	  c = cadj[c-0x80];
	}
	osSyncPrintf("%c",c);
      }
	osSyncPrintf("\n");
    }
    osSyncPrintf("---->\n");
  }
#endif
  __clear_cw_fb();
}


/*==================================================*/
void
cwPutBuffer(CW_ID wid,String str,int x,int y)
{ /* Clipping not currently considered. */
  unsigned char *cp;
  CW_WINDOW *cwp;

  cwp = cwSearchWindowID(wid);
  cp = base_win_c + ((cwp->geo.y+y)*BASE_CW_WIN_W + cwp->geo.x + x);

  while(*str != '\0'){
    if(*str >= 0x20) *cp = *str;
    cp++;
    str++;
  }

}

void
cwPutWindowFrame(CW_ID wid,int type,String str)
{
  CW_WINDOW *cwp;
  unsigned char *cp;
  int i,j;
  static char tc_ul[] = "\x90\x94" /*"+|"*/;
  static char tc_ur[] = "\x91\x95" /*"+|"*/;
  static char tc_dl[] = "\x92\x94" /*"+|"*/;
  static char tc_dr[] = "\x93\x95" /*"+|"*/;
  /*tyoe bit0: upper corner + or |, bit1: lower corner + or | */
  cwp = cwSearchWindowID(wid);
  cp = base_win_c + 
    ((cwp->geo.y-1)*BASE_CW_WIN_W + cwp->geo.x-1);

  *cp++ = tc_ul[type&1];
  for(j = 0;j < cwp->geo.w;j++)
    *cp++= 0x96 /*'-'*/;
  *cp++ = tc_ur[type&1];
  for(i = 0;i < cwp->geo.h;i++){
    cp += BASE_CW_WIN_W - cwp->geo.w -2;
    *cp++ = 0x94 /*'|'*/;
    for(j = 0;j < cwp->geo.w;j++)
      *cp++= ' ';
    *cp++ = 0x95 /*'|'*/;
  }
  cp += BASE_CW_WIN_W - cwp->geo.w -2;
  *cp++ = tc_dl[(type>>1)&1];
  for(j = 0;j < cwp->geo.w;j++)
    *cp++= 0x97 /*'-'*/;
  *cp++ = tc_dr[(type>>1)&1];
  if(str != NULL){
    cp = base_win_c + 
      ((cwp->geo.y-1)*BASE_CW_WIN_W + cwp->geo.x);
    *cp++ = '[';
    for(i = 0;*str != NULL;i++){
      *cp++ = *str++;
    }
    *cp = ']';
  }

}

void
cwPutCursorMB(CW_ID wid,int ypos,int type)
{
  CW_WINDOW *cwp;
  unsigned char *cp;
  static char *csc[] = {"\x8a\x8b","\x8a\x8b"/*"><","><"*/};

  cwp = cwSearchWindowID(wid);

  cp = base_win_c + 
    (cwp->geo.y+ypos)*BASE_CW_WIN_W + (cwp->geo.x-1);
  *cp = *csc[type];
  cp += (cwp->geo.w+1);
  *cp = *(csc[type]+1);
}

void
cwPutCursorLabel(CW_ID wid,int xpos,int ypos,int llen,int type)
{
  CW_WINDOW *cwp;
  unsigned char *cp;
  static String lbl[] = {"\x8a\x8b","\x8a\x8b","\x8b\x8a"/*"><","><","<>"*/};

  cwp = cwSearchWindowID(wid);

  cp = base_win_c + 
    (cwp->geo.y+ypos)*BASE_CW_WIN_W + (cwp->geo.x+xpos-1);
  *cp = *lbl[type];
  cp += (llen+1);
  *cp = *(lbl[type]+1);

}

void
cwPutSeparater(CW_ID wid,int x,int y,int w,int type)
{
  CW_WINDOW *cwp;
  unsigned char *cp;
  int i;
  static char *septc[] = {"- ","= "};

  cwp = cwSearchWindowID(wid);

  cp = base_win_c + 
    (cwp->geo.y+y)*BASE_CW_WIN_W + (cwp->geo.x+x);
  for(i = 0;i < w;i++){
    *cp++ = *(septc[type]+(i&1));
  }

}


