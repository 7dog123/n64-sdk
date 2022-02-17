/*
  mrn/Screen.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 23, 1999.
*/

#ifndef _mrn_Screen_h
#define _mrn_Screen_h 1

#include "mrn/View.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
#define MRN_SCREEN_SUCCESS		(0)
#define MRN_SCREEN_FAILURE		(1)

#define MRN_SCREEN_RES_NTSC_320_240	(0)
#define MRN_SCREEN_RES_NTSC_320_240D	(1)
#define MRN_SCREEN_RES_NTSC_640_480I	(2)
#define MRN_SCREEN_RES_NTSC_640_480	(3)

#define MRN_SCREEN_RES_FPAL_320_240	(8)
#define MRN_SCREEN_RES_FPAL_320_240D	(9)
#define MRN_SCREEN_RES_FPAL_640_480I	(10)
#define MRN_SCREEN_RES_FPAL_640_480	(11)

/* Declare prototype structures */
struct _MrnContext;
struct _MrnView;
struct _NuxScFrame;

/* Declare structures */
typedef struct _MrnScreen
{
    _msoDeriveFrom( MrnView );

    u32	number_of_frame_buffers;
    u16	draw_buffer;
    u16	display_buffer;
    u8	*frame_buffer_ptr_array[ 3 ];
    u8	*z_buffer_ptr;
} MrnScreen;

/* Declare functions */
extern int mrnScreenInit( MrnScreen *screen_ptr,
			  const u32 resolution,
			  const u32 number_of_frame_buffers,
			  const u32 frame_buffer_depth,
			  const u32 z_buffer );
extern int mrnScreenSetMode( MrnScreen *screen_ptr,
			     const u32 resolution,
			     const u32 number_of_frame_buffers,
			     const u32 frame_buffer_depth,
			     const u32 z_buffer );
extern struct _NuxScFrame *mrnScreenBeginFrame( MrnScreen *screen_ptr );
extern struct _NuxScFrame *mrnScreenEndFrame( MrnScreen *screen_ptr );
extern int mrnScreenSwapBuffer( MrnScreen *screen_ptr,
				const int buffer_index );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Screen_h */
