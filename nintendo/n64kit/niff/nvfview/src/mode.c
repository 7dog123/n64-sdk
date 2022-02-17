/*
  nvfview
  mode.c
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#include <ultra64.h>
#include "mgi/App.h"
#include "mrn/Group.h"
#include "mrn/Screen.h"
#include "mrn/View.h"
#include "mso/debug.h"
#include "mode.h"

#define ULTRA_D_BUG 1

typedef struct
{
    u32	ntsc_mode;
    u32	fpal_mode;
    u32	depth;
    u32	number_of_frame_buffers;
} Resolution;


void modeResetBG( MODE *mode )
{
    mode->bg_color.rgba.r = mode->default_bg_color.rgba.r;
    mode->bg_color.rgba.g = mode->default_bg_color.rgba.g;
    mode->bg_color.rgba.b = mode->default_bg_color.rgba.b;
    mode->bg_color.rgba.a = mode->default_bg_color.rgba.a;
}

void modeResetFog( MODE *mode )
{
    mode->fog.near		= mode->default_fog.near;
    mode->fog.far		= mode->default_fog.far;
    mode->fog.color.vector[ 0 ]	= mode->default_fog.color.vector[ 0 ];
    mode->fog.color.vector[ 1 ]	= mode->default_fog.color.vector[ 1 ];
    mode->fog.color.vector[ 2 ]	= mode->default_fog.color.vector[ 2 ];
    mode->fog.color.vector[ 3 ]	= mode->default_fog.color.vector[ 3 ];
    mode->fog.is_active		= mode->default_fog.is_active;
}

void modeStoreFog( MODE *mode )
{
    if ( ( mode->fog.node_ptr )&&( mode->active_object == OBJECT_SCENE ) )
    {
	*mode->fog.near_ptr		= ( float )mode->fog.near;
	*mode->fog.far_ptr		= ( float )mode->fog.far;
	mode->fog.color_ptr[ 0 ]	= mode->fog.color.vector[ 0 ];
	mode->fog.color_ptr[ 1 ]	= mode->fog.color.vector[ 1 ];
	mode->fog.color_ptr[ 2 ]	= mode->fog.color.vector[ 2 ];
	mode->fog.color_ptr[ 3 ]	= mode->fog.color.vector[ 3 ];
	*mode->fog.flags_ptr		= mode->fog.is_active;
    }
}

void modeStoreBG( MODE *mode )
{
    int		i;
    MrnGroup	*group_ptr;
    MrnView	*view_ptr;
    MvmColor4c	bg_color;

    if ( ( mode->bg_node_ptr )&&( mode->active_object == OBJECT_SCENE ) )
    {
	mode->bg_color_ptr[ 0 ] = mode->bg_color.vector[ 0 ];
	mode->bg_color_ptr[ 1 ] = mode->bg_color.vector[ 1 ];
	mode->bg_color_ptr[ 2 ] = mode->bg_color.vector[ 2 ];
	mode->bg_color_ptr[ 3 ] = mode->bg_color.vector[ 3 ];
    }
    else
    {
	bg_color.rgba.r = mode->bg_color.rgba.r;
	bg_color.rgba.g = mode->bg_color.rgba.g;
	bg_color.rgba.b = mode->bg_color.rgba.b;
	bg_color.rgba.a = mode->bg_color.rgba.a;

	for ( i = 0; i < MRN_SCENE_MAX_GROUPS; ++i )
	{
	    group_ptr = _mgiAppGetScene( )->group_ptr_array[ i ];
	    if ( group_ptr )
	    {
		view_ptr = group_ptr->view_ptr;
		if ( view_ptr ) mrnViewSetClearColor( view_ptr, bg_color );
	    }
	}
    }
}

void modeResetCamera( MODE *mode )
{
    mode->camera_mode = CAMERA_CONTROL;
    mode->scene_camera_enable = 0;
    mode->camera_reset_request = 1;
}

void modeResetObject( MODE *mode )
{
    mode->active_object = OBJECT_SCENE;
    mode->object_reset_request = 1;
}

void modeLoadVideoMode( MODE *mode )
{
    mode->gamma_enable		= 1;
    mode->gamma_dither_enable	= 1;
    mode->dither_filter_enable	= 1;
    mode->divot_enable		= 1;
    mode->resolution		= 0;
}

void modeStoreVideoMode( MODE *mode )
{
    static const Resolution	RESOLUTION_TABLE[ ] =
    {
	MRN_SCREEN_RES_NTSC_320_240,	MRN_SCREEN_RES_FPAL_320_240,	16, 2,
	MRN_SCREEN_RES_NTSC_320_240D,	MRN_SCREEN_RES_FPAL_320_240D,	16, 2,
	MRN_SCREEN_RES_NTSC_320_240,	MRN_SCREEN_RES_FPAL_320_240,	32, 2,
	MRN_SCREEN_RES_NTSC_320_240D,	MRN_SCREEN_RES_FPAL_320_240D,	32, 2,
	MRN_SCREEN_RES_NTSC_640_480,	MRN_SCREEN_RES_FPAL_640_480,	16, 2,
	MRN_SCREEN_RES_NTSC_640_480I,	MRN_SCREEN_RES_FPAL_640_480I,	16, 1
    };

    static int	last_resolution = 0;

    const Resolution	*resolution_ptr;
    u32			resolution_id;

#ifdef ULTRA_D_BUG
    osViSetSpecialFeatures( ( mode->gamma_enable ) ?
			    OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF );
    osViSetSpecialFeatures( ( mode->gamma_dither_enable ) ?
			    OS_VI_GAMMA_DITHER_ON : OS_VI_GAMMA_DITHER_OFF );
    osViSetSpecialFeatures( ( mode->dither_filter_enable ) ?
			    OS_VI_DITHER_FILTER_ON : OS_VI_DITHER_FILTER_OFF );
    osViSetSpecialFeatures( ( mode->divot_enable ) ?
			    OS_VI_DIVOT_ON : OS_VI_DIVOT_OFF );
#else
    u32 video_mode = 0;

    video_mode |= ( mode->gamma_enable ) ? OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF;
    video_mode |= ( mode->gamma_dither_enable ) ?
			OS_VI_GAMMA_DITHER_ON : OS_VI_GAMMA_DITHER_OFF;
    video_mode |= ( mode->dither_filter_enable ) ?
			OS_VI_DITHER_FILTER_ON : OS_VI_DITHER_FILTER_OFF;
    video_mode |= ( mode->divot_enable ) ? OS_VI_DIVOT_ON : OS_VI_DIVOT_OFF;
    osViSetSpecialFeatures( video_mode );
#endif
    if ( last_resolution != mode->resolution )
    {
	last_resolution = mode->resolution;
	resolution_ptr = &RESOLUTION_TABLE[ mode->resolution ];
	resolution_id = ( osTvType == OS_TV_PAL ) ?
			resolution_ptr->fpal_mode : resolution_ptr->ntsc_mode;
	if ( mrnScreenSetMode( _mgiAppGetScreen( ),
			       resolution_id,
			       resolution_ptr->number_of_frame_buffers,
			       resolution_ptr->depth,
			       1 ) == MRN_SCREEN_FAILURE )
	{
	    resolution_ptr = &RESOLUTION_TABLE[ 0 ];
	    resolution_id = ( osTvType == OS_TV_PAL ) ?
			resolution_ptr->fpal_mode : resolution_ptr->ntsc_mode;
	    mrnScreenSetMode( _mgiAppGetScreen( ),
			      resolution_id,
			      resolution_ptr->number_of_frame_buffers,
			      resolution_ptr->depth,
			      1 );
	}
    }
}
