/*
 * [CCBL]
 *
 * rom_reg.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _ROM_REG_H_
#define _ROM_REG_H_
#include "rcp_reg.h"

#define HOSTIO_ROM_START 0xf00000
#define ROM_REG_DATA_START (HOSTIO_ROM_START+0x100)
#define ROM_REG_DATA_BODY (HOSTIO_ROM_START+0x104)

#define ROM_REG_MODEL_DATA 0xf80000 /* 0xf80000 - 0xfbffff */
#define ROM_REG_BGMODEL_DATA 0xfc0000 /* 0xfc0000 - 0xfdffff */

typedef struct ROM_REG_s {
  CYCLE_TYPE rr_cycl;
  GEO_MODE rr_gm;
  CC_REG rr_ccac;
  PRIM_COL rr_prm;
  ENV_COL rr_env;
  RENDER_MODE rr_rm;
  BLEND_COL rr_blnd;
  FOG_COL rr_fog;
  COLOR_DITHER rr_cd;
  ALPHA_DITHER rr_ad;
  ALPHA_COMPARE rr_ac;
  LIGHT_COL rr_lc;
  VSF rr_vsf;
  FOG_POS rr_fp;
  TEX_FILT rr_tf;
} ROM_REG;

typedef struct CCBL_CMD_s {
  char cmd_id0[2];		/* 'C','C' */
  u8 cmd_reg[4];		/* command body */
  char cmd_id1[2];		/* 'B','L' */
} CCBL_CMD;



/* ------- */
extern ROM_REG rrHostParam;


#endif /* !_ROM_REG_H_ */
