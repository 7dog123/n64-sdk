/*
  obj.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 26, 1999.
*/

#include <gu.h>

#include "mgk/App.h"
#include "mgk/Obj.h"
#include "mhc/Module.h"
#include "mhc/Scene.h"
#include "mif/ChunkParser.h"
#include "mif/FileParser.h"
#ifdef _USE_EPI_
# include "mis/RomInputEpi.h"
#else	/* _USE_EPI_ */
# include "mis/RomInputPi.h"
#endif	/* _USE_EPI_ */
#include "msn/Float.h"
#include "msn/FormParser.h"
#include "msn/PerspectiveCamera.h"
#include "mso/debug.h"
#include "mso/Allocator.h"

/*-- types --------------------------------------------------------------*/
typedef void ( *RotateFunc )( MvmMatrix33f dest,
			      const float x, const float y, const float z,
			      const MvmMatrix33f source );

/*-- Static function prototype -------------------------------------------*/
static MisInput *open_input( const u32 start_addr, const u32 end_addr );
static void rotate_x( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source );
static void rotate_y( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source );
static void rotate_z( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source );

/*--------------------------------------------------------------------*/
void mgkObjInit( MgkObj *obj_ptr, const u32 module_index )
{
    obj_ptr->translation[ 0 ]	= 0.0f;
    obj_ptr->translation[ 1 ]	= 0.0f;
    obj_ptr->translation[ 2 ]	= 0.0f;
    obj_ptr->rotation_mode	= MGK_OBJ_ROT_XYZ;

    obj_ptr->rotation[ 0 ]	= 0.0f;
    obj_ptr->rotation[ 1 ]	= 0.0f;
    obj_ptr->rotation[ 2 ]	= 0.0f;

    obj_ptr->scale[ 0 ]		= 1.0f;
    obj_ptr->scale[ 1 ]		= 1.0f;
    obj_ptr->scale[ 2 ]		= 1.0f;

    obj_ptr->module_index = module_index;

    obj_ptr->anim_start_frame	= 0;
    obj_ptr->anim_index_ptr	= NULL;
    obj_ptr->anim_time_ptr	= NULL;
    obj_ptr->anim_pitch		= 0.0f;
    obj_ptr->anim_start		= 0.0f;
    obj_ptr->anim_length	= 0.0f;
    obj_ptr->anim_loop		= 0;

    obj_ptr->camera_mask_ptr	= NULL;
}

/*--------------------------------------------------------------------*/
int mgkObjLoad( MgkObj *obj_ptr,
		const u32 rom_start_addr,
		const u32 rom_end_addr )
{
    static MifFormParser	form_parser;
    static MifFileParser	file_parser;
    MisInput			*input_ptr;
    int				error_code;
    MhcScene			*scene_ptr;
    MhcModule			*module_ptr;
    MhcNode			*node_ptr;

    scene_ptr = _mgkAppGetHierarchy( );
    module_ptr = _mhcSceneGetModule( scene_ptr, obj_ptr->module_index );

    msnFormParserInit( &form_parser );
    mifFileParserInit( &file_parser, &form_parser, NULL );

    input_ptr = open_input( rom_start_addr, rom_end_addr );

    error_code = mhcModuleLoad( module_ptr, &file_parser, input_ptr );

    if ( error_code == 0 )
    {
	mhcModuleActivate( module_ptr );
	mhcSceneBind( scene_ptr );

	node_ptr = mhcModuleGetNodeByName( module_ptr, " index" );
	obj_ptr->anim_index_ptr = ( float * )_mhcNodeGetFieldPtr( node_ptr,
						MSN_FLOAT_FIELD_VALUE, 0 );

	node_ptr = mhcModuleGetNodeByName( module_ptr, " time" );
	obj_ptr->anim_time_ptr = ( float * )_mhcNodeGetFieldPtr( node_ptr,
						MSN_FLOAT_FIELD_VALUE, 0 );

	node_ptr = NULL;
	obj_ptr->camera_mask_ptr = NULL;
	mhcModuleGetNodeByType( module_ptr,
				_mifMagicDefine( 'P', 'C', 'A', 'M' ),
				1, &node_ptr );
	if ( node_ptr )
	{
	     obj_ptr->camera_mask_ptr = ( u32 * )_mhcNodeGetFieldPtr( node_ptr,
				MSN_PERSPECTIVE_CAMERA_FIELD_GROUP_MASK, 0 );
	}
    }

    _misInputClose( input_ptr );
    _misInputDestroy( input_ptr );
    _msoPrintf( "ErrorCode:%d\n", error_code );

    return error_code;
}

/*--------------------------------------------------------------------*/
void mgkObjCreateCamera( MgkObj *obj_ptr,
			 const float fov_y,
			 const float aspect_ratio,
			 const float clip_near,
			 const float clip_far )
{
    MhcModule			*module_ptr;
    MsnPerspectiveCamera	*camera_ptr;

    module_ptr = _mhcSceneGetModule( _mgiAppGetHierarchy( ),
				     obj_ptr->module_index );
    if ( module_ptr->status == MHC_MODULE_STATUS_NOT_LOADED )
    {
	camera_ptr = msoMalloc( sizeof( MsnPerspectiveCamera ) );
	msnPerspectiveCameraInit( camera_ptr );

	obj_ptr->camera_mask_ptr = &camera_ptr->group_mask;

	camera_ptr->camera.camera.persp.field_of_view_y	= fov_y;
	camera_ptr->camera.aspect_ratio			= aspect_ratio;
	camera_ptr->camera.clip_near			= clip_near;
	camera_ptr->camera.clip_far			= clip_far;

	module_ptr->max_nodes = 1;
	module_ptr->node_ptr_array = msoMalloc( sizeof( MhcNode * ) *
						module_ptr->max_nodes );

	module_ptr->number_of_root_nodes = 1;
	module_ptr->root_node_handle_array = msoMalloc( sizeof( MhcNodeHandle )
					* module_ptr->number_of_root_nodes );
	module_ptr->root_node_handle_array[ 0 ].index = 0;

	_mhcModuleAddNode( module_ptr, _msoUpCast( MhcNode, camera_ptr ) );

	module_ptr->status = MHC_MODULE_STATUS_LOADED;
	mhcModuleActivate( module_ptr );
	mhcSceneBind( _mgiAppGetHierarchy( ) );

	gMgkApp.active_camera_ptr = obj_ptr;
    }
}

/*--------------------------------------------------------------------*/
void mgkObjUnload( MgkObj *obj_ptr )
{
    MhcScene			*scene_ptr;
    MhcModule			*module_ptr;

    scene_ptr = _mgkAppGetHierarchy( );
    module_ptr = _mhcSceneGetModule( scene_ptr, obj_ptr->module_index );

    mhcModuleInactivate( module_ptr );
    nuxScFrameAllEndWait( );
    mhcModuleUnload( module_ptr );
    mhcSceneBind( scene_ptr );

    obj_ptr->anim_index_ptr	= NULL;
    obj_ptr->anim_time_ptr	= NULL;
}

/*--------------------------------------------------------------------*/
void mgkObjSetAnim( MgkObj *obj_ptr, const s32 anim_index )
{
    if ( obj_ptr->anim_index_ptr )
    {
	*obj_ptr->anim_index_ptr = ( float )anim_index;
    }
}

/*--------------------------------------------------------------------*/
void mgkObjPlayAnim( MgkObj *obj_ptr,
		     const float start,
		     const float end,
		     const float pitch,
		     const int loop )
{
    obj_ptr->anim_start		= start;
    obj_ptr->anim_length	= end - start;
    obj_ptr->anim_pitch		= pitch;
    obj_ptr->anim_loop		= loop;
}

/*--------------------------------------------------------------------*/
void mgkObjMove( MgkObj *obj_ptr, const float x, const float y, const float z )
{
    obj_ptr->translation[ 0 ] = x;
    obj_ptr->translation[ 1 ] = y;
    obj_ptr->translation[ 2 ] = z;
}

/*--------------------------------------------------------------------*/
void mgkObjRotate( MgkObj *obj_ptr, const int mode,
		   const float x, const float y, const float z )
{
    obj_ptr->rotation_mode = mode;

    obj_ptr->rotation[ 0 ] = x;
    obj_ptr->rotation[ 1 ] = y;
    obj_ptr->rotation[ 2 ] = z;
}

/*--------------------------------------------------------------------*/
void mgkObjLookAt( MgkObj *obj_ptr,
		   const float x, const float y, const float z,
		   const float x_at, const float y_at, const float z_at,
		   const float x_up, const float y_up, const float z_up )
{
    obj_ptr->rotation_mode = MGK_OBJ_ROT_LOOK_AT;

    obj_ptr->translation[ 0 ] = x;
    obj_ptr->translation[ 1 ] = y;
    obj_ptr->translation[ 2 ] = z;

    obj_ptr->at[ 0 ] = x_at;
    obj_ptr->at[ 1 ] = y_at;
    obj_ptr->at[ 2 ] = z_at;

    obj_ptr->up[ 0 ] = x_up;
    obj_ptr->up[ 1 ] = y_up;
    obj_ptr->up[ 2 ] = z_up;
}

/*--------------------------------------------------------------------*/
void mgkObjScale( MgkObj *obj_ptr,
		  const float x, const float y, const float z )
{
    obj_ptr->scale[ 0 ] = x;
    obj_ptr->scale[ 1 ] = y;
    obj_ptr->scale[ 2 ] = z;
}

/*--------------------------------------------------------------------*/
void mgkObjEval( MhcScene *scene_ptr, MgkObj *obj_ptr )
{
    static RotateFunc rotate_func[ 3 ][ 6 ] = {
	rotate_x, rotate_x, rotate_y, rotate_y, rotate_z, rotate_z,
	rotate_y, rotate_z, rotate_z, rotate_x, rotate_x, rotate_y,
	rotate_z, rotate_y, rotate_x, rotate_z, rotate_y, rotate_x
    };

    float		time;
    float		mat[ 4 ][ 4 ];
    MvmMatrix33f	tmp;
    float		x, y, z;
    MhcModule		*module_ptr;

    module_ptr = _mhcSceneGetModule( scene_ptr, obj_ptr->module_index );

    time = obj_ptr->anim_pitch * ( _mgkAppGetFrameCount( ) -
				   obj_ptr->anim_start_frame );
    if ( obj_ptr->anim_loop )
    {
	while ( time < 0.0f ) time += obj_ptr->anim_length;
	while ( time >= obj_ptr->anim_length ) time -= obj_ptr->anim_length;
    }
    if ( obj_ptr->anim_time_ptr )
    {
	*obj_ptr->anim_time_ptr = time + obj_ptr->anim_start;
    }

    if ( obj_ptr->rotation_mode == MGK_OBJ_ROT_LOOK_AT )
    {
	guLookAtF( mat, obj_ptr->translation[ 0 ],
			obj_ptr->translation[ 1 ],
			obj_ptr->translation[ 2 ],
			obj_ptr->at[ 0 ], obj_ptr->at[ 1 ], obj_ptr->at[ 2 ],
			obj_ptr->up[ 0 ], obj_ptr->up[ 1 ], obj_ptr->up[ 2 ] );
	module_ptr->orientation[ 0 ][ 0 ] = mat[ 0 ][ 0 ];
	module_ptr->orientation[ 0 ][ 1 ] = mat[ 1 ][ 0 ];
	module_ptr->orientation[ 0 ][ 2 ] = mat[ 2 ][ 0 ];

	module_ptr->orientation[ 1 ][ 0 ] = mat[ 0 ][ 1 ];
	module_ptr->orientation[ 1 ][ 1 ] = mat[ 1 ][ 1 ];
	module_ptr->orientation[ 1 ][ 2 ] = mat[ 2 ][ 1 ];

	module_ptr->orientation[ 2 ][ 0 ] = mat[ 0 ][ 2 ];
	module_ptr->orientation[ 2 ][ 1 ] = mat[ 1 ][ 2 ];
	module_ptr->orientation[ 2 ][ 2 ] = mat[ 2 ][ 2 ];
    }
    else
    {
	x = obj_ptr->rotation[ 0 ];
	y = obj_ptr->rotation[ 1 ];
	z = obj_ptr->rotation[ 2 ];
	_mvmMatrix33fSetIdentity( tmp );
	rotate_func[ 0 ][ obj_ptr->rotation_mode ]( module_ptr->orientation,
						    x, y, z, tmp );
	rotate_func[ 1 ][ obj_ptr->rotation_mode ]( tmp, x, y, z,
						    module_ptr->orientation );
	rotate_func[ 2 ][ obj_ptr->rotation_mode ]( module_ptr->orientation,
						    x, y, z, tmp );
    }

    mvmMatrix33fScale( module_ptr->scaled_orientation, obj_ptr->scale,
		       module_ptr->orientation );
    mvmVector3fCopy( module_ptr->translation, obj_ptr->translation );
}

/*--------------------------------------------------------------------*/
static MisInput *open_input( const u32 start_addr, const u32 end_addr )
{
#ifdef _USE_EPI_

    static MisRomInputEpi	rom_input;
    u32				size;

    size = end_addr - start_addr;
    misRomInputEpiInit( &rom_input );
    misRomInputEpiOpen( &rom_input, start_addr, size );

#else	/* _USE_EPI_ */

    static MisRomInputPi	rom_input;
    u32				size;

    size = end_addr - start_addr;
    misRomInputPiInit( &rom_input );
    misRomInputPiOpen( &rom_input, start_addr, size );

#endif	/* _USE_EPI_ */

    return _msoUpCast( MisInput, &rom_input );
}

/*--------------------------------------------------------------------*/
static void rotate_x( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source )
{
    ( void )y;
    ( void )z;

    mvmMatrix33fRotateX( dest, x, source );
}

/*--------------------------------------------------------------------*/
static void rotate_y( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source )
{
    ( void )x;
    ( void )z;

    mvmMatrix33fRotateY( dest, y, source );
}

/*--------------------------------------------------------------------*/
static void rotate_z( MvmMatrix33f dest,
		      const float x, const float y, const float z,
		      const MvmMatrix33f source )
{
    ( void )x;
    ( void )y;

    mvmMatrix33fRotateZ( dest, z, source );
}
