/*
  msn/DirUpConstr.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 14, 1998.
*/

#ifndef _msn_DirUpConstr_h
#define _msn_DirUpConstr_h 1

#include "mhc/DirUpConstr.h"
#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macros */
#define MSN_DIR_UP_CONSTR_FIELD_DIRECTION		(0)
#define MSN_DIR_UP_CONSTR_FIELD_UPVECTOR		(1)

/* Declare structures */
typedef MhcDirUpConstr MsnDirUpConstr;

/* Declare functions */
extern void msnDirUpConstrInit( MsnDirUpConstr *constr_ptr );

/* Declare a global variable */
extern MifChunkParser gMsnDirUpConstrChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_DirUpConstr_h */
