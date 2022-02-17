/*
  msn/PositionConstr.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_PositionConstr_h
#define _msn_PositionConstr_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_POSITION_CONSTR_FIELD_POSITION		(0)
#define MSN_POSITION_CONSTR_FIELD_GLOBAL_POSITION	(1)

/* Declare structures */
typedef struct _MsnPositionConstr
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		position;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnPositionConstr;

/* Declare functions */
extern void msnPositionConstrInit( MsnPositionConstr *constr_ptr );

/* Declare global variables */
extern MifChunkParser gMsnPositionConstrChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_PositionConstr_h */
