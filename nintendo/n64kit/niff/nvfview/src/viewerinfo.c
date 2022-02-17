/*
  nvfview
  viewerinfo.c
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 14, 1998.
*/

#include "mgi/App.h"
#include "mhc/Module.h"
#include "mhc/Scene.h"
#include "mif/ChunkParser.h"
#include "mif/FileParser.h"
#ifdef _USE_EPI_
# include "mis/RomInputEpi.h"
#else	/* _USE_EPI_ */
# include "mis/RomInputPi.h"
#endif	/* _USE_EPI_ */
#include "msn/FormParser.h"
#include "mso/Allocator.h"
#include "mso/debug.h"
#include "viewerinfo.h"

#define ANIM_INFO_READ_COUNT	(32)
#define MODULE_INFO_READ_COUNT	(32)
#define VIEWER_INFO_READ_COUNT	(8)

/*--------------------------------------------------------------------*/
static int read_anim_info( MisInput *input_ptr, AnimInfo *anim_info_ptr )
{
    if ( misInputRead( input_ptr, ANIM_INFO_READ_COUNT, anim_info_ptr ) !=
	 ANIM_INFO_READ_COUNT )
    {
	return -1;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
static int read_module_info( MisInput *input_ptr, ModuleInfo *module_info_ptr )
{
    if ( misInputRead( input_ptr, MODULE_INFO_READ_COUNT, module_info_ptr ) !=
	 MODULE_INFO_READ_COUNT )
    {
	return -1;
    }
    if ( module_info_ptr->nvf_size > MODEL_MAX_SIZE ) return -2;

    return 0;
}

/*--------------------------------------------------------------------*/
static int read_viewer_info( MisInput *input_ptr, ViewerInfo *viewer_info_ptr )
{
    if ( misInputRead( input_ptr, VIEWER_INFO_READ_COUNT, viewer_info_ptr ) !=
	 VIEWER_INFO_READ_COUNT )
    {
	return -1;
    }
    if ( viewer_info_ptr->magic != _mifMagicDefine( 'N', 'V', 'F', 'V' ) )
    {
	return -2;
    }
    if ( ( viewer_info_ptr->number_of_modules < 1 )||
	 ( viewer_info_ptr->number_of_modules > 8 ) )
    {
	return -3;
    }

    return 0;
}

/*--------------------------------------------------------------------*/
static int load_module( MisInput *input_ptr,
			MhcModule *module_ptr,
			ModuleInfo *module_info_ptr,
			MifFileParser *file_parser_ptr )
{
    int	error_code;
    u32	i;

    error_code = read_module_info( input_ptr, module_info_ptr );
    module_info_ptr->anim_info_array = NULL;
    if ( error_code ) return error_code;

    module_info_ptr->anim_info_array = msoMalloc( sizeof( AnimInfo ) *
					module_info_ptr->number_of_anims );
    _msoPrintf( "Num of anims: %d\n", module_info_ptr->number_of_anims );
    for ( i = 0; i < module_info_ptr->number_of_anims; ++i )
    {
	error_code = read_anim_info( input_ptr,
				     &module_info_ptr->anim_info_array[ i ] );
	if ( error_code ) return error_code;
    }

    error_code = mhcModuleLoad( module_ptr, file_parser_ptr, input_ptr );
    if ( error_code == 0 ) mhcModuleActivate( module_ptr );
    return error_code;
}

/*--------------------------------------------------------------------*/
static MisInput *open_input( void )
{
#ifdef _USE_EPI_

    static MisRomInputEpi	rom_input;
    misRomInputEpiInit( &rom_input );
    misRomInputEpiOpen( &rom_input, MODEL_ADDR, MODEL_MAX_SIZE );

#else	/* _USE_EPI_ */

    static MisRomInputPi	rom_input;
    misRomInputPiInit( &rom_input );
    misRomInputPiOpen( &rom_input, MODEL_ADDR, MODEL_MAX_SIZE );

#endif	/* _USE_EPI_ */

    return _msoUpCast( MisInput, &rom_input );
}

/*--------------------------------------------------------------------*/
int LoadScene( MhcScene *scene_ptr, ViewerInfo *viewer_info_ptr )
{
    static MifFormParser	form_parser;
    static MifFileParser	file_parser;
    MisInput			*input_ptr;
    int				error_code;
    u32				i;

    msnFormParserInit( &form_parser );
    mifFileParserInit( &file_parser, &form_parser, NULL );

    input_ptr = open_input( );

    error_code = read_viewer_info( input_ptr, viewer_info_ptr );
    viewer_info_ptr->module_info_array = NULL;
    if ( !error_code )
    {
	viewer_info_ptr->module_info_array = msoMalloc( sizeof( ModuleInfo ) *
					viewer_info_ptr->number_of_modules );
	for ( i = 0; i < viewer_info_ptr->number_of_modules; ++i )
	{
	    _msoPrintf( "Module #%d\n", i );
	    error_code = load_module( input_ptr,
				      _mhcSceneGetModule( scene_ptr, i ),
				      &viewer_info_ptr->module_info_array[ i ],
				      &file_parser );
	    if ( error_code ) break;
	}
    }

    _misInputClose( input_ptr );
    _msoPrintf( "ErrorCode:%d\n", error_code );

    mhcSceneBind( scene_ptr );

    return error_code;
}
