/*
  mrn/Camera.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 12, 1998.
*/

#ifndef _mrn_Camera_h
#define _mrn_Camera_h 1

#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MRN_CAMERA_TYPE_PERSPECTIVE	(0)
#define MRN_CAMERA_TYPE_ORTHOGONAL	(1)

/* Declare prototype structures */
struct _MrnContext;
struct _MrnView;

/* Declare structures */
typedef struct _MrnPerspectiveCamera
{
    float	field_of_view_y;
} MrnPerspectiveCamera;

typedef struct _MrnOrthogonalCamera
{
    float	ky;
} MrnOrthogonalCamera;

typedef struct _MrnCamera
{
    u32			type;
    MvmMatrix33f	orientation;
    MvmVector3f		position;

    float		aspect_ratio;
    float		clip_near;
    float		clip_far;
    float		clip_left;
    float		clip_right;
    float		clip_top;
    float		clip_bottom;
    union
    {
	MrnPerspectiveCamera	persp;
	MrnOrthogonalCamera	ortho;
    } camera;
} MrnCamera;

/* Declare functions */
extern void mrnCameraInit( MrnCamera *camera_ptr, const u32 type );

extern Gfx *mrnCameraGenerateGfx( MrnCamera *camera_ptr,
				  struct _MrnContext *context_ptr,
				  Gfx *gfx_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mrn_Camera_h */
