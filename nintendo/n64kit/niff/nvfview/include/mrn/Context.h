/*
  mrn/Context.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 28, 1998.
*/

#ifndef _mrn_Context_h
#define _mrn_Context_h 1

#include "mrn/LightSetList.h"
#include "mrn/MaterialList.h"
#include "mrn/ObjectList.h"
#include "mrn/TextureImageList.h"
#include "mrn/TextureLutList.h"
#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MrnBlenderMode;
struct _MrnCamera;
struct _MrnLightSet;
struct _MrnMaterial;
struct _MrnScene;
struct _MrnTexture;
struct _MrnTextureImage;
struct _MrnTextureLut;
struct _MrnView;

/* Declare structures */
typedef struct _MrnContext
{
    struct _MrnScene		*scene_ptr;
    struct _MrnTextureImage	*current_texture_image_ptr;
    struct _MrnTextureLut	*current_texture_lut_ptr;
    struct _MrnTexture		*current_texture_ptr;
    struct _MrnLightSet		*current_light_set_ptr;
    struct _MrnMaterial		*current_material_ptr;
    struct _MrnView		*current_view_ptr;
    struct _MrnCamera		*current_camera_ptr;

    u8				is_light_set_changed;
    u8				is_pipe_sync_done;
    u8				current_cycle_type;
    u32				current_blender_code;
    u32				current_blend_color;
    u32				current_alpha_compare_mode;
    u32				current_geometry_mode;
    MvmColor4c			current_fog_color;
} MrnContext;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare functions */
extern Gfx *mrnContextSetView( MrnContext *context_ptr,
			       struct _MrnView *view_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetCamera( MrnContext *context_ptr,
				 struct _MrnCamera *camera_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetTextureImage( MrnContext *context_ptr,
			struct _MrnTextureImage *image_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetTextureLut( MrnContext *context_ptr,
			struct _MrnTextureLut *lut_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetTexture( MrnContext *context_ptr,
			struct _MrnTexture *texture_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetLightSet( MrnContext *context_ptr,
			struct _MrnLightSet *light_set_ptr, Gfx *gfx_ptr );

extern Gfx *mrnContextSetMaterial( MrnContext *context_ptr,
			struct _MrnMaterial *material, Gfx *gfx_ptr );

extern Gfx *mrnContextSetBlenderMode( MrnContext *context_ptr,
		struct _MrnBlenderMode blender_mode_array[ 2 ], Gfx *gfx_ptr );

extern Gfx *mrnContextSetFogColor( MrnContext *context_ptr,
			const u32 fog_color, Gfx *gfx_ptr );

/* Declare Macros */
#define _mrnContextInit(context_ptr,scn_ptr) \
{\
    (context_ptr)->scene_ptr = (scn_ptr);			\
    (context_ptr)->current_texture_image_ptr	= NULL;		\
    (context_ptr)->current_texture_lut_ptr	= NULL;		\
    (context_ptr)->current_texture_ptr		= NULL;		\
    (context_ptr)->current_light_set_ptr	= NULL;		\
    (context_ptr)->current_material_ptr		= NULL;		\
    (context_ptr)->current_view_ptr		= NULL;		\
    (context_ptr)->current_camera_ptr		= NULL;		\
    (context_ptr)->is_light_set_changed		= TRUE;		\
    (context_ptr)->is_pipe_sync_done		= FALSE;	\
    (context_ptr)->current_cycle_type		= 0xFF;		\
    (context_ptr)->current_blender_code		= 0xFFFFFFFF;	\
    (context_ptr)->current_blend_color		= 0;		\
    (context_ptr)->current_alpha_compare_mode	= 0xFFFFFFFF;	\
    (context_ptr)->current_geometry_mode	= 0xFFFFFFFF;	\
    (context_ptr)->current_fog_color.packed	= 0;		\
}

#define _mrnContextPipeSync(context_ptr,gfx_ptr) \
{									\
    if ( !(context_ptr)->is_pipe_sync_done ) gDPPipeSync( (gfx_ptr)++ );\
    (context_ptr)->is_pipe_sync_done = TRUE;				\
}

#ifdef F3DEX_GBI_2
#define _mrnContextSetGeometryMode(context_ptr,mode,gfx_ptr)	\
{								\
    if ( (context_ptr)->current_geometry_mode != (mode) )	\
    {								\
	gSPLoadGeometryMode( (gfx_ptr)++, (mode) );		\
    }								\
    (context_ptr)->current_geometry_mode = (mode);		\
}
#else	/* F3DEX_GBI_2 */
#define _mrnContextSetGeometryMode(context_ptr,mode,gfx_ptr)	\
{								\
    if ( (context_ptr)->current_geometry_mode != (mode) )	\
    {								\
	gSPClearGeometryMode( &(gfx_ptr)[ 0 ], G_SHADE		\
		| G_SHADING_SMOOTH | G_LIGHTING | G_TEXTURE_GEN	\
		| G_TEXTURE_GEN_LINEAR | G_FOG | G_CULL_FRONT	\
		| G_CULL_BACK | G_CULL_BOTH | G_ZBUFFER		\
		| G_LOD );					\
	gSPSetGeometryMode( &(gfx_ptr)[ 1 ], (mode) );		\
	(gfx_ptr) += 2;						\
    }								\
    (context_ptr)->current_geometry_mode = (mode);		\
}
#endif	/* F3DEX_GBI_2 */

#endif /* _mrn_Context_h */
