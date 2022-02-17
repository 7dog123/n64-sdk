/*
 * [CCBL]
 *
 * pad.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "pad.h"

#define MAX_PADS MAXCONTROLLERS

#define RPT_START_TIME 17
#define RPT_CUE_TIME 2


static u32 pad_exist;

Pad_D Mpad[MAX_PADS];

void get_pad(void );

void
init_pad(void )
{
  u32 ct;
  int i;
  Pad_D *pd;

  pad_exist = nuContInit();

  for(i = 0,ct = pad_exist,pd = Mpad;i < MAX_PADS;i++,pd++){
    pd->pad_stat = (ct & 1)? OK_PAD:NO_PAD;
    pd->button = pd->trigger = pd->repeat;
    pd->x_3D = pd->y_3D = 0;
    pd->rptc[0] = pd->rptc[1] = pd->rptc[2] = pd->rptc[3] = 128;
  }
  //  nuContReadFuncSet((NUContReadFunc)get_pad);
  nuContReadFuncSet((NUContReadFunc)NULL);
}


/*
 * get_pad
 * A nuContRead hook function used when retracing. 
 * Creates pad data used by the main function of the game. 
 */
void
get_pad(void )
{
  register int i,j;
  OSContPad *cp;
  Pad_D *pd;
  u16 oldb;
  static u16 rptmask[8] = {
    PAD_U,PAD_D,PAD_R,PAD_L,PAD_CU,PAD_CD,PAD_CR,PAD_CL};

  cp = nuContData;		/* NuSYS internal paddata */
  pd = Mpad;
  for(i = 0;i < MAX_PADS;i++,cp++,pd++){
    if(pd->pad_stat == NO_PAD) continue;
    if(cp->errno & (CONT_NO_RESPONSE_ERROR | CONT_OVERRUN_ERROR)){
      pd->pad_stat = INVALID_PAD;
    }else{
      pd->pad_stat = OK_PAD;
      oldb = pd->button;
      pd->button = cp->button;
      pd->trigger = (pd->button ^ oldb) & pd->button;
      pd->x_3D = cp->stick_x;
      pd->y_3D = cp->stick_y;
      pd->repeat = 0;
      for(j = 0;j < 8;j++){
	if(pd->button & rptmask[j]){
	  if((pd->rptc[j] == RPT_CUE_TIME) || 
	     (pd->rptc[j] == RPT_START_TIME)){
	    pd->repeat |= rptmask[j];
	  }
	  pd->rptc[j]--;
	  if(pd->rptc[j] == 0) pd->rptc[j] = RPT_CUE_TIME;
	}else{
	  pd->rptc[j] = RPT_START_TIME;
	}
      }
    }
  }
}

