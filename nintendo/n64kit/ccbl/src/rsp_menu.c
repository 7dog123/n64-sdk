/*
 * [CCBL]
 *
 * rsp_menu.c
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

/* sp section menu ------- */

#define RSP_LABEL_MAX 3

LABEL spLabel[RSP_LABEL_MAX] = {
  {0,0,"GEO_MODE"},
  {0,1,"LIGHT_COL"},
  {0,2,"FOG_POS"},
};

void rspEvent(CW_ID wid);
void rspDisp(CW_ID wid);

int rspPos = 0;

MENU rspMENU = {
  2,2,9,RSP_LABEL_MAX,
  rspEvent,
  rspDisp,
  NULL
};


void
rspCreate(void )
{
  __create_win_nomode(&rspMENU);
}


void
rspEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  void gmCreate(void);
  void ltCreate(void);
  void fpCreate(void);

  static createfunc rspcf[RSP_LABEL_MAX] = 
  {
    gmCreate,
    ltCreate,
    fpCreate,
  };

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      rspcf[rspPos]();
    }else{
      if(pd->trigger & PAD_U){
	rspPos--;
	if(rspPos < 0) rspPos++;
      }
      if(pd->trigger & PAD_D){
	rspPos++;
	if(rspPos >= RSP_LABEL_MAX) rspPos--;
      }
    }
  }
}


void
rspDisp(CW_ID wid)
{
  LABEL *lp;
  int i;

  cwPutWindowFrame(wid,1,NULL);
  for(i = 0,lp = spLabel;i < RSP_LABEL_MAX;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
  }
  cwPutCursorMB(wid,rspPos,0);
}


/*----- Geometry Mode ---- */

void gmEvent(CW_ID wid);
void gmDisp(CW_ID wid);

MENU gmMENU = {
  8,4,19,GEO_MODE_LEN+1,
  gmEvent,
  gmDisp,
  NULL
};


int gmPos = 0;

void
gmCreate(void )
{
  __create_win(&gmMENU);
}

void
gmEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_CD){
      toggleGeometryModeVal(gmPos);
    }else{
      if(pd->repeat & PAD_U){
	gmPos--;
	if(gmPos < 0) gmPos++;
      }
      if(pd->repeat & PAD_D){
	gmPos++;
	if(gmPos >= GEO_MODE_LEN) gmPos--;
      }
    }
  }

}

LABEL gmLabel[GEO_MODE_LEN] = {
  {1,0,"G_SHADE"},
  {1,1,"G_LIGHTING"},
  {1,2,"G_SHADING_SMOOTH"},
  {1,3,"G_ZBUFFER"},
  {1,4,"G_TEXTURE_GEN"},
  {1,5,"G_TEXTURE_GEN_L"},
  {1,6,"G_CULL_FRONT"},
  {1,7,"G_CULL_BACK"},
  {1,8,"G_FOG"},
  {1,10," REFLECTION EN"}
};

void
gmDisp(CW_ID wid)
{
  int i;
  LABEL *lp = gmLabel;
  static char *onoff[2] = {
    "x",
    "O"};

  cwPutWindowFrame(wid,0,"GEO_MODE");
  cwPutSeparater(wid,0,9,gmMENU.w,0);
   for(i = 0;i < GEO_MODE_LEN;i++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",17,lp->y);
    cwPutBuffer(wid,
		onoff[getGeometryModeVal(i)],
		18,lp->y);
    lp++;
  }
  cwPutCursorLabel(wid,1,gmLabel[gmPos].y,16,1);
}

/* Light color */

void ltEvent(CW_ID wid);
void ltDisp(CW_ID wid);

MENU ltMenu = {
  12,5,15,9,
  ltEvent,
  ltDisp,
  NULL
};

static int ltPosX = 0;
static int ltPosY = 0;

void
ltCreate(void)
{
  __create_win(&ltMenu);
}

void
ltEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  u8 tval;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    tval = getLightColorVal(ltPosY*LC_LEN+ltPosX);
    if(touch_u8_val(&tval)){
      setLightColorVal(ltPosY*LC_LEN+ltPosX,tval);
    }else{
      if(pd->repeat & PAD_L){
	ltPosX--;
	if(ltPosX < 0) ltPosX++;
      }
      if(pd->repeat & PAD_R){
	ltPosX++;
	if(ltPosX >= LC_LEN) ltPosX--;
      }
      if(pd->repeat & PAD_U){
	ltPosY--;
	if(ltPosY < 0) ltPosY++;
      }
      if(pd->repeat & PAD_D){
	ltPosY++;
	if(ltPosY >= LIGHT_COL_NUM) ltPosY--;
      }
    }
  }
}

static LABEL lclt[LIGHT_COL_NUM] = {
  {0,1,"DIF1:"},
  {0,2,"DIF2:"},
  {0,3,"DIF3:"},
  {0,4,"DIF4:"},
  {0,5,"DIF5:"},
  {0,6,"DIF6:"},
  {0,7,"DIF7:"},
  {0,8,"AMB :"},
};

void
ltDisp(CW_ID wid)
{
  int i;
  LABEL *lbl;
  u8 c_tmp[8];

  static String clh = "R  G  B";
  
  cwPutWindowFrame(wid,0,"LIGHT COLOR");

  cwPutBuffer(wid,clh,6,0);
  for(i = 0,lbl = lclt;i < LIGHT_COL_NUM;i++,lbl++){
    cwPutBuffer(wid,lbl->str,lbl->x,lbl->y);
    sprintf(c_tmp,"%02X",getLightColorVal(i*LC_LEN+LC_R));
    cwPutBuffer(wid,c_tmp,6,lbl->y);
    sprintf(c_tmp,"%02X",getLightColorVal(i*LC_LEN+LC_G));
    cwPutBuffer(wid,c_tmp,9,lbl->y);
    sprintf(c_tmp,"%02X",getLightColorVal(i*LC_LEN+LC_B));
    cwPutBuffer(wid,c_tmp,12,lbl->y);
  }
  cwPutCursorLabel(wid,ltPosX*3+6,ltPosY+1,2,1);
}

/* Fog Position */

void fpEvent(CW_ID wid);
void fpDisp(CW_ID wid);

MENU fpMenu = {
  8,6,10,6,
  fpEvent,
  fpDisp,
  NULL
};


static int fpPosY = 0;
static int fpPosX = 0;

void
fpCreate(void)
{
  __create_win(&fpMenu);
}

void
fpEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  int a,min,max;

  static int regt[2]={FOG_POS_MIN_L,FOG_POS_MAX_L};
  static int addt[4]={1000,100,10,1};

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->repeat & (PAD_CU|PAD_CD)){
      if(fpPosY == 0){
	/* Takes a value of min 0 to 1000 but not max or greater. */
	a = getFogPositionVal(FOG_POS_MIN_L);
	max = getFogPositionVal(FOG_POS_MAX_L);
	if(pd->repeat & PAD_CU){
	  a -= addt[fpPosX];
	  if(a < 0) a = 0;
	}
	if(pd->repeat & PAD_CD){
	  a += addt[fpPosX];
	  if(a >= max ) a = max-1;
	}
      }else{
	/* Takes a value of min 0 to 1000 but not min or less.  */
	a = getFogPositionVal(FOG_POS_MAX_L);
	min = getFogPositionVal(FOG_POS_MIN_L);
	if(pd->repeat & PAD_CU){
	  a -= addt[fpPosX];
	  if(a <= min) a = min+1;
	}
	if(pd->repeat & PAD_CD){
	  a += addt[fpPosX];
	  if(a > 1000 ) a = 1000;
	}
      }
      setFogPositionVal(regt[fpPosY],a);
    }else{
      if(pd->trigger & PAD_U){
	fpPosY--;
	if(fpPosY < 0) fpPosY++;
      }
      if(pd->trigger & PAD_D){
	fpPosY++;
	if(fpPosY >= FOG_POS_MAX) fpPosY--;
      }
      if(pd->trigger & PAD_L){
	fpPosX--;
	if(fpPosX < 0) fpPosX++;
      }
      if(pd->trigger & PAD_R){
	fpPosX++;
	if(fpPosX >= 4) fpPosX--;
      }

    }
  }

}

void
fpDisp(CW_ID wid)
{
  char pbuf[16];

  cwPutWindowFrame(wid,0,"FOG_POS");
  cwPutBuffer(wid,"MIN:",1,1);
  cwPutBuffer(wid,"MAX:",1,4);

  sprintf(pbuf,"%04d",getFogPositionVal(FOG_POS_MIN_L));
  cwPutBuffer(wid,pbuf,5,1);
  sprintf(pbuf,"%04d",getFogPositionVal(FOG_POS_MAX_L));
  cwPutBuffer(wid,pbuf,5,4);

  cwPutCursorLabel(wid,1,fpPosY*3+1,3,1);
  cwPutBuffer(wid,"*",fpPosX+5,fpPosY*3+2);
}

#if 0
/* model data */

void mdlEvent(CW_ID wid);
void mdlDisp(CW_ID wid);

#define MDL_LABEL_MAX MDL_NO_MAX

MENU mdlMenu = {
  10,6,10,MDL_LABEL_MAX+2,
  mdlEvent,
  mdlDisp,
  NULL
};

static int mdlPos = 0;

void
mdlCreate(void)
{
  __create_win(&mdlMenu);
}

void
mdlEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
    }else{
      if(pd->repeat & PAD_U){
	mdlPos--;
	if(mdlPos < 0) mdlPos++;
      }
      if(pd->repeat & PAD_D){
	mdlPos++;
	if(mdlPos >= MDL_LABEL_MAX) mdlPos--;
      }
    }
  }
}

static String mdlLabel[MDL_LABEL_MAX] = {
  "TETRA",
  "CUBE",
  "SPHERE",
};

void
mdlDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,0,"MODEL");
  for(i = 0;i < MDL_LABEL_MAX;i++){
    cwPutBuffer(wid,mdlLabel[i],1,i+1);
  }
  cwPutCursorLabel(wid,1,mdlPos+1,8,0);
}

#endif

