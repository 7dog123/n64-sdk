/*
 * [CCBL]
 *
 * model.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _MDL_H_
#define _MDL_H_
#include <nusys.h>
#include "./shape.h"

typedef struct MDL_TEX_s{
  void *img;
  u32 fmt,size,w,h;} MDL_TEX;

#endif /* !_MDL_H_ */
