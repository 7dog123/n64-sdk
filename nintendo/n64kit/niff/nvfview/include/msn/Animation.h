/*
  msn/Animation.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _msn_Animation_h
#define _msn_Animation_h 1

#include "mhc/Animation.h"
#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_ANIMATION_FIELD_FUNCTION_INDEX	(0)
#define MSN_ANIMATION_FIELD_TIME		(1)
#define MSN_ANIMATION_FIELD_VALUE		(2)
#define MSN_ANIMATION_FIELD_DIFFERENTIAL	(3)

/* Declare structures */
typedef MhcAnimation MsnAnimation;

/* Declare functions */
extern void msnAnimationInit( MsnAnimation *animation_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnAnimationChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Animation_h */
