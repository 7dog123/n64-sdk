/*
 * [CCBL]
 *
 * ccbl_host.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "model_load.h"
#include "rom_reg.h"

DMA_TABLE mdlrom[MDL_NO_MAX] = {
  {_tetraSegmentRomStart,_tetraSegmentRomEnd},
  {_cubeSegmentRomStart,_cubeSegmentRomEnd},
  {_sphereSegmentRomStart,_sphereSegmentRomEnd},
  {_xy_yzSegmentRomStart,_xy_yzSegmentRomEnd},
  {_gridSegmentRomStart,_gridSegmentRomEnd},
  {_triSegmentRomStart,_triSegmentRomEnd},
  {_textSegmentRomStart,_textSegmentRomEnd},
  {_mizoSegmentRomStart,_mizoSegmentRomEnd},
  {_torus2SegmentRomStart,_torus2SegmentRomEnd},
};

NDR_RESINFO **ndrs = (NDR_RESINFO **)MODEL_LOAD_ADDR;

static int um_enable;
static u32 um_length;
static int old_model;

void
load_model_data(int model)
{
  DMA_TABLE *dt;

  if(old_model != model){	/* DMA immediately after model change only ! ! */
    if(model > MDL_USER){
      dt = &mdlrom[model];
      nuPiReadRom((u32)dt->start,
		  (u32 *)MODEL_LOAD_ADDR,
		  (u32)(dt->end - dt->start));
    }else{
      /* 
       *  When USER MODEL has been changed while being displayed, 
	*  it must be reselected. 
       * 
       */
      nuPiReadRom((u32)ROM_REG_MODEL_DATA,
		  (u32 *)MODEL_LOAD_ADDR,
		  um_length);
    }
    old_model = model;
  }
}

void
user_model_init(void)
{

  um_enable = 0;
  old_model = -2;		/* Value not possible after resetting */
}

int
get_user_model_sw(void)
{
  return um_enable;
}

void
set_user_model_sw(int swval)
{
  um_enable = swval;
}

void
set_user_model_length(u32 len)
{
  um_length = len;
}

