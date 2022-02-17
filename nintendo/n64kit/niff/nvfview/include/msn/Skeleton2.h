/*
  msn/Skeleton2.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 24, 1999.
*/

#ifndef _msn_Skeleton2_h
#define _msn_Skeleton2_h 1

#include "mhc/NodeHandle.h"
#include "mvm/Vector.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcModule;
struct _MhcScene;
struct _MisInput;
struct _MrnScene;

/* Declare types of a structure */
typedef struct _MsnSkeleton2
{
    u32			flip;
    float		bone_length[ 2 ];
    MvmVector3f		joint_scale[ 2 ];
    MvmVector3f		effector;
    MvmVector3f		axis;
    MvmMatrix33f	coord_system;
    u32			number_of_children[ 3 ];
    MhcNodeHandle	*child_array[ 3 ];

    MvmMatrix33f	global_orientation[ 2 ];
    MvmVector3f		global_position[ 2 ];
} MsnSkeleton2;

/* Declare Functions */
extern void msnSkeleton2Init( MsnSkeleton2 *skeleton_ptr );
extern void msnSkeleton2Destroy( MsnSkeleton2 *skeleton_ptr );
extern void msnSkeleton2Bind( MsnSkeleton2 *skeleton_ptr,
			      struct _MhcModule *module_ptr,
			      struct _MhcScene *scene_ptr );
extern void msnSkeleton2Resolve( MsnSkeleton2 *skeleton_ptr,
				 struct _MhcScene *scene_ptr,
				 struct _MhcInstance *instance_ptr,
				 const MvmMatrix33f skeleton_coord_system );
extern void msnSkeleton2DrawIcon( MsnSkeleton2 *skeleton_ptr,
				  struct _MrnScene *scene_ptr,
				  const u32 group_index );
extern int msnSkeleton2Read( MsnSkeleton2 *skeleton_ptr,
			     MisInput *input_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_skeleton_h */
