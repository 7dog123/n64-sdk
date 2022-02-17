/*
 * [CCBL]
 *
 * boot.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include <string.h>
#include "mysys.h"

static OSThread	IdleThread;		/* Idle thread */
static OSThread	MainThread;		/* Main thread */

OSPiHandle *pih;

/************************************************************************/
/* The boot thread stack can be reused after the initial thread is started,	*/
/* so it is reused for the main thread.  by Nintendo  */
/************************************************************************/
u64 nuMainStack[NU_MAIN_STACK_SIZE/8]; /* boot/main thread stack */
static u64 IdleStack[NU_IDLE_STACK_SIZE/8]; /* Idle thread stack */
/************************************************************************/

void (*nuIdleFunc)(void);		/* Idle loop callback function */
					   
/*--------------------------------------*/
/* Static Function			*/
/*--------------------------------------*/
static void idle(void *arg);		/* idle function */

/*--------------------------------------*/
/* Extern Function			*/
/*--------------------------------------*/
extern void mainproc(void *);		/* game main function */

/*----------------------------------------------------------------------*/
/*	NuSYS initialization and startup.		   */
/*	IN:	pointer to main function 		   */
/*	RET:	nothing				   */
/*----------------------------------------------------------------------*/
void myBoot(void)
{
  osInitialize();	/* Initialize N64 OS. */
  pih = osCartRomInit();

  /* Generate and execute Idle thread. */
  osCreateThread(&IdleThread,NU_IDLE_THREAD_ID, idle,(void *)NULL,
		 (IdleStack + NU_IDLE_STACK_SIZE/8), 10);

  osStartThread(&IdleThread);

}


/* IDLE THREAD */
static void idle(void *arg)
{
  /* Initialize CALLBACK function. */
  nuIdleFunc = NULL;

  nuPiInit();

  /* Start scheduler.						 */
  /* VI setting is NTSC/ANTIALIASING/NON-INTERLACE/16bitPixel.	*/
  /* It can be changed using osViSetMode.			*/
  nuScCreateScheduler(OS_VI_NTSC_LAN1, 1);

    
  /* Set VI interface					*/
  /*    Specify OS_VI_DITHER_FILTER_ON.			*/
  /*    Use DITHER filtering (default setting is OFF).		*/
  /* Settings here are changed by ccbl settings. */
  osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON
			 | OS_VI_GAMMA_ON
			 | OS_VI_GAMMA_DITHER_OFF
			 | OS_VI_DIVOT_OFF);

  /* Create main thread for application. */
  osCreateThread(&MainThread, NU_MAIN_THREAD_ID, mainproc,(void *)NULL,
		 (nuMainStack + NU_MAIN_STACK_SIZE/8), NU_MAIN_THREAD_PRI);

  osStartThread(&MainThread);

    /* Decrease priority of IDLE thread and move processing to main thread. */
  osSetThreadPri(&IdleThread, NU_IDLE_THREAD_PRI);

  /* Idle loop */
  while(1){
    if(nuIdleFunc != NULL){
      /* Execute Idle function. */
      (*nuIdleFunc)();
    }
  }
}


