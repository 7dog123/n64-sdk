/*
 * [CCBL]
 *
 * bg_model.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "mdl.h"
#include "rcp_reg.h"
#include "bg_model.h"

#include "xy_bgm.h"
#include "stars.h"


NDR_RESINFO *bg_models[BG_MODEL_LEN] = {
  NULL,
  &resinfo_xy_bgm,
  &resinfo_stars,
};


