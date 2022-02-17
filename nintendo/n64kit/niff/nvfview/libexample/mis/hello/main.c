/*
  mis/hello/main.c
    An example of 'libmis'  
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 25, 1998.
*/

#include <ultra64.h>
#include "mis/RomInputPi.h"
#include "mso/debug.h"

/* Declare 'hello segment' area */
extern u8 _helloSegmentRomStart[ ];
extern u8 _helloSegmentRomEnd[ ];

/*--------------------------------------------------------------------*/
static void print( MisInput *input_ptr )
{
    int	c;
    while ( ( c = _misInputGet( input_ptr ) ) >= 0 ) _msoPrintf( "%c", c );
}

/*--------------------------------------------------------------------*/
void main_proc( void *arg )
{
    MisRomInputPi	rom_input;

    ( void )arg;

    misRomInputPiInit( &rom_input );
    misRomInputPiOpen( &rom_input, ( u32 )_helloSegmentRomStart,
		( u32 )_helloSegmentRomEnd - ( u32 )_helloSegmentRomStart );
    print( _msoUpCast( MisInput, &rom_input ) );
}
