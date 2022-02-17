/*
  mrn/Texture.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _mrn_Texture_h
#define _mrn_Texture_h 1

#include "mrn/ObjectList.h"
#include "mrn/TextureTile.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MRN_TEXTURE_MAX_TILES	(7)

/* Declare structures */
typedef struct _MrnTexture
{
    struct _MrnTexture		*next_ptr;
    MrnObjectList		object_list;
				/* List of objects which uses this Texture
				   Internally, it sorts objects. */

    u16				scale_s;
    u16				scale_t;
    u16				texel_size;
    u8				mipmap;
    u8				detail;
    u8				filter;
    u8				perspective_correction;
    u8				yuv_color_convert;
    u8				number_of_tiles;
    MrnTextureTile		tile_array[ MRN_TEXTURE_MAX_TILES ];
} MrnTexture;

/* Declare functions */
extern void mrnTextureInit( MrnTexture *texture_ptr );

extern Gfx *mrnTextureGenerateGfx( MrnTexture *texture_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnTextureDrawObjects( MrnTexture *texture_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

/* Declare a Global variable */
extern MrnTexture	gMrnTextureNull;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macro */
#define _mrnTextureIsEnable(texture_ptr) ( (texture_ptr)->number_of_tiles > 0 )

#endif /* _mrn_Texture_h */
