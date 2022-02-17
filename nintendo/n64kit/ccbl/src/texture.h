/*
 * [CCBL]
 *
 * texture.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "mdl.h"

enum texture_no {
  TX_USER_DEFINED = -1,
  TX_RGBA16_MARIO,
  TX_RGBA16_TREE,
  TX_RGBA16_BRICK,
  TX_RGBA16_CHECK,
  TX_RGBA16_BRICK_MM,
  TX_RGBA32_GRADIENT,
  TX_IA16_GRADIENT,
  TX_RGBA16_REFLECT,
  TX_I8_HIGHLIGHT,
  TX_ITEM_LEN
};    

extern MDL_TEX textures[];

#endif /* !_TEXTURE_H_ */
