
/*======================================================================*/
/*		NIFF to Gfx Converter					*/
/*		n64.h							*/
/*									*/
/*		Copyright (C) 1997,1998, NINTENDO Co,Ltd.		*/
/*									*/
/*----------------------------------------------------------------------*/ 
#ifndef __N64
#define __N64

/* ----------------------------------------------------------------------

	Extracted only those that are used internally from IRIX version /usr/include/PR/ultratypes.h, gbi.h.
	
	When the macro_WIN32 is defined, an environment in which a file with this program can be compiled in the Win32 environment of Microsoft(TM)Windows(TM) will be set.

 ---------------------------------------------------------------------- */
#ifndef _ULTRATYPES_H_	
#define _ULTRATYPES_H_	/*  Since OS2.0I-Patch3, the definition of 'ultratypes.h' is stated in 'gbi.h' file. The definition here avoids overlapping with it.
			   This is not ultratype.h'!! */
/**********************************************************************
 * General data types for R4300
 */
typedef unsigned char			u8;	/* unsigned  8-bit */
typedef unsigned short			u16;	/* unsigned 16-bit */
typedef unsigned long			u32;	/* unsigned 32-bit */
#ifdef _WIN32
typedef unsigned __int64		u64;	/* unsigned 64-bit */
#else
typedef unsigned long long		u64;	/* unsigned 64-bit */
#endif

typedef signed char			s8;	/* signed  8-bit */
typedef short				s16;	/* signed 16-bit */
typedef long				s32;	/* signed 32-bit */
#ifdef _WIN32
typedef __int64				s64;	/* signed 64-bit */
#else
typedef long long			s64;	/* signed 64-bit */
#endif

typedef volatile unsigned char		vu8;	/* unsigned  8-bit */
typedef volatile unsigned short		vu16;	/* unsigned 16-bit */
typedef volatile unsigned long		vu32;	/* unsigned 32-bit */
#ifdef _WIN32
typedef volatile unsigned __int64	vu64;	/* unsigned 64-bit */
#else
typedef volatile unsigned long long	vu64;	/* unsigned 64-bit */
#endif

typedef volatile signed char		vs8;	/* signed  8-bit */
typedef volatile short			vs16;	/* signed 16-bit */
typedef volatile long			vs32;	/* signed 32-bit */
#ifdef _WIN32
typedef volatile __int64		vs64;	/* signed 64-bit */
#else
typedef volatile long long		vs64;	/* signed 64-bit */
#endif

typedef float				f32;	/* single prec floating point*/
typedef double				f64;	/* double prec floating point*/
#endif	/* #ifndef _ULTRATYPES_H_ */

#endif   /* #ifndef __N64 */
