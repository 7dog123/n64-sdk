/*
  msn/FormParser.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 12, 1998.
*/

#ifndef _msn_FormParser_h
#define _msn_FormParser_h 1

#include "mif/ChunkParser.h"
#include "mif/FormParser.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare a structure */
typedef MifFormParser MsnFormParser;

/* Declare functions */
extern void msnFormParserInit( MsnFormParser *parser_ptr );

/* Declare a global variable */
extern MifChunkParser *gMsnChunkParserList[ ];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_FormParser_h */
