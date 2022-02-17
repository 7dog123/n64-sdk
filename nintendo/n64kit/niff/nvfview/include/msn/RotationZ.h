/*
  msn/RotationZ.h
    CopZright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 6, 1999.
*/

#ifndef _msn_RotationZ_h
#define _msn_RotationZ_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/Rotation1.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MSN_ROTATION_Z_FIELD_ROTATION		(0)
#define MSN_ROTATION_Z_FIELD_GLOBAL_ORIENTATION	(1)

/* Declare types of a structure */
typedef MhcRotation1 MsnRotationZ;

/* Declare Functions */
extern void msnRotationZInit( MsnRotationZ *rotation_ptr );

/* Declare global variables */
extern MifChunkParser gMsnRotationZChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_RotationZ_h */
