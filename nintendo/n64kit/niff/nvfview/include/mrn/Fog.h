/*
  mrn/Fog.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 22, 1998.
*/

#ifndef _mrn_Fog_h
#define _mrn_Fog_h 1

#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare protorype structure */
struct _MrnGroup;

/* Declare structures */
typedef struct _MrnFog
{
    int		is_enable;
    u16		fog_near;
    u16		fog_far;
    MvmColor4c	color;
} MrnFog;

/* Declare functions */
extern void mrnFogInit( MrnFog *fog );

extern Gfx *mrnFogGenerateGfx( MrnFog *fog_ptr, Gfx *gfx_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Fog_h */
