/*
  msn/RotationY.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _msn_RotationY_h
#define _msn_RotationY_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/Rotation1.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_ROTATION_Y_FIELD_ROTATION		(0)
#define MSN_ROTATION_Y_FIELD_GLOBAL_ORIENTATION	(1)

/* Declare types of a structure */
typedef MhcRotation1 MsnRotationY;

/* Declare Functions */
extern void msnRotationYInit( MsnRotationY *rotation_ptr );

/* Declare global variables */
extern MifChunkParser gMsnRotationYChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_RotationY_h */
