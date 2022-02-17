/*
  nvfview
  main.c
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 28, 1999.
*/

#include "mgi/App.h"
#include "mgi/Character.h"
#include "mgi/Job.h"
#include "mhc/Module.h"
#include "mhc/Node.h"
#include "mhc/Scene.h"
#include "mif/ChunkParser.h"
#include "mrn/Group.h"
#include "mrn/Scene.h"
#include "mrn/Screen.h"
#include "msn/PerspectiveCamera.h"
#include "mso/CascadeAllocator.h"
#include "mso/HeapAllocator.h"
#include "mso/debug.h"
#include "mvm/Matrix.h"

#include "nusys.h"

#include "pack.h"
#include "menu.h"
#include "mode.h"
#include "viewerinfo.h"

#define DEFAULT_SCENE_MODULE_ID	(0)
#define OBJECT_MODULE_ID	(1)

extern MgiCharacter *CreateDefaultScene( MhcModule *module_ptr );
extern MgiCharacter *CreateObject( MhcModule *module_ptr );

extern MENU gRootMenu;
extern u8 _codeSegmentEnd[ ];
extern u32 gMgiEvalCount[ ];

/* ===========================================================================
	variables
 =========================================================================== */
MODE		gMode;
ViewerInfo	gViewerInfo;

/* ===========================================================================
	functions
 =========================================================================== */
static void resetreg(void)
{
    MhcNode	*camera_node_ptr;

    gMode.anim_pitch = ANIM_PITCH_1;
    gMode.anim_index = 0;

    modeResetCamera( &gMode );
    modeResetObject( &gMode );
    modeResetBG( &gMode );
    modeResetFog( &gMode );
    modeLoadVideoMode( &gMode );
    gMode.icon_visibility = 0;

    if ( mhcModuleGetNodeByType(
		_mhcSceneGetModule( _mgiAppGetHierarchy( ), 1 ),
		_mifMagicDefine( 'P', 'C', 'A', 'M' ), 1, &camera_node_ptr ) )
    {
	gMode.scene_camera_enable = 1;
	gMode.camera_mode = CAMERA_SCENE;
    }
    else gMode.scene_camera_enable = 0;

    gMode.dither_filter_enable = TRUE;
}

void mode_callback( MgiJob *job_ptr, MgiApp *app_ptr )
{
    static char	buf[ 16 ];
#if 0
    u32		eval_count;
#endif
    MvmColor4c	bg_color;
    int		i;

    ( void )job_ptr;

    gMgiApp.is_perfbar_enable = gMode.perfmon_enable;

    menu( &gRootMenu, app_ptr->cont_data, NULL );
    modeStoreFog( &gMode );
    modeStoreBG( &gMode );
    modeStoreVideoMode( &gMode );

    sprintf( buf, "%3dFPS", gMgiApp.frame_rate );
    nuDebConTextPos( 0, 32, 4 );
    nuDebConTextColor( 0, 7 );
    nuDebConCPuts( 0, buf );

#if 0
    eval_count = 0;
    for ( i = 0; i < 100; ++i )
    {
	eval_count += gMgiEvalCount[ i ];
    }
    sprintf( buf, "%5duSec", eval_count / 100 / 1000 );
    nuDebConTextPos( 0, 30, 5 );
    nuDebConTextColor( 0, 7 );
    nuDebConCPuts( 0, buf );
#endif

    _mgiAppGetHierarchy( )->icon_visibility = gMode.icon_visibility;
}

void callback( MgiJob *job_ptr, MgiApp *app_ptr )
{
}

/* ------------------------------------------------------------------------- */
void setup_allocator( void )
{
    static MsoHeapAllocator	heap_allocator[ 2 ];
    static MsoCascadeAllocator	cascade_allocator;

    void		*heap_ptr;

    heap_ptr = _codeSegmentEnd;
    msoHeapAllocatorInit( &heap_allocator[ 0 ],
			  heap_ptr, 0x80400000 - ( u32 )heap_ptr );
    if ( osMemSize > 4194304 )
    {
	msoHeapAllocatorInit( &heap_allocator[ 1 ],
			      ( void * )0x80400000, 0x80800000 - 0x80400000 );
	msoCascadeAllocatorInit( &cascade_allocator,
			_msoUpCast( MsoAllocator, &heap_allocator[ 0 ] ),
			( u32 )heap_ptr, 0x80400000,
			_msoUpCast( MsoAllocator, &heap_allocator[ 1 ] ),
			( u32 )0x80400000, 0x80800000 );
	msoSetDefaultAllocator( _msoUpCast( MsoAllocator,
					    &cascade_allocator ) );
    }
    else
    {
	msoSetDefaultAllocator( _msoUpCast( MsoAllocator,
					    &heap_allocator[ 0 ] ) );
    }
}

/* ---------------------------------------------------------------------------
   main function

   main function that user uses. User has control but not outside main function
 --------------------------------------------------------------------------- */
void mainproc(void *arg)
{
    static MgiJob	mode_job;
    static MgiJob	viewer_job;
    MgiCharacter	*default_scene_ptr;
    MgiCharacter	*object_ptr;

    int		i;
    MrnGroup	*group_ptr;

    ( void )arg;

    /* Initialize Default allocator */
    setup_allocator( );

    _msoPrintfInit( );

    _msoPrintf( "Start\n" );
    /* Initialize Application */
    mgiAppInit( 2, 1024, 65536, 16384, 8, 262144, NULL );
    gMgiApp.is_perfbar_enable = TRUE;
    gMode.perfmon_enable = TRUE;
#ifdef F3DEX_GBI_2
    gMgiApp.render_microcode = NU_GFX_UCODE_F3DEX2_REJ;
#else	/* F3DEX_GBI_2 */
    gMgiApp.render_microcode = NU_GFX_UCODE_F3DEX2_REJ;
#endif	/* F3DEX_GBI_2 */
    nuDebConClear(0);
    nuDebConTextPos(0, 0, 0);
    nuDebConCPuts(0, "NIFF");

    /* Initialize Group */
    for ( i = 0; i < MRN_SCENE_MAX_GROUPS; ++i )
    {
	group_ptr = ( MrnGroup * )msoMalloc( sizeof( MrnGroup ) );
	mrnGroupInit( group_ptr );
	_mgiAppGetScene( )->group_ptr_array[ i ] = group_ptr;
	group_ptr->view_ptr = _msoUpCast( MrnView, _mgiAppGetScreen( ) );
    }

    LoadScene( _mgiAppGetHierarchy( ), &gViewerInfo );

    /* Initialize register */
    resetreg();

    /* Registering Character/Job */
    mgiJobInit( &mode_job, mode_callback, NULL );
    mgiJobInit( &viewer_job, callback, NULL );

    default_scene_ptr =
	CreateDefaultScene( _mhcSceneGetModule( _mgiAppGetHierarchy( ),
						DEFAULT_SCENE_MODULE_ID ) );
    _mgiAppAddCharacter( default_scene_ptr );

    object_ptr = CreateObject( _mhcSceneGetModule( _mgiAppGetHierarchy( ),
						   OBJECT_MODULE_ID ) );
    _mgiAppAddCharacter( object_ptr );

    mgiAppAddFrameJob( &mode_job );
    mgiAppAddRenderJob( &viewer_job );

    mgiAppMainLoop( );
}
