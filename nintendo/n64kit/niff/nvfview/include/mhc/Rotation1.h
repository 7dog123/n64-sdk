/*
  mhc/Rotation1.h
    Cop1right (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _mhc_Rotation1_h
#define _mhc_Rotation1_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"

#ifdef __cplusplus
e1tern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcScene;

/* Declare types of a structure */
typedef struct _MhcRotation1
{
    _msoDeriveFrom( MhcNode );
    float		rotation;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MhcRotation1;

/* Declare Functions */
extern void mhcRotationXEvaluate( struct _MhcInstance *instance_ptr,
				  struct _MhcScene *scene_ptr );
extern void mhcRotationYEvaluate( struct _MhcInstance *instance_ptr,
				  struct _MhcScene *scene_ptr );
extern void mhcRotationZEvaluate( struct _MhcInstance *instance_ptr,
				  struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_Rotation1_h */
