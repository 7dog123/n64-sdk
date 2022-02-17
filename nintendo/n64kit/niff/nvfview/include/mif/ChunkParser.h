/*
  mif/ChunkParser.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 06, 1998.
*/

#ifndef _mif_ChunkParser_h
#define _mif_ChunkParser_h 1

#include "mis/Buffer.h"
#include "mis/Input.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

struct _MifChunkParser;

/*
 *  Structure declaration 
 */
typedef int (*MifChunkParserReadFunc)(struct _MifChunkParser *chunk_parser_ptr,
                                      MisInput *input_ptr, const u32 size,
                                      void *option);
typedef u32 MifMagic;

typedef struct _MifChunkParser {
	MifMagic  chunk_magic;
	MifChunkParserReadFunc read;
	struct _MifChunkParser *left;
	struct _MifChunkParser *right;    /* Use the right pointer as the list pointer.  */
} MifChunkParser;

/*
 *  Macro definitions
 */
#define _mifChunkParserRead( chunk_parser_ptr, input_ptr, size, option) \
        ( (chunk_parser_ptr)->read( chunk_parser_ptr, input_ptr, size, option) )
#define _mifMagicDefine(a, b, c, d) ( (((u32)(a)) << 24) + (((u32)(b)) << 16) + (((u32)(c)) << 8) + ((u32)(d)) )

/*
 *  Declare external reference     
 */
extern void mifChunkParserInit(MifChunkParser *, const MifMagic,
                               MifChunkParserReadFunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mif_ChunkParser_h */
