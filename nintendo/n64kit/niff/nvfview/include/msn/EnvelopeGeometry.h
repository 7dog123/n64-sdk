/*
  msn/EnvelopeGeometry.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 19, 1998.
*/

#ifndef _msn_EnvelopeGeometry_h
#define _msn_EnvelopeGeometry_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_ENVELOPE_GEOMETRY_FIELD_ORIENTATION		(0)
#define MSN_ENVELOPE_GEOMETRY_FIELD_SCALED_ORIENTATION	(1)
#define MSN_ENVELOPE_GEOMETRY_FIELD_POSITION		(2)
#define MSN_ENVELOPE_GEOMETRY_FIELD_SCALE		(3)

/* Declare structures */
typedef struct _MsnEnvelopeGeometry
{
    _msoDeriveFrom( MhcNode );
    u32			number_of_joints;
    MvmMatrix33f	*orientation_array;
    MvmMatrix33f	*scaled_orientation_array;
    MvmVector3f		*position_array;
    MvmVector3f		*scale_array;
    MhcNodeHandle	vertex;
} MsnEnvelopeGeometry;

/* Declare functions */
extern void msnEnvelopeGeometryInit( MsnEnvelopeGeometry *geometry_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnEnvelopeGeometryChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_EnvelopeGeometry_h */
