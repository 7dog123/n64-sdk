/*
  app.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 1, 1999.
*/

#define NUX	1

#include "nusys.h"
#ifdef NUX
# include "nux.h"
#endif
#include "mgi/App.h"
#include "mgk/App.h"
#include "mgk/Obj.h"
#include "mso/Allocator.h"

MgkApp	gMgkApp;

/*--------------------------------------------------------------------*/
void mgkAppInit( const u32 frame_latency,
		 const u32 gfx_length,
		 const u32 frame_resource_size,
		 const u32 instance_queue_size,
		 const u32 transform_buffer_size,
		 const u32 max_objs,
		 MgkObj *obj_array,
		 void *user_data )
{
    u32	i;

    mgiAppInit( frame_latency, gfx_length, frame_resource_size,
		instance_queue_size, max_objs, transform_buffer_size,
		&gMgkApp );

    gMgkApp.number_of_objs	= max_objs;
    gMgkApp.obj_array		= obj_array;
    gMgkApp.active_camera_ptr	= NULL;

    gMgkApp.user_data = user_data;

    for ( i = 0; i < max_objs; ++i ) mgkObjInit( &obj_array[ i ], i );

    gMgiApp.is_perfbar_enable = FALSE;
    gMgiApp.render_microcode = NU_GFX_UCODE_F3DEX2_REJ;

    nuDebConClear(0);
}

/*--------------------------------------------------------------------*/
void mgkAppInitGroups( void )
{
    int		i;
    MrnGroup	*group_ptr;

    for ( i = 0; i < MRN_SCENE_MAX_GROUPS; ++i )
    {
	group_ptr = ( MrnGroup * )msoMalloc( sizeof( MrnGroup ) );
	mrnGroupInit( group_ptr );
	_mgiAppGetScene( )->group_ptr_array[ i ] = group_ptr;
	group_ptr->view_ptr = _msoUpCast( MrnView, _mgiAppGetScreen( ) );
    }
}

/*--------------------------------------------------------------------*/
void mgkAppEvalAll( void )
{
    u32	i;
    u32	*camera_mask_ptr;

    /* Select camera */
    for ( i = 0; i < gMgkApp.number_of_objs; ++i )
    {
	camera_mask_ptr = gMgkApp.obj_array[ i ].camera_mask_ptr;
	if ( camera_mask_ptr ) *camera_mask_ptr = 0;
    }
    if ( gMgkApp.active_camera_ptr )
    {
	camera_mask_ptr = gMgkApp.active_camera_ptr->camera_mask_ptr;
	if ( camera_mask_ptr ) *camera_mask_ptr = 0xFFFFFFFF;
    }
    else
    {
	for ( i = 0; i < gMgkApp.number_of_objs; ++i )
	{
	    camera_mask_ptr = gMgkApp.obj_array[ i ].camera_mask_ptr;
	    if ( camera_mask_ptr )
	    {
		*camera_mask_ptr = 0xFFFFFFFF;
		break;
	    }
	}
    }

    /* Process for Obj */
    for ( i = 0; i < gMgkApp.number_of_objs; ++i )
    {
	mgkObjEval( _mgiAppGetHierarchy( ), &gMgkApp.obj_array[ i ] );
    }

    /* Evaluating hierarchy */
    mhcSceneEvaluateFlat( _mgiAppGetHierarchy( ), _mgiAppGetScene( ) );
}

/*--------------------------------------------------------------------*/
Gfx *mgkAppDraw( void )
{
    gMgiApp.current_gfx_ptr = mrnSceneBuildGfx( _mgiAppGetScene( ),
						gMgiApp.current_gfx_ptr );
    return gMgiApp.current_gfx_ptr;
}
