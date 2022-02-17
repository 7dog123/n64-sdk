/*
  msn/Function.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Mar. 18, 1999.
*/

#ifndef _msn_Function_h
#define _msn_Function_h 1

#include "mhc/Function.h"
#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare macro */
#define MSN_FUNCTION_CONTINUITY_DISCONT	MHC_FUNCTION_CONTINUITY_DISCONT
#define MSN_FUNCTION_CONTINUITY_C0	MHC_FUNCTION_CONTINUITY_C0
#define MSN_FUNCTION_CONTINUITY_C1	MHC_FUNCTION_CONTINUITY_C1

/* Declare prototype structure */
struct _MsnFunction;

/* Declare types of a structure */
typedef MhcFunctionGetValueFunc MsnFunctionGetValueFunc;
typedef MhcFunction MsnFunction;

/* Declare Functions */
extern void msnConstFunctionInit( MsnFunction *function_ptr );
extern void msnLinearFunctionInit( MsnFunction *function_ptr );
extern void msnHermiteFunctionInit( MsnFunction *function_ptr );

/* Declare global variables */
extern MifChunkParser gMsnConstFunctionChunkParser;
extern MifChunkParser gMsnLinearFunctionChunkParser;
extern MifChunkParser gMsnHermiteFunctionChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_Function_h */
