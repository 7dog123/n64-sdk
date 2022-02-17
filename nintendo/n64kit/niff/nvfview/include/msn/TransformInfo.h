/*
  msn/TransformInfo.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 19, 1998.
*/

#ifndef _msn_TransformInfo_h
#define _msn_TransformInfo_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/TransformInfo.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_TRANSFORM_INFO_FIELD_SCALE			(0)
#define MSN_TRANSFORM_INFO_FIELD_CLASSIC_SCALE		(1)
#define MSN_TRANSFORM_INFO_FIELD_POSITION		(2)
#define MSN_TRANSFORM_INFO_FIELD_ORIENTATION		(3)
#define MSN_TRANSFORM_INFO_FIELD_SCALED_ORIENTATION	(4)

/* Declare types of a structure */
typedef MhcTransformInfo MsnTransformInfo;

/* Declare Functions */
extern void msnTransformInfoInit( MsnTransformInfo *transform_ptr );

/* Declare global variables */
extern MifChunkParser gMsnTransformInfoChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_TransformInfo_h */
