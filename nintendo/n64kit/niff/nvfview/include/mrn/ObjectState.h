/*
  mrn/ObjectState.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1998.
*/

#ifndef _mrn_ObjectState_h
#define _mrn_ObjectState_h 1

#include "mrn/BlenderMode.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_OBJECT_STATE_FLAGS_CULL_FRONT	(1)
#define MRN_OBJECT_STATE_FLAGS_CULL_BACK	(2)
#define MRN_OBJECT_STATE_FLAGS_Z_ENABLE		(4)
#define MRN_OBJECT_STATE_FLAGS_VERTEX_ALPHA	(8)
#define MRN_OBJECT_STATE_FLAGS_VERTEX_COLOR	(16)

/* Declare prototype structures */
struct _MrnContext;
struct _MrnGroup;
struct _MrnLightSet;
struct _MrnMaterial;
struct _MrnObjectState;
struct _MrnTexture;

/* Declare structures */
typedef struct _MrnObjectState
{
    MrnBlenderMode	blender_mode[ 2 ];
    MvmVector3f		center;
    u32			geometry_mode;
    u8			flags;
    u8			group_index;
    u16			priority;
} MrnObjectState;

/* Declare functions */
extern void mrnObjectStateInit( MrnObjectState *state_ptr );

extern Gfx *mrnObjectStateSetupGeometry( MrnObjectState *state_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

extern Gfx *mrnObjectStateSetupBlender( MrnObjectState *ObjectState_ptr,
			struct _MrnContext *context_ptr, Gfx *gfx_ptr );

/* Declare a Global variable */
extern MrnObjectState	gMrnObjectStateNull;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros */
#define __mrnObjectStateBlenderCode(p,m,a,b)			\
	( ( (p) << MRN_OBJECT_STATE_BLENDER_CODE_P_SHIFT ) |	\
	  ( (m) << MRN_OBJECT_STATE_BLENDER_CODE_M_SHIFT ) |	\
	  ( (a) << MRN_OBJECT_STATE_BLENDER_CODE_A_SHIFT ) |	\
	  ( (b) << MRN_OBJECT_STATE_BLENDER_CODE_B_SHIFT ) )

#define _mrnObjectStateRenderCode(p1,m1,a1,b1,p2,m2,a2,b2,mode)	\
	( ( __mrnObjectStateBlenderCode(p1,m1,a1,b1) <<		\
		 MRN_OBJECT_STATE_RENDER_CODE_BL1_SHIFT ) |	\
	  ( __mrnObjectStateBlenderCode(p2,m2,a2,b2) <<		\
		 MRN_OBJECT_STATE_RENDER_CODE_BL2_SHIFT ) |	\
	  ( (mode) << MRN_OBJECT_STATE_RENDER_CODE_MODE_SHIFT ) )

#endif /* _mrn_ObjectState_h */
