/*
  mvm/util.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 16, 1998.
*/

#ifndef _mvm_util_h
#define _mvm_util_h 1

#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare functions */
extern int mvmGetAngle( const MvmVector3f v1, const MvmVector3f v2 );
					/* Return 'theta/PI*32768'. */

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macros */
#define EPSILON (1.0e-6f)
#define rsqrtf(x) ( 1.0f / sqrtf( x ) )
#define mrsqrtf(k,x) ( (k) / sqrtf( x ) )
#define rsqrtf2(x) ( ( (x) < EPSILON ) ? 0.0f : rsqrtf( x ) )
#define mrsqrtf2(k,x) ( ( (x) < EPSILON ) ? 0.0f : mrsqrtf( x ) )
#define pow2(x) ( (x) * (x) )

#endif /* _mvm_util_h */
