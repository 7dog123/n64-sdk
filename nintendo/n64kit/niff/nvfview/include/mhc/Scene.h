/*
  mhc/Scene.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 9, 1999.
*/

#ifndef _mhc_Scene_h
#define _mhc_Scene_h 1

#include "mhc/InstanceList.h"
#include "mhc/Module.h"
#include "mhc/ModuleNode.h"
#include "mhc/Node.h"
#include "mhc/NodeList.h"
#include "mvm/Vector.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MHC_SCENE_MAX_GROUPS	(32)

/* Declare prototype structure */
struct _MhcInstance;
struct _MrnScene;

/* Declare types of a structure */
typedef struct _MhcScene
{
    u32				max_modules;
    MhcModule			*module_array;
    u32				max_instances;
    struct _MhcInstance		*instance_array;
    float			*transform_buffer;
    float			*transform_ptr;
    MhcModuleNode		*root_node_array;
    MhcNode			*camera_node_ptr_array[ MHC_SCENE_MAX_GROUPS ];
    MhcNodeList			wait_node_list;
    MhcInstanceList		free_instance_list;
    MhcInstanceList		ready_instance_list;
    struct _MrnScene		*mrn_scene_ptr;
    u32				icon_visibility;
} MhcScene;

/* Declare Functions */
extern void mhcSceneInit( MhcScene *scene_ptr, const u32 max_modules,
		const u32 max_instances, const u32 transform_buffer_size );

extern void mhcSceneDestroy( MhcScene *scene_ptr );

extern struct _MhcNode *mhcSceneGetNode( MhcScene *scene_ptr,
				const u32 module_id, const char *node_name );

extern int mhcSceneEvaluate( MhcScene *scene_ptr,
			     struct _MrnScene *mrn_scene_ptr );

extern int mhcSceneEvaluateFlat( MhcScene *scene_ptr,
				 struct _MrnScene *mrn_scene_ptr );

extern int mhcSceneEvaluateInstances( MhcScene *scene_ptr );

extern struct _MhcInstance *mhcSceneCreateInstance( MhcScene *scene_ptr );

extern void mhcScenePutInstance( MhcScene *scene_ptr,
				 struct _MhcInstance *instance_ptr );

extern void mhcSceneBind( MhcScene *scene_ptr );

extern float *mhcSceneAllocTransformBuffer( MhcScene *scene_ptr,
					    const u32 size );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macro */
#define _mhcSceneGetModule(scene_ptr,id) \
	( &(scene_ptr)->module_array[ (id) ] )

#define _mhcSceneAllocVector3f(scene_ptr) \
	( ( MvmVector3f * )mhcSceneAllocTransformBuffer( scene_ptr, 3 ) )

#define _mhcSceneAllocMatrix33f(scene_ptr) \
	( ( MvmMatrix33f * )mhcSceneAllocTransformBuffer( scene_ptr, 9 ) )

#endif /* _mhc_Scene_h */
