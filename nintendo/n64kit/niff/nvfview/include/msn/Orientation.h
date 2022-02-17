/*
  msn/Orientation.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 19, 1998.
*/

#ifndef _msn_Orientation_h
#define _msn_Orientation_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_ORIENTATION_FIELD_EX			(0)
#define MSN_ORIENTATION_FIELD_EY			(1)
#define MSN_ORIENTATION_FIELD_GLOBAL_ORIENTATION	(2)

/* Declare structures */
typedef struct _MsnOrientation
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		axis[ 2 ];
    MvmMatrix33f	orientation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnOrientation;

/* Declare functions */
extern void msnOrientationInit( MsnOrientation *orientation_ptr );

/* Declare global variables */
extern MifChunkParser gMsnOrientationChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Orientation_h */
