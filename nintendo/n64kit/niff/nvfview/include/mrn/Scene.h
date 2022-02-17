/*
  mrn/Scene.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 9, 1998.
*/

#ifndef _mrn_Scene_h
#define _mrn_Scene_h 1

#include "mrn/Fog.h"
#include "mrn/Group.h"
#include "mrn/ObjectList.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_SCENE_MAX_GROUPS	32

/* Declare structures */
typedef struct _MrnScene
{
    u32			frame_resource_size;
    u8			*frame_resource_buffer;
    u32			alloc_cursor[ 2 ];
    u32			free_cursor;
    u8			latency;
    MrnFog		fog;
    MrnGroup		*group_ptr_array[ MRN_SCENE_MAX_GROUPS ];
    MrnObjectList	object_list;
} MrnScene;

/* Declare functions */
extern void mrnSceneInit( MrnScene *scene_ptr, const u32 frame_resource_size );

extern void mrnSceneDestroy( MrnScene *scene_ptr );

extern Gfx *mrnSceneBuildGfx( MrnScene *scene_ptr, Gfx *gfx_ptr );

extern void *mrnSceneAllocFrameResource( MrnScene *scene_ptr, const u32 size,
					 const u32 alignment );
					 /* The MAX value of alignment is 12. */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macros */
#define _mrnSceneAddObject(scene_ptr,object_ptr) \
	{ _mrnObjectListPushFront( &(scene_ptr)->object_list, (object_ptr) ); }

#endif /* _mrn_Scene_h */
