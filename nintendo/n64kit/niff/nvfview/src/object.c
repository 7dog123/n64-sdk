/*
  nvfview
  object.c
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 18, 1999.
*/

#include "nusys.h"

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "viewerinfo.h"

#include "mgi/App.h"
#include "mgi/Character.h"
#include "mgi/Control.h"
#include "mgi/Job.h"
#include "mhc/Module.h"
#include "mhc/Node.h"
#include "mif/ChunkParser.h"
#include "msn/BgColor.h"
#include "msn/DepthFog.h"
#include "msn/Float.h"
#include "msn/PerspectiveCamera.h"
#include "mso/debug.h"

#define CONTROL_OBJECT_TIME	(0)
#define CONTROL_OBJECT_INDEX	(1)
#define ANIM_THRESHOLD		(32)

extern MODE		gMode;
extern ViewerInfo	gViewerInfo;

static void object_callback( MgiJob *job_ptr, MgiApp *app_ptr );

static MgiControl control_array[ ] =
{
    { " time", NULL, MSN_FLOAT_FIELD_VALUE, 1, NULL },
    { " index", NULL, MSN_FLOAT_FIELD_VALUE, 1, NULL }
};

static MgiCharacter default_object;

static void initialize_fog( MhcModule *module_ptr )
{
    gMode.fog.node_ptr	= NULL;
    gMode.fog.near_ptr	= NULL;
    gMode.fog.far_ptr	= NULL;
    gMode.fog.color_ptr	= NULL;
    gMode.fog.flags_ptr	= NULL;

    gMode.default_fog.node_ptr		= NULL;
    gMode.default_fog.near_ptr		= NULL;
    gMode.default_fog.far_ptr		= NULL;
    gMode.default_fog.color_ptr		= NULL;
    gMode.default_fog.flags_ptr		= NULL;
    gMode.default_fog.near		= 1000;
    gMode.default_fog.far		= 1000;
    gMode.default_fog.color.vector[ 0 ]	= 0;
    gMode.default_fog.color.vector[ 1 ]	= 0;
    gMode.default_fog.color.vector[ 2 ]	= 0;
    gMode.default_fog.color.vector[ 3 ]	= 0;
    gMode.default_fog.is_active		= 0;

    mhcModuleGetNodeByType( module_ptr, _mifMagicDefine( 'D', 'F', 'O', 'G' ),
			    1, &gMode.fog.node_ptr );
    if ( gMode.fog.node_ptr )
    {
	gMode.fog.near_ptr = ( float * )_mhcNodeGetFieldPtr(
					gMode.fog.node_ptr,
					MSN_DEPTH_FOG_FIELD_NEAR, 0 );
	gMode.fog.far_ptr = ( float * )_mhcNodeGetFieldPtr(
					gMode.fog.node_ptr,
					MSN_DEPTH_FOG_FIELD_FAR, 0 );
	gMode.fog.color_ptr = ( float * )_mhcNodeGetFieldPtr(
					gMode.fog.node_ptr,
					MSN_DEPTH_FOG_FIELD_COLOR, 0 );
	gMode.fog.flags_ptr = ( u32 * )_mhcNodeGetFieldPtr(
					gMode.fog.node_ptr,
					MSN_DEPTH_FOG_FIELD_ACTIVE, 0 );

	gMode.default_fog.near =		*gMode.fog.near_ptr;
	gMode.default_fog.far =			*gMode.fog.far_ptr;
	gMode.default_fog.color.vector[ 0 ] =	gMode.fog.color_ptr[ 0 ];
	gMode.default_fog.color.vector[ 1 ] =	gMode.fog.color_ptr[ 1 ];
	gMode.default_fog.color.vector[ 2 ] =	gMode.fog.color_ptr[ 2 ];
	gMode.default_fog.color.vector[ 3 ] =	gMode.fog.color_ptr[ 3 ];
	gMode.default_fog.is_active =		*gMode.fog.flags_ptr;
    }

    gMode.fog.near		= gMode.default_fog.near;
    gMode.fog.far		= gMode.default_fog.far;
    gMode.fog.color.vector[ 0 ]	= gMode.default_fog.color.vector[ 0 ];
    gMode.fog.color.vector[ 1 ]	= gMode.default_fog.color.vector[ 1 ];
    gMode.fog.color.vector[ 2 ]	= gMode.default_fog.color.vector[ 2 ];
    gMode.fog.color.vector[ 3 ]	= gMode.default_fog.color.vector[ 3 ];
    gMode.fog.is_active		= gMode.default_fog.is_active;
}

static void initialize_bg( MhcModule *module_ptr )
{
    gMode.bg_node_ptr	= NULL;
    gMode.bg_color_ptr	= NULL;
    gMode.default_bg_color.vector[ 0 ]	= 0;
    gMode.default_bg_color.vector[ 1 ]	= 0;
    gMode.default_bg_color.vector[ 2 ]	= 0;
    gMode.default_bg_color.vector[ 3 ]	= 255.0f;

    mhcModuleGetNodeByType( module_ptr, _mifMagicDefine( 'B', 'G', 'C', 'L' ),
			    1, &gMode.bg_node_ptr );
    if ( gMode.bg_node_ptr )
    {
	gMode.bg_color_ptr = ( float * )_mhcNodeGetFieldPtr( gMode.bg_node_ptr,
						MSN_BG_COLOR_FIELD_COLOR, 0 );
	gMode.default_bg_color.vector[ 0 ] =	gMode.bg_color_ptr[ 0 ];
	gMode.default_bg_color.vector[ 1 ] =	gMode.bg_color_ptr[ 1 ];
	gMode.default_bg_color.vector[ 2 ] =	gMode.bg_color_ptr[ 2 ];
	gMode.default_bg_color.vector[ 3 ] =	gMode.bg_color_ptr[ 3 ];
    }

    gMode.bg_color.vector[ 0 ]	= gMode.default_bg_color.vector[ 0 ];
    gMode.bg_color.vector[ 1 ]	= gMode.default_bg_color.vector[ 1 ];
    gMode.bg_color.vector[ 2 ]	= gMode.default_bg_color.vector[ 2 ];
    gMode.bg_color.vector[ 3 ]	= gMode.default_bg_color.vector[ 3 ];
}

MgiCharacter *CreateObject( MhcModule *module_ptr )
{
    /* What it does internally is to return pointer to a static
       object. It doesn't create an object. */

    mgiCharacterInit( &default_object, object_callback, NULL );
    default_object.module_ptr = module_ptr;
    default_object.number_of_controls = sizeof( control_array ) /
					sizeof( MgiControl );
    default_object.control_array = control_array;

    mgiCharacterActivate( &default_object );

    initialize_fog( module_ptr );
    initialize_bg( module_ptr );

    return &default_object;
}

static void select_camera( MgiCharacter *char_ptr )
{
    MhcNode			*camera_node_ptr;
    MsnPerspectiveCamera	*camera_ptr;

    if ( gMode.scene_camera_enable )
    {
	mhcModuleGetNodeByType( char_ptr->module_ptr,
		_mifMagicDefine( 'P', 'C', 'A', 'M' ), 1, &camera_node_ptr );
	camera_ptr = _msoDownCast( MsnPerspectiveCamera, MhcNode,
				   camera_node_ptr );
	camera_ptr->group_mask = ( gMode.camera_mode == CAMERA_SCENE ) ?
					0xFFFFFFFF : 0;
    }
}

float get_pitch( void )
{
    switch ( gMode.anim_pitch )
    {
    case ANIM_PITCH_1:
	return 1.0f;
    case ANIM_PITCH_2:
	return 2.0f;
    case ANIM_PITCH_HALF:
	return 0.5f;
    case ANIM_PITCH_QUARTER:
	return 0.25f;
    default:
	break;
    }
    return 0.0f;
}

static void animate( MgiCharacter *char_ptr, NUContData *pad )
{
    static char		time_str[ ] = "          ";
    static int		anim_mode = 0;

    float	time, length, pitch;
    AnimInfo	*anim_info_ptr;

    if ( gViewerInfo.module_info_array[ 1 ].number_of_anims == 0 ) return;

    anim_info_ptr = &gViewerInfo.module_info_array[ 1 ].anim_info_array[
							gMode.anim_index ];

    length = anim_info_ptr->end_frame - anim_info_ptr->start_frame;
    time = mgiControlGetFloat( &char_ptr->control_array[ CONTROL_OBJECT_TIME ]
			     );

    pitch = 0.0f;

    if ( pad[ 0 ].trigger & CONT_A )
    {
	if ( anim_mode != 0 ) anim_mode = 0;
	else anim_mode = 1;
    }
    if ( pad[ 0 ].trigger & CONT_B )
    {
	if ( anim_mode != 0 ) anim_mode = 0;
	else anim_mode = -1;
    }

    if ( anim_mode > 0 ) pitch = get_pitch( );
    if ( anim_mode < 0 ) pitch = -get_pitch( );
    if ( pad[ 0 ].trigger & CONT_R )
    {
	pitch = get_pitch( );
	anim_mode = 0;
    }
    if ( pad[ 0 ].trigger & CONT_L )
    {
	pitch = -get_pitch( );
	anim_mode = 0;
    }


    time += pitch;
    while ( time < anim_info_ptr->start_frame )
    {
	time += length;
    }
    while ( time >= anim_info_ptr->end_frame )
    {
	time -= length;
    }

    mgiControlSetFloat( &char_ptr->control_array[ CONTROL_OBJECT_TIME ],
			time );
    mgiControlSetFloat( &char_ptr->control_array[ CONTROL_OBJECT_INDEX ],
			( float )gMode.anim_index );

    nuDebConTextPos(0, 30, 3);
    nuDebConTextColor(0, 7);
    sprintf( time_str, "%08.2f", time );
    nuDebConCPuts(0, time_str);
}

static void object_callback( MgiJob *job_ptr, MgiApp *app_ptr )
{
    MgiCharacter	*character_ptr;

    character_ptr = ( MgiCharacter * )job_ptr->user_data;

    select_camera( character_ptr );
    animate( character_ptr, app_ptr->cont_data );

}
