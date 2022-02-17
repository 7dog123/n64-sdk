/*
  mif/FileParser.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 06, 1998.
*/

#ifndef _mif_FileParser_h
#define _mif_FileParser_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mis/Buffer.h"
#include "mis/Input.h"
#include "mso/derive.h"
#include "mif/ChunkParser.h"
#include "mif/FormParser.h"

#include <ultra64.h>


typedef struct _MifFileParser {
	MifFormParser *form_parser_ptr_list;
} MifFileParser;


/*
 *  Declare external reference
 */
extern void mifFileParserInit(MifFileParser *,...);
extern int mifFileParserRead(MifFileParser *, MisInput *, void *);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
