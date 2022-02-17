/*
 * [CCBL]
 *
 * model_load.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _MODEL_LOAD_H_
#define _MODEL_LOAD_H_
#include "shape.h"


typedef struct DMA_TABLE_s {
  u8 *start,*end;
} DMA_TABLE;


enum model_no {
  MDL_USER = -1,
  MDL_TETRA,
  MDL_CUBE,
  MDL_SPHERE,
  MDL_XY_YZ,
  MDL_GRID,
  MDL_TRI,
  MDL_TEXT,
  MDL_MIZO,
  MDL_TORUS2,
  MDL_NO_MAX
};

extern u8 _tetraSegmentRomStart[];
extern u8 _tetraSegmentRomEnd[];
extern u8 _cubeSegmentRomStart[];
extern u8 _cubeSegmentRomEnd[];
extern u8 _sphereSegmentRomStart[];
extern u8 _sphereSegmentRomEnd[];
extern u8 _xy_yzSegmentRomStart[];
extern u8 _xy_yzSegmentRomEnd[];
extern u8 _gridSegmentRomStart[];
extern u8 _gridSegmentRomEnd[];
extern u8 _triSegmentRomStart[];
extern u8 _triSegmentRomEnd[];
extern u8 _textSegmentRomStart[];
extern u8 _textSegmentRomEnd[];
extern u8 _mizoSegmentRomStart[];
extern u8 _mizoSegmentRomEnd[];
extern u8 _torus2SegmentRomStart[];
extern u8 _torus2SegmentRomEnd[];

extern void load_model_data(int model);
extern void user_model_init(void);
extern int get_user_model_sw(void);
extern void set_user_model_sw(int swval);
extern void set_user_model_length(u32 len);

extern NDR_RESINFO **ndrs;

#endif /* !_MODEL_LOAD_H_ */
