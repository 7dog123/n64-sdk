/*
 * [CCBL]
 *
 * rdp_menu.c
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

/* dp section menu ------- */
#define RDP_LABEL_MAX 4

void rdpEvent(CW_ID wid);
void rdpDisp(CW_ID wid);

int rdpPos = 0;

MENU rdpMENU = {
  7,2,12,RDP_LABEL_MAX,
  rdpEvent,
  rdpDisp,
  NULL
};


void
rdpCreate(void )
{
  __create_win_nomode(&rdpMENU);

}

static LABEL rdpLabel[RDP_LABEL_MAX] = {
  {0,0,"CYCLE_TYPE"},
  {0,1,"CL_COMBINER"},
  {0,2,"BLENDER"},
  {0,3,"TEX_FILTER"},
};

void
rdpEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  void ctCreate(void);
  void combCreate(void);
  void blndCreate(void);
  void tfCreate(void);
  static createfunc rdpcf[RDP_LABEL_MAX] = {
    ctCreate,
    combCreate,
    blndCreate,
    tfCreate,
  };

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      rdpcf[rdpPos]();
    }else{
      if(pd->trigger & PAD_U){
	rdpPos--;
	if(rdpPos < 0) rdpPos = 0;
      }
      if(pd->trigger & PAD_D){
	rdpPos++;
	if(rdpPos >= RDP_LABEL_MAX) rdpPos = (RDP_LABEL_MAX - 1);
      }
    }
  }
}

void
rdpDisp(CW_ID wid)
{
  int i;
  LABEL *lp;

  cwPutWindowFrame(wid,1,NULL);
  for(i = 0,lp = rdpLabel;i < RDP_LABEL_MAX;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
  }
  cwPutCursorMB(wid,rdpPos,0);
}


/* cycle type------*/

void ctEvent(CW_ID wid);
void ctDisp(CW_ID wid);

static int ctPos;

MENU ctMenu = {
  16,3,14,4,
  ctEvent,
  ctDisp,
};

void
ctCreate(void)
{
  __create_win(&ctMenu);
  ctPos = getCycleModeVal();
}

void
ctEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  static int ct[2] = {RDP_1_CYCLE,RDP_2_CYCLE};

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setCycleModeVal(ct[ctPos]);
    }else{
      if(pd->repeat &(PAD_U |PAD_D))
	ctPos = (ctPos+1) & 1;
    }
  }
}

void
ctDisp(CW_ID wid)
{
  cwPutWindowFrame(wid,0,"CYCLE TYPE");
  cwPutBuffer(wid,"G_CYC_1CYCLE",1,1);
  cwPutBuffer(wid,"G_CYC_2CYCLE",1,2);
  cwPutCursorLabel(wid,1,ctPos+1,12,0);
}

/*- color combiner --------------------------------------------*/

void combEvent(CW_ID wid);
void combDisp(CW_ID wid);

#define COMB_LABEL_MAX 3

MENU combMenu = {
  16,4,10,COMB_LABEL_MAX,
  combEvent,
  combDisp,
  NULL
};

static LABEL combLabel[COMB_LABEL_MAX] = {
  {0,0,"COMBINE_MD"},
  {0,1,"ENV_COLOR"},
  {0,2,"PRIM_COLOR"}
};

static combPos = 0;

void
combCreate(void)
{
  __create_win_nomode(&combMenu);
}

void
combEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  void cmCreate(void);
  void ecCreate(void);
  void pcCreate(void);
  static createfunc combcf[COMB_LABEL_MAX] = {
    cmCreate,
    ecCreate,
    pcCreate,
  };

  
  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      combcf[combPos]();
    }else{
      if(pd->trigger & PAD_U){
	combPos--;
	if(combPos < 0) combPos++;
      }
      if(pd->trigger & PAD_D){
	combPos++;
	if(combPos >= COMB_LABEL_MAX) combPos--;
      }
    }
  }
}

void
combDisp(CW_ID wid)
{
  int i;
  LABEL *lp;

  cwPutWindowFrame(wid,1,NULL);
  for(i = 0,lp = combLabel;i < COMB_LABEL_MAX;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
  }
  cwPutCursorMB(wid,combPos,0);
}


/* combine mode ---*/

typedef struct CC_LABEL_s {
  String dstr;
  String mstr;
  int mux;
} CC_LABEL;

static CC_LABEL ccA[] = {
  {"COMB","COMBINE",G_CCMUX_COMBINED},
  {"TEX0","TEXEL0",G_CCMUX_TEXEL0},
  {"TEX1","TEXEL1",G_CCMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE","SHADE",G_CCMUX_SHADE},
  {" ENV","ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"NOISE","NOISE",G_CCMUX_NOISE},
  {" 1.0","1.0",G_CCMUX_1},
  {" 0.0","0.0",G_CCMUX_0},
  {NULL,NULL,0}
};
static CC_LABEL ccB[] = {
  {"COMB","COMBINED",G_CCMUX_COMBINED},
  {"TEX0","TEXEL0",G_CCMUX_TEXEL0},
  {"TEX1","TEXEL1",G_CCMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE","SHADE",G_CCMUX_SHADE},
  {" ENV","ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"CENTR","CENTER",G_CCMUX_CENTER},
  {" K4", "K4",G_CCMUX_K4},
  {" 0.0","0.0",G_CCMUX_0},
  {NULL,NULL,0}
};
static CC_LABEL ccC[] = {
  {"COMB","COMBINED",G_CCMUX_COMBINED},
  {"TEX0","TEXEL0",G_CCMUX_TEXEL0},
  {"TEX1","TEXEL1",G_CCMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE","SHADE",G_CCMUX_SHADE},
  {"ENV","ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {"SCALE","SCALE",G_CCMUX_SCALE},
  {" C_AL","COMBINED_ALPHA",G_CCMUX_COMBINED_ALPHA},
  {"T0_AL","TEXEL0_ALPHA",G_CCMUX_TEXEL0_ALPHA},
  {"T1_AL","TEXEL1_ALPHA",G_CCMUX_TEXEL1_ALPHA},
  {" P_AL","PRIMITIVE_ALPHA",G_CCMUX_PRIMITIVE_ALPHA},
  {" S_AL","SHADE_ALPHA",G_CCMUX_SHADE_ALPHA},
  {" E_AL","ENV_ALPHA",G_CCMUX_ENV_ALPHA},
  {"LOD_F","LOD_FRACTION",G_CCMUX_LOD_FRACTION},
  {"P_L_F","PRIM_LOD_FRAC",G_CCMUX_PRIM_LOD_FRAC},
  {" K5","K5",G_CCMUX_K5},
  {" 0.0","0.0",G_CCMUX_0},
  {NULL,NULL,0}
};

static CC_LABEL ccD[] = {
  {"COMB","COMBINED",G_CCMUX_COMBINED},
  {"TEX0","TEXEL0",G_CCMUX_TEXEL0},
  {"TEX1","TEXEL1",G_CCMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_CCMUX_PRIMITIVE},
  {"SHADE","SHADE",G_CCMUX_SHADE},
  {" ENV","ENVIRONMENT",G_CCMUX_ENVIRONMENT},
  {" 1.0","1.0",G_CCMUX_1},
  {" 0.0","0.0",G_CCMUX_0},
  {NULL,NULL,0}
};
static CC_LABEL acABD[] = {
  {"COMB","COMBINED",G_ACMUX_COMBINED},
  {"TEX0","TEXEL0",G_ACMUX_TEXEL0},
  {"TEX1","TEXEL1",G_ACMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_ACMUX_PRIMITIVE},
  {"SHADE","SHADE",G_ACMUX_SHADE},
  {" ENV","ENVIRONMENT",G_ACMUX_ENVIRONMENT},
  {" 1.0","1.0",G_ACMUX_1},
  {" 0.0","0.0",G_ACMUX_0},
  {NULL,NULL,0}
};
static CC_LABEL acC[] = {
  {"TEX0","TEXEL0",G_ACMUX_TEXEL0},
  {"TEX1","TEXEL1",G_ACMUX_TEXEL1},
  {"PRIM","PRIMITIVE",G_ACMUX_PRIMITIVE},
  {"SHADE","SHADE",G_ACMUX_SHADE},
  {"ENV","ENVIRONMENT",G_ACMUX_ENVIRONMENT},
  {"LOD_F","LOD_FRACTION",G_ACMUX_LOD_FRACTION},
  {"P_L_F","PRIM_LOD_FRAC",G_ACMUX_PRIM_LOD_FRAC},
  {" 0.0","0.0",G_ACMUX_0},
  {NULL,NULL,0}
};

CC_LABEL *
__cclabel(int mval,CC_LABEL *clp)
{

  for(;clp->dstr != NULL;clp++){
    if(clp->mux == mval) return clp;
  }
  return NULL;
}


typedef struct CCPS_s {
  int x,y;
  int cycl,rno;
  CC_LABEL *ccl;
  int xo,yo;
} CCPS;
  
#define CC_DT_MAX 16
static CCPS ccdt[CC_DT_MAX] = {
  {2,1,0,CC_A,ccA,0,0},
  {10,1,0,CC_B,ccB,0,0},
  {19,1,0,CC_C,ccC,-4,0},
  {27,1,0,CC_D,ccD,-6,0},

  {2,3,1,CC_A,ccA,0,0},
  {10,3,1,CC_B,ccB,0,0},
  {19,3,1,CC_C,ccC,-4,-1},
  {27,3,1,CC_D,ccD,-6,0},

  {2,6,0,AC_A,acABD,0,0},
  {10,6,0,AC_B,acABD,0,0},
  {19,6,0,AC_C,acC,0,0},
  {27,6,0,AC_D,acABD,-6,0},

  {2,8,1,AC_A,acABD,0,0},
  {10,8,1,AC_B,acABD,0,0},
  {19,8,1,AC_C,acC,0,0},
  {27,8,1,AC_D,acABD,-6,0},
};

static LABEL cc_macro1_l[] = {
  {0,0,"PRIMITIVE"},
  {0,0,"SHADE"},
  {0,0,"MODULATEI"},
  {0,0,"MODULATEIA"},
  {0,0,"MODULATEIDECALA"},
  {0,0,"MODULATERGB"},
  {0,0,"MODULATERGBA"},
  {0,0,"MODULATERGBDECALA"},
  {0,0,"MODULATEI_PRIM"},
  {0,0,"MODULATEIA_PRIM"},
  {0,0,"MODULATEIDECALA_PRIM"},
  {0,0,"MODULATERGB_PRIM"},
  {0,0,"MODULATERGBA_PRIM"},
  {0,0,"MODULATERGBDECALA_PRIM"},
  {0,0,"DECALRGB"},
  {0,0,"DECALRGBA"},
  {0,0,"BLENDI"},
  {0,0,"BLENDIA"},
  {0,0,"BLENDIDECALA"},
  {0,0,"BLENDRGBA"},
  {0,0,"BLENDRGBDECALA"},
  {0,0,"ADDRGB"},
  {0,0,"ADDRGBDECALA"},
  {0,0,"REFLECTRGB"},
  {0,0,"REFLECTRGBDECALA"},
  {0,0,"HILITERGB"},
  {0,0,"HILITERGBA"},
  {0,0,"HILITERGBDECALA"},
  {0,0,"SHADEDECALA"},
  {0,0,"BLENDPE"},
  {0,0,"BLENDPEDECALA"},
  {0,0,"TRILERP"},
  {0,0,"INTERFERENCE"},
  {0,0,NULL}
};

static LABEL cc_macro2_l[] = {
  {0,0,"PASS2"},
  {0,0,"MODULATEI2"},
  {0,0,"MODULATEIA2"},
  {0,0,"MODULATERGB2"},
  {0,0,"MODULATERGBA2"},
  {0,0,"MODULATEI_PRIM2"},
  {0,0,"MODULATEIA_PRIM2"},
  {0,0,"MODULATERGB_PRIM2"},
  {0,0,"MODULATERGBA_PRIM2"},
  {0,0,"DECALRGB2"},
  {0,0,"BLENDI2"},
  {0,0,"BLENDIA2"},
  {0,0,"HILITERGB2"},
  {0,0,"HILITERGBA2"},
  {0,0,"HILITERGBDECALA2"},
  {0,0,"HILITERGBPASSA2"},
  {0,0,NULL}
};


void cmEvent(CW_ID wid);
void cmDisp(CW_ID wid);

static int cmPosX = 0;
static int cmPosY = 0;

#define CM_X_MAX 4
#define CM_Y_MAX 6


MENU cmMenu = {
  2,5,33,12,
  cmEvent,
  cmDisp,
};

void
cmCreate(void)
{
  __create_win(&cmMenu);
}

void
cmSetFunc(int val)
{
  setCCACMacroVal((cmPosY-4),val);
  setMacroCombineModeVal(cmPosY-4);
  setCCACTouch(cmPosY-4,0);
}

void
cmEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  CCPS *ccps;
  void ccsmCreate(int x,int y,int cycl,int rno,CC_LABEL *cl);

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      if(cmPosY < 4){
	if(!((cmPosY&1) && (getCycleModeVal()==RDP_1_CYCLE))){
	  ccps = &ccdt[cmPosY*CM_X_MAX+cmPosX];

	  ccsmCreate(ccps->x+ccps->xo+cmMenu.x,
		     ccps->y+ccps->yo+cmMenu.y,
		     ccps->cycl,
		     ccps->rno,
		     ccps->ccl);
	}
      }else{	/* macro menu */
	if(!((cmPosY&1) && (getCycleModeVal()==RDP_1_CYCLE))){
	  slbCreate((cmPosY-4)?cc_macro2_l:cc_macro1_l,
		    getCCACMacroVal((cmPosY-4)),
		    10+cmMenu.x,0+cmMenu.y,
		    0,16,
		    cmSetFunc);
	}
      }
    }else{
      if(pd->trigger & PAD_L){
	cmPosX--;
	if(cmPosX < 0) cmPosX++;
      }
      if(pd->trigger & PAD_R){
	cmPosX++;
	if(cmPosX >= CM_X_MAX) cmPosX--;
      }
      if(pd->trigger & PAD_U){
	cmPosY--;
	if(cmPosY < 0) cmPosY++;
      }
      if(pd->trigger & PAD_D){
	cmPosY++;
	if(cmPosY >= CM_Y_MAX) cmPosY--;
      }
    }
  }

}

static String shiki = "(       -       )*       +       ";

void
cmDisp(CW_ID wid)
{
  CC_LABEL *cl;
  LABEL *ll;
  CCPS *ccps;
  int i;
  static String nashi = "[---]";
  static String nomacro_str = "**** NO MACRO ****";

  cwPutWindowFrame(wid,0,"COMBINE MODE");

  cwPutSeparater(wid,0,4,cmMenu.w,0);
  cwPutSeparater(wid,0,9,cmMenu.w,1);
  //  cwPutBuffer(wid,cmSep,0,9);

  cwPutBuffer(wid,"[CC1]",0,0);
  cwPutBuffer(wid,shiki,0,1);
  cwPutBuffer(wid,(getCycleModeVal()==RDP_1_CYCLE)?nashi:"[CC2]",0,2);
  cwPutBuffer(wid,shiki,0,3);
  cwPutBuffer(wid,"[AC1]",0,5);
  cwPutBuffer(wid,shiki,0,6);
  cwPutBuffer(wid,(getCycleModeVal()==RDP_1_CYCLE)?nashi:"[AC2]",0,7);
  cwPutBuffer(wid,shiki,0,8);

  
  for(i = 0,ccps=ccdt;i < CC_DT_MAX;i++,ccps++){
    cl = __cclabel(getCCACVal(ccps->cycl,ccps->rno),ccps->ccl);
    cwPutBuffer(wid,cl->dstr,ccps->x,ccps->y);
  }

  cwPutBuffer(wid,"[CYCLE1]:",0,10);
  (getCCACTouch(RDP_1_CYCLE))?
    cwPutBuffer(wid,nomacro_str,10,10):
    cwPutBuffer(wid,cc_macro1_l[getCCACMacroVal(RDP_1_CYCLE)].str,10,10);
  cwPutBuffer(wid,(getCycleModeVal())?"[CYCLE2]:":"[------]:",0,11);
  (getCCACTouch(RDP_2_CYCLE))?
    cwPutBuffer(wid,nomacro_str,10,11):
    cwPutBuffer(wid,cc_macro2_l[getCCACMacroVal(RDP_2_CYCLE)].str,10,11);

  if(cmPosY < 4){
    ccps = &ccdt[cmPosY*CM_X_MAX+cmPosX];
    cwPutCursorLabel(wid,ccps->x,ccps->y,5,0);
  }else{
    ll = (cmPosY-4)?
      &cc_macro2_l[getCCACMacroVal(RDP_2_CYCLE)]:
      &cc_macro1_l[getCCACMacroVal(RDP_1_CYCLE)];
    cwPutCursorLabel(wid,10,(cmPosY-4)+10,
		     strlen((getCCACTouch(cmPosY-4))?nomacro_str:ll->str),0);
  }

}


/* CC select menu */
void ccsmEvent(CW_ID wid);
void ccsmDisp(CW_ID wid);
void ccsmDelete(CW_ID wid);

MENU ccsmMenu = {
  0,0,0,0,
  ccsmEvent,
  ccsmDisp,
  NULL
};

CC_LABEL *ccsmCCL;
int ccsmReg;
int ccsmCycle;
int ccsmPos;

void
ccsmCreate(int x,int y,int cycl,int rno,CC_LABEL *cl)
{
  CC_LABEL *clt;
  int  i,a;
  int nowCC;
  int max_w;

  nowCC = getCCACVal(cycl,rno);
  max_w = 0;
  for(i = 0,clt=cl;;i++,clt++){
    if(clt->dstr == NULL) break;
    a = strlen(clt->mstr);
    if(a > max_w) max_w = a;
    if(nowCC == clt->mux) ccsmPos = i;
  }

  ccsmCCL = cl;
  ccsmMenu.x = x;
  ccsmMenu.y = y;
  ccsmMenu.w = max_w;
  ccsmMenu.h = i;
  ccsmReg = rno;
  ccsmCycle = cycl;

  __create_win(&ccsmMenu);

}

void
ccsmEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  int old;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      old = getCCACVal(ccsmCycle,ccsmReg);
      setCCACVal(ccsmCycle,ccsmReg,ccsmCCL[ccsmPos].mux);
      if(old != getCCACVal(ccsmCycle,ccsmReg))
	setCCACTouch(ccsmCycle,1);
      cwDeleteWindow(wid);
    }else{
      if(pd->repeat & PAD_U){
	ccsmPos--;
	if(ccsmPos < 0) ccsmPos++;
      }
      if(pd->repeat & PAD_D){
	ccsmPos++;
	if(ccsmPos >= ccsmMenu.h) ccsmPos--;
      }
    }
  }
}


void
ccsmDisp(CW_ID wid)
{
  CC_LABEL *cl;
  int i;

  cwPutWindowFrame(wid,3,NULL);
  for(i=0,cl = ccsmCCL;cl->mstr != NULL;i++,cl++){
    cwPutBuffer(wid,cl->mstr,0,i);
  }
  cwPutCursorMB(wid,ccsmPos,1);
}

/* prim color */

void pcEvent(CW_ID wid);
void pcDisp(CW_ID wid);

MENU pcMenu = {
  13,10,11,7,
  pcEvent,
  pcDisp,
  NULL
};
static pcPos = 0;
void
pcCreate(void)
{
  __create_win(&pcMenu);
}

void
pcEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  u8 pc_val;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    pc_val = getPrimColVal(pcPos);
    if(touch_u8_val(&pc_val)){
      setPrimColVal(pcPos,pc_val);
    }else{
      if(pd->repeat & PAD_U){
	pcPos--;
	if(pcPos < 0) pcPos++;
      }
      if(pd->repeat & PAD_D){
	pcPos++;
	if(pcPos >= PRIM_COL_LEN) pcPos--;
      }
    }
  }
}

void
pcDisp(CW_ID wid)
{
  int i;
  LABEL *lp;
  static u8 pb[16];

  static LABEL pmc_l[] = {
    {1,0,"RED"},
    {1,1,"GREEN"},
    {1,2,"BLUE"},
    {1,3,"ALPHA"},
    {1,5,"MIN"},
    {1,6,"LOD"}
  };

  cwPutWindowFrame(wid,0,"PRIM COL");
  cwPutSeparater(wid,0,4,pcMenu.w,0);
  for(i = 0,lp=pmc_l;i < PRIM_COL_LEN;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",6,lp->y);
    sprintf(pb,"%02X",getPrimColVal(i));
    cwPutBuffer(wid,pb,8,lp->y);
  }
  cwPutCursorLabel(wid,1,pmc_l[pcPos].y,5,2);
}

/* Env color */

void ecEvent(CW_ID wid);
void ecDisp(CW_ID wid);

MENU ecMenu = {
  13,9,11,4,
  ecEvent,
  ecDisp,
  NULL
};

static ecPos = 0;
void
ecCreate(void)
{
  __create_win(&ecMenu);
}

void
ecEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];
  u8 ec_val;

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    ec_val = getEnvColVal(ecPos);
    if(touch_u8_val(&ec_val)){
      setEnvColVal(ecPos,ec_val);
    }else{
      if(pd->repeat & PAD_U){
	ecPos--;
	if(ecPos < 0) ecPos++;
      }
      if(pd->repeat & PAD_D){
	ecPos++;
	if(ecPos >= ENV_COL_LEN) ecPos--;
      }
    }
  }
}

void
ecDisp(CW_ID wid)
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

  cwPutWindowFrame(wid,0,"ENV COL");
  for(i = 0,lp=enc_l;i < ENV_COL_LEN;i++,lp++){
    cwPutBuffer(wid,lp->str,lp->x,lp->y);
    cwPutBuffer(wid,":",6,lp->y);
    sprintf(pb,"%02X",getEnvColVal(i));
    cwPutBuffer(wid,pb,8,lp->y);
  }
  cwPutCursorLabel(wid,1,enc_l[ecPos].y,5,2);
}


/* TextureFilter */
void tfEvent(CW_ID wid);
void tfDisp(CW_ID wid);

MENU tfMenu = {
  9,9,16,5,
  tfEvent,
  tfDisp,
  NULL
};

static tfPos = 0;
void
tfCreate(void)
{
  __create_win(&tfMenu);
  tfPos = getTexFiltVal();
}

void
tfEvent(CW_ID wid)
{
  Pad_D *pd = &Mpad[0];

  if(pd->trigger & PAD_B){
    cwDeleteWindow(wid);
  }else{
    if(pd->trigger & PAD_A){
      setTexFiltVal(tfPos);
    }else{
      if(pd->repeat & PAD_U){
	tfPos--;
	if(tfPos < 0) tfPos++;
      }
      if(pd->repeat & PAD_D){
	tfPos++;
	if(tfPos >= TEX_FILT_LEN) tfPos--;
      }
    }
  }
}

void
tfDisp(CW_ID wid)
{
  int i;
  static String tf_l[] = {
    "G_TF_POINT",
    "G_TF_AVERAGE",
    "G_TF_BILERP"
  };

  cwPutWindowFrame(wid,0,"TEXTURE FILTER");

  for(i = 0;i < TEX_FILT_LEN;i++){
    cwPutBuffer(wid,tf_l[i],2,i+1);
  }
  cwPutCursorLabel(wid,2,tfPos+1,12,0);
}
