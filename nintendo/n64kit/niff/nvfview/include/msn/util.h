/*
  msn/util.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 16, 1998.
*/

#ifndef _msn_util_h
#define _msn_util_h 1

#include "mrn/Object.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structure */
struct _MhcNodeHandle;
struct _MisInput;
struct _MrnScene;
struct _MsoGfxBuffer;

/* Declare Functions */
extern int msnReadNodeHandleArray( struct _MisInput *input_ptr,
				   u32 *node_count_ptr,
				   struct _MhcNodeHandle **handle_array_ptr );

extern int msnReadVertexArray( struct _MisInput *input_ptr,
			       const u32 number_of_vertices,
			       Vtx *vtx_array );

extern int msnReadDrawCommand( struct _MisInput *input_ptr,
			       struct _MsoGfxBuffer *gfx_buffer_ptr );

extern int msnReadVertexGroups( struct _MisInput *input_ptr,
				struct _MsoGfxBuffer *gfx_buffer_ptr,
				const u32 vertex_buffer_addr );

extern void msnShowAxisIcon( struct _MrnScene *scene_ptr,
			     const MvmMatrix33f orientation,
			     const MvmVector3f position,
			     const u32 group_index );

extern MrnObject *msnCreateWireObject( struct _MrnScene *scene_ptr,
				       const u32 group_index,
				       MrnObjectDrawFunc draw_func,
				       void *user_data );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_util_h */
