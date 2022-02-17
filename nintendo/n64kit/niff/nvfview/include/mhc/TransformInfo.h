/*
  mhc/TransformInfo.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 19, 1999.
*/

#ifndef _mhc_TransformInfo_h
#define _mhc_TransformInfo_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcScene;

/* Declare types of a structure */
typedef struct _MhcTransformInfo
{
    _msoDeriveFrom( MhcNode );
    MvmVector3f		scale;
    MvmVector3f		classic_scale;
    MvmVector3f		position;
    MvmMatrix33f	orientation;
    MvmMatrix33f	scaled_orientation;
} MhcTransformInfo;

/* Declare Functions */
extern void mhcTransformInfoEvaluate( struct _MhcInstance *instance_ptr,
				      struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_TransformInfo_h */
