/*
 * [CCBL]
 *
 * mysys.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _MYSYS_H_
#define _MYSYS_H_
/*
 * mysys.h
 * This file also called from spec. 
 */

#define APPNAME "ccbl"

#define MDL_SEGMENT 4
#define VTX_SEGMENT 5
#define TEX_SEGMENT 6

#define MODEL_LOAD_ADDR 0x80200000

#ifdef _LANGUAGE_C
#include <assert.h>

/* system.c */
typedef struct {int *argc;char **argv;} APPARG;
#define MAX_ARGUMENT 32

APPARG *arg_make(char *);

/* system.c */ 

/* boot.c */
extern int debug;
extern OSPiHandle *pih;

/* heap.c */
#define HEAP_LENGTH 0x40000

/*
 *  DEBUG print macros
 */
#ifdef	DEBUG
#ifdef ISVIEWER
#define	osSyncPrintf	isPrintf
#else
#define	osSyncPrintf	osSyncPrintf
#endif
#else
#define	osSyncPrintf	if (0) osSyncPrintf
#endif

#endif	/* _LANGUAGE_C */
#endif /* !_MYSYS_H_ */

