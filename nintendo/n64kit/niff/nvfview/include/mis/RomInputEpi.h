/*
  mis/RomInputEpi.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 5, 1999.
*/

#ifndef _mis_RomInputEpi_h
#define _mis_RomInputEpi_h 1

#include "mis/Buffer.h"
#include "mis/Input.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare type */
typedef struct _MisRomInputEpi
{
    _msoDeriveFrom( MisInput );
    u32		top_address;
    u32		size;
    u32		current_address;
    s8		io_request_count;
    u32		dma_size;
    OSPiHandle	*cart_handle;
    OSMesgQueue	io_message_queue;
    OSMesg	message_buffer;
    OSIoMesg	io_message;
    MisBuffer	buffer;
} MisRomInputEpi;

/* Declare functions */
extern void misRomInputEpiInit( MisRomInputEpi *rom_input_ptr );
extern void misRomInputEpiOpen( MisRomInputEpi *rom_input_ptr,
			        const u32 dev_addr, const u32 size );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mis_RomInputEpi_h */
