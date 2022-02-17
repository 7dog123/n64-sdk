/*
  msn/SkeletonUv2.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 24, 1999.
*/

#ifndef _msn_SkeletonUv2_h
#define _msn_SkeletonUv2_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"
#include "msn/Skeleton2.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_SKELETON_UV2_FIELD_BONE_LENGTH		(0)
#define MSN_SKELETON_UV2_FIELD_JOINT1_SCALE		(1)
#define MSN_SKELETON_UV2_FIELD_JOINT2_SCALE		(2)
#define MSN_SKELETON_UV2_FIELD_EFFECTOR_POSITION	(3)
#define MSN_SKELETON_UV2_FIELD_AXIS			(4)
#define MSN_SKELETON_UV2_FIELD_RESPLANE_POSITION	(5)

/* Declare types of a structure */
typedef struct _MsnSkeletonUv2
{
    _msoDeriveFrom( MhcNode );
    MsnSkeleton2	skeleton;
    MvmVector3f		resplane;
} MsnSkeletonUv2;

/* Declare Functions */
extern void msnSkeletonUv2Init( MsnSkeletonUv2 *skeleton_ptr );

/* Declare global variables */
extern MifChunkParser gMsnSkeletonUv2ChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_SkeletonUv2_h */
