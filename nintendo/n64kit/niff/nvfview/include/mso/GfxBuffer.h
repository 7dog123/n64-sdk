/*
  mso/GfxBuffer.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 8, 1998.
*/

#ifndef _mso_GfxBuffer_h
#define _mso_GfxBuffer_h 1

#include "mso/ListBase.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSO_GFX_CLUSTER_SIZE		(4096)
#define MSO_GFX_CLUSTER_CAPACITY	\
	( ( MSO_GFX_CLUSTER_SIZE - 8 ) / sizeof( Gfx ) )

/* Declare structures */
typedef struct _MsoGfxCluster
{
    struct _MsoGfxCluster	*next_ptr;
    u32				number_of_gfxs;
    Gfx				gfx_array[ MSO_GFX_CLUSTER_CAPACITY ];
} MsoGfxCluster;

_msoListBaseDefine( MsoGfxCluster );

typedef struct _MsoGfxBuffer
{
    MsoGfxClusterList	cluster_list;
    u32			number_of_gfxs;
} MsoGfxBuffer;

/* Declare functions */
extern void msoGfxBufferInit( MsoGfxBuffer *buffer_ptr );

extern void msoGfxBufferDestroy( MsoGfxBuffer *buffer_ptr );

extern Gfx *msoGfxBufferReserve( MsoGfxBuffer *buffer_ptr );

extern void msoGfxBufferStore( MsoGfxBuffer *buffer_ptr, Gfx *dest_array );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_Geometry_h */
