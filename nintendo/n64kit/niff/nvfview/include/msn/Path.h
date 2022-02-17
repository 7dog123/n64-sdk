/*
  msn/Path.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 2, 1998.
*/

#ifndef _msn_Path_h
#define _msn_Path_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_PATH_FIELD_FUNCTION_INDEX	(0)
#define MSN_PATH_FIELD_TIME		(1)
#define MSN_PATH_FIELD_VALUE		(2)
#define MSN_PATH_FIELD_DIFFERENTIAL	(3)
#define MSN_PATH_FIELD_GLOBAL_POSITION	(4)

/* Declaration Structure */
typedef struct _MsnPath
{
    _msoDeriveFrom( MhcNode );
    u32			function_index;
    u32			last_function_index;
    float		time;
    u32			key_search_hint;
    MvmVector3f		value;
    MvmVector3f		differential;
    u32			number_of_functions;
    MhcNodeHandle	*function_array;
    u32			number_of_children;
    MhcNodeHandle	*child_array;
} MsnPath;

/* Declare Function */
extern void msnPathInit( MsnPath *path_ptr );

/* Declare global variables */
extern MifChunkParser gMsnPathChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Path_h */
