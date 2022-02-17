/*
  mgi/App.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 2, 1998.
*/

#ifndef _mgi_App_h
#define _mgi_App_h 1

#include "mgi/Character.h"
#include "mgi/JobList.h"
#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/Scene.h"
#include "mrn/Scene.h"
#include "mrn/Screen.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct st_ContData;

/* Declare types of a structure */
typedef struct _MgiApp
{
    MgiJobList		frame_job_list;
    MgiJobList		render_job_list;

    MhcScene		hierarchy;
    MrnScene		render_scene;
    MrnScreen		screen;

    u32			gfx_length;
    Gfx			**gfx_array;
    u32			current_gfx;
    Gfx			*current_gfx_ptr;

    u32			is_perfbar_enable;
    u32			render_microcode;

    u32			frame_latency;
    u32			frame_count;
    u32			frame_rate;

    int			number_of_controllers;
    u16			*last_button;
    struct st_ContData	*cont_data;

    void		*user_data;
} MgiApp;

/* Declare Functions */
extern void mgiAppInit( const u32 frame_latency,
			const u32 gfx_length,
			const u32 frame_resource_size,
			const u32 instance_queue_size,
			const u32 max_modules,
			const u32 transform_buffer_size,
			void *user_data );

extern void mgiAppMainLoop( void );
extern void mgiAppBeginFrame( void );
extern void mgiAppEndFrame( void );

extern void mgiAppAddRenderJob( MgiJob *job_ptr );
extern void mgiAppInsertRenderJob( MgiJob *new_job_ptr, MgiJob *job_ptr );
extern void mgiAppRemoveRenderJob( MgiJob *job_ptr );

extern void mgiAppAddFrameJob( MgiJob *job_ptr );
extern void mgiAppInsertFrameJob( MgiJob *new_job_ptr, MgiJob *job_ptr );
extern void mgiAppRemoveFrameJob( MgiJob *job_ptr );

/* Declare a Global variable */
extern MgiApp gMgiApp;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macros */
#define _mgiAppAddCharacter(char_ptr) mgiAppAddRenderJob( &( char_ptr )->job )
#define _mgiAppGetHierarchy() (&gMgiApp.hierarchy)
#define _mgiAppGetScene() (&gMgiApp.render_scene)
#define _mgiAppGetScreen() (&gMgiApp.screen)
#define _mgiAppGetFrameCount( ) (gMgiApp.frame_count)

#endif /* _mgi_App_h */
