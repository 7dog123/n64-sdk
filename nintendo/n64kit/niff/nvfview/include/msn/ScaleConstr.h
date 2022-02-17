/*
  msn/ScaleConstr.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#ifndef _msn_ScaleConstr_h
#define _msn_ScaleConstr_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_SCALE_CONSTR_FIELD_SCALE		(0)

/* Declare structures */
typedef struct _MsnScaleConstr
{
    _msoDeriveFrom( MhcNode );
    u32			number_of_scales;
    MvmVector3f		*scale_array;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnScaleConstr;

/* Declare functions */
extern void msnScaleConstrInit( MsnScaleConstr *constr_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnScaleConstrChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_ScaleConstr_h */
