/*
  msn/OrientationConstr.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 26, 1998.
*/

#ifndef _msn_OrientationConstr_h
#define _msn_OrientationConstr_h 1

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
#define MSN_ORIENTATION_CONSTR_FIELD_ORIENTATION	(0)
#define MSN_ORIENTATION_CONSTR_FIELD_GLOBAL_ORIENTATION	(1)

/* Declare structures */
typedef struct _MsnOrientationConstr
{
    _msoDeriveFrom( MhcNode );
    MvmMatrix33f	orientation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnOrientationConstr;

/* Declare functions */
extern void msnOrientationConstrInit( MsnOrientationConstr *constr_ptr );

/* Declare global variables */
extern MifChunkParser gMsnOrientationConstrChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_OrientationConstr_h */
