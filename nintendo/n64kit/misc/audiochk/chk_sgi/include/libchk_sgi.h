/*======================================================================*/
/*		NuSYS	Audio Library for SGI Library & naudio		*/
/*		libchk_sgi.h						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*	$Id: libchk_sgi.h,v 1.10 1999/01/14 05:45:36 ohki Exp ohki $	*/
/*======================================================================*/
#ifndef _LIBCHK_SGI_H_
#define _LIBCHK_SGI_H_
#ifndef N_AUDIO
#define N_AUDIO
#endif
#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif
/*----------------------------------------------------------------------*/    
/*----------------------------------------------------------------------*/
/*	DEFINE								*/
/*----------------------------------------------------------------------*/

/*--------------------------------------*/
/* SEQUENCE DEFINE			*/
/*--------------------------------------*/
#define NU_AU_SEQ_VOICE_MAX	24      /* Maximum number of voices */
#define NU_AU_SEQ_EVENT_MAX	48      /* Number of events */
#define NU_AU_SEQ_CHANNEL_MAX	16      /* Number of MIDI channels (normally 16) */
#define	NU_AU_SEQ_HEAP_SIZE	(16*NU_AU_CHANNEL_MAX+32*NU_AU_EVENT_MAX)	/* reference */
#define NU_AU_SEQ_PLAYER0	0
#define NU_AU_SEQ_PLAYER1	1
#define	NU_AU_SEQ_MODE_FADEOUT		0x0001
#define	NU_AU_SEQ_MODE_PLAYPENDING	0x0002


/*--------------------------------------*/
/* SOUND DEFINE				*/
/*--------------------------------------*/
#define NU_AU_SND_SOUND_MAX	8     /* Maximum number of sounds */  
#define NU_AU_SND_EVENT_MAX	(NU_AU_SND_SOUND_MAX*2)   /* Maximum number of events */
#define NU_AU_SND_HEAP_SIZE	(NU_AU_SND_SOUND_MAX*48+NU_AU_SND_EVENT*64)	/* reference */

/*--------------------------------------*/
/* SOUND DEFINE				*/
/*--------------------------------------*/
#define	NU_AU_BUFFER_MAX	0x1000 /* Size of buffer for synthesizer */	/* reference */
#define	NU_AU_HEAP_MIN_SIZE	(NU_AU_SND_HEAP_SIZE+NU_AU_SEQ_HEAP_SIZE+NU_AU_SYN_HEAP_SIZE+NU_AU_DMA_BUFFER_NUM*NU_AU_DMA_BUFFER_SIZE+NU_AU_CLIST_SIZE*2)	/* reference */
#define NU_AU_HEAP_SIZE		0x50000	/* Default heap size */
#define NU_AU_HEAP_ADDR		(NU_GFX_FRAMEBUFFER_ADDR - NU_AU_HEAP_SIZE)

#define	NU_AU_FRAMERATE_NTSC	60	/* NTSC/MPAL		*/	/* reference */
#define	NU_AU_FRAMERATE_PAL	50	/* PAL			*/	/* reference */
    
/* nuaumgr.h start */
#define	NU_AU_SYN_VVOICE_MAX	64	/* Maximum number of virtual voices (not used) */
#define NU_AU_SYN_PVOICE_MAX	32	/* Maximum number of physical voices */
#define NU_AU_SYN_UPDATE_MAX	128	/* Max. number of synthesizer parameter updates */
#define	NU_AU_SYN_HEAP_SIZE	(144+NU_AU_SYN_PVOICE_MAX*432+32*NU_AU_SYN_UPDATE_MAX+0x2000)	/* reference for you */

/*--------------------------------------*/
/* AUDIO DMA DEFINE			*/
/*--------------------------------------*/
#define	NU_AU_DMA_BUFFER_NUM	64	/* Number of DMA transfer buffers */
#define	NU_AU_DMA_BUFFER_SIZE	1024    /* DMA buffer size */
#define NU_AU_BUFFER_USE_FRAME  1	/* Frame interval for clearing DMABuffer */

/*--------------------------------------*/
/* SOUND DEFINE				*/
/*--------------------------------------*/
#define	NU_AU_MGR_THREAD_PRI	70
#define	NU_AU_MGR_THREAD_ID	6
#define NU_AU_STACK_SIZE	0x2000
#define	NU_AU_CLIST_LEN		0x800
#define	NU_AU_CLIST_SIZE	(NU_AU_CLIST_LEN*sizeof(Acmd))    /* Size of command list buffer */	/* reference for you */

#define	NU_AU_OUTPUT_RATE	32000   /* Frequency setting */
#define	NU_AU_MESG_MAX		8

#define	NU_AU_AUDIO_SAMPLES	184	/* Number of samples is a multiple of 184 */

#define NU_AU_AUDIO_EXTRASMP	0	/* Extension of number of samples */

#define NU_AU_TASK_STOP		0	/* Stop execution of audio task */
#define NU_AU_TASK_RUN		1	/* Enable execution of audio task */

#define NU_AU_AI_FIFO_MSG	0x100	/* AI event message */
#define NU_AU_AI_DEBUG_MSG	0x1000	/* For AI debugging */
    
/*--------------------------------------*/
/* DEBUG & PERFORMANCE			*/
/*--------------------------------------*/
#define	NU_AU_DEBUG_NORMAL	0x00000001	/* warning & error 	*/
#define	NU_AU_DEBUG_DISABLEDMA	0x00010000	/* disable dma callback	*/
#define	NU_AU_DEBUG_DISABLEAI	0x00020000	/* disable set AI	*/
#define	NU_AU_DEBUG_DISABLETASK	0x00040000	/* disable task		*/
#define	NU_AU_DEBUG_FIFOOFF	0x00080000	/* FIFO EVENT OFF	*/
#define	NU_AU_DEBUG_RETRACEOFF	0x00100000	/* RETRACE EVENT OFF	*/
    
#define NU_AU_DEBUG_NODMABUF	0x00000001	/* No DMA Buffer 	*/
#define NU_AU_DEBUG_ACMDBUFOVER 0x00000002	/* Acmd buffer is small */
#define NU_AU_DEBUG_DMABUFSIZE	0x00000004	/* dma buffer size is small */
#define	NU_AU_DEBUG_DMANOTCOMPLETE    0x00000008 /* dma not completed 	*/

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#include <ultra64.h>

#include <internal_n.h>
#include <internal_n_sn.h>

#include <nusys.h>

/*--------------------------------------*/
/* audio typedef			*/
/*--------------------------------------*/
/*--------------------------------------*/
/* DMA BUFFER STRUCT			*/
/*--------------------------------------*/
typedef struct {
    ALLink	node;		/* Link list pointer */
    s32		startAddr;	/* Address of data in ROM */
    s32		frameCnt;	/* Counter indicating the remaining number of frames for which the buffer is still effective */
    char*	ptr;		/* Value of pointer to buffer */
} NUDMABuffer;
/*-----------------------------------------*/
/*   The DMA status is used in the         */
/* sequence player's DMA callback routine. */
/*   This structure holds the usage state  */
/* of the DMA Buffer.                      */
/*-----------------------------------------*/
typedef struct {
    u8		initialized;  /* Flag indicating whether already initialized or not */
    NUDMABuffer* firstUsed;   /* Start of the used DMA Buffer link list */
    NUDMABuffer* firstFree;   /* Start of the free DMA Buffer link list */
} NUDMAState;


/*--------------------------------------*/
/* CALL BACK Function	typedef		*/
/*--------------------------------------*/
typedef void (*NUAuPreNMIFunc)(NUScMsg,u32);	/* PRENMI callback function */
typedef void (*NUAuMgrFunc)(void);		/* Acmd callback function */

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* extern variables 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/    
/*--------------------------------------*/
/*  audio variables 			*/
/*--------------------------------------*/

/* from nuaudma.c */
extern OSMesgQueue	nuAuDmaMesgQ;
extern OSMesg*		nuAuDmaMesgBuf;
extern OSIoMesg*	nuAuDmaIOMesgBuf;

extern NUDMAState	nuAuDmaState;
extern NUDMABuffer*	nuAuDmaBuf;
extern s16		nuAuDmaBufNum;
extern s16		nuAuDmaBufSize;
extern u32		nuAuDmaDisableFlag;	/* Does sample need to be DMA transferred ? */

/* from nuauheap.c */
extern ALHeap		nuAuHeap;		/* Heap structure */

/* from nuaumgrconfig.c */
extern ALSynConfig	nuAuSynConfig;

/* from nuaumgrparams.c */
extern u64*		nuAuMgrStack;
extern NUScTask		nuAuTask;		/* Audio task buffer */
extern s16*		nuAuBuffer_ptr[];	/* Audio buffer */
extern NUScClient	nuAuClient;
extern OSThread		nuAuMgrThread;
extern u32		nuAuFrameCounter;	/* Frame counter */
extern ALGlobals	nuAuGlobal;
extern NUAuPreNMIFunc	nuAuPreNMIFunc;
extern NUAuMgrFunc	nuAuMgrFunc;
extern OSMesgQueue	nuAuMesgQ;	/* Audio manager queue */
extern u32		nuAuAcmdLen;
extern s16		nuAuFrameSampleSize;	/* Number of samples created at once */
extern s16		nuAuExtraSampleSize;	/* Number of surplus samples */
extern u8		nuAuTaskStop;
extern u8		nuAuPreNMI;
extern u8		nuAuRetraceCount;

extern u32		nuAuDebFlag;
extern u32		nuAuDebStatus;		 /* Status flag */
extern u32		nuAuDebDmaCount;	 /* Total number of PI-DMAs */
extern u32		nuAuDebDmaFrame;	 /* Counter measuring number of DMAs */
extern u32		nuAuDebDmaMax;	         /* Maximum number of PI-DMAs */
extern u32		nuAuDebDmaBufMaxUse;     /* Maximum number of DMA buffers to use */
extern u32		nuAuDebDmaCallbackCount; /* Total number of DMA callbacks */
extern u32		nuAuDebDmaCallbackFrame; /* Number of DMA callbacks */
extern u32		nuAuDebDmaCallbackMax;   /* Maximum number of DMA callbacks */
extern u32		nuAuDebAcmdLenMax;	 /* Maximum value for audio command list */
extern u32		nuAuDebDmaLengthFrame;   /* Necessary sample length */
extern u32		nuAuDebDmaLengthMax;     /* Maximum necessary sample length */

/*----------------------------------------------------------------------*/    
/*----------------------------------------------------------------------*/
/* Global Function 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*--------------------------------------*/
/* audio manager function		*/
/*--------------------------------------*/
extern s32 nuAuMgrInit(void* heap_ptr, u32 size, ALSynConfig* synconfig);
extern s32 nuAuMgrInitEx(void* heap_ptr, u32 size, ALSynConfig* synConfig);

extern void nuAuPreNMIFuncSet(NUAuPreNMIFunc func);
extern void nuAuMgrFuncSet(NUAuMgrFunc func);
extern ALDMAproc nuAuDmaNew(NUDMAState **state);
extern void nuAuCleanDMABuffers(void);

extern void nuAuHeapInit(ALHeap* hp, u8* base, s32 len);
extern void* nuAuHeapAlloc(s32 length);
extern s32 nuAuHeapGetFree(void);
extern s32 nuAuHeapGetUsed(void);

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* MACRO	 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

/* Remove the callback function */
#define nuAuPreNMIFuncRemove()	nuAuPreNMIFuncSet(NULL)
#define nuAuMgrFuncRemove()	nuAuMgrFuncSet(NULL)

/*----------------------------------------------------------------------*/    
/* nuaumgr.h end */
    
/*--------------------------------------*/
/* audio typedef			*/
/*--------------------------------------*/
/* Sequence player structure */
typedef struct st_Seqence{
    ALCSPlayer	player;     	/* Sequence player structure */
    ALCSeq	sequence;
    u8*		data_ptr;       /* Sequence data */
    s32		seqno;          /* Sequence No. */
    u32		mode;		/* Control extension */
    u16		counter;
    u16		speed;
} NUAuSeqPlayer;

typedef struct st_SndState {
    ALSndId*	Id;
    u8		flag;
} NUAuSndId;

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* extern variables 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/    
/*--------------------------------------*/
/*  audio variables 			*/
/*--------------------------------------*/
extern NUAuSeqPlayer	nuAuSeqPlayer[];	
extern u8*		nuAuSeqData;	/* reference */
extern ALBankFile*	nuAuSeqBank_ptr;
extern ALSeqFile*	nuAuSeqFile_ptr;
extern ALSndPlayer	nuAuSndPlayer;
extern ALBankFile*	nuAuSndBank_ptr;
extern ALSndId*       	nuAuSndId;
extern ALSeqpConfig	nuAuSeqpConfig;
extern ALSndpConfig	nuAuSndpConfig;

/*----------------------------------------------------------------------*/    
/*----------------------------------------------------------------------*/
/* Global Function 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*--------------------------------------*/
/* audio manager function		*/
/*--------------------------------------*/
extern s32 nuAuInit(void);
extern s32 nuAuInitEx(void);

extern void nuAuSeqPlayerInit(ALSeqpConfig* seqpconfig, u32 size, u32 player_no);
extern void nuAuSeqPlayerBankSet(u8* bank_ptr, u32 bank_size, u8* table_ptr);
extern void nuAuSeqPlayerPlay(u32 player_no);
extern void nuAuSeqPlayerSeqSet(u8* seq_addr);
extern void nuAuSeqPlayerSetNo(u32 player_no ,u32 seq_no);
extern void nuAuSeqPlayerFadeOut(u32 player_no ,u32 speed);
extern void nuAuSeqPlayerControl(void);

extern void nuAuSndPlayerInit(ALSndpConfig* sndconfig);
extern void nuAuSndPlayerBankSet(u8* bank_addr, u32 bank_size, u8* table_addr);
extern ALSndId nuAuSndPlayerPlay(u32 sndNo);

extern void nuAuPreNMIProc(NUScMsg mesg_type, u32 frameCounter);

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* MACRO	 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

/* Remove callback functions */
#define nuAuSeqPlayerGetChlVol(player_no, chan)				\
	alCSPGetChlVol(&nuAuSeqPlayer[player_no].player, chan)
#define nuAuSeqPlayerGetChlFXMix(player_no, chan)			\
	alCSPGetChlFXMix(&nuAuSeqPlayer[player_no].player, chan)
#define nuAuSeqPlayerGetChlPan(player_no, chan)				\
	alCSPGetChlPan(&nuAuSeqPlayer[player_no].player, chan)
#define nuAuSeqPlayerGetChlPriority(player_no, chan)			\
	alCSPGetChlPriority(&nuAuSeqPlayer[player_no].player, chan)
#define nuAuSeqPlayerGetChlProgram(player_no, chan)			\
	alCSPGetChlProgram(&nuAuSeqPlayer[player_no].player, chan)
#define nuAuSeqPlayerGetSeq(player_no)				\
	alCSPGetSeq(&nuAuSeqPlayer[player_no].player)
#define nuAuSeqPlayerGetSeqno(player_no)				\
        nuAuSeqPlayer[player_no].seqno
#define nuAuSeqPlayerGetState(player_no)				\
	alCSPGetState(&nuAuSeqPlayer[player_no].player)
#define nuAuSeqPlayerGetTempo(player_no)				\
	alCSPGetTempo(&nuAuSeqPlayer[player_no].player)
#define nuAuSeqPlayerGetVol(player_no)					\
	alCSPGetVol(&nuAuSeqPlayer[player_no].player)
#define nuAuSeqPlayerStop(player_no)				\
	alCSPStop(&nuAuSeqPlayer[player_no].player)
#define nuAuSeqPlayerSetVol(player_no, vol)			\
	alCSPSetVol(&nuAuSeqPlayer[player_no].player, vol)
#define nuAuSeqPlayerSetTempo(player_no, tempo)			\
	alCSPSetTempo(&nuAuSeqPlayer[player_no].player, tempo)
#define nuAuSeqPlayerSetChlProgram(player_no, chan, prog)	\
	alCSPSetChlProgram(&nuAuSeqPlayer[player_no].player, chan, prog)
#define nuAuSeqPlayerSetChlPriority(player_no, chan, priority)	\
	alCSPSetChlPriority(&nuAuSeqPlayer[player_no].player, chan, priority)
#define nuAuSeqPlayerSetChlPan(player_no, chan, pan)	\
	alCSPSetChlPan(&nuAuSeqPlayer[player_no].player, chan, pan)
#define nuAuSeqPlayerSetChlFXMix(player_no, chan, fxmix)	\
	alCSPSetChlFXMix(&nuAuSeqPlayer[player_no].player, chan, fxmix)
#define nuAuSeqPlayerSetChlVol(player_no, chan, vol)	\
	alCSPSetChlVol(&nuAuSeqPlayer[player_no].player, chan, vol)
#define nuAuSeqPlayerSendMidi(player_no, ticks, status, byte1, byte2)	\
	alCSPSetPlayerSendMidi(&nuAuSeqPlayer[player_no].player, ticks, status, byte1, byte2)

#define nuAuSndPlayerGetState()		alSndpGetState(&nuAuSndPlayer)
#define nuAuSndPlayerPlayAt(delta)	alSndpPlayAt(&nuAuSndPlayer,delta)
#define nuAuSndPlayerSetFXMix(mix)	alSndpSetFXMix(&nuAuSndPlayer,mix)
#define nuAuSndPlayerSetPan(pan)	alSndpSetPan(&nuAuSndPlayer,pan)
#define nuAuSndPlayerSetPitch(pitch)	alSndpSetPitch(&nuAuSndPlayer,pitch)
#define nuAuSndPlayerSetPriority(id,priority)	alSndpSetPriority(&nuAuSndPlayer,id,priority)
#define nuAuSndPlayerSetVol(vol)	alSndpSetVol(&nuAuSndPlayer,vol)
#define nuAuSndPlayerStop()	alSndpStop(&nuAuSndPlayer)
#define nuAuSndPlayerSetSound(SndId)	alSndpSetSound(&nuAuSndPlayer,SndId)


/*----------------------------------------------------------------------*/    
#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
#endif /* _LIBCHK_SGI_H_ */
