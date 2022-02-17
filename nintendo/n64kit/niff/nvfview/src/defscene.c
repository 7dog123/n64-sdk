/*
  nvfview
  defscene.c
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#include "nusys.h"

#include "pack.h"
#include "menu.h"
#include "mode.h"

#include "mgi/App.h"
#include "mgi/Character.h"
#include "mgi/Control.h"
#include "mgi/Job.h"
#include "mhc/Module.h"
#include "mhc/Node.h"
#include "msn/DepthFog.h"
#include "msn/Orientation.h"
#include "msn/PerspectiveCamera.h"
#include "msn/Switch.h"
#include "msn/Translation.h"
#include "mso/debug.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#define CONTROL_GROUP_MASK	(0)
#define CONTROL_CAMERA_POS	(1)
#define CONTROL_CAMERA_AT	(2)
#define CONTROL_CAMERA_UP	(3)
#define CONTROL_OBJECT_ORI	(4)
#define CONTROL_FOG_SWITCH	(5)
#define CONTROL_FOG_NEAR	(6)
#define CONTROL_FOG_FAR		(7)
#define CONTROL_FOG_COLOR	(8)
#define CONTROL_OBJECT_SWITCH	(9)	/* switch between NINTENDO/OBJECT */

static void scene_callback( MgiJob *job_ptr, MgiApp *app_ptr );

static MgiControl control_array[ ] =
{
    { "camera", NULL, MSN_PERSPECTIVE_CAMERA_FIELD_GROUP_MASK, 1, NULL },
    { "camera_position", NULL, MSN_TRANSLATION_FIELD_TRANSLATION, 3, NULL },
    { "interest", NULL, MSN_TRANSLATION_FIELD_TRANSLATION, 3, NULL },
    { "up", NULL, MSN_TRANSLATION_FIELD_TRANSLATION, 3, NULL },
    { "object", NULL, MSN_ORIENTATION_FIELD_EX, 6, NULL },
    { "fog_switch", NULL, MSN_SWITCH_FIELD_WHICH_CHOICE, 1, NULL },
    { "fog", NULL, MSN_DEPTH_FOG_FIELD_NEAR, 1, NULL },
    { "fog", NULL, MSN_DEPTH_FOG_FIELD_FAR, 1, NULL },
    { "fog", NULL, MSN_DEPTH_FOG_FIELD_COLOR, 3, NULL },
    { "switch", NULL, MSN_SWITCH_FIELD_WHICH_CHOICE, 1, NULL }
};

static MgiCharacter default_scene;

MgiCharacter *CreateDefaultScene( MhcModule *module_ptr )
{
    /* What it does internally is to return pointer to a static object.
       It doesn't create a scene. */

    mgiCharacterInit( &default_scene, scene_callback, NULL );
    default_scene.module_ptr = module_ptr;
    default_scene.number_of_controls = sizeof( control_array ) /
				       sizeof( MgiControl );
    default_scene.control_array = control_array;

    mgiCharacterActivate( &default_scene );

    return &default_scene;
}

extern MODE		gMode;

static void set_fog_parameter( MgiCharacter *char_ptr )
{
    u32			fog_switch;
    float		fog_near;
    float		fog_far;
    MvmColor4f		fog_color;

    if ( ( !gMode.fog.node_ptr )||( gMode.active_object != OBJECT_SCENE ) )
    {
	fog_switch		= ( gMode.fog.is_active ) ? 0 : 0xFFFFFFFF;
	fog_near		= ( float )gMode.fog.near;
	fog_far			= ( float )gMode.fog.far;
	fog_color.rgba.r	= ( float )gMode.fog.color.rgba.r;
	fog_color.rgba.g	= ( float )gMode.fog.color.rgba.g;
	fog_color.rgba.b	= ( float )gMode.fog.color.rgba.b;
	fog_color.rgba.a	= ( float )gMode.fog.color.rgba.a;

	mgiControlSetULong( &char_ptr->control_array[ CONTROL_FOG_SWITCH ],
			    fog_switch );
	mgiControlSetFloat( &char_ptr->control_array[ CONTROL_FOG_NEAR ],
			    fog_near );
	mgiControlSetFloat( &char_ptr->control_array[ CONTROL_FOG_FAR ],
			    fog_far );
	mgiControlSetFloats( &char_ptr->control_array[ CONTROL_FOG_COLOR ],
			     fog_color.vector );
    }
    else
    {
	mgiControlSetULong( &char_ptr->control_array[ CONTROL_FOG_SWITCH ],
			    0xFFFFFFFF );
    }
}

static void select_object( MgiCharacter *char_ptr )
{
    mgiControlSetULong( &char_ptr->control_array[ CONTROL_OBJECT_SWITCH ],
			( gMode.active_object != OBJECT_SCENE ) );
}

static void reset_camera( MgiCharacter *char_ptr )
{
    MvmVector3f		camera_pos;
    MvmVector3f		camera_up;
    MvmVector3f		camera_at;

    camera_pos[ 0 ] = 0.0f;
    camera_pos[ 1 ] = 0.0f;
    camera_pos[ 2 ] = 1000.0f;

    camera_up[ 0 ] = 0.0f;
    camera_up[ 1 ] = 1.0f;
    camera_up[ 2 ] = 0.0f;

    camera_at[ 0 ] = 0.0f;
    camera_at[ 1 ] = 0.0f;
    camera_at[ 2 ] = 0.0f;

    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_POS ],
			 camera_pos );
    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_AT ],
			 camera_at );
    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_UP ],
			 camera_up );

    gMode.camera_reset_request = 0;
}

static void move_camera( MgiCharacter *char_ptr, NUContData *pad )
{
    float		stx, sty;
    MvmVector3f		camera_pos;
    MvmVector3f		camera_up;
    MvmVector3f		camera_at;

    mgiControlGetFloats( &char_ptr->control_array[ CONTROL_CAMERA_POS ],
			 camera_pos );
    mgiControlGetFloats( &char_ptr->control_array[ CONTROL_CAMERA_AT ],
			 camera_at );
    mgiControlGetFloats( &char_ptr->control_array[ CONTROL_CAMERA_UP ],
			 camera_up );

    if ( pad[ 0 ].button & CONT_CD )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	camera_pos[ 1 ] += 10.0f;
	camera_at[ 1 ] += 10.0f;
    }
    if ( pad[ 0 ].button & CONT_CU )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	camera_pos[ 1 ] -= 10.0f;
	camera_at[ 1 ] -= 10.0f;
    }
    if ( pad[ 0 ].button & CONT_CL )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	camera_pos[ 0 ] += 10.0f;
	camera_at[ 0 ] += 10.0f;
    }
    if ( pad[ 0 ].button & CONT_CR )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	camera_pos[ 0 ] -= 10.0f;
	camera_at[ 0 ] -= 10.0f;
    }

    stx = pad[ 0 ].stick_x;
    sty = pad[ 0 ].stick_y;
    if ( ( !( pad[ 0 ].button & CONT_G ) )&&
	 ( ( stx * stx + sty * sty ) > 16.0f ) )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	camera_pos[ 2 ] += sty;
	camera_at[ 2 ] += sty;
    }

    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_POS ],
			 camera_pos );
    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_AT ],
			 camera_at );
    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_CAMERA_UP ],
			 camera_up );

    mgiControlSetULong( &char_ptr->control_array[ CONTROL_GROUP_MASK ], 0 );
    if ( ( gMode.camera_mode == CAMERA_CONTROL )||
	 ( gMode.scene_camera_enable == 0 ) )
    {
	mgiControlSetULong( &char_ptr->control_array[ CONTROL_GROUP_MASK ],
			    0xFFFFFFFF );
    }
}

static void reset_object( MgiCharacter *char_ptr )
{
    MvmVector3f		orientation[ 2 ];

    orientation[ 0 ][ 0 ] = 1.0f;
    orientation[ 0 ][ 1 ] = 0.0f;
    orientation[ 0 ][ 2 ] = 0.0f;

    orientation[ 1 ][ 0 ] = 0.0f;
    orientation[ 1 ][ 1 ] = 1.0f;
    orientation[ 1 ][ 2 ] = 0.0f;

    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_OBJECT_ORI ],
			 &orientation[ 0 ][ 0 ] );

    gMode.object_reset_request = 0;
}

static void move_object( MgiCharacter *char_ptr, NUContData *pad )
{
    float		stx, sty, angle;
    MvmVector3f		object_ori[ 2 ];
    MvmVector3f		tmp, axis;
    MvmMatrix33f	matrix;

    mgiControlGetFloats( &char_ptr->control_array[ CONTROL_OBJECT_ORI ],
			 &object_ori[ 0 ][ 0 ] );

    stx = pad[ 0 ].stick_x;
    sty = pad[ 0 ].stick_y;
    axis[ 0 ] = -sty * 0.01f;
    axis[ 1 ] = stx * 0.01f;
    axis[ 2 ] = 0.0f;
    angle = sqrtf( stx * stx + sty * sty );

    if ( ( pad[ 0 ].button & CONT_G )&&( angle > 4.0f ) )
    {
	gMode.camera_mode = CAMERA_CONTROL;
	mvmMatrix33fRotation( matrix, angle * 0.1f, axis );
	_mvmVector3fTransform33f( tmp, object_ori[ 0 ], matrix );
	_mvmVector3fCopy( object_ori[ 0 ], tmp );
	_mvmVector3fTransform33f( tmp, object_ori[ 1 ], matrix );
	_mvmVector3fCopy( object_ori[ 1 ], tmp );
    }

    mgiControlSetFloats( &char_ptr->control_array[ CONTROL_OBJECT_ORI ],
			 &object_ori[ 0 ][ 0 ] );
}

static void scene_callback( MgiJob *job_ptr, MgiApp *app_ptr )
{
    MgiCharacter	*character_ptr;

    character_ptr = ( MgiCharacter * )job_ptr->user_data;

    set_fog_parameter( character_ptr );
    select_object( character_ptr );

    if ( gMode.camera_reset_request ) reset_camera( character_ptr );
    else move_camera( character_ptr, app_ptr->cont_data );

    if ( gMode.object_reset_request ) reset_object( character_ptr );
    else move_object( character_ptr, app_ptr->cont_data );
}
