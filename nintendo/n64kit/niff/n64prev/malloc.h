/*======================================================================*/
/*		NIFFprev						*/
/*		malloc.h						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*									*/
/*======================================================================*/
#ifndef __MALLOC_H__
#define __MALLOC_H__

#ifndef _ULTRA64_H_
#include <ultra64.h>
#endif

/* ===========================================================================
	defines
 =========================================================================== */

/* The heap memory area of the user is 1M. */
#define MALLOC_SPACE (1024*1024/8)

/* OCTARY is the macro which converts the byte-length to the element number as 
   the 8-byte array.  It does not provide the 8-byte alignment.
   ex.) OCTARY(7) = 1;
	OCTARY(8) = 1;
	OCTARY(9) = 2;
*/
#define OCTARY(len) ((((len)-1)>>3)+1)

/* ===========================================================================
	type definisions
 =========================================================================== */
typedef enum {
    MHFLG_USED = 0x01,
    MHFLG_BEFOREUSED = 0x02
} MHFLAG;

/* MEMHEADER is fixed to 8-byte. */
typedef struct{
    u32 flag;
    u32 length;		/* The byte-length including MEMHEADER. */
} MEMHEADER;

/* MEMCTRL should be arranged on the 8-byte boundary. */
typedef struct{
    MEMHEADER *topadrs;
    MEMHEADER *endadrs;
    MEMHEADER *searchtop;
} MEMCTRL;

/* ===========================================================================
	public functions
 =========================================================================== */
void minit(void);
void *amalloc(int want, void *ap);
void afree( void *ptr, void *ap );
void *malloc(int want);
void free( void *ptr );
void *acreate(int want);
void adelete(void *ap);

#endif   /* #ifndef __MALLOC_H__ */
