/*
  mvm/Matrix.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 11, 1998.
*/

#ifndef _mvm_Matrix_h
#define _mvm_Matrix_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare types of a structure */
typedef float MvmMatrix22f[ 2 ][ 2 ];
typedef float MvmMatrix33f[ 3 ][ 3 ];
typedef float MvmMatrix44f[ 4 ][ 4 ];

/* Declare Functions */
extern void mvmMatrix22fSetIdentity( MvmMatrix22f dest );
extern void mvmMatrix33fSetIdentity( MvmMatrix33f dest );
extern void mvmMatrix44fSetIdentity( MvmMatrix44f dest );

extern void mvmMatrix22fCopy( MvmMatrix22f dest, const MvmMatrix22f src );
extern void mvmMatrix33fCopy( MvmMatrix33f dest, const MvmMatrix33f src );
extern void mvmMatrix44fCopy( MvmMatrix44f dest, const MvmMatrix44f src );

extern void mvmMatrix22fAdd( MvmMatrix22f dest, const MvmMatrix22f a,
						const MvmMatrix22f b );
extern void mvmMatrix33fAdd( MvmMatrix33f dest, const MvmMatrix33f a,
						const MvmMatrix33f b );
extern void mvmMatrix44fAdd( MvmMatrix44f dest, const MvmMatrix44f a,
						const MvmMatrix44f b );

extern void mvmMatrix22fSub( MvmMatrix22f dest, const MvmMatrix22f a,
						const MvmMatrix22f b );
extern void mvmMatrix33fSub( MvmMatrix33f dest, const MvmMatrix33f a,
						const MvmMatrix33f b );
extern void mvmMatrix44fSub( MvmMatrix44f dest, const MvmMatrix44f a,
						const MvmMatrix44f b );

extern void mvmMatrix22fProduct( MvmMatrix22f dest, const MvmMatrix22f a,
						    const MvmMatrix22f b );
extern void mvmMatrix33fProduct( MvmMatrix33f dest, const MvmMatrix33f a,
						    const MvmMatrix33f b );
extern void mvmMatrix44fProduct( MvmMatrix44f dest, const MvmMatrix44f a,
						    const MvmMatrix44f b );

extern void mvmMatrix22fScale( MvmMatrix22f dest, const float scale[ 2 ],
						  const MvmMatrix22f matrix );
extern void mvmMatrix33fScale( MvmMatrix33f dest, const float scale[ 3 ],
						  const MvmMatrix33f matrix );
extern void mvmMatrix44fScale( MvmMatrix44f dest, const float scale[ 4 ],
						  const MvmMatrix44f matrix );

extern void mvmMatrix33fRotateX( MvmMatrix33f dest, const float angle,
						const MvmMatrix33f matrix );
extern void mvmMatrix33fRotateY( MvmMatrix33f dest, const float angle,
						const MvmMatrix33f matrix );
extern void mvmMatrix33fRotateZ( MvmMatrix33f dest, const float angle,
						const MvmMatrix33f matrix );

extern void mvmMatrix33fRotationX( MvmMatrix33f dest, const float angle );
extern void mvmMatrix33fRotationY( MvmMatrix33f dest, const float angle );
extern void mvmMatrix33fRotationZ( MvmMatrix33f dest, const float angle );

extern void mvmMatrix33fRotation( MvmMatrix33f dest, const float angle,
						     const float axis[ 3 ] );

extern void mvmMatrix33fOrientation( MvmMatrix33f dest, const float ex[ 3 ],
							const float ey[ 3 ] );

/* Declare macro */
/* These macros have side effects */
#define _mvmMatrix22fSetIdentity(dest) \
{ \
    (dest)[ 0 ][ 0 ] = 1.0f; \
    (dest)[ 0 ][ 1 ] = 0.0f; \
    (dest)[ 1 ][ 0 ] = 0.0f; \
    (dest)[ 1 ][ 1 ] = 1.0f; \
}

#define _mvmMatrix33fSetIdentity(dest) \
{ \
    (dest)[ 0 ][ 0 ] = 1.0f; \
    (dest)[ 0 ][ 1 ] = 0.0f; \
    (dest)[ 0 ][ 2 ] = 0.0f; \
    (dest)[ 1 ][ 0 ] = 0.0f; \
    (dest)[ 1 ][ 1 ] = 1.0f; \
    (dest)[ 1 ][ 2 ] = 0.0f; \
    (dest)[ 2 ][ 0 ] = 0.0f; \
    (dest)[ 2 ][ 1 ] = 0.0f; \
    (dest)[ 2 ][ 2 ] = 1.0f; \
}

#define _mvmMatrix44fSetIdentity(dest) \
{ \
    (dest)[ 0 ][ 0 ] = 1.0f; \
    (dest)[ 0 ][ 1 ] = 0.0f; \
    (dest)[ 0 ][ 2 ] = 0.0f; \
    (dest)[ 0 ][ 3 ] = 0.0f; \
    (dest)[ 1 ][ 0 ] = 0.0f; \
    (dest)[ 1 ][ 1 ] = 1.0f; \
    (dest)[ 1 ][ 2 ] = 0.0f; \
    (dest)[ 1 ][ 3 ] = 0.0f; \
    (dest)[ 2 ][ 0 ] = 0.0f; \
    (dest)[ 2 ][ 1 ] = 0.0f; \
    (dest)[ 2 ][ 2 ] = 1.0f; \
    (dest)[ 2 ][ 3 ] = 0.0f; \
    (dest)[ 3 ][ 0 ] = 0.0f; \
    (dest)[ 3 ][ 1 ] = 0.0f; \
    (dest)[ 3 ][ 2 ] = 0.0f; \
    (dest)[ 3 ][ 3 ] = 1.0f; \
}

#define _mvmMatrix22fCopy(dest,src) \
{ \
    (dest)[ 0 ][ 0 ] = (src)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (src)[ 0 ][ 1 ]; \
    (dest)[ 1 ][ 0 ] = (src)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (src)[ 1 ][ 1 ]; \
}

#define _mvmMatrix33fCopy(dest,src) \
{ \
    (dest)[ 0 ][ 0 ] = (src)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (src)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (src)[ 0 ][ 2 ]; \
    (dest)[ 1 ][ 0 ] = (src)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (src)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (src)[ 1 ][ 2 ]; \
    (dest)[ 2 ][ 0 ] = (src)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (src)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (src)[ 2 ][ 2 ]; \
}

#define _mvmMatrix44fCopy(dest,src) \
{ \
    (dest)[ 0 ][ 0 ] = (src)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (src)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (src)[ 0 ][ 2 ]; \
    (dest)[ 0 ][ 3 ] = (src)[ 0 ][ 3 ]; \
    (dest)[ 1 ][ 0 ] = (src)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (src)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (src)[ 1 ][ 2 ]; \
    (dest)[ 1 ][ 3 ] = (src)[ 1 ][ 3 ]; \
    (dest)[ 2 ][ 0 ] = (src)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (src)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (src)[ 2 ][ 2 ]; \
    (dest)[ 2 ][ 3 ] = (src)[ 2 ][ 3 ]; \
    (dest)[ 3 ][ 0 ] = (src)[ 3 ][ 0 ]; \
    (dest)[ 3 ][ 1 ] = (src)[ 3 ][ 1 ]; \
    (dest)[ 3 ][ 2 ] = (src)[ 3 ][ 2 ]; \
    (dest)[ 3 ][ 3 ] = (src)[ 3 ][ 3 ]; \
}

#define _mvmMatrix22fAdd(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] + (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] + (b)[ 0 ][ 1 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] + (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] + (b)[ 1 ][ 1 ]; \
}

#define _mvmMatrix33fAdd(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] + (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] + (b)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (a)[ 0 ][ 2 ] + (b)[ 0 ][ 2 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] + (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] + (b)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (a)[ 1 ][ 2 ] + (b)[ 1 ][ 2 ]; \
    (dest)[ 2 ][ 0 ] = (a)[ 2 ][ 0 ] + (b)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (a)[ 2 ][ 1 ] + (b)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (a)[ 2 ][ 2 ] + (b)[ 2 ][ 2 ]; \
}

#define _mvmMatrix44fAdd(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] + (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] + (b)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (a)[ 0 ][ 2 ] + (b)[ 0 ][ 2 ]; \
    (dest)[ 0 ][ 3 ] = (a)[ 0 ][ 3 ] + (b)[ 0 ][ 3 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] + (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] + (b)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (a)[ 1 ][ 2 ] + (b)[ 1 ][ 2 ]; \
    (dest)[ 1 ][ 3 ] = (a)[ 1 ][ 3 ] + (b)[ 1 ][ 3 ]; \
    (dest)[ 2 ][ 0 ] = (a)[ 2 ][ 0 ] + (b)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (a)[ 2 ][ 1 ] + (b)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (a)[ 2 ][ 2 ] + (b)[ 2 ][ 2 ]; \
    (dest)[ 2 ][ 3 ] = (a)[ 2 ][ 3 ] + (b)[ 2 ][ 3 ]; \
    (dest)[ 3 ][ 0 ] = (a)[ 3 ][ 0 ] + (b)[ 3 ][ 0 ]; \
    (dest)[ 3 ][ 1 ] = (a)[ 3 ][ 1 ] + (b)[ 3 ][ 1 ]; \
    (dest)[ 3 ][ 2 ] = (a)[ 3 ][ 2 ] + (b)[ 3 ][ 2 ]; \
    (dest)[ 3 ][ 3 ] = (a)[ 3 ][ 3 ] + (b)[ 3 ][ 3 ]; \
}

#define _mvmMatrix22fSub(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] - (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] - (b)[ 0 ][ 1 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] - (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] - (b)[ 1 ][ 1 ]; \
}

#define _mvmMatrix33fSub(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] - (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] - (b)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (a)[ 0 ][ 2 ] - (b)[ 0 ][ 2 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] - (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] - (b)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (a)[ 1 ][ 2 ] - (b)[ 1 ][ 2 ]; \
    (dest)[ 2 ][ 0 ] = (a)[ 2 ][ 0 ] - (b)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (a)[ 2 ][ 1 ] - (b)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (a)[ 2 ][ 2 ] - (b)[ 2 ][ 2 ]; \
}

#define _mvmMatrix44fSub(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = (a)[ 0 ][ 0 ] - (b)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (a)[ 0 ][ 1 ] - (b)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (a)[ 0 ][ 2 ] - (b)[ 0 ][ 2 ]; \
    (dest)[ 0 ][ 3 ] = (a)[ 0 ][ 3 ] - (b)[ 0 ][ 3 ]; \
    (dest)[ 1 ][ 0 ] = (a)[ 1 ][ 0 ] - (b)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (a)[ 1 ][ 1 ] - (b)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (a)[ 1 ][ 2 ] - (b)[ 1 ][ 2 ]; \
    (dest)[ 1 ][ 3 ] = (a)[ 1 ][ 3 ] - (b)[ 1 ][ 3 ]; \
    (dest)[ 2 ][ 0 ] = (a)[ 2 ][ 0 ] - (b)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (a)[ 2 ][ 1 ] - (b)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (a)[ 2 ][ 2 ] - (b)[ 2 ][ 2 ]; \
    (dest)[ 2 ][ 3 ] = (a)[ 2 ][ 3 ] - (b)[ 2 ][ 3 ]; \
    (dest)[ 3 ][ 0 ] = (a)[ 3 ][ 0 ] - (b)[ 3 ][ 0 ]; \
    (dest)[ 3 ][ 1 ] = (a)[ 3 ][ 1 ] - (b)[ 3 ][ 1 ]; \
    (dest)[ 3 ][ 2 ] = (a)[ 3 ][ 2 ] - (b)[ 3 ][ 2 ]; \
    (dest)[ 3 ][ 3 ] = (a)[ 3 ][ 3 ] - (b)[ 3 ][ 3 ]; \
}

#define __mvmMatrix22fRowColumnProduct(a,row,b,col) \
	( (a)[ (row) ][ 0 ] * (b)[ 0 ][ (col) ] + \
	  (a)[ (row) ][ 1 ] * (b)[ 1 ][ (col) ] )

#define _mvmMatrix22fProduct(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = __mvmMatrix22fRowColumnProduct( (a), 0, (b), 0 ); \
    (dest)[ 0 ][ 1 ] = __mvmMatrix22fRowColumnProduct( (a), 0, (b), 1 ); \
    (dest)[ 1 ][ 0 ] = __mvmMatrix22fRowColumnProduct( (a), 1, (b), 0 ); \
    (dest)[ 1 ][ 1 ] = __mvmMatrix22fRowColumnProduct( (a), 1, (b), 1 ); \
}

#define __mvmMatrix33fRowColumnProduct(a,row,b,col) \
	( (a)[ (row) ][ 0 ] * (b)[ 0 ][ (col) ] + \
	  (a)[ (row) ][ 1 ] * (b)[ 1 ][ (col) ] + \
	  (a)[ (row) ][ 2 ] * (b)[ 2 ][ (col) ] )

#define _mvmMatrix33fProduct(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = __mvmMatrix33fRowColumnProduct( (a), 0, (b), 0 ); \
    (dest)[ 0 ][ 1 ] = __mvmMatrix33fRowColumnProduct( (a), 0, (b), 1 ); \
    (dest)[ 0 ][ 2 ] = __mvmMatrix33fRowColumnProduct( (a), 0, (b), 2 ); \
    (dest)[ 1 ][ 0 ] = __mvmMatrix33fRowColumnProduct( (a), 1, (b), 0 ); \
    (dest)[ 1 ][ 1 ] = __mvmMatrix33fRowColumnProduct( (a), 1, (b), 1 ); \
    (dest)[ 1 ][ 2 ] = __mvmMatrix33fRowColumnProduct( (a), 1, (b), 2 ); \
    (dest)[ 2 ][ 0 ] = __mvmMatrix33fRowColumnProduct( (a), 2, (b), 0 ); \
    (dest)[ 2 ][ 1 ] = __mvmMatrix33fRowColumnProduct( (a), 2, (b), 1 ); \
    (dest)[ 2 ][ 2 ] = __mvmMatrix33fRowColumnProduct( (a), 2, (b), 2 ); \
}

#define __mvmMatrix44fRowColumnProduct(a,row,b,col) \
	( (a)[ (row) ][ 0 ] * (b)[ 0 ][ (col) ] + \
	  (a)[ (row) ][ 1 ] * (b)[ 1 ][ (col) ] + \
	  (a)[ (row) ][ 2 ] * (b)[ 2 ][ (col) ] + \
	  (a)[ (row) ][ 3 ] * (b)[ 3 ][ (col) ] )

#define _mvmMatrix44fProduct(dest,a,b) \
{ \
    (dest)[ 0 ][ 0 ] = __mvmMatrix44fRowColumnProduct( (a), 0, (b), 0 ); \
    (dest)[ 0 ][ 1 ] = __mvmMatrix44fRowColumnProduct( (a), 0, (b), 1 ); \
    (dest)[ 0 ][ 2 ] = __mvmMatrix44fRowColumnProduct( (a), 0, (b), 2 ); \
    (dest)[ 0 ][ 3 ] = __mvmMatrix44fRowColumnProduct( (a), 0, (b), 3 ); \
    (dest)[ 1 ][ 0 ] = __mvmMatrix44fRowColumnProduct( (a), 1, (b), 0 ); \
    (dest)[ 1 ][ 1 ] = __mvmMatrix44fRowColumnProduct( (a), 1, (b), 1 ); \
    (dest)[ 1 ][ 2 ] = __mvmMatrix44fRowColumnProduct( (a), 1, (b), 2 ); \
    (dest)[ 1 ][ 3 ] = __mvmMatrix44fRowColumnProduct( (a), 1, (b), 3 ); \
    (dest)[ 2 ][ 0 ] = __mvmMatrix44fRowColumnProduct( (a), 2, (b), 0 ); \
    (dest)[ 2 ][ 1 ] = __mvmMatrix44fRowColumnProduct( (a), 2, (b), 1 ); \
    (dest)[ 2 ][ 2 ] = __mvmMatrix44fRowColumnProduct( (a), 2, (b), 2 ); \
    (dest)[ 2 ][ 3 ] = __mvmMatrix44fRowColumnProduct( (a), 2, (b), 3 ); \
    (dest)[ 3 ][ 0 ] = __mvmMatrix44fRowColumnProduct( (a), 3, (b), 0 ); \
    (dest)[ 3 ][ 1 ] = __mvmMatrix44fRowColumnProduct( (a), 3, (b), 1 ); \
    (dest)[ 3 ][ 2 ] = __mvmMatrix44fRowColumnProduct( (a), 3, (b), 2 ); \
    (dest)[ 3 ][ 3 ] = __mvmMatrix44fRowColumnProduct( (a), 3, (b), 3 ); \
}

#define _mvmMatrix22fScale(dest,s,m) \
{ \
    (dest)[ 0 ][ 0 ] = (s)[ 0 ] * (m)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (s)[ 0 ] * (m)[ 0 ][ 1 ]; \
    (dest)[ 1 ][ 0 ] = (s)[ 1 ] * (m)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (s)[ 1 ] * (m)[ 1 ][ 1 ]; \
}

#define _mvmMatrix33fScale(dest,s,m) \
{ \
    (dest)[ 0 ][ 0 ] = (s)[ 0 ] * (m)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (s)[ 0 ] * (m)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (s)[ 0 ] * (m)[ 0 ][ 2 ]; \
    (dest)[ 1 ][ 0 ] = (s)[ 1 ] * (m)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (s)[ 1 ] * (m)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (s)[ 1 ] * (m)[ 1 ][ 2 ]; \
    (dest)[ 2 ][ 0 ] = (s)[ 2 ] * (m)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (s)[ 2 ] * (m)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (s)[ 2 ] * (m)[ 2 ][ 2 ]; \
}

#define _mvmMatrix44fScale(dest,s,m) \
{ \
    (dest)[ 0 ][ 0 ] = (s)[ 0 ] * (m)[ 0 ][ 0 ]; \
    (dest)[ 0 ][ 1 ] = (s)[ 0 ] * (m)[ 0 ][ 1 ]; \
    (dest)[ 0 ][ 2 ] = (s)[ 0 ] * (m)[ 0 ][ 2 ]; \
    (dest)[ 0 ][ 3 ] = (s)[ 0 ] * (m)[ 0 ][ 3 ]; \
    (dest)[ 1 ][ 0 ] = (s)[ 1 ] * (m)[ 1 ][ 0 ]; \
    (dest)[ 1 ][ 1 ] = (s)[ 1 ] * (m)[ 1 ][ 1 ]; \
    (dest)[ 1 ][ 2 ] = (s)[ 1 ] * (m)[ 1 ][ 2 ]; \
    (dest)[ 1 ][ 3 ] = (s)[ 1 ] * (m)[ 1 ][ 3 ]; \
    (dest)[ 2 ][ 0 ] = (s)[ 2 ] * (m)[ 2 ][ 0 ]; \
    (dest)[ 2 ][ 1 ] = (s)[ 2 ] * (m)[ 2 ][ 1 ]; \
    (dest)[ 2 ][ 2 ] = (s)[ 2 ] * (m)[ 2 ][ 2 ]; \
    (dest)[ 2 ][ 3 ] = (s)[ 2 ] * (m)[ 2 ][ 3 ]; \
    (dest)[ 3 ][ 0 ] = (s)[ 3 ] * (m)[ 3 ][ 0 ]; \
    (dest)[ 3 ][ 1 ] = (s)[ 3 ] * (m)[ 3 ][ 1 ]; \
    (dest)[ 3 ][ 2 ] = (s)[ 3 ] * (m)[ 3 ][ 2 ]; \
    (dest)[ 3 ][ 3 ] = (s)[ 3 ] * (m)[ 3 ][ 3 ]; \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mvm_Matrix_h */
