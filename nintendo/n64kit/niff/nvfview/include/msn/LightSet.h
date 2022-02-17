/*
  msn/LightSet.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 12, 1998.
*/

#ifndef _msn_LightSet_h
#define _msn_LightSet_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/LightSet.h"
#include "mso/derive.h"
#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_LIGHT_SET_MAX_LIGHTS	(7)

#define MSN_LIGHT_SET_FIELD_AMBIENT	(0)

/* Declare structures */
typedef struct _MsnLightSet
{
    _msoDeriveFrom( MhcNode );
    MrnLightSet		light_set;
    MhcNodeHandle	light_array[ MSN_LIGHT_SET_MAX_LIGHTS ];
} MsnLightSet;

/* Declare functions */
extern void msnLightSetInit( MsnLightSet *set_ptr );

/* Declare global variables */
extern MifChunkParser gMsnLightSetChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_LightSet_h */
