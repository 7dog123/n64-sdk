/*
  main.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 9, 1999.
*/

#include "mgk/App.h"
#include "mgk/Obj.h"
#include "mso/debug.h"
#include "mso/HeapAllocator.h"
#include "nusys.h"

#define	MAX_OBJS	(4)

extern u8 _stageSegmentRomStart[ ], _stageSegmentRomEnd[ ];
extern u8 _animalSegmentRomStart[ ], _animalSegmentRomEnd[ ];
extern u8 _codeSegmentEnd[ ];

MgkObj	gObjArray[ MAX_OBJS ];

/* -------------------------------------------------------------------*/
void setup_allocator( void )
{
    static MsoHeapAllocator	heap_allocator;

    void		*heap_ptr;

    heap_ptr = _codeSegmentEnd;
    msoHeapAllocatorInit( &heap_allocator,
			  heap_ptr, 0x80380000 - ( u32 )heap_ptr );
    msoSetDefaultAllocator( _msoUpCast( MsoAllocator, &heap_allocator ) );
}

/* -------------------------------------------------------------------*/
static void move_cpu_char( void )
{
    static float	pos = 0.0f;
    static float	vel = -3.0f;

    if ( ( pos <= -300.0f )||( pos >= 300.0f ) ) vel = -vel;
    pos += vel;
    mgkObjMove( &gObjArray[ 1 ], -300.0f, 0.0f, pos );
}

/* -------------------------------------------------------------------*/
static void move_player_char_and_camera( void )
{
    static float	dir_x = 0.0f;
    static float	dir_z = 1.0f;
    static float	vel = 0.0f;
    static float	pos_x = 0.0f;
    static float	pos_z = 0.0f;

    float	vx;
    float	vz;
    float	n;

    vel = gMgiApp.cont_data->stick_y * 0.125f;
    if ( ( gMgiApp.cont_data->stick_x <= -32 )||
	 ( gMgiApp.cont_data->stick_x >= 32 ) )
    {
	vx = - dir_z * gMgiApp.cont_data->stick_x / 1024.0f;
	vz = dir_x * gMgiApp.cont_data->stick_x / 1024.0f;
	dir_x += vx;
	dir_z += vz;
	n = 1.0f / sqrtf( dir_x * dir_x + dir_z * dir_z );
	dir_x *= n;
	dir_z *= n;
    }

    pos_x += dir_x * vel;
    pos_z += dir_z * vel;

    mgkObjLookAt( &gObjArray[ 2 ], pos_x, 0.0f, pos_z,
				   pos_x - dir_x, 0.0f, pos_z - dir_z,
				   0.0f, 1.0f, 0.0f );

    mgkObjLookAt( &gObjArray[ 3 ],
		  pos_x - dir_x * 600.0f, 300.0f, pos_z - dir_z * 600.0f,
		  pos_x, 100.0f, pos_z,
		  0.0f, 1.0f, 0.0f );
}

/* -------------------------------------------------------------------*/
void mainproc( void *arg )
{
    ( void )arg;

    /* Initialize default allocator */
    setup_allocator( );

    _msoPrintfInit( );

    /* Initialize application */
    mgkAppInit( 2, 32768, 65536, 256, 16384, MAX_OBJS, gObjArray, NULL );

    /* Change screen resolution */
    if ( osTvType == OS_TV_PAL )
    {
	mrnScreenSetMode( _mgiAppGetScreen( ), MRN_SCREEN_RES_FPAL_320_240,
			  2, 16, 1 );
    }
    else
    {
	mrnScreenSetMode( _mgiAppGetScreen( ), MRN_SCREEN_RES_NTSC_320_240,
			  2, 16, 1 );
    }
    _msoUpCast( MrnView, _mgiAppGetScreen( ) )->clear_flags =
						MRN_VIEW_CLEAR_DEPTH_BUFFER;

    mgkAppInitGroups( );

    /* load NVF */
    mgkObjLoad( &gObjArray[ 0 ], ( u32 )_stageSegmentRomStart,
				 ( u32 )_stageSegmentRomEnd );
    mgkObjLoad( &gObjArray[ 1 ], ( u32 )_animalSegmentRomStart,
				 ( u32 )_animalSegmentRomEnd );
    mgkObjLoad( &gObjArray[ 2 ], ( u32 )_animalSegmentRomStart,
				 ( u32 )_animalSegmentRomEnd );
    mgkObjCreateCamera( &gObjArray[ 3 ], 45.0f, 1.333333333f, 5.0f, 2000.0 );

    mgkObjSetAnim( &gObjArray[ 1 ], 0 );
    mgkObjPlayAnim( &gObjArray[ 1 ], 0.0f, 60.0f, 1.0f, 1 );

    /* Main loop */
    while ( 1 )
    {
	++gMgiApp.frame_count;
	nuContDataGetExAll( gMgiApp.cont_data );

	_mgkAppBeginFrame( );

	move_cpu_char( );
	move_player_char_and_camera( );

	mgkAppEvalAll( );
	mgkAppDraw( );
	_mgkAppEndFrame( );
    }
}
