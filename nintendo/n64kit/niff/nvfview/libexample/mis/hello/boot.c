/*
  mis/hello/boot.c
    A example of 'libmis'
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 25, 1998.
*/

#include <ultra64.h>
#include "mso/HeapAllocator.h"
#include "mso/debug.h"

#define IDLE_STACK_SIZE	(8192)
#define MAIN_STACK_SIZE	(65536)
#define HEAP_SIZE	(1048576)

#define IDLE_THREAD_ID	(1)
#define MAIN_THREAD_ID	(2)

#define INITIAL_IDLE_THREAD_PRIORITY	(10)
#define MAIN_THREAD_PRIORITY		(10)

#define MAX_PI_MESSAGES	(256)

static OSThread	idle_thread;
static OSThread	main_thread;

static u64	idle_stack[ IDLE_STACK_SIZE / 8 ];
u64		main_stack[ MAIN_STACK_SIZE / 8 ];

static u64		heap[ HEAP_SIZE / 8 ];
static MsoHeapAllocator	allocator;


/* Declare prototype of functions */
static void init_pi( void );
static void idle_proc( void *arg );
extern void main_proc( void *arg );

/*--------------------------------------------------------------------*/
void boot( void )
{
    osInitialize();

    osCreateThread( &idle_thread, IDLE_THREAD_ID, idle_proc, NULL,
		    &idle_stack[ IDLE_STACK_SIZE / 8 ],
		    INITIAL_IDLE_THREAD_PRIORITY );
    osStartThread( &idle_thread );
}

/*--------------------------------------------------------------------*/
static void init_pi( void )
{
    static OSMesgQueue	pi_message_queue;
    static OSMesg	pi_message_buffer[ MAX_PI_MESSAGES ];

    osCreatePiManager( OS_PRIORITY_PIMGR, &pi_message_queue,
		       pi_message_buffer, MAX_PI_MESSAGES );
}

/*--------------------------------------------------------------------*/
static void idle_proc( void *arg )
{
    init_pi( );

    msoHeapAllocatorInit( &allocator, heap, HEAP_SIZE );
    msoSetDefaultAllocator( _msoUpCast( MsoAllocator, &allocator ) );

    _msoPrintfInit( );

    osCreateThread( &main_thread, MAIN_THREAD_ID, main_proc, NULL,
		    &main_stack[ MAIN_STACK_SIZE / 8 ], MAIN_THREAD_PRIORITY );
    osStartThread( &main_thread );

    /* Restore normal priority  */
    osSetThreadPri( &idle_thread, OS_PRIORITY_IDLE );

    while( 1 );	/* Infinite loop !! */
}
