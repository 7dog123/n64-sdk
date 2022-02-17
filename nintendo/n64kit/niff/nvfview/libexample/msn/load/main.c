/*
  mhc/load/main.c
    libmhc example
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 8, 1998.
*/

#include <ultra64.h>
#include "mhc/ModuleNode.h"
#include "mhc/Scene.h"
#include "mif/FileParser.h"
#include "mif/FormParser.h"
#include "mis/Input.h"
#include "mis/RomInputPi.h"
#include "msn/FormParser.h"
#include "mso/debug.h"

/* Declaration of nvf segment  */
extern u8 _nvfSegmentRomStart[ ];
extern u8 _nvfSegmentRomEnd[ ];

/*--------------------------------------------------------------------*/
void main_proc( void *arg )
{
    static MifFileParser	file_parser;
    static MisRomInputPi	rom_input;
    static MhcScene		scene;
    static MifFormParser	form_parser;

    int	error_code;

    ( void )arg;

    misRomInputPiInit( &rom_input );
    misRomInputPiOpen( &rom_input, ( u32 )_nvfSegmentRomStart,
		( u32 )_nvfSegmentRomEnd - ( u32 )_nvfSegmentRomStart );

    mhcSceneInit( &scene, 4, 128, 4096 );
    msnFormParserInit( &form_parser );
    mifFileParserInit( &file_parser, &form_parser, NULL );

    error_code = mifFileParserRead( &file_parser,
				    _msoUpCast( MisInput, &rom_input ),
				    _mhcSceneGetModule( &scene, 0 ) );
    _msoPrintf( "ErrorCode:%d\n", error_code );
}
