/*
 * [CCBL]
 *
 * texture.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "mdl.h"
#include "texture.h"

#include "tx_tree.h"
#include "tx_mario.h"
#include "tx_brickMM.h"
#include "tx_check.h"
#include "tx_grad32.h"
#include "tx_gradIA16.h"
#include "tx_reflect.h"
#include "tx_highlight.h"

MDL_TEX textures[TX_ITEM_LEN] = {
  {tx_mario,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32},
  {tx_tree,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32},
  {tx_brickMM_orig,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32},
  {tx_check,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32},
  {tx_brickMM_dl,0,0,0,0},
  {tx_grad32,G_IM_FMT_RGBA,G_IM_SIZ_32b,32,32},
  {tx_gradIA16,G_IM_FMT_IA,G_IM_SIZ_16b,32,32},
  {tx_reflect,G_IM_FMT_RGBA,G_IM_SIZ_16b,32,32},
  {tx_highlight,G_IM_FMT_I,G_IM_SIZ_8b,32,32},
};

