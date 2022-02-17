/*
  mvm/Vector.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 17, 1998.
*/

#ifndef _mvm_Vector_h
#define _mvm_Vector_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>
#include <mvm/Matrix.h>

/* Declare structures */
typedef s8 MvmVector2sc[ 2 ];
typedef s8 MvmVector3sc[ 3 ];
typedef s8 MvmVector4sc[ 4 ];
typedef u8 MvmVector2uc[ 2 ];
typedef u8 MvmVector3uc[ 3 ];
typedef u8 MvmVector4uc[ 4 ];

typedef s16 MvmVector2ss[ 2 ];
typedef s16 MvmVector3ss[ 3 ];
typedef s16 MvmVector4ss[ 4 ];
typedef u16 MvmVector2us[ 2 ];
typedef u16 MvmVector3us[ 3 ];
typedef u16 MvmVector4us[ 4 ];

typedef s32 MvmVector2sl[ 2 ];
typedef s32 MvmVector3sl[ 3 ];
typedef s32 MvmVector4sl[ 4 ];
typedef u32 MvmVector2ul[ 2 ];
typedef u32 MvmVector3ul[ 3 ];
typedef u32 MvmVector4ul[ 4 ];

typedef float MvmVector2f[ 2 ];
typedef float MvmVector3f[ 3 ];
typedef float MvmVector4f[ 4 ];

/* Declare functions */
extern void mvmVector2fCopy( MvmVector2f dest, const MvmVector2f src );
extern void mvmVector3fCopy( MvmVector3f dest, const MvmVector3f src );
extern void mvmVector4fCopy( MvmVector4f dest, const MvmVector4f src );

extern void mvmVector2fMag( MvmVector2f dest, const float k,
					      const MvmVector2f src );
extern void mvmVector3fMag( MvmVector3f dest, const float k,
					      const MvmVector3f src );
extern void mvmVector4fMag( MvmVector4f dest, const float k,
					      const MvmVector4f src );

extern void mvmVector2fAdd( MvmVector2f dest, const MvmVector2f a,
					      const MvmVector2f b );
extern void mvmVector3fAdd( MvmVector3f dest, const MvmVector3f a,
					      const MvmVector3f b );
extern void mvmVector4fAdd( MvmVector4f dest, const MvmVector4f a,
					      const MvmVector4f b );

extern void mvmVector2fSub( MvmVector2f dest, const MvmVector2f a,
					      const MvmVector2f b );
extern void mvmVector3fSub( MvmVector3f dest, const MvmVector3f a,
					      const MvmVector3f b );
extern void mvmVector4fSub( MvmVector4f dest, const MvmVector4f a,
					      const MvmVector4f b );

extern void mvmVector2fScale( MvmVector2f dest, const MvmVector2f a,
						const MvmVector2f b );
extern void mvmVector3fScale( MvmVector3f dest, const MvmVector3f a,
						const MvmVector3f b );
extern void mvmVector4fScale( MvmVector4f dest, const MvmVector4f a,
						const MvmVector4f b );

extern float mvmVector2fDot( const MvmVector2f a, const MvmVector2f b );
extern float mvmVector3fDot( const MvmVector3f a, const MvmVector3f b );
extern float mvmVector4fDot( const MvmVector4f a, const MvmVector4f b );

extern void mvmVector3fCross( MvmVector3f dest, const MvmVector3f a,
						const MvmVector3f b );

extern void mvmVector2fTransform22f( MvmVector2f dest, const MvmVector2f v,
						       const MvmMatrix22f m );
extern void mvmVector3fTransform33f( MvmVector3f dest, const MvmVector3f v,
						       const MvmMatrix33f m );
extern void mvmVector3fTransform33fp( MvmVector3f dest, const MvmVector3f v,
				const MvmMatrix33f m, const MvmVector3f p );
extern void mvmVector4fTransform44f( MvmVector4f dest, const MvmVector4f v,
						       const MvmMatrix44f m );

/* Declare Macros */
#define _mvmVector2fCopy(dest,src) \
{ \
    (dest)[ 0 ] = (src)[ 0 ]; \
    (dest)[ 1 ] = (src)[ 1 ]; \
}

#define _mvmVector3fCopy(dest,src) \
{ \
    (dest)[ 0 ] = (src)[ 0 ]; \
    (dest)[ 1 ] = (src)[ 1 ]; \
    (dest)[ 2 ] = (src)[ 2 ]; \
}

#define _mvmVector4fCopy(dest,src) \
{ \
    (dest)[ 0 ] = (src)[ 0 ]; \
    (dest)[ 1 ] = (src)[ 1 ]; \
    (dest)[ 2 ] = (src)[ 2 ]; \
    (dest)[ 3 ] = (src)[ 3 ]; \
}

#define _mvmVector2fMag(dest,k,src) \
{ \
    (dest)[ 0 ] = (k) * (src)[ 0 ]; \
    (dest)[ 1 ] = (k) * (src)[ 1 ]; \
}

#define _mvmVector3fMag(dest,k,src) \
{ \
    (dest)[ 0 ] = (k) * (src)[ 0 ]; \
    (dest)[ 1 ] = (k) * (src)[ 1 ]; \
    (dest)[ 2 ] = (k) * (src)[ 2 ]; \
}

#define _mvmVector4fMag(dest,k,src) \
{ \
    (dest)[ 0 ] = (k) * (src)[ 0 ]; \
    (dest)[ 1 ] = (k) * (src)[ 1 ]; \
    (dest)[ 2 ] = (k) * (src)[ 2 ]; \
    (dest)[ 3 ] = (k) * (src)[ 3 ]; \
}

#define _mvmVector2fAdd(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] + (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] + (b)[ 1 ]; \
}

#define _mvmVector3fAdd(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] + (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] + (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] + (b)[ 2 ]; \
}

#define _mvmVector4fAdd(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] + (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] + (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] + (b)[ 2 ]; \
    (dest)[ 3 ] = (a)[ 3 ] + (b)[ 3 ]; \
}

#define _mvmVector2fSub(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] - (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] - (b)[ 1 ]; \
}

#define _mvmVector3fSub(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] - (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] - (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] - (b)[ 2 ]; \
}

#define _mvmVector4fSub(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] - (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] - (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] - (b)[ 2 ]; \
    (dest)[ 3 ] = (a)[ 3 ] - (b)[ 3 ]; \
}

#define _mvmVector2fScale(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] * (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] * (b)[ 1 ]; \
}

#define _mvmVector3fScale(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] * (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] * (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] * (b)[ 2 ]; \
}

#define _mvmVector4fScale(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 0 ] * (b)[ 0 ]; \
    (dest)[ 1 ] = (a)[ 1 ] * (b)[ 1 ]; \
    (dest)[ 2 ] = (a)[ 2 ] * (b)[ 2 ]; \
    (dest)[ 3 ] = (a)[ 3 ] * (b)[ 3 ]; \
}

#define _mvmVector2fDot(a,b) ( (a)[ 0 ] * (b)[ 0 ] + (a)[ 1 ] * (b)[ 1 ] )
#define _mvmVector3fDot(a,b) ( (a)[ 0 ] * (b)[ 0 ] + (a)[ 1 ] * (b)[ 1 ] + \
			       (a)[ 2 ] * (b)[ 2 ] )
#define _mvmVector4fDot(a,b) ( (a)[ 0 ] * (b)[ 0 ] + (a)[ 1 ] * (b)[ 1 ] + \
			       (a)[ 2 ] * (b)[ 2 ] + (a)[ 3 ] * (b)[ 3 ] )

#define _mvmVector3fCross(dest,a,b) \
{ \
    (dest)[ 0 ] = (a)[ 1 ] * (b)[ 2 ] - (a)[ 2 ] * (b)[ 1 ]; \
    (dest)[ 1 ] = (a)[ 2 ] * (b)[ 0 ] - (a)[ 0 ] * (b)[ 2 ]; \
    (dest)[ 2 ] = (a)[ 0 ] * (b)[ 1 ] - (a)[ 1 ] * (b)[ 0 ]; \
}

#define _mvmVector2fTransform22f(dest,v,m) \
{ \
    (dest)[ 0 ] = (v)[ 0 ] * (m)[ 0 ][ 0 ] + (v)[ 1 ] * (m)[ 1 ][ 0 ]; \
    (dest)[ 1 ] = (v)[ 0 ] * (m)[ 0 ][ 1 ] + (v)[ 1 ] * (m)[ 1 ][ 1 ]; \
}

#define _mvmVector3fTransform33f(dest,v,m) \
{ \
    (dest)[ 0 ] = (v)[ 0 ] * (m)[ 0 ][ 0 ] + (v)[ 1 ] * (m)[ 1 ][ 0 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 0 ]; \
    (dest)[ 1 ] = (v)[ 0 ] * (m)[ 0 ][ 1 ] + (v)[ 1 ] * (m)[ 1 ][ 1 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 1 ]; \
    (dest)[ 2 ] = (v)[ 0 ] * (m)[ 0 ][ 2 ] + (v)[ 1 ] * (m)[ 1 ][ 2 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 2 ]; \
}

#define _mvmVector3fTransform33fp(dest,v,m,p) \
{ \
    (dest)[ 0 ] = (v)[ 0 ] * (m)[ 0 ][ 0 ] + (v)[ 1 ] * (m)[ 1 ][ 0 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 0 ] + (p)[ 0 ]; \
    (dest)[ 1 ] = (v)[ 0 ] * (m)[ 0 ][ 1 ] + (v)[ 1 ] * (m)[ 1 ][ 1 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 1 ] + (p)[ 1 ]; \
    (dest)[ 2 ] = (v)[ 0 ] * (m)[ 0 ][ 2 ] + (v)[ 1 ] * (m)[ 1 ][ 2 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 2 ] + (p)[ 2 ]; \
}

#define _mvmVector4fTransform44f(dest,v,m) \
{ \
    (dest)[ 0 ] = (v)[ 0 ] * (m)[ 0 ][ 0 ] + (v)[ 1 ] * (m)[ 1 ][ 0 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 0 ] + (v)[ 3 ] * (m)[ 3 ][ 0 ]; \
    (dest)[ 1 ] = (v)[ 0 ] * (m)[ 0 ][ 1 ] + (v)[ 1 ] * (m)[ 1 ][ 1 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 1 ] + (v)[ 3 ] * (m)[ 3 ][ 1 ]; \
    (dest)[ 2 ] = (v)[ 0 ] * (m)[ 0 ][ 2 ] + (v)[ 1 ] * (m)[ 1 ][ 2 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 2 ] + (v)[ 3 ] * (m)[ 3 ][ 2 ]; \
    (dest)[ 3 ] = (v)[ 0 ] * (m)[ 0 ][ 3 ] + (v)[ 1 ] * (m)[ 1 ][ 3 ] + \
		  (v)[ 2 ] * (m)[ 2 ][ 3 ] + (v)[ 3 ] * (m)[ 3 ][ 3 ]; \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mvm_Vector_h */
