/*
  msn/Float.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 16, 1998.
*/

#ifndef _msn_Float_h
#define _msn_Float_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare a constant macro */
#define MSN_FLOAT_FIELD_VALUE	(0)

/* Declare structures */
typedef struct _MsnFloat
{
    _msoDeriveFrom( MhcNode );
    u32		number_of_elements;
    float	*value_array;
} MsnFloat;

/* Declare functions */
extern void msnFloatInit( MsnFloat *float_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnFloatChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Float_h */
