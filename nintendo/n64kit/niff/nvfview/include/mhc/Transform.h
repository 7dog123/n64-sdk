/*
  mhc/Transform.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 20, 1999.
*/

#ifndef _mhc_Transform_h
#define _mhc_Transform_h 1

#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MhcTransform
{
    MvmMatrix33f	*orientation_ptr;
    MvmMatrix33f	*scaled_orientation_ptr;
    MvmVector3f		*translation_ptr;
    MvmVector3f		*scale_ptr;
} MhcTransform;

/* Declare functions */
extern void mhcTransformGenerateMatrix( MhcTransform *transform_ptr,
					MvmMatrix44f matrix );
extern void mhcTransformGenerateOrientation( MhcTransform *transform_ptr,
					     MvmMatrix33f orientation );
extern void mhcTransformGenerateMtx( MhcTransform *transform_ptr,
				     Mtx *mtx_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros  */
#define _mhcTransformCopy(dest_ptr,src_ptr) \
{ \
    (dest_ptr)->orientation_ptr		= (src_ptr)->orientation_ptr; \
    (dest_ptr)->scaled_orientation_ptr	= (src_ptr)->scaled_orientation_ptr; \
    (dest_ptr)->translation_ptr		= (src_ptr)->translation_ptr; \
    (dest_ptr)->scale_ptr		= (src_ptr)->scale_ptr; \
}

#endif /* _mhc_Transform_h */
