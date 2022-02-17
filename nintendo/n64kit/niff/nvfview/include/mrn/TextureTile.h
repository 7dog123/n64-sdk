/*
  mrn/TextureTile.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 10, 1998.
*/

#ifndef _mrn_TextureTile_h
#define _mrn_TextureTile_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_TEXTURE_TILE_FORMAT_I4		(0)
#define MRN_TEXTURE_TILE_FORMAT_I8		(1)
#define MRN_TEXTURE_TILE_FORMAT_IA31		(2)
#define MRN_TEXTURE_TILE_FORMAT_IA44		(3)
#define MRN_TEXTURE_TILE_FORMAT_IA88		(4)
#define MRN_TEXTURE_TILE_FORMAT_RGBA5551	(5)
#define MRN_TEXTURE_TILE_FORMAT_RGBA8888	(6)
#define MRN_TEXTURE_TILE_FORMAT_YUV		(7)
#define MRN_TEXTURE_TILE_FORMAT_CI4		(8)
#define MRN_TEXTURE_TILE_FORMAT_CI8		(9)

#define MRN_TEXTURE_TILE_CLAMP_MIRROR		(1)
#define MRN_TEXTURE_TILE_CLAMP_CLAMP		(2)

/* Declare structures */
typedef struct _MrnTextureTile
{
    u8	format;
    u8  lut_offset;
    u16	tmem_addr;
    u16	stride;
    u32	s[2];
    u32	t[2];
    u8	clamp_mode_s;
    u8	clamp_mode_t;
    u8	shift_s;
    u8	shift_t;
    u8	mask_s;
    u8	mask_t;
} MrnTextureTile;

/* Declare functions */
extern Gfx *mrnTextureTileGenerateGfx( const MrnTextureTile *tile_ptr,
				       const u8 tile_index,
				       const u16 tmem_offset,
				       const u8 additional_lut_offset,
				       Gfx *gfx_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_TextureTile_h */
