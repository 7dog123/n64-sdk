/*
 * [CCBL]
 *
 * bl_menu.c
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

/*- BLENDER ------------------------------------------------*/

void blndEvent(CW_ID wid);
void blndDisp(CW_ID wid);

#define BLND_LABEL_MAX 4

MENU blndMenu = {
  15,5,12,BLND_LABEL_MAX,
  blndEvent,
  blndDisp,
  NULL
};

static LABEL blndLabel[BLND_LABEL_MAX] = {
  {0,0,"RENDER_MD"},
  {0,1,"BL_COLOR"},
  {0,2,"FOG_COLOR"},
  {0,3,"CD AD AC "},
};

static blndPos = 0;

void
blndCreate(void)
{
  __create_win_nomode(&blndMenu);
}

void
blndEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  void rmCreate(void);
  void bcCreate(void);
  void fcCreate(void);
  void cdCreate(void);

  static createfunc blndcf[BLND_LABEL_MAX] = {
    rmCreate,
    bcCreate,
    fcCreate,
    cdCreate,
  };

  
  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      blndcf[blndPos]();
    }else{
      if(pd->trigger & PAD_U){
	blndPos--;
	if(blndPos < 0) blndPos++;
      }
      if(pd->trigger & PAD_D){
	blndPos++;
	if(blndPos >= BLND_LABEL_MAX) blndPos--;
      }
    }
  }
}

void
blndDisp(CW_ID wid)
{
  int i;
  LABEL *lp;

  cwPutWindowFrame(wid,1,NULL);
  for(i = 0,lp = blndLabel;i < BLND_LABEL_MAX;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
  }
  cwPutCursorMB(wid,blndPos,0);
}



/* render mode ----*/
void rmEvent(CW_ID wid);
void rmDisp(CW_ID wid);

MENU rmMenu = {
  2,4,33,18,
  rmEvent,
  rmDisp,
};

typedef struct BLS_LABEL_s {
  String str;
  int x,y;
  int regno;
  int csr;			/* Cursor type */
} BLS_LABEL;

#define BLS_LABEL_MAX 12
static BLS_LABEL blsl[BLS_LABEL_MAX] = {
  {"AA_EN:", 1,2-1,BL_AA_EN,0},
  {"Z_CMP:", 9,2-1,BL_Z_CMP,0},
  {"Z_UPD:",17,2-1,BL_Z_UPD,0},
  {"IM_RD:",25,2-1,BL_IM_RD,0},
  {"CV_XA:", 1,3-1,BL_CVG_X_ALPHA,0},
  {"A_CVG:", 9,3-1,BL_ALPHA_CVG_SEL,0},
  {"FC_BL:",17,3-1,BL_FORCE_BL,0},
  {"C_CVG:",25,3-1,BL_CLR_ON_CVG,0},
  {"CVG_DST_",1,5-1,0,0},
  {"CVG_DST_",1,5-1,0,0},
  {"ZMODE_",18,5-1,0,0},
  {"ZMODE_",18,5-1,0,0}
};

typedef struct BL_MUX_LABEL_s {
  String d_str;
  String m_str;
  int rval;
} BL_MUX_LABEL;

static BL_MUX_LABEL muxPM[] = {
  {"C_IN","CLR_IN",G_BL_CLR_IN},
  {"C_MEM","CLR_MEM",G_BL_CLR_MEM},
  {"C_BL","CLR_BL",G_BL_CLR_BL},
  {"C_FOG","CLR_FOG",G_BL_CLR_FOG},
};

static BL_MUX_LABEL muxA[] = {
  {"A_IN","A_IN",G_BL_A_IN},
  {"A_FOG","A_FOG",G_BL_A_FOG},
  {"A_SHA","A_SHADE",G_BL_A_SHADE},
  {"  0","0",G_BL_0},
};

static BL_MUX_LABEL muxB[] = {
  {"1-A","1MA",G_BL_1MA},
  {"A_MEM","A_MEM",G_BL_A_MEM},
  {"  1","1",G_BL_1},
  {"  0","0",G_BL_0},
};


typedef struct BL_MUX_s {
  int x,y;
  int cycl,rno;
  BL_MUX_LABEL *muxn;
  int xo,yo;
} BL_MUX;

#define BL_MUX_MAX 8
static BL_MUX muxdt[BL_MUX_MAX] = {
  /* cycle 1 */
  {2,7,RDP_1_CYCLE,BL_MUX_P,muxPM,0,0},
  {10,7,RDP_1_CYCLE,BL_MUX_A,muxA,0,0},
  {18,7,RDP_1_CYCLE,BL_MUX_M,muxPM,0,0},
  {26,7,RDP_1_CYCLE,BL_MUX_B,muxB,-2,0},
  /* cycle 2 */
  {2,11,RDP_2_CYCLE,BL_MUX_P,muxPM,0,0},
  {10,11,RDP_2_CYCLE,BL_MUX_A,muxA,0,0},
  {18,11,RDP_2_CYCLE,BL_MUX_M,muxPM,0,0},
  {26,11,RDP_2_CYCLE,BL_MUX_B,muxB,-2,0},
};

#define BL_SWITCH_MAX 8
static int bl_sw_rno[BL_SWITCH_MAX] = {
  BL_AA_EN,
  BL_Z_CMP,
  BL_Z_UPD,
  BL_IM_RD,
  BL_CVG_X_ALPHA,
  BL_ALPHA_CVG_SEL,
  BL_FORCE_BL,
  BL_CLR_ON_CVG,
};

static String bl_cvg_l[BL_CVG_DST_MAX+1] = {
  "CLAMP",
  "WRAP",
  "FULL",
  "SAVE",
};

static String bl_zm_l[BL_ZMODE_MAX+1] = {
  "OPA",
  "INTER",
  "XLU",
  "DEC",
};

#define RM_C_X_MAX 4
#define RM_C_Y_MAX 7

static int rmPosX = 0;
static int rmPosY = 0;

static LABEL rm_macro1_l[] = {
  {0,0,"AA_ZB_OPA_SURF"},
  {0,0,"AA_ZB_XLU_SURF"},
  {0,0,"AA_ZB_OPA_DECAL"},
  {0,0,"AA_ZB_XLU_DECAL"},
  {0,0,"AA_ZB_OPA_INTER"},
  {0,0,"AA_ZB_XLU_INTER"},
  {0,0,"AA_ZB_XLU_LINE"},
  {0,0,"AA_ZB_DEC_LINE"},
  {0,0,"AA_ZB_TEX_EDGE"},
  {0,0,"AA_ZB_TEX_INTER"},
  {0,0,"AA_ZB_SUB_SURF"},
  {0,0,"AA_ZB_PCL_SURF"},
  {0,0,"AA_ZB_OPA_TERR"},
  {0,0,"AA_ZB_TEX_TERR"},
  {0,0,"AA_ZB_SUB_TERR"},
  {0,0,"RA_ZB_OPA_SURF"},
  {0,0,"RA_ZB_OPA_DECAL"},
  {0,0,"RA_ZB_OPA_INTER"},
  {0,0,"AA_OPA_SURF"},
  {0,0,"AA_XLU_SURF"},
  {0,0,"AA_XLU_LINE"},
  {0,0,"AA_DEC_LINE"},
  {0,0,"AA_TEX_EDGE"},
  {0,0,"AA_SUB_SURF"},
  {0,0,"AA_PCL_SURF"},
  {0,0,"AA_OPA_TERR"},
  {0,0,"AA_TEX_TERR"},
  {0,0,"AA_SUB_TERR"},
  {0,0,"RA_OPA_SURF"},
  {0,0,"ZB_OPA_SURF"},
  {0,0,"ZB_XLU_SURF"},
  {0,0,"ZB_OPA_DECAL"},
  {0,0,"ZB_XLU_DECAL"},
  {0,0,"ZB_CLD_SURF"},
  {0,0,"ZB_OVL_SURF"},
  {0,0,"ZB_PCL_SURF"},
  {0,0,"OPA_SURF"},
  {0,0,"XLU_SURF"},
  {0,0,"CLD_SURF"},
  {0,0,"TEX_EDGE"},
  {0,0,"PCL_SURF"},
  {0,0,"G_RM_ADD"},
  {0,0,"FOG_SHADE_A"},
  {0,0,"FOG_PRIM_A"},
  {0,0,"PASS"},
  {0,0,NULL}
};

static LABEL rm_macro2_l[] = {
  {0,0,"AA_ZB_OPA_SURF2"},
  {0,0,"AA_ZB_XLU_SURF2"},
  {0,0,"AA_ZB_OPA_DECAL2"},
  {0,0,"AA_ZB_XLU_DECAL2"},
  {0,0,"AA_ZB_OPA_INTER2"},
  {0,0,"AA_ZB_XLU_INTER2"},
  {0,0,"AA_ZB_XLU_LINE2"},
  {0,0,"AA_ZB_DEC_LINE2"},
  {0,0,"AA_ZB_TEX_EDGE2"},
  {0,0,"AA_ZB_TEX_INTER2"},
  {0,0,"AA_ZB_SUB_SURF2"},
  {0,0,"AA_ZB_PCL_SURF2"},
  {0,0,"AA_ZB_OPA_TERR2"},
  {0,0,"AA_ZB_TEX_TERR2"},
  {0,0,"AA_ZB_SUB_TERR2"},
  {0,0,"RA_ZB_OPA_SURF2"},
  {0,0,"RA_ZB_OPA_DECAL2"},
  {0,0,"RA_ZB_OPA_INTER2"},
  {0,0,"AA_OPA_SURF2"},
  {0,0,"AA_XLU_SURF2"},
  {0,0,"AA_XLU_LINE2"},
  {0,0,"AA_DEC_LINE2"},
  {0,0,"AA_TEX_EDGE2"},
  {0,0,"AA_SUB_SURF2"},
  {0,0,"AA_PCL_SURF2"},
  {0,0,"AA_OPA_TERR2"},
  {0,0,"AA_TEX_TERR2"},
  {0,0,"AA_SUB_TERR2"},
  {0,0,"RA_OPA_SURF2"},
  {0,0,"ZB_OPA_SURF2"},
  {0,0,"ZB_XLU_SURF2"},
  {0,0,"ZB_OPA_DECAL2"},
  {0,0,"ZB_XLU_DECAL2"},
  {0,0,"ZB_CLD_SURF2"},
  {0,0,"ZB_OVL_SURF2"},
  {0,0,"ZB_PCL_SURF2"},
  {0,0,"OPA_SURF2"},
  {0,0,"XLU_SURF2"},
  {0,0,"CLD_SURF2"},
  {0,0,"TEX_EDGE2"},
  {0,0,"PCL_SURF2"},
  {0,0,"G_RM_ADD2"},
  {0,0,NULL}
};


void
rmCreate(void)
{
  __create_win(&rmMenu);
}

void
rmEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  int __rmValSet(void);
  void __rmCursorMove(void);

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(__rmValSet()) __rmCursorMove();
  }

}

void
rmSetFunc(int val)
{
  setRenderModeMacroVal((rmPosY-5),val);
  setMacroRMVal(rmPosY-5);
  setRMTouch(rmPosY-5,0);
}

int
__rmValSet(void )
{
  Pad_D *pd = &Mpad[0];
  int c;
  BL_MUX *blmp;

  void czsCreate(int type,int x,int y,String *strp);
  void blmuxCreate(int cycle,int rno,int prvx,int prvy,BL_MUX_LABEL *lp);

  switch(rmPosY){
  case 0:
  case 1:
    if(pd->trigger & PAD_CD){
      c = rmPosY*RM_C_X_MAX+rmPosX;
      toggleRMSwitchVal(blsl[c].regno);
      setRMTouch(0,1);
      setRMTouch(1,1);
      return 0;
    }
    break;
  case 2:
    if(pd->trigger & PAD_A){
      c = (rmPosX >> 1) & 1;
      czsCreate(c,
		rmMenu.x+9+c*15,
		rmMenu.y+3,
		(c)?bl_zm_l:bl_cvg_l);
      return 0;
    }
    break;
  case 3:
  case 4:
    if(pd->trigger & PAD_A){
      if(!((rmPosY==4) && (getCycleModeVal()==RDP_1_CYCLE))){
	blmp = &muxdt[(rmPosY-3)*4+rmPosX];
	blmuxCreate(blmp->cycl,
		    blmp->rno,
		    rmMenu.x+blmp->x+blmp->xo,
		    rmMenu.y+blmp->y+blmp->yo,
		    blmp->muxn);
      }
      return 0;
    }
    break;
  case 5:
  case 6:
    if(pd->trigger & PAD_A){
      if(!((rmPosY==6) && (getCycleModeVal()==RDP_1_CYCLE))){
	slbCreate((rmPosY-5)?rm_macro2_l:rm_macro1_l,
		  getRenderModeMacroVal(rmPosY-5),
		  10+rmMenu.x,(rmPosY-5)+rmMenu.y,
		  0,16,
		  rmSetFunc);
      }
      return 0;
    }
    break;
  }
  return 1;
}

void
__rmCursorMove(void )
{
  Pad_D *pd = &Mpad[0];

  if(pd->repeat & PAD_U){
    rmPosY--;
    if(rmPosY < 0) rmPosY++;
  }
  if(pd->repeat & PAD_D){
    rmPosY++;
    if(rmPosY >= RM_C_Y_MAX) rmPosY--;
  }

  if((rmPosY < 5) && (pd->repeat & PAD_L)){
    rmPosX -= (rmPosY==2)?2:1;
    if(rmPosX < 0) rmPosX = 0;
  }
  if(pd->repeat & PAD_R){
    rmPosX += (rmPosY==2)?2:1;
    if(rmPosX >= RM_C_X_MAX) rmPosX = RM_C_X_MAX-1;
  }
}   

void
rmDisp(CW_ID wid)
{
  int i;
  BLS_LABEL *bl_p;
  BL_MUX *mx_p;

  static String rmShiki = 
    "(       *       +       *       )";
   /*012345678901234567890123456789012*/
  static String rmSk2 =
    "(      +      )";
  static String rmWaru = 
    "-----------------";
  static String onoff[] = {"x","O"};
  static String nomacro_str = "**** NO MACRO ****";


  cwPutWindowFrame(wid,0,"RENDER MODE");
  cwPutSeparater(wid,0,5,rmMenu.w,1);
  cwPutSeparater(wid,0,15,rmMenu.w,1);
  for(i = 0,bl_p=blsl;i < BLS_LABEL_MAX;i++,bl_p++){
    cwPutBuffer(wid,bl_p->str,bl_p->x,bl_p->y);
  }
  cwPutBuffer(wid,rmShiki,0,7);
  cwPutBuffer(wid,rmWaru,8,8);
  cwPutBuffer(wid,rmSk2,9,9);
  cwPutBuffer(wid,rmShiki,0,11);
  cwPutBuffer(wid,rmWaru,8,12);
  cwPutBuffer(wid,rmSk2,9,13);

  /* print value*/
  
  for(i = 0,bl_p=blsl;i < BL_SWITCH_MAX;i++,bl_p++){
    cwPutBuffer(wid,
		onoff[getRMSwitchVal(bl_sw_rno[i])],
		bl_p->x+6,bl_p->y);
  } /* print switch */
  /*cvg*/
  cwPutBuffer(wid,bl_cvg_l[getRMCvgVal()],9,4);
  /*zmode*/
  cwPutBuffer(wid,bl_zm_l[getRMZmodeVal()],24,4);
  /*mux*/
  cwPutBuffer(wid,"[MUX1]",0,6);
  cwPutBuffer(wid,(getCycleModeVal())?"[MUX2]":"[----]",0,10);
  for(i = 0;i < 2;i++){
    cwPutBuffer(wid,muxPM[getRMMuxVal(i,BL_MUX_P)].d_str,2,7+i*4);
    cwPutBuffer(wid,muxA[getRMMuxVal(i,BL_MUX_A)].d_str,10,7+i*4);
    cwPutBuffer(wid,muxA[getRMMuxVal(i,BL_MUX_A)].d_str,10,9+i*4);
    cwPutBuffer(wid,muxPM[getRMMuxVal(i,BL_MUX_M)].d_str,18,7+i*4);
    cwPutBuffer(wid,muxB[getRMMuxVal(i,BL_MUX_B)].d_str,26,7+i*4);
    cwPutBuffer(wid,muxB[getRMMuxVal(i,BL_MUX_B)].d_str,18,9+i*4);
  }
  /* macro */
  cwPutBuffer(wid,"[CYCLE1]:",0,16);
  (getRMTouch(0))?
    cwPutBuffer(wid,nomacro_str,10,16):
    cwPutBuffer(wid,rm_macro1_l[getRenderModeMacroVal(RDP_1_CYCLE)].str,10,16);
  cwPutBuffer(wid,(getCycleModeVal())?"[CYCLE2]:":"[------]:",0,17);
  (getRMTouch(1))?
    cwPutBuffer(wid,nomacro_str,10,17):
    cwPutBuffer(wid,rm_macro2_l[getRenderModeMacroVal(RDP_2_CYCLE)].str,10,17);
  /*- cursor put */
  if(rmPosY < 3){
      bl_p = &blsl[rmPosY*RM_C_X_MAX+rmPosX];
    if(rmPosY != 2){
      cwPutCursorLabel(wid,bl_p->x,bl_p->y,5,1);
    }else{
      cwPutCursorLabel(wid,bl_p->x+strlen(bl_p->str),bl_p->y,5,0 );
    }
  }else{
    if(rmPosY < 5){
      mx_p = &muxdt[(rmPosY-3)*RM_C_X_MAX+rmPosX];
      cwPutCursorLabel(wid,mx_p->x,mx_p->y,5,0);
    }else{
      {
	int len;
	if(getRMTouch(rmPosY-5)){
	  len = strlen(nomacro_str);
	}else{
	  len = strlen((rmPosY-5)?
		 rm_macro2_l[getRenderModeMacroVal(RDP_2_CYCLE)].str:
		 rm_macro1_l[getRenderModeMacroVal(RDP_1_CYCLE)].str);
	}
	cwPutCursorLabel(wid,10,16+(rmPosY-5),len,0);
      }
    }
  }

}


/* cvg zmode set*/
void czsEvent(CW_ID wid);
void czsDisp(CW_ID wid);
void czsDelete(CW_ID wid);

MENU czsMenu = {
  0,0,5,4,
  czsEvent,
  czsDisp,
  NULL
};

static String *czsStr;
static int czsPos;
static int czsType;


void (*czssetfnc[2])(int ) = {
  setRMCvgVal,
  setRMZmodeVal

};
int (*czsgetfnc[2])(void) = {
  getRMCvgVal,
  getRMZmodeVal
};

void
czsCreate(int type,int x,int y,String *strp)
{

  czsStr = strp;
  czsType = type;
  czsMenu.x = x;
  czsMenu.y = y;
  czsMenu.w = 5;		/* Arbitrary */
  czsMenu.h = 4;		/* Arbitrary */
  czsPos = czsgetfnc[type]();
  __create_win(&czsMenu);
}

void
czsEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  int old;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      old = czsgetfnc[czsType]();
      czssetfnc[czsType](czsPos);
      if(old != czsgetfnc[czsType]()){
	setRMTouch(0,1);
	setRMTouch(1,1);
      }
      cwDeleteWindow(wid);
    }else{
      if(pd->repeat & PAD_U){
	czsPos--;
	if(czsPos < 0) czsPos++;
      }
      if(pd->repeat & PAD_D){
	czsPos++;
	if(czsPos >= 4) czsPos--;
      }
    }
  }

}
void
czsDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,3,NULL);
  for(i = 0;i < 4;i++)
    cwPutBuffer(wid,czsStr[i],0,i);
  cwPutCursorMB(wid,czsPos,1);
}

/* blender mux set*/

void blmuxEvent(CW_ID wid);
void blmuxDisp(CW_ID wid);

MENU blmuxMenu = {
  0,0,5,4,
  blmuxEvent,
  blmuxDisp,
  NULL
};

static BL_MUX_LABEL *blmuxLabel;
static int blmuxPos;
static int blmuxCycle;
static int blmuxRno;


void
blmuxCreate(int cycle,int rno,int prvx,int prvy,BL_MUX_LABEL *lp)
{

  blmuxLabel = lp;
  blmuxCycle = cycle;
  blmuxRno = rno;
  blmuxMenu.x = prvx+0;
  blmuxMenu.y = prvy+0;
  blmuxMenu.w = 7;		/* Arbitrary */
  blmuxMenu.h = 4;		/* Arbitrary */
  blmuxPos = getRMMuxVal(cycle,rno);
  __create_win(&blmuxMenu);
}

void
blmuxEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  int old;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      old = getRMMuxVal(blmuxCycle,blmuxRno);
      setRMMuxVal(blmuxCycle,blmuxRno,blmuxPos);
      if(old != getRMMuxVal(blmuxCycle,blmuxRno)) setRMTouch(blmuxCycle,1);
      cwDeleteWindow(wid);
    }else{
      if(pd->repeat & PAD_U){
	blmuxPos--;
	if(blmuxPos < 0) blmuxPos++;
      }
      if(pd->repeat & PAD_D){
	blmuxPos++;
	if(blmuxPos >= 4) blmuxPos--;
      }
    }
  }

}
void
blmuxDisp(CW_ID wid)
{
  int i;

  cwPutWindowFrame(wid,3,NULL);
  for(i = 0;i < 4;i++)
    cwPutBuffer(wid,blmuxLabel[i].m_str,0,i);
  cwPutCursorMB(wid,blmuxPos,1);
}

/* Blend color */

void bcEvent(CW_ID wid);
void bcDisp(CW_ID wid);

MENU bcMenu = {
  11,10,11,4,
  bcEvent,
  bcDisp,
  NULL
};
static bcPos = 0;
void

bcCreate(void)
{
  __create_win(&bcMenu);
}

void
bcEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  u8 bc_val;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    bc_val = getBlendColVal(bcPos);
    if(touch_u8_val(&bc_val)){
      setBlendColVal(bcPos,bc_val);
    }else{
      if(pd->repeat & PAD_U){
	bcPos--;
	if(bcPos < 0) bcPos++;
      }
      if(pd->repeat & PAD_D){
	bcPos++;
	if(bcPos >= BLEND_COL_LEN) bcPos--;
      }
    }
  }
}

void
bcDisp(CW_ID wid)
{
  int i;
  LABEL *lp;
  static u8 pb[16];

  static LABEL enc_l[] = {
    {1,0,"RED"},
    {1,1,"GREEN"},
    {1,2,"BLUE"},
    {1,3,"ALPHA"},
  };

  cwPutWindowFrame(wid,0,"BLND COL");
  for(i = 0,lp=enc_l;i < BLEND_COL_LEN;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",6,lp->y);
    sprintf(pb,"%02X",getBlendColVal(i));
    cwPutBuffer(wid,pb,8,lp->y);
  }
  cwPutCursorLabel(wid,1,enc_l[bcPos].y,5,2);
}

/* Fog color */

void fcEvent(CW_ID wid);
void fcDisp(CW_ID wid);

MENU fcMenu = {
  12,11,11,4,
  fcEvent,
  fcDisp,
  NULL
};
static fcPos = 0;
void

fcCreate(void)
{
  __create_win(&fcMenu);
}

void
fcEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  u8 fc_val;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    fc_val = getFogColVal(fcPos);
    if(touch_u8_val(&fc_val)){
      setFogColVal(fcPos,fc_val);
    }else{
      if(pd->repeat & PAD_U){
	fcPos--;
	if(fcPos < 0) fcPos++;
      }
      if(pd->repeat & PAD_D){
	fcPos++;
	if(fcPos >= FOG_COL_LEN) fcPos--;
      }
    }
  }
}

void
fcDisp(CW_ID wid)
{
  int i;
  LABEL *lp;
  static u8 pb[16];

  static LABEL enc_l[] = {
    {1,0,"RED"},
    {1,1,"GREEN"},
    {1,2,"BLUE"},
    {1,3,"ALPHA"},
  };

  cwPutWindowFrame(wid,0,"FOG COL");
  for(i = 0,lp=enc_l;i < FOG_COL_LEN;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",6,lp->y);
    sprintf(pb,"%02X",getFogColVal(i));
    cwPutBuffer(wid,pb,8,lp->y);
  }
  cwPutCursorLabel(wid,1,enc_l[fcPos].y,5,2);
}

/* {color,alpha} dither  alpha compare */

void cdEvent(CW_ID wid);
void cdDisp(CW_ID wid);

#define CD_AD_AC_MAX 3

MENU cdMenu = {
  8,8,20,12,
  cdEvent,
  cdDisp,
  NULL
};

int cdPos = 0;

static void (*cdsetfunc[CD_AD_AC_MAX])(int val) = {
  setColorDitherVal,
  setAlphaDitherVal,
  setAlphaCompareVal
};

static int (*cdgetfunc[CD_AD_AC_MAX])(void) = {
  getColorDitherVal,
  getAlphaDitherVal,
  getAlphaCompareVal
};

static LABEL cdvall[] = {
  {0,0,"MAGICSQ"},
  {0,0,"BAYER"},
  {0,0,"NOISE"},
  {0,0,"DISABLE"},
  {0,0,NULL}
};
static LABEL advall[] = {
  {0,0,"PATTERN"},
  {0,0,"NOTPATTERN"},
  {0,0,"NOISE"},
  {0,0,"DISABLE"},
  {0,0,NULL}
};
static LABEL acvall[] = {
  {0,0,"NONE"},
  {0,0,"THRESHOLD"},
  {0,0,"DITHER"},
  {0,0,NULL}
};

static LABEL *cdlbl[CD_AD_AC_MAX] = {
  cdvall,advall,acvall
};

static LABEL cdpl[CD_AD_AC_MAX] = {
  4,2,"G_CD_",
  4,6,"G_AD_",
  4,10,"G_AC_"
};

void
cdCreate(void)
{
  __create_win(&cdMenu);
}

void
cdSetFunc(int val)
{
  cdsetfunc[cdPos](val);
}

void
cdEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      slbCreate(cdlbl[cdPos],cdgetfunc[cdPos](),
		cdMenu.x+10,cdMenu.y+cdpl[cdPos].y-1,
		0,0,
		cdSetFunc);
    }else{
      if(pd->trigger & PAD_U){
	cdPos--;
	if(cdPos < 0 ) cdPos++;
      }
      if(pd->trigger & PAD_D){
	cdPos++;
	if(cdPos >= CD_AD_AC_MAX ) cdPos--;
      }
    }
  }

}


void
cdDisp(CW_ID wid)
{
  int i;
  LABEL *lp;

  static LABEL ll[CD_AD_AC_MAX] = {
    0,0,"[COLOR DITHER]",
    0,4,"[ALPHA DITHER]",
    0,8,"[ALPHA COMPARE]"
  };
  static String ad2cd_l[] = {
    "MAGICSQ)",
    "BAYER)",
    "MAGICSQ)",
    "BAYER)",
  };
  
  cwPutWindowFrame(wid,0,"CD AD AC");
  for(i = 0;i < CD_AD_AC_MAX;i++){
    cwPutBuffer(wid,ll[i].str,ll[i].x,ll[i].y);
    cwPutBuffer(wid,cdpl[i].str,cdpl[i].x,cdpl[i].y);
    lp = cdlbl[i];
    cwPutBuffer(wid,lp[cdgetfunc[i]()].str,9,cdpl[i].y);
  }
  i = cdgetfunc[1]();
  if(i < 2){
    cwPutBuffer(wid,(i)?"(~":"(",10,7);
    cwPutBuffer(wid,ad2cd_l[cdgetfunc[0]()],11+i,7);
  }else{
    cwPutBuffer(wid,"(-------)",10,7);
  }
  
  cwPutCursorLabel(wid,9,cdpl[cdPos].y,10,0);

}




