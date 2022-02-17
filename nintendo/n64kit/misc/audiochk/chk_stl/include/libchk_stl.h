/*======================================================================*/
/*		NuSystem						*/
/*		libchk_stl.h						*/
/*									*/
/*		Copyright (C) 1999, NINTENDO Co,Ltd.			*/
/*									*/
/*======================================================================*/

#ifndef _LIBCHK_STL_H_
#define _LIBCHK_STL_H_
#ifndef N_AUDIO
#define N_AUDIO
#endif

/*--------------------------------------*/
/* SYNTHESIZER AND PLAYER DEFINES	*/
/*--------------------------------------*/
#define NU_AU_STL_CHANNELS	24
#define NU_AU_STL_UPDATE_MAX	256
#define NU_AU_STL_FIFO_LENGTH	64
#define NU_AU_STL_CLIST_LEN	0x800
#define NU_AU_STL_OUTPUT_RATE	32000

/*--------------------------------------*/
/* AUDIO DMA DEFINE			*/
/*--------------------------------------*/
#define	NU_AU_STL_DMA_BUFFER_NUM	64	/* Number of DMA transfer buffers 	*/
#define	NU_AU_STL_DMA_BUFFER_SIZE	1024    /* DMA buffer size */

/*--------------------------------------*/
/* AUDIO HEAP DEFINE			*/
/*--------------------------------------*/
#define NU_AU_STL_HEAP_SIZE	0x50000	/* Default heap size */
#define NU_AU_STL_HEAP_ADDR	(NU_GFX_FRAMEBUFFER_ADDR - NU_AU_STL_HEAP_SIZE)

/*--------------------------------------*/
/* USERS DATA DEFINE			*/
/*--------------------------------------*/
#define NU_AU_STL_SONG_SIZE	0x4000
#define NU_AU_STL_SAMPLE_SIZE	0x4000
#define NU_AU_STL_SE_SIZE	0x4000

/*--------------------------------------*/
/* SYNTHE DEFINE			*/
/*--------------------------------------*/
#define	NU_AU_SYN_VVOICE_MAX	64	/* Maximum number of virtual voices (not used)  */
#define NU_AU_SYN_PVOICE_MAX	32	/* Maximum number of physical voices */
#define NU_AU_SYN_UPDATE_MAX	128	/* Max. number of synthesizer parameter updates  */
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

#ifdef N_AUDIO
#define	NU_AU_AUDIO_SAMPLES	184	/* Number of samples is a multiple of 184 */
#else
#define	NU_AU_AUDIO_SAMPLES	16	/* Number of samples is a multiple of 16 */
#endif	/* N_AUDIO */

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
#include <internal_sc.h>
#include <internal_sc_sn.h>
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
/*   The DMA status used in the         */
/* sequence player's DMA callback routine. */
/*   This structure holds the usage state  */
/* of the DMA Buffer.                      */
/*--------------------------------------*/
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
extern u32		nuAuDmaDisableFlag;	/* Does sample need to be DMA transferred? */

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
extern s16		nuAuExtraSampleSize;	/* Number of extra samples */
extern u8		nuAuTaskStop;
extern u8		nuAuPreNMI;
extern u8		nuAuRetraceCount;

extern u32		nuAuDebFlag;
extern u32		nuAuDebStatus;		/* Status flag */
extern u32		nuAuDebDmaCount;	/* Total number of PI-DMAs */
extern u32		nuAuDebDmaFrame;	/* Counter measuring number of DMAs */
extern u32		nuAuDebDmaMax;	/* Maximum number of PI-DMAs */
extern u32		nuAuDebDmaBufMaxUse; /* Maximum number of DMA buffers to use */
extern u32		nuAuDebDmaCallbackCount; /* Total number of DMA callbacks */
extern u32		nuAuDebDmaCallbackFrame; /* Number of DMA callbacks */
extern u32		nuAuDebDmaCallbackMax; /* Maximum number of DMA callbacks */
extern u32		nuAuDebAcmdLenMax;	/* Maximum value for audio command list */
extern u32		nuAuDebDmaLengthFrame; /* Necessary sample length */
extern u32		nuAuDebDmaLengthMax; /* Maximum necessary sample length */

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
#include <sched.h>

/* --------- MUSIC PLAYER API TYPEDEFS --------- */

/* audio manager and synthesizer initialize function */
typedef void	*(*LIBMUSinit_audio)	(void *);

/* configuration */
typedef struct 
{
    u32		control_flag;

    u32 	channels;
//    void	*sched;
    u32		thread_priority;
    u8		*heap;
    u32		heap_length;
    void	*audio_heap;

    u8		*ptr;
    u8		*wbk;

    void	*default_fxbank;

    u32		fifo_length;

    u32		fxtype;

    LIBMUSinit_audio syn_init_func;
    u32		syn_updates;
    u32		syn_output_rate;
    u32		syn_rsp_cmds;
    u32		syn_retraceCount;
    u32		syn_num_dma_bufs;
    u32		syn_dma_buf_size;

// Special Addition
//    OSPiHandle	*diskrom_handle;
} musConfig;

/* enabled/disable flag */
typedef enum
{
    MUSBOOL_OFF,
    MUSBOOL_ON
} musBool;

/* task descriptor */
typedef struct
{
    u64		*data;		/* address of Acmd list		*/
    s32		data_size;	/* size of Acmd list		*/
    u64		*ucode;		/* address of microcode code	*/
    u64		*ucode_data;	/* address of microcode data	*/
} musTask;

/* handle type */
typedef u32	musHandle;

/* marker callback function */
typedef void	(*LIBMUScb_marker)	(musHandle, s32);

/* scheduler support callback functions */
typedef void	(*LIBMUScb_install)	(void);
typedef OSScMsg	*(*LIBMUScb_waitframe)	(void); // yutaka
typedef void 	(*LIBMUScb_dotask)	(musTask *);

/* scheduler support callback list */
typedef struct
{
    LIBMUScb_install	install;	/* called when thread starts	*/
    LIBMUScb_waitframe	waitframe;	/* called to wait for vsync message */
    LIBMUScb_dotask	dotask;		/* called to process RSP task	*/
} musSched;


/* --------- MUSIC PLAYER API MACROS --------- */

/* control flags */
#define MUSCONTROL_RAM	(1<<0)

/* channel types flags */
#define MUSFLAG_EFFECTS	1
#define MUSFLAG_SONGS	2


/* --------- MUSIC PLAYER GLOBAL VALUES --------- */
extern s32 mus_random_seed;

/* scheduler support, if you use the library supported traditional audio manager */
extern OSSched mus_sched;

/* --------- MUSIC PLAYER API FUNCTION PROTOTYPES --------- */

/* initialise */
extern s32 MusPlayerInitialize		(musConfig *config);

/* audio configuration */
extern s32 MusSetFxType			(s32 fxtype);
extern s32 MusSetSongFxChange		(musBool onoff);

/* set master volume levels */
extern void MusSetMasterVolume		(u32 flags, s32 volume);

/* start songs and sound effects */
extern musHandle MusStartSong		(void *addr);
extern musHandle MusStartSongFromMarker	(void *addr, s32 marker);
extern musHandle MusStartEffect		(s32 number);
extern musHandle MusStartEffect2	(s32 number, s32 volume, s32 pan , s32 restartflag, s32 priority);

/* stop and query sound types */
extern void MusStop			(u32 flags, s32 speed);
extern s32  MusAsk			(u32 flags);

/* handle based processing */
extern s32 MusHandleAsk			(musHandle handle);
extern s32 MusHandleStop		(musHandle handle, s32 speed);
extern s32 MusHandleSetVolume		(musHandle handle, s32 volume);
extern s32 MusHandleSetPan		(musHandle handle, s32 pan);
extern s32 MusHandleSetFreqOffset	(musHandle handle, f32 offset);
extern s32 MusHandleSetTempo		(musHandle handle, s32 tempo);
extern s32 MusHandleSetReverb		(musHandle handle, s32 reverb);
extern s32 MusHandlePause		(musHandle handle);
extern s32 MusHandleUnPause		(musHandle handle);
extern void *MusHandleGetPtrBank	(musHandle handle);

/* sample bank support */
extern void MusPtrBankInitialize	(void *pbank, void *wbank);
extern void *MusPtrBankSetSingle	(void *ipbank);
extern void MusPtrBankSetCurrent	(void *ipbank);
extern void *MusPtrBankGetCurrent	(void);

/* sound effect bank support */
extern void MusFxBankInitialize		(void *fxbank);
extern void MusFxBankSetSingle		(void *ifxbank);
extern void MusFxBankSetCurrent		(void *ifxbank);
extern void *MusFxBankGetCurrent	(void);
extern s32  MusFxBankNumberOfEffects	(void *ifxbank);
extern void MusFxBankSetPtrBank		(void *ifxbank, void *ipbank);
extern void *MusFxBankGetPtrBank	(void *ifxbank);
extern void MusFxBankSetSingle		(void *ifxbank);

/* marker callback support */
extern void MusSetMarkerCallback	(void *callback);

/* wave list lookup in song header */
extern u32 MusHandleWaveCount		(musHandle handle);
extern u16 *MusHandleWaveAddress	(musHandle handle);

/* scheduler support, if you use the library supported traditional audio manager */
extern void MusSetScheduler		(musSched *sched_list);

/* intialization fuction, if you use the library supported traditional audio manager */
extern s32  *MusIntialize			(musConfig *);
extern void *MusAudioManagerInitialize		(void *);

/* macros to support previous sample bank functions - use is not recommended! */
#define MusBankInitialize(pbank,wbank)	\
	MusPtrBankInitialize(pbank,wbank)

#define MusBankStartSong(ipbank, addr)	\
	MusStartSong((addr)==(void *)MusPtrBankSetSingle(ipbank) ? (addr):(addr))

#define MusBankStartEffect(ipbank, number) \
	MusStartEffect((number)==(s32)MusPtrBankSetSingle(ipbank) ? (number):(number))

#define MusBankStartEffect2(ipbank, number, volume, pan, restartflag, priority) \
	MusStartEffect2((number)==(s32)MusPtrBankSetSingle(ipbank) ? (number):(number), \
			volume, pan, restartflag, priority)



/* --- DEVELOPEMENT API FUNCTION PROTOTYPES --- */

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* extern variables 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*--------------------------------------*/
/*  audio variables 			*/
/*--------------------------------------*/
extern musConfig nuAuStlConfig;

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* Global Function 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
extern void *nuAuStlMgrInit(void *config);
extern void *nuAuStlMgrInitEx(void *config);

extern void nuAuStlPreNMIProc(NUScMsg mesg_type, u32 frameCounter);

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/* MACRO	 							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
#define nuAuPreNMIProc(mesg_type, frameCounter) \
    nuAuStlPreNMIProc(mesg_type, frameCounter)

/*----------------------------------------------------------------------*/    
#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
#endif /* _LIBCHK_STL_H__ */
