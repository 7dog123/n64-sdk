/*
  mrn/LightSet.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Feb. 9, 1999.
*/

#ifndef _mrn_LightSet_h
#define _mrn_LightSet_h 1

#include "mrn/ObjectList.h"
#include "mrn/Light.h"
#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

#define MRN_LIGHT_SET_MAX_LIGHTS	(7)

/* Declare prptotype structure */
struct _MrnContext;
struct _MrnMaterial;

/* Declare structures */
typedef struct _MrnLightSet
{
    struct _MrnLightSet	*next_ptr;
    MrnObjectList	object_list;
			/* List of object which uses 'LightSet'.
			   Internally, it sorts object. */

    u8			number_of_lights;
    u8			use_point_lights;
    MvmColor3f		ambient;
    MrnLight		light_array[ MRN_LIGHT_SET_MAX_LIGHTS ];
} MrnLightSet;

/* Declare functions */
extern void mrnLightSetInit( MrnLightSet *light_set_ptr );

extern Gfx *mrnLightSetDrawObjects( MrnLightSet *light_set_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );
extern Gfx *mrnLightSetGenerateGfx( MrnLightSet *light_set_ptr,
				    struct _MrnContext *context_ptr,
				    const struct _MrnMaterial *material_ptr,
				    const MvmVector3f object_position,
				    Gfx *gfx_ptr );
extern Gfx *mrnLightSetModifyColor( const MrnLightSet *light_set_ptr,
		struct _MrnContext *context_ptr,
		const struct _MrnMaterial *material_ptr, Gfx *gfx_ptr );

/* Declare Global variables */
extern MrnLightSet	gMrnLightSetNull;
extern MrnLightSet	gMrnLightSetDefault;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_LightSet_h */
