/*
  sched.c
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 9, 1999.
    Customized scheduler for NuSYS
*/

#include "nux.h"

/*-- Constant macro definition --------------------------------------------*/
#define VSYNC_MSG	(0)
#define RSP_DONE_MSG	(1)		/* RSP task finished */
#define RDP_DONE_MSG	(2)		/* RDP rendering finished */
#define PRE_NMI_MSG	(3)
#define QUEUE_SYNC_MSG	(4)		/* FrameQueue Synchronization */
#define GET_PERF_MSG	(8)		/* Obtain Performance profile */
#define PAL_FRAME_RATE	(50)
#define NTSC_FRAME_RATE	(60)
#define	STOP_FLAG	(8)
#define	SEND_FRAME_MSG	(4)
#define	QUEUE_SIZE_MASK	(3)

/*-- Macro definition ------------------------------------------------------*/
#ifdef NU_DEBUG
# define DEBUG_PRINT(str) osSyncPrintf(str)
#else	/* NU_DEBUG */
# define DEBUG_PRINT(str)
#endif	/* NU_DEBUG */
#define IS_FRAME_MSG(msg) ( (msg) & 1 )
#define IS_QUEUE_SYNC_MSG(msg) \
	( ( (msg) >= QUEUE_SYNC_MSG )&&( (msg) < QUEUE_SYNC_MSG + 4 ) )

/*-- Static function prototype -------------------------------------------*/
static void message_handler( void *ptr );
static s32 default_unlock( NuxScFrame *frame_ptr );
static s32 default_lock( NuxScFrame *frame_ptr );
static void dispatch( NUScTask *task_ptr, NuxScPerfWork *perf_work_ptr );
static void dispatch_audio( NUScTask *task_ptr, NuxScPerfWork *perf_work_ptr );
static void set_rsp_count( NuxSched *sched_ptr );
static void set_audio_count( NuxSched *sched_ptr );
static void set_rdp_count( NuxSched *sched_ptr );
static void record_frame_count( NuxSched *sched_ptr );
static void set_up_perf_buffer( NuxSched *sched_ptr );
static void broadcast( NUScMsg *msg );
static void frame_queue_put( NuxSched *sched_ptr, NuxScFrame *frame_ptr );
static void frame_queue_pop( NuxSched *sched_ptr );
static void clear_messages( OSMesgQueue *message_queue_ptr );
static NUScTask *next_task( NuxSched *sched_ptr );
static NUScTask *execute_task( NuxSched *sched_ptr );
static void handle_vsync( NuxSched *sched_ptr );
static void handle_queue_sync( NuxSched *sched_ptr, const int queue_size );
static void *state_idle( NuxSched *sched_ptr, const u32 message_code );
static void *state_rsp_wait( NuxSched *sched_ptr, const u32 message_code );
static void *state_rsp_followed_rdp( NuxSched *sched_ptr,
				     const u32 message_code );
static void *state_rdp_wait( NuxSched *sched_ptr, const u32 message_code );
static void *state_yield_wait( NuxSched *sched_ptr, const u32 message_code );
static void *state_audio( NuxSched *sched_ptr, const u32 message_code );
static void *state_audio_no_rdp( NuxSched *sched_ptr, const u32 message_code );
static void *state_audio_idle( NuxSched *sched_ptr, const u32 message_code );
static void *state_audio_yielded( NuxSched *sched_ptr,
				  const u32 message_code );
static void *state_audio_yielded2( NuxSched *sched_ptr,
				  const u32 message_code );

/*-- Static variables -----------------------------------------------------*/
static u64		nuScStack[ NU_SC_STACK_SIZE / 8 ];
static NuxSched		nuxsched;
static NuxScFrame	frame_array[ NUX_SC_FRAME_QUEUE_SIZE ];
static int		next_frame = 0;

/*-- Global variables -----------------------------------------------------*/
u32				nuScRetraceCounter;
u8				nuScPreNMIFlag = 0;
NUScPreNMIFunc			nuScPreNMIFunc	= NULL;
volatile NuxScUnlockFrameFunc	nuxScUnlockFrame	= default_unlock;
volatile NuxScLockFrameFunc	nuxScLockFrame	= default_lock;
volatile u32			nuxGfxFrameSpool = 0;

/*-- NuSystem compatible interface -------------------------------------*/
void nuScCreateScheduler( u8 videoMode, u8 numFields )
{
    /* Initialize variables */
    nuxsched.clientList		= NULL;
    nuxsched.retraceMsg		= NU_SC_RETRACE_MSG;
    nuxsched.prenmiMsg		= NU_SC_PRENMI_MSG;
    nuxsched.retraceCount	= numFields;
    nuxsched.frameRate		= ( osTvType == OS_TV_PAL ) ? 50 : 60;
    nuxsched.task_stop_count	= ( nuxsched.frameRate / 2 ) /
				  nuxsched.retraceCount - 5;
    nuxsched.flags		= 0;
    nuxsched.vsync_count	= 0;
    nuxsched.frame_queue_size	= 0;
    nuxsched.frame_queue.head	= NULL;
    nuxsched.frame_queue.tail	= NULL;

    nuScPreNMIFlag		= 0;

    nuxsched.perf.rsp		= 0;
    nuxsched.perf.rdp		= 0;
    nuxsched.perf.frame_rate	= 0;

    nuxsched.perf.counter.clock_count	= 0;
    nuxsched.perf.counter.command_count	= 0;
    nuxsched.perf.counter.pipe_count	= 0;
    nuxsched.perf.counter.tmem_count	= 0;

    /* Create message que */
    osCreateMesgQueue( &nuxsched.taskMessageQueue, nuxsched.taskMessageBuffer,
		       NUX_SC_MAX_MESGS );
    osCreateMesgQueue( &nuxsched.replyMessageQueue,
		       nuxsched.replyMessageBuffer,
		       1 );

    /* Set the video mode */
    osCreateViManager( OS_PRIORITY_VIMGR );
    osViSetMode( &osViModeTable[ videoMode ] );
    osViBlack( TRUE );

    /* Register the event handler */
    osViSetEvent( &nuxsched.taskMessageQueue, ( OSMesg )VSYNC_MSG, numFields );
    osSetEventMesg( OS_EVENT_SP, &nuxsched.taskMessageQueue,
		    ( OSMesg )RSP_DONE_MSG );
    osSetEventMesg( OS_EVENT_DP, &nuxsched.taskMessageQueue,
		    ( OSMesg )RDP_DONE_MSG );
    osSetEventMesg( OS_EVENT_PRENMI, &nuxsched.taskMessageQueue,
		    ( OSMesg )PRE_NMI_MSG );

    /* Start the Scheduler thread */
    osCreateThread( &nuxsched.schedulerThread, 19,
		    (void(*)(void*))message_handler,
		    (void *)&nuxsched,
		    nuScStack+NU_SC_STACK_SIZE/sizeof(u64),
		    NU_SC_HANDLER_PRI );
    osStartThread( &nuxsched.schedulerThread );
}

/*-- NuSystem compatible interface -------------------------------------*/
OSMesgQueue *nuScGetAudioMQ( void )
{
    return &nuxsched.taskMessageQueue;
}

/*-- NuSystem compatible interface -------------------------------------*/
OSMesgQueue *nuScGetGfxMQ( void )
{
    return &nuxsched.taskMessageQueue;
}

/*-- NuSystem compatible interface -------------------------------------*/
void nuScAddClient( NUScClient *client, OSMesgQueue *msgQ, NUScMsg msgType )
{
    OSIntMask	mask;

    mask = osSetIntMask( OS_IM_NONE );

    client->msgQ	= msgQ;
    client->next	= nuxsched.clientList;
    client->msgType	= msgType;
    nuxsched.clientList	= client;

    /* Dispatch a message if a PRENMI message has already been received.	*/
    if ( ( msgType & NU_SC_PRENMI_MSG ) && nuScPreNMIFlag )
    {
	osSendMesg( msgQ, ( OSMesg* )&nuxsched.prenmiMsg, OS_MESG_NOBLOCK );
    }

    osSetIntMask(mask);
}

/*-- NuSystem compatible interface -------------------------------------*/
void nuScResetClientMesgType( NUScClient* client, NUScMsg msgType )
{
    OSIntMask	mask;
    mask = osSetIntMask( OS_IM_NONE );
    client->msgType = msgType;
    osSetIntMask(mask);
}

/*-- NuSystem compatible interface -------------------------------------*/
void nuScRemoveClient( NUScClient *c )
{
    NUScClient*	client	= nuxsched.clientList; 
    NUScClient*	prev	= 0;
    OSIntMask	mask;

    mask = osSetIntMask(OS_IM_NONE);
    while(client != 0){
	if(client == c){
	    if(prev){
		prev->next = c->next;
	    } else {
		nuxsched.clientList = c->next;
	    }
	    break;
	}
	prev   = client;
	client = client->next;
    }
    osSetIntMask(mask);
}

/*-- NuSystem compatible interface -------------------------------------*/
s32 nuScGetFrameRate( void )
{
    return nuxsched.frameRate;
}

/*--------------------------------------------------------------------*/
NuxScFrame *nuxScNewFrame( void )
{
    NuxScFrame	*frame_ptr;
    frame_ptr = &frame_array[ next_frame ];
    frame_ptr->task_list.head = NULL;
    frame_ptr->task_list.tail = NULL;
    next_frame = ( next_frame + 1 ) % NUX_SC_FRAME_QUEUE_SIZE;
    return frame_ptr;
}

/*--------------------------------------------------------------------*/
void nuxScFrameAddTask( NuxScFrame *frame_ptr, NUScTask *task_ptr )
{
    task_ptr->next = NULL;

    if ( frame_ptr->task_list.tail )
    {
	frame_ptr->task_list.tail->next = task_ptr;
    }
    else frame_ptr->task_list.head = task_ptr;

    frame_ptr->task_list.tail = task_ptr;
}

/*--------------------------------------------------------------------*/
int nuxScSendFrame( NuxScFrame *frame_ptr, const int wait, const int size )
{
    u32	message_code;

    if ( size > 3 ) return NUX_SC_FAILURE;
    if ( wait == NUX_SC_WAIT )
    {
	message_code = QUEUE_SYNC_MSG + size;
	clear_messages( &nuxsched.replyMessageQueue );
	osSendMesg( &nuxsched.taskMessageQueue, ( OSMesg )message_code,
		    OS_MESG_BLOCK );
	osRecvMesg( &nuxsched.replyMessageQueue, NULL, OS_MESG_BLOCK );
    }
    else
    {
	if ( nuxGfxFrameSpool > size ) return NUX_SC_FAILURE;
    }

    if ( frame_ptr )
    {
	message_code = ( u32 )frame_ptr + 1;
	osSendMesg( &nuxsched.taskMessageQueue, ( OSMesg )message_code,
		    OS_MESG_BLOCK );
    }
    return NUX_SC_SUCCESS;
}

/*--------------------------------------------------------------------*/
void nuxScFrameAllEndWait( void )
{
    nuxScSendFrame( NULL, NUX_SC_WAIT, 0 );
}

/*--------------------------------------------------------------------*/
void nuxScGetPerf( NuxScPerf *perf_ptr )
{
    u32	rdp_clock_cycle;

    rdp_clock_cycle = ( osTvType == OS_TV_PAL ) ? 6243 : 6085;

    osSendMesg( &nuxsched.taskMessageQueue, ( OSMesg )GET_PERF_MSG,
		OS_MESG_BLOCK );
    osRecvMesg( &nuxsched.replyMessageQueue, NULL, OS_MESG_BLOCK );

    perf_ptr->rsp	= OS_CYCLES_TO_USEC( nuxsched.perf_buffer.rsp );
    perf_ptr->rdp	= OS_CYCLES_TO_USEC( nuxsched.perf_buffer.rdp );
    perf_ptr->audio	= OS_CYCLES_TO_USEC( nuxsched.perf_buffer.audio ) * 0;

    perf_ptr->clock	= nuxsched.perf_buffer.counter.clock_count * 100 /
			  rdp_clock_cycle;
    perf_ptr->command	= nuxsched.perf_buffer.counter.command_count * 100 /
			  rdp_clock_cycle;
    perf_ptr->pipe	= nuxsched.perf_buffer.counter.pipe_count * 100 /
			  rdp_clock_cycle;
    perf_ptr->tmem	= nuxsched.perf_buffer.counter.tmem_count * 100 /
			  rdp_clock_cycle;

    perf_ptr->frame_rate = nuxsched.perf_buffer.frame_rate;
}

#ifdef NU_DEBUG
typedef struct { NuxScState state; u32 message; } History;
History history[ 8 ] = { NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0 };
#endif	/* NU_DEBUG */

/*--------------------------------------------------------------------*/
static void message_handler( void *ptr )
{
    OSMesg		message;
    u32			message_code;
    NuxScState		state;

    ( void )ptr;

    state = state_idle;
    osDpSetStatus( DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_CMD_CTR |
		   DPC_CLR_CLOCK_CTR );
    nuxsched.perf_work.valid_frame_table_size	= 0;
    nuxsched.perf_work.frame_table_cursor	= 0;
    while ( TRUE )
    {
	osRecvMesg( &nuxsched.taskMessageQueue, &message, OS_MESG_BLOCK );
	message_code = ( u32 )message;
	if ( IS_QUEUE_SYNC_MSG( message_code ) )
	{
	    handle_queue_sync( &nuxsched, message_code - QUEUE_SYNC_MSG );
	    continue;
	}
	if ( message_code == PRE_NMI_MSG )
	{
	    nuxsched.pre_nmi_count = 1;
	    broadcast( &nuxsched.prenmiMsg );
	    if ( nuScPreNMIFunc != NULL ) ( *nuScPreNMIFunc )( );
	    continue;
	}
	if ( message_code == GET_PERF_MSG )
	{
	    set_up_perf_buffer( &nuxsched );
	    osSendMesg( &nuxsched.replyMessageQueue, ( OSMesg )0,
			OS_MESG_NOBLOCK );
	    continue;
	}

#ifdef NU_DEBUG
	history[ 7 ] = history[ 6 ];
	history[ 6 ] = history[ 5 ];
	history[ 5 ] = history[ 4 ];
	history[ 4 ] = history[ 3 ];
	history[ 3 ] = history[ 2 ];
	history[ 2 ] = history[ 1 ];
	history[ 1 ] = history[ 0 ];
	history[ 0 ].state = state;
	history[ 0 ].message = message_code;
#endif	/* NU_DEBUG */

	state = state( &nuxsched, message_code );
	if ( state == NULL ) while ( TRUE );
    }
}

/*--------------------------------------------------------------------*/
static void broadcast( NUScMsg *msg )
{
    NUScClient	*client_ptr;
  
    for ( client_ptr = nuxsched.clientList; client_ptr != NULL;
	  client_ptr = client_ptr->next )
    {
	if ( client_ptr->msgType & *msg )
	{
	    osSendMesg( client_ptr->msgQ, ( OSMesg )msg, OS_MESG_NOBLOCK );
	}
    }
}

/*--------------------------------------------------------------------*/
static void dispatch( NUScTask *task_ptr, NuxScPerfWork *perf_work_ptr )
{
    osWritebackDCacheAll( );
    osSpTaskStart( &task_ptr->list );
    perf_work_ptr->task_start = osGetCount( );
}

/*--------------------------------------------------------------------*/
static void dispatch_audio( NUScTask *task_ptr, NuxScPerfWork *perf_work_ptr )
{
    osWritebackDCacheAll( );
    osSpTaskStart( &task_ptr->list );
    perf_work_ptr->audio_start = osGetCount( );
}

/*--------------------------------------------------------------------*/
static void set_rsp_count( NuxSched *sched_ptr )
{
    sched_ptr->perf_work.rsp_done = osGetCount( );
    sched_ptr->perf.rsp += sched_ptr->perf_work.rsp_done -
			   sched_ptr->perf_work.task_start;
}

/*--------------------------------------------------------------------*/
static void set_audio_count( NuxSched *sched_ptr )
{
    sched_ptr->perf_work.rsp_done = osGetCount( );
    sched_ptr->perf.audio += sched_ptr->perf_work.rsp_done -
			     sched_ptr->perf_work.audio_start;
}

/*--------------------------------------------------------------------*/
static void set_rdp_count( NuxSched *sched_ptr )
{
    sched_ptr->perf_work.rdp_done = osGetCount( );
    sched_ptr->perf.rdp += sched_ptr->perf_work.rdp_done -
			   sched_ptr->perf_work.task_start;

    osDpGetCounters( ( u32 * )&sched_ptr->perf_work.counter );
    osDpSetStatus( DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_CMD_CTR |
		   DPC_CLR_CLOCK_CTR );
    sched_ptr->perf.counter.clock_count +=
		sched_ptr->perf_work.counter.clock_count;
    sched_ptr->perf.counter.command_count +=
		sched_ptr->perf_work.counter.command_count;
    sched_ptr->perf.counter.pipe_count +=
		sched_ptr->perf_work.counter.pipe_count;
    sched_ptr->perf.counter.tmem_count +=
		sched_ptr->perf_work.counter.tmem_count;
}

/*--------------------------------------------------------------------*/
static void record_frame_count( NuxSched *sched_ptr )
{
    sched_ptr->perf_work.frame_table[ sched_ptr->perf_work.frame_table_cursor ]
		= sched_ptr->vsync_count;
    sched_ptr->perf_work.frame_table_cursor =
			( sched_ptr->perf_work.frame_table_cursor + 1 ) &
			NUX_SC_FRAME_TABLE_INDEX_MASK;
    if ( sched_ptr->perf_work.valid_frame_table_size <
	 NUX_SC_FRAME_TABLE_SIZE )
    {
	++sched_ptr->perf_work.valid_frame_table_size;
    }
}

/*--------------------------------------------------------------------*/
static void set_up_perf_buffer( NuxSched *sched_ptr )
{
    u32	top_index, bottom_index;
    u32	interval;

    sched_ptr->perf_buffer.rsp = sched_ptr->perf.rsp;
    sched_ptr->perf_buffer.rdp = sched_ptr->perf.rdp;
    sched_ptr->perf_buffer.audio = sched_ptr->perf.audio;
    sched_ptr->perf_buffer.counter.clock_count =
				sched_ptr->perf.counter.clock_count;
    sched_ptr->perf_buffer.counter.command_count =
				sched_ptr->perf.counter.command_count;
    sched_ptr->perf_buffer.counter.pipe_count =
				sched_ptr->perf.counter.pipe_count;
    sched_ptr->perf_buffer.counter.tmem_count =
				sched_ptr->perf.counter.tmem_count;

    sched_ptr->perf_buffer.frame_rate = 0;
    if ( sched_ptr->perf_work.valid_frame_table_size > 1 )
    {
	top_index = ( sched_ptr->perf_work.frame_table_cursor - 1 +
		NUX_SC_FRAME_TABLE_SIZE ) & NUX_SC_FRAME_TABLE_INDEX_MASK;
	bottom_index = ( sched_ptr->perf_work.frame_table_cursor -
		sched_ptr->perf_work.valid_frame_table_size +
		NUX_SC_FRAME_TABLE_SIZE ) & NUX_SC_FRAME_TABLE_INDEX_MASK;
	interval = sched_ptr->perf_work.frame_table[ top_index ] -
		   sched_ptr->perf_work.frame_table[ bottom_index ];
	if ( interval > 0 )
	{
	    sched_ptr->perf_buffer.frame_rate = sched_ptr->frameRate *
			( sched_ptr->perf_work.valid_frame_table_size - 1 ) /
			interval;
	}
    }

    sched_ptr->perf.rsp = 0;
    sched_ptr->perf.rdp = 0;
    sched_ptr->perf.audio = 0;
    sched_ptr->perf.counter.clock_count	= 0;
    sched_ptr->perf.counter.command_count	= 0;
    sched_ptr->perf.counter.pipe_count	= 0;
    sched_ptr->perf.counter.tmem_count	= 0;
}

/*--------------------------------------------------------------------*/
static void send_task_complete_message( NUScTask *task_ptr )
{
    osSendMesg( task_ptr->msgQ, task_ptr->msg, OS_MESG_BLOCK );
}

/*--------------------------------------------------------------------*/
static NUScTask *execute_task( NuxSched *sched_ptr )
{
    NuxScFrame	*frame_ptr;
    NUScTask	*next_task_ptr = NULL;

    if ( sched_ptr->flags & STOP_FLAG ) return NULL;

    frame_ptr = sched_ptr->frame_queue.head;
    if ( frame_ptr )
    {
	if ( nuxScLockFrame( frame_ptr ) == NUX_SC_SUCCESS )
	{
	    record_frame_count( sched_ptr );
	    next_task_ptr = frame_ptr->task_list.head;
	    if ( next_task_ptr ) dispatch( next_task_ptr,
					   &sched_ptr->perf_work );
	}
    }
    return next_task_ptr;
}

/*--------------------------------------------------------------------*/
static NUScTask *next_task( NuxSched *sched_ptr )
{
    NUScTask	*next_task_ptr = NULL;
    NuxScFrame	*frame_ptr;

    if ( sched_ptr->flags & STOP_FLAG ) return NULL;

    if ( sched_ptr->task_ptr )
    {
	next_task_ptr = sched_ptr->task_ptr->next;
	if ( next_task_ptr )
	{
	    dispatch( next_task_ptr, &sched_ptr->perf_work );
	    return next_task_ptr;
	}
    }

    frame_ptr = sched_ptr->frame_queue.head;
    if ( frame_ptr )
    {
	nuxScUnlockFrame( frame_ptr );
	frame_queue_pop( sched_ptr );
	frame_ptr = sched_ptr->frame_queue.head;
	if ( frame_ptr )
	{
	    if ( nuxScLockFrame( frame_ptr ) == NUX_SC_SUCCESS )
	    {
		record_frame_count( sched_ptr );
		next_task_ptr = frame_ptr->task_list.head;
		if ( next_task_ptr ) dispatch( next_task_ptr,
					       &sched_ptr->perf_work );
	    }
	}
    }

    return next_task_ptr;
}

/*--------------------------------------------------------------------*/
static void frame_queue_put( NuxSched *sched_ptr, NuxScFrame *frame_ptr )
{
    if ( !( sched_ptr->flags & STOP_FLAG ) )
    {
	frame_ptr->next = NULL;

	if ( sched_ptr->frame_queue.tail )
			sched_ptr->frame_queue.tail->next = frame_ptr;
	else sched_ptr->frame_queue.head = frame_ptr;
	sched_ptr->frame_queue.tail = frame_ptr;

	++sched_ptr->frame_queue_size;
    }
}

/*--------------------------------------------------------------------*/
static void frame_queue_pop( NuxSched *sched_ptr )
{
    NuxScFrame	*head_ptr;

    head_ptr = sched_ptr->frame_queue.head;
    if ( head_ptr )
    {
	sched_ptr->frame_queue.head = head_ptr->next;
	if ( !sched_ptr->frame_queue.head ) sched_ptr->frame_queue.tail = NULL;
    }
    --sched_ptr->frame_queue_size;
    if ( sched_ptr->flags & SEND_FRAME_MSG )
    {
	if ( sched_ptr->frame_queue_size <=
	     sched_ptr->flags & QUEUE_SIZE_MASK )
	{
	    osSendMesg( &sched_ptr->replyMessageQueue, ( OSMesg )0,
			OS_MESG_NOBLOCK );
	    sched_ptr->flags &= ~( SEND_FRAME_MSG | QUEUE_SIZE_MASK );
	}
    }
}

/*--------------------------------------------------------------------*/
static void clear_messages( OSMesgQueue *message_queue_ptr )
{
    while ( !osRecvMesg( message_queue_ptr, NULL, OS_MESG_NOBLOCK ) );
}

/*--------------------------------------------------------------------*/
static void handle_vsync( NuxSched *sched_ptr )
{
    ++sched_ptr->vsync_count;
    if ( sched_ptr->pre_nmi_count )
    {
	if ( !( sched_ptr->flags & STOP_FLAG ) )
	{
	    ++sched_ptr->pre_nmi_count;
	    if ( ++sched_ptr->pre_nmi_count > sched_ptr->task_stop_count )
	    {
		sched_ptr->flags |= STOP_FLAG;
		osAfterPreNMI( );
		osViSetYScale( 1.0f );
		osViBlack( TRUE );
	    }
	}
    }
    broadcast( &sched_ptr->retraceMsg );
}

/*--------------------------------------------------------------------*/
static void handle_queue_sync( NuxSched *sched_ptr, const int queue_size )
{
    if ( sched_ptr->frame_queue_size <= queue_size )
    {
	osSendMesg( &nuxsched.replyMessageQueue, ( OSMesg )0,
		    OS_MESG_NOBLOCK );
    }
    else sched_ptr->flags |= SEND_FRAME_MSG | queue_size;
}

/*-- State: idle -----------------------------------------------------*/
static void *state_idle( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	sched_ptr->task_ptr = execute_task( sched_ptr );
	handle_vsync( sched_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	else return ( void * )state_idle;
    case RSP_DONE_MSG:
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: Idle RSP/RDP.\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	sched_ptr->task_ptr = execute_task( sched_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	return ( void * )state_idle;
    }
    else
    {
	sched_ptr->audio_ptr = ( NUScTask * )message_code;
	dispatch( sched_ptr->audio_ptr, &sched_ptr->perf_work );
	return ( void * )state_audio_idle;
    }
}

/*-- State: RSP wait -------------------------------------------------*/
static void *state_rsp_wait( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_rsp_wait;
    case RSP_DONE_MSG:
	set_rsp_count( sched_ptr );
	if ( sched_ptr->task_ptr->flags & NU_SC_NORDP )
	{
	    sched_ptr->task_ptr = next_task( sched_ptr );
	    if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	    return ( void * )state_idle;
	}
	return ( void * )state_rdp_wait;
    case RDP_DONE_MSG:
	set_rdp_count( sched_ptr );
	return ( void * )state_rsp_followed_rdp;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_rsp_wait:FRAME\n" );
	return ( void * )state_rsp_wait;
    }
    else
    {
	osSpTaskYield( );
	return ( void * )state_yield_wait;
    }
}

/*-- State: RSP followed RDP -----------------------------------------*/
static void *state_rsp_followed_rdp( NuxSched *sched_ptr,
				     const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_rsp_followed_rdp;
    case RSP_DONE_MSG:
	set_rsp_count( sched_ptr );
	sched_ptr->task_ptr = next_task( sched_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	return ( void * )state_idle;
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: RSPFollowedRDP  RDP.\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_rsp_followed_rdp:FRAME\n" );
	return ( void * )state_rsp_followed_rdp;
    }
    else
    {
	osSpTaskYield( );
	return ( void * )state_yield_wait;
    }
}

/*-- State: RDP wait -------------------------------------------------*/
static void *state_rdp_wait( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_rdp_wait;
    case RSP_DONE_MSG:
	DEBUG_PRINT( "Error: RDPWait RSP\n" );
	return NULL;
    case RDP_DONE_MSG:
	set_rdp_count( sched_ptr );
	sched_ptr->task_ptr = next_task( sched_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	return ( void * )state_idle;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_rdp_wait:FRAME\n" );
	return ( void * )state_rdp_wait;
    }
    else
    {
	sched_ptr->audio_ptr = ( NUScTask * )message_code;
	dispatch( sched_ptr->audio_ptr, &sched_ptr->perf_work );
	return ( void * )state_audio;
    }
}

/*-- State: yield wait -----------------------------------------------*/
static void *state_yield_wait( NuxSched *sched_ptr, const u32 message_code )
{
    int	yielded;

    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_yield_wait;
    case RSP_DONE_MSG:
	set_rsp_count( sched_ptr );
	yielded = osSpTaskYielded( &sched_ptr->task_ptr->list );
	dispatch( sched_ptr->audio_ptr, &sched_ptr->perf_work );
	if ( yielded ) return ( void * )state_audio_yielded;
	if ( sched_ptr->task_ptr->flags & NU_SC_NORDP )
	{
	    return ( void * )state_audio_no_rdp;
	}
	return ( void * )state_audio;
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: YieldWait RDP.\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_yield_wait:FRAME\n" );
	return ( void * )state_yield_wait;
    }
    else
    {
	DEBUG_PRINT( "Error: YieldWait Audio.\n" );
	return NULL;
    }
}

/*-- State: audio ----------------------------------------------------*/
static void *state_audio( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_audio;
    case RSP_DONE_MSG:
	set_audio_count( sched_ptr );
	send_task_complete_message( sched_ptr->audio_ptr );
	return ( void * )state_rdp_wait;
    case RDP_DONE_MSG:
	set_rdp_count( sched_ptr );
	return ( void * )state_audio_no_rdp;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_audio:FRAME\n" );
	return ( void * )state_audio;
    }
    else
    {
	DEBUG_PRINT( "Error: Audio Audio.\n" );
	return NULL;
    }
}

/*-- State: audio no RDP ---------------------------------------------*/
static void *state_audio_no_rdp( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_audio_no_rdp;
    case RSP_DONE_MSG:
	set_audio_count( sched_ptr );
	send_task_complete_message( sched_ptr->audio_ptr );
	sched_ptr->task_ptr = next_task( sched_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	return ( void * )state_idle;
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: AudioNoRDP RDP\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	return ( void * )state_audio_no_rdp;
    }
    else
    {
	DEBUG_PRINT( "Error: AudioNoRDP Audio.\n" );
	return NULL;
    }
}

/*-- State: audio idle -----------------------------------------------*/
static void *state_audio_idle( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_audio_idle;
    case RSP_DONE_MSG:
	set_audio_count( sched_ptr );
	sched_ptr->task_ptr = execute_task( sched_ptr );
	send_task_complete_message( sched_ptr->audio_ptr );
	if ( sched_ptr->task_ptr ) return ( void * )state_rsp_wait;
	return ( void * )state_idle;
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: AudioIdle RDP.\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	return ( void * )state_audio_idle;
    }
    else
    {
	DEBUG_PRINT( "Error: AudioIdle Audio.\n" );
	return NULL;
    }
}

/*-- State: audio yielded --------------------------------------------*/
static void *state_audio_yielded( NuxSched *sched_ptr, const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_audio_yielded;
    case RSP_DONE_MSG:
	set_audio_count( sched_ptr );
	dispatch( sched_ptr->task_ptr, &sched_ptr->perf_work );
	send_task_complete_message( sched_ptr->audio_ptr );
	return ( void * )state_rsp_wait;
    case RDP_DONE_MSG:
	set_rdp_count( sched_ptr );
	return ( void * )state_audio_yielded2;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_audio_yielded:FRAME\n" );
	return ( void * )state_audio_yielded;
    }
    else
    {
	DEBUG_PRINT( "Error: AudioYielded Audio.\n" );
	return NULL;
    }
}

/*-- State: audio yielded --------------------------------------------*/
static void *state_audio_yielded2( NuxSched *sched_ptr,
				   const u32 message_code )
{
    switch ( message_code )
    {
    case VSYNC_MSG:
	handle_vsync( sched_ptr );
	return ( void * )state_audio_yielded2;
    case RSP_DONE_MSG:
	set_audio_count( sched_ptr );
	dispatch( sched_ptr->task_ptr, &sched_ptr->perf_work );
	send_task_complete_message( sched_ptr->audio_ptr );
	return ( void * )state_rsp_followed_rdp;
    case RDP_DONE_MSG:
	DEBUG_PRINT( "Error: AudioYielded2 RDP\n" );
	return NULL;
    default:
	break;
    }

    if ( IS_FRAME_MSG( message_code ) )
    {
	frame_queue_put( sched_ptr, ( NuxScFrame * )( message_code & ~1 ) );
	DEBUG_PRINT( "state_audio_yielded:FRAME\n" );
	return ( void * )state_audio_yielded;
    }
    else
    {
	DEBUG_PRINT( "Error: AudioYielded Audio.\n" );
	return NULL;
    }
}

/*--------------------------------------------------------------------*/
static s32 default_unlock( NuxScFrame *frame_ptr )
{
    if ( nuGfxCfb )
    {
	osViBlack( FALSE );
	osViSwapBuffer( nuGfxCfb[ frame_ptr->id ] );
    }
    else
    {
	osViBlack( TRUE );
    }
    return NUX_SC_SUCCESS;
}

/*--------------------------------------------------------------------*/
static s32 default_lock( NuxScFrame *frame_ptr )
{
    void	*frame_buffer_ptr;

    if ( nuGfxCfb )
    {
	frame_buffer_ptr =  nuGfxCfb[ frame_ptr->id ];
	return ( osViGetCurrentFramebuffer( ) != frame_buffer_ptr ) ?
					NUX_SC_SUCCESS : NUX_SC_FAILURE;
    }
}
