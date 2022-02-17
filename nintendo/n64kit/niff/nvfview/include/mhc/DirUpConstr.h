/*
  mhc/DirUpConstr.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Apr. 5, 1999.
*/

#ifndef _mhc_DirUpConstr_h
#define _mhc_DirUpConstr_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcScene;

/* Declare types of a structure */
typedef struct _MhcDirUpConstr
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		direction;
    MvmVector3f		upvector;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MhcDirUpConstr;

/* Declare Functions */
extern void mhcDirUpConstrEvaluate( struct _MhcInstance *instance_ptr,
				    struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_DirUpConstr_h */
