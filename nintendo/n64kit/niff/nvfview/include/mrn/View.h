/*
  mrn/View.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 27, 1998.
*/

#ifndef _mrn_View_h
#define _mrn_View_h 1

#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_VIEW_CLEAR_COLOR_BUFFER	(1)
#define MRN_VIEW_CLEAR_DEPTH_BUFFER	(2)

/* Declare a prototype structure */
struct _MrnContext;

/* Declare structures */
typedef u32 ( *MrnViewBufferAddress )( struct _MrnView *view_ptr );

typedef struct _MrnView
{
    u16				color_depth;
    u16				z_depth;
    u16				is_clean;
    u16				clear_flags;
    u32				interlace;
    u32				interlace_mode;
    u32				clear_color;
    u32				clear_depth;
    u32				width;
    u32				height;
    u32				frame_buffer_segment;
    u32				z_buffer_segment;
    MrnViewBufferAddress	frame_buffer_address;
    MrnViewBufferAddress	z_buffer_address;
    MrnViewBufferAddress	number_of_frame_buffers;
    MrnViewBufferAddress	current_field;
} MrnView;

/* Declare functions */
extern void mrnViewInit( MrnView *view_ptr );
extern Gfx *mrnViewGenerateClearGfx( MrnView *view_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );
extern Gfx *mrnViewGenerateSetupGfx( MrnView *view_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );
extern void mrnViewSetClearColor( MrnView *view_ptr, MvmColor4c color );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_View_h */
