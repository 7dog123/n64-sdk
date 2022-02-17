/*
  mif/read_chunk/main.c
    A example of 'libmif'. 
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 08, 1998.
*/

#include <ultra64.h>
#include "mis/RomInputPi.h"
#include "mso/debug.h"
#include "mif/FileParser.h"


static int read_chunk_nhdr( MifChunkParser *, MisInput *, const u32, void * );
static int read_chunk_xlat( MifChunkParser *, MisInput *, const u32, void * );
static int read_chunk_rota( MifChunkParser *, MisInput *, const u32, void * );


/* FormParser Start Here */
static MifFormParser gMifFormParser = {
	_mifMagicDefine( 'F', 'O', 'R', 'M'),
};
/* FormParser End Here */

/* ChunkParser Start Here */
static MifChunkParser gMifChunkParser = {
	_mifMagicDefine( 'N', 'H', 'D', 'R'), read_chunk_nhdr
};

static MifChunkParser gMifChunkParser2 = {
	_mifMagicDefine( 'X', 'L', 'A', 'T'), read_chunk_xlat
};

static MifChunkParser *gMifChunkParserPtrArray[] = {
	&gMifChunkParser, &gMifChunkParser2, NULL
};

static MifChunkParser gMifChunkParser3 = {
	_mifMagicDefine( 'R', 'O', 'T', 'A'), read_chunk_xlat
};

static MifChunkParser *gMifChunkParserPtrArray2[] = {
	&gMifChunkParser3, NULL
};
/* ChunkParser End Here */


/* Declare 'test.nvs segment' area */
extern u8 _testSegmentRomStart[ ];
extern u8 _testSegmentRomEnd[ ];


/*--------------------------------------------------------------------*/
static int read_chunk_nhdr( MifChunkParser *chunk_parser_ptr, MisInput *input_ptr,
                            const u32 size, void *option )
{
	u32 read_size;
	u32 p;

	read_size = misInputRead( input_ptr, size, &p);
	_msoPrintf("call read_chunk_nhdr function read_size = %d, read_data = %d\n", read_size, p);
	return ( read_size != size );
}

/*--------------------------------------------------------------------*/
static int read_chunk_xlat( MifChunkParser *chunk_parser_ptr, MisInput *input_ptr,
                            const u32 size, void *option )
{
	u32 read_size;
	u32 p;

	read_size = misInputRead( input_ptr, size, &p);
	_msoPrintf("call read_chunk_xlat function read_size = %d, read_data = %d\n", read_size, p);
	return ( read_size != size );
}
/*--------------------------------------------------------------------*/
static int read_chunk_rota( MifChunkParser *chunk_parser_ptr, MisInput *input_ptr,
                            const u32 size, void *option )
{
	u32 read_size;
	u32 p;

	read_size = misInputRead( input_ptr, size, &p);
	_msoPrintf("call read_chunk_rota function read_size = %d, read_data = %d\n", read_size, p);
	return ( read_size != size );
}

/*--------------------------------------------------------------------*/
void main_proc( void *arg )
{
    MisRomInputPi rom_input;
	MifFileParser file_parser;
	int error_code;

	( void )arg;

	/* Initialize debug print */
	_msoPrintfInit();

	misRomInputPiInit( &rom_input );
	misRomInputPiOpen( &rom_input, ( u32 )_testSegmentRomStart,
		( u32 )_testSegmentRomEnd - ( u32 )_testSegmentRomStart );

	/* Initialize FormParser */
	mifFormParserInit(&gMifFormParser, _mifMagicDefine( 'N', 'V', 'F', 'B'),
	                  gMifChunkParserPtrArray, gMifChunkParserPtrArray2, (MifChunkParser**)NULL);
	/* Initialize FileParser */
	mifFileParserInit(&file_parser, &gMifFormParser, (MifFormParser*)NULL);

	/* Read FileParser */
	if ( (error_code = mifFileParserRead(&file_parser, _msoUpCast( MisInput, &rom_input ), "")) )
		_msoPrintf("mifFileParserRead Error\n");
	_msoPrintf("error_code %d\n", error_code);
}
