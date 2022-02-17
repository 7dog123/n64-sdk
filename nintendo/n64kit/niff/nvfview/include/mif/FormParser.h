/*
  mif/FormParser.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 06, 1998.
*/

#ifndef _mif_FormParser_h
#define _mif_FormParser_h 1

#include "mis/Buffer.h"
#include "mis/Input.h"
#include "mso/derive.h"
#include "mif/ChunkParser.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>
#include <stdarg.h>


typedef struct _MifFormParser {
	MifMagic form_magic;
	struct _MifFormParser *next;
	MifChunkParser *chunk_parser_ptr_list;
} MifFormParser;

/*
 * Declare external reference
 */
extern void mifFormParserInit(MifFormParser *, const MifMagic,...);
extern int mifFormParserRead(MifFormParser *, MisInput *, const u32, void *);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
