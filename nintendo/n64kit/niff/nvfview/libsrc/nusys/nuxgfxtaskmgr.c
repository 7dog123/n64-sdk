/*
  nuxgfxtaskmgr.c
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 9, 1999.
    Graphic task scheduler for customized scheduler
*/

#include "nusys.h"
#include "nux.h"

static u32		nuGfxTask_index;
static NuxScFrame	*current_frame_ptr;

NUScTask	nuGfxTask[ NUX_GFX_TASK_NUM ];	/* Graphics task structure */
NUUcode*	nuGfxUcode;
volatile u32	nuGfxTaskSpool;			/* Number of task spools */
OSMesgQueue	nuGfxTaskMgrMesgQ;



u16**		nuGfxCfb = NULL;	/* Pointer to frame buffer	*/
u32		nuGfxCfbNum;	/* Number of frame buffer	*/
u16*		nuGfxCfb_ptr;	/* Frame buffers to be rendered	*/
u16*		nuGfxZBuffer;	/* Pointer to Z-buffer		*/
u32		nuGfxDisplay;	/* Screen display on/off	*/
u32		nuGfxCfbCounter;

NUGfxSwapCfbFunc nuGfxSwapCfbFunc = NULL; /* swapbuf callback function ptr */
NUGfxTaskEndFunc nuGfxTaskEndFunc = NULL; /* task end callback  ptr */

/*----------------------------------------------------------------------*/
/*	nuGfxTaskMgrInit - Initializes Task Manager			*/
/*	IN:	None							*/
/*									*/
/*	RET:	None							*/
/*----------------------------------------------------------------------*/
void nuGfxTaskMgrInit( void )
{
    u32	cnt;

    nuGfxTaskSpool = 0;
    nuGfxDisplayOff();		/* Disable screen display */

#if 0
    /* Launch graphic task manager thread */
    osCreateThread(&GfxTaskMgrThread, NU_GFX_TASKMGR_THREAD_ID, nuGfxTaskMgr,
		   (void*)NULL,
		   (GfxTaskMgrStack + NU_GFX_TASKMGR_STACK_SIZE/sizeof(u64)),
		   NU_GFX_TASKMGR_THREAD_PRI );
    osStartThread(&GfxTaskMgrThread);
#endif
    
    /* Initialize task structure	*/
    /* Define constants in advance	*/
    for(cnt = 0; cnt < NUX_GFX_TASK_NUM; cnt++){
	 nuGfxTask[cnt].next			= &nuGfxTask[cnt+1];
	 nuGfxTask[cnt].msgQ			= &nuGfxTaskMgrMesgQ;
	 nuGfxTask[cnt].list.t.type		= M_GFXTASK;
	 nuGfxTask[cnt].list.t.flags		= 0x00;
	 nuGfxTask[cnt].list.t.ucode_boot	= (u64*)rspbootTextStart;
	 nuGfxTask[cnt].list.t.ucode_boot_size 	= ((s32) rspbootTextEnd 
						    - (s32) rspbootTextStart);
	 nuGfxTask[cnt].list.t.ucode_size 	= SP_UCODE_SIZE;
	 nuGfxTask[cnt].list.t.ucode_data_size 	= SP_UCODE_DATA_SIZE;
	 nuGfxTask[cnt].list.t.dram_stack	= (u64*) nuDramStack;
	 nuGfxTask[cnt].list.t.dram_stack_size 	= SP_DRAM_STACK_SIZE8;
	 nuGfxTask[cnt].list.t.output_buff	= (u64 *)&nuRDPOutputBuf[0];
	 nuGfxTask[cnt].list.t.output_buff_size =
	     (u64 *)(nuRDPOutputBuf + NU_GFX_RDP_OUTPUTBUFF_SIZE);
	 nuGfxTask[cnt].list.t.yield_data_ptr	= (u64 *) nuYieldBuf;
	 nuGfxTask[cnt].list.t.yield_data_size	= OS_YIELD_DATA_SIZE;
	 nuGfxTask[cnt].msgQ			= &nuGfxTaskMgrMesgQ;	 
    }
    nuGfxTask_index	= 0;
    current_frame_ptr	= NULL;
}

/*--------------------------------------------------------------------*/
NuxScFrame *nuxGfxCurrentFrame( void )
{
    return current_frame_ptr;
}

/*--------------------------------------------------------------------*/
NuxScFrame *nuxGfxNewFrame( void )
{
    if ( current_frame_ptr )
    {
	nuxScSendFrame( current_frame_ptr, NUX_SC_WAIT, 0 );
    }

    nuGfxCfbCounter = ( nuGfxCfbCounter + 1 ) % nuGfxCfbNum;
    current_frame_ptr = nuxScNewFrame( );
    current_frame_ptr->id = nuGfxCfbCounter;
    nuGfxCfb_ptr = ( u16 * )nuGfxCfb[ nuGfxCfbCounter ];

    return current_frame_ptr;
}

/*----------------------------------------------------------------------*/
/*	nuxGfxTaskStart - Starts the graphics task			*/
/*									*/
/*	Sends the graphics task startup message to the Scheduler.	*/
/*	For flag, specify one of the following values according to the UCODE.*/
/*		NU_SC_NOSWAPBUFFER	Do not swap frame buffer after	*/
/*					the task ends.			*/
/*		NU_SC_SWAPBUFFER	Swap frame buffer after the task ends. */
/*					Specify this as the final task in the frame. */
/*					The Task Manager actually swaps the /*
/*		NU_SC_NORDP		Do not use the RDP, or do not wait*/
/*					for messages from the RDP.  Usually*/
/*					specified with RDP-only microcode. */
/*		NU_SC_UCODE_XBUS	Specify this with XBUS microcode */
/*		NU_SC_TASK_YIELDED	Equivalent to OS_TASK_YIELDED	*/
/*		NU_SC_TASK_DP_WAIT	Equivalent to OS_TASK_DP_WAIT	*/
/*		NU_SC_TASK_LODABLE	Equivalent to OS_TASK_LOADABLE	*/
/*					Specify when the self-loading	*/
/*					feature of UCODE is used. 	*/
/*		NU_SC_TASK_SP_ONLY	Equivalent to OS_TASK_SP_ONLY	*/
/*									*/
/*	IN:	gfxListptr	Pointer to the display list		*/
/*		gfxListSize 	Size of the display list		*/
/*		ucode		Microcode array number 			*/
/*		flag		Flag used when starting task		*/
/*	RET:	None							*/
/*----------------------------------------------------------------------*/
void nuxGfxTaskStart( NuxScFrame *frame_ptr,
		      Gfx *gfxList_ptr, const u32 gfxListSize,
		      const u32 ucode, const u32 flag )
{
    OSIntMask	mask;
    static u16	beforeFlag = 0;
    NUScTask	*nuGfxTask_ptr;

    nuGfxTask_ptr = &nuGfxTask[ nuGfxTask_index ];
	 
    nuGfxTask_ptr->list.t.data_ptr	= (u64*)gfxList_ptr;
    nuGfxTask_ptr->list.t.data_size	= gfxListSize;
    nuGfxTask_ptr->list.t.flags	= flag >> 16;
    nuGfxTask_ptr->list.t.ucode 	= nuGfxUcode[ucode].ucode;
    nuGfxTask_ptr->list.t.ucode_data	= nuGfxUcode[ucode].ucode_data;
    nuGfxTask_ptr->flags		= flag & 0x0000ffff;
#if 0
    nuGfxTask_ptr->framebuffer		= (u16*)nuGfxCfb_ptr;
#endif

    /* When the previously started microcode was XBUS microcode, */
    /* the OSTask structure flag must to set to OS_TASK_DP_WAIT,*/
    /* so this is checked here.  However, this is usually not	*/
    /* problematic because the function waits for the RDP to	*/
    /* finish as along as NU_SC_NORDP is not specified.		*/
    if(beforeFlag & NU_SC_UCODE_XBUS){
	nuGfxTask_ptr->list.t.flags |= OS_TASK_DP_WAIT;
	beforeFlag ^= NU_SC_UCODE_XBUS;	 
    }
    beforeFlag = flag;
     
    mask = osSetIntMask(OS_IM_NONE);
    osSetIntMask(mask);

    nuxScFrameAddTask( frame_ptr, nuGfxTask_ptr );

    /* Change the task buffer to the next pointer. */
    nuGfxTask_index = ( nuGfxTask_index + 1 ) % NUX_GFX_TASK_NUM;
}

/*-- NuSystem compatible interface--------------------------------------*/
/*	nuGfxTaskStart - Starts the graphics task			*/
/*									*/
/*	Sends the graphics task startup message to the Scheduler.	*/
/*	For flag, specify one of the following values according to the specified UCODE.	*/
/*		NU_SC_NOSWAPBUFFER	Do not swap frame buffer after the task ends.*/
/*		NU_SC_SWAPBUFFER	Swap frame buffer after the task ends. */
/*					Specify this as the final task in the frame. */
/*					The Task Manager actually swaps the */ 
/*					frame buffer. 			*/
/*		NU_SC_NORDP		Do not use the RDP, or do not wait*/
/*					for messages from the RDP.  Usually*/
/*					specified with RDP-only microcode. */
/*		NU_SC_UCODE_XBUS	Specify this with XBUS microcode */
/*		NU_SC_TASK_YIELDED	Equivalent to OS_TASK_YIELDED	*/
/*		NU_SC_TASK_DP_WAIT	Equivalent to OS_TASK_DP_WAIT	*/
/*		NU_SC_TASK_LODABLE	Equivalent to OS_TASK_LOADABLE	*/
/*					Specify when the self-loading	*/
/*					feature of UCODE is used. 	*/
/*		NU_SC_TASK_SP_ONLY	Equivalent to OS_TASK_SP_ONLY	*/
/*									*/
/*	IN:	gfxListptr	Pointer to the display list		*/
/*		gfxListSize 	Size of the display list		*/
/*		ucode		Microcode array number			*/
/*		flag		Flag used when starting task		*/
/*	RET:	None							*/
/*----------------------------------------------------------------------*/
void nuGfxTaskStart( Gfx *gfxList_ptr, u32 gfxListSize, u32 ucode, u32 flag )
{
    if ( !current_frame_ptr ) current_frame_ptr = nuxGfxNewFrame( );
    nuxGfxTaskStart( current_frame_ptr, gfxList_ptr, gfxListSize, ucode,
		     flag );
    if ( flag & NU_SC_SWAPBUFFER )
    {
	nuxScSendFrame( current_frame_ptr, NUX_SC_WAIT, 0 );
	current_frame_ptr = NULL;
    }
}
