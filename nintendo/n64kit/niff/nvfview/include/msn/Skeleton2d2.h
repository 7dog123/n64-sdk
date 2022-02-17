/*
  msn/Skeleton2d2.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 24, 1998.
*/

#ifndef _msn_Skeleton2d2_h
#define _msn_Skeleton2d2_h 1

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
#define MSN_SKELETON_2D2_FIELD_BONE_LENGTH		(0)
#define MSN_SKELETON_2D2_FIELD_JOINT1_SCALE		(1)
#define MSN_SKELETON_2D2_FIELD_JOINT2_SCALE		(2)
#define MSN_SKELETON_2D2_FIELD_EFFECTOR_POSITION	(3)
#define MSN_SKELETON_2D2_FIELD_AXIS			(4)

/* Declare types of a structure */
typedef struct _MsnSkeleton2d2
{
    _msoDeriveFrom( MhcNode );
    MsnSkeleton2	skeleton;
} MsnSkeleton2d2;

/* Declare Functions */
extern void msnSkeleton2d2Init( MsnSkeleton2d2 *skeleton_ptr );

/* Declare global variables */
extern MifChunkParser gMsnSkeleton2d2ChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Skeleton2d2_h */
