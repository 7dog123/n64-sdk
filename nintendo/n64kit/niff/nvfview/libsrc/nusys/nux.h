/*
  nux.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 4, 1999.
*/

#ifndef _NUX_H
#define _NUX_H 1

#include "nusys.h"

/* Constant macro */
#define NUX_SC_SUCCESS			(0)
#define NUX_SC_FAILURE			(1)
#define NUX_SC_NOWAIT			(0)
#define NUX_SC_WAIT			(1)
#define NUX_SC_FRAME_QUEUE_SIZE		(4)
#define NUX_SC_MAX_MESGS		(8)
#define NUX_SC_FRAME_TABLE_SIZE		(16)
#define NUX_SC_FRAME_TABLE_INDEX_MASK	(NUX_SC_FRAME_TABLE_SIZE - 1)
#define NUX_GFX_TASK_NUM		(32)

/* Type prototype */
struct _NuxSched;

/* Type */
typedef struct _NuxScTaskList
{
    NUScTask	*head;
    NUScTask	*tail;
} NuxScTaskList;

typedef struct _NuxScFrame
{
    struct _NuxScFrame	*next;
    u32			id;
    NuxScTaskList	task_list;
    void		*user_data;
} NuxScFrame;

typedef struct _NuxScFrameQueue
{
    NuxScFrame	*head;
    NuxScFrame	*tail;
} NuxScFrameQueue;

typedef struct _NuxScRdpCtr
{
    u32	clock_count;
    u32	command_count;
    u32	pipe_count;
    u32	tmem_count;
} NuxScRdpCtr;

typedef struct _NuxScPerfWork
{
    u32		task_start;
    u32		audio_start;
    u32		rsp_done;
    u32		rdp_done;
    NuxScRdpCtr	counter;
    u16		valid_frame_table_size;
    u16		frame_table_cursor;
    u32		frame_table[ NUX_SC_FRAME_TABLE_SIZE ];
} NuxScPerfWork;

typedef struct _NuxScPerfInternal
{
    u64		rsp;
    u64		rdp;
    u64		audio;
    u32		frame_rate;
    NuxScRdpCtr	counter;
} NuxScPerfInternal;

typedef struct _NuxScPerf
{
    u32		rsp;
    u32		rdp;
    u32		audio;
    u32		clock;
    u32		command;
    u32		pipe;
    u32		tmem;
    u32		frame_rate;
} NuxScPerf;

typedef void *( *NuxScState )( struct _NuxSched *sched_ptr,
			       const u32 message_code );

typedef struct _NuxSched
{
    /* Message */
    NUScMsg		retraceMsg;
    NUScMsg		prenmiMsg;

    /* Definition of message queue */
    OSMesgQueue		taskMessageQueue;
    OSMesg		taskMessageBuffer[NUX_SC_MAX_MESGS];
    OSMesgQueue		replyMessageQueue;
    OSMesg		replyMessageBuffer[NU_SC_MAX_MESGS];

    /* Definition of thread */
    OSThread		schedulerThread;

    /* Client list  */
    NUScClient		*clientList;

    /* Internal status */
    u32			vsync_count;
    u32			retraceCount;
    u8			frameRate;
    u8			task_stop_count;
    u8			pre_nmi_count;
    u8			flags;

    /* Managing Frame/task */
    u32			frame_queue_size;
    NuxScFrameQueue	frame_queue;
    NUScTask		*task_ptr;
    NUScTask		*audio_ptr;

    /* Performance profile */
    NuxScPerfWork	perf_work;
    NuxScPerfInternal	perf;
    NuxScPerfInternal	perf_buffer;
} NuxSched;

typedef s32 ( *NuxScUnlockFrameFunc )( NuxScFrame *frame_ptr );
typedef s32 ( *NuxScLockFrameFunc )( NuxScFrame *frame_ptr );

extern NuxScFrame *nuxScNewFrame( void );
extern void nuxScFrameAddTask( NuxScFrame *frame_ptr, NUScTask *task_ptr );
extern int nuxScSendFrame( NuxScFrame *frame_ptr, const int wait,
						  const int size );
extern void nuxScFrameAllEndWait( void );
extern void nuxScGetPerf( NuxScPerf *perf_ptr );

extern NuxScFrame *nuxGfxCurrentFrame( void );
extern NuxScFrame *nuxGfxNewFrame( void );
extern void nuxGfxTaskStart( NuxScFrame *frame_ptr,
			     Gfx *gfxList_ptr, const u32 gfxListSize,
			     const u32 ucode, const u32 flag );
void nuxDebConDisp( u32 flag );
void nuxDebConDispEX2( u32 flag );
void nuxDebTaskPerfBar1EX2( NuxScPerf *perf_ptr, u32 frameNum, u32 y,
			    u32 flag );

extern volatile NuxScUnlockFrameFunc	nuxScUnlockFrame;
extern volatile NuxScLockFrameFunc	nuxScLockFrame;


#endif	/* _NUX_H */
