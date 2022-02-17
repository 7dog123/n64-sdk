/*
  msn/DirectionConstr.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 9, 1998.
*/

#ifndef _msn_DirectionConstr_h
#define _msn_DirectionConstr_h 1

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
#define MSN_DIRECTION_CONSTR_FIELD_DIRECTION		(0)
#define MSN_DIRECTION_CONSTR_FIELD_GLOBAL_ORIENTATION	(1)

/* Declare structures */
typedef struct _MsnDirectionConstr
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		direction;
    MvmMatrix33f	orientation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnDirectionConstr;

/* Declare functions */
extern void msnDirectionConstrInit( MsnDirectionConstr *constr_ptr );

/* Declare global variables */
extern MifChunkParser gMsnDirectionConstrChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_DirectionConstr_h */
