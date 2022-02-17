/*
  msn/PerspectiveCamera.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 12, 1998.
*/

#ifndef _msn_PerspectiveCamera_h
#define _msn_PerspectiveCamera_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mrn/Camera.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_PERSPECTIVE_CAMERA_FIELD_FIELD_OF_VIEW_Y	(0)
#define MSN_PERSPECTIVE_CAMERA_FIELD_ASPECT_RATIO	(1)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_NEAR		(2)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_FAR		(3)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_LEFT		(4)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_RIGHT		(5)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_TOP		(6)
#define MSN_PERSPECTIVE_CAMERA_FIELD_CLIP_BOTTOM	(7)
#define MSN_PERSPECTIVE_CAMERA_FIELD_GROUP_MASK		(8)

/* Declare structures */
typedef struct _MsnPerspectiveCamera
{
    _msoDeriveFrom( MhcNode );
    MrnCamera		camera;
    u32			group_mask;
} MsnPerspectiveCamera;

/* Declare functions */
extern void msnPerspectiveCameraInit( MsnPerspectiveCamera *camera_ptr );

/* Declare global variables */
extern MifChunkParser gMsnPerspectiveCameraChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_PerspectiveCamera_h */
