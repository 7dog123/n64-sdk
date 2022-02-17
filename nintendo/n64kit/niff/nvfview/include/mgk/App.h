/*
  mgk/App.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 25, 1999.
*/

#ifndef _mgk_App_h
#define _mgk_App_h 1

#include "mgi/App.h"
#include "mhc/Scene.h"
#include "mrn/Scene.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MgkObj;

/* Declare types of a structure */
typedef struct _MgkApp
{
    u32			number_of_objs;
    struct _MgkObj	*obj_array;
    struct _MgkObj	*active_camera_ptr;
    void		*user_data;
} MgkApp;

/* Declare Functions */
extern void mgkAppInit( const u32 frame_latency,
			const u32 gfx_length,
			const u32 frame_resource_size,
			const u32 instance_queue_size,
			const u32 transform_buffer_size,
			const u32 max_objs,
		        struct _MgkObj *obj_array,
			void *user_data );
extern void mgkAppInitGroups( void );
extern void mgkAppEvalAll( void );
extern Gfx *mgkAppDraw( void );

/* Declare global variables */
extern MgkApp gMgkApp;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macro */
#define _mgkAppGetHierarchy() _mgiAppGetHierarchy( )
#define _mgkAppGetScene() _mgiAppGetScene( )
#define _mgkAppGetScreen() _mgiAppGetScreen( )
#define _mgkAppBeginFrame() mgiAppBeginFrame( )
#define _mgkAppEndFrame() mgiAppEndFrame( )
#define _mgkAppGetFrameCount( ) _mgiAppGetFrameCount( )

#endif /* _mgk_App_h */
