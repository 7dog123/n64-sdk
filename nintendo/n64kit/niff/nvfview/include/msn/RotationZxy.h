/*
  msn/RotationZxy.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 16, 1998.
*/

#ifndef _msn_RotationZxy_h
#define _msn_RotationZxy_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_ROTATION_ZXY_FIELD_ROTATION			(0)
#define MSN_ROTATION_ZXY_FIELD_GLOBAL_ORIENTATION	(1)

/* Declare structures */
typedef struct _MsnRotationZxy
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		rotation;
    MvmMatrix33f	orientation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnRotationZxy;

/* Declare functions */
extern void msnRotationZxyInit( MsnRotationZxy *rotation_ptr );

/* Declare global variables */
extern MifChunkParser gMsnRotationZxyChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_RotationZxy_h */
