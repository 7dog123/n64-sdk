/*
  mis/RomInputPi.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 24, 1998.
*/

#ifndef _mis_RomInputPi_h
#define _mis_RomInputPi_h 1

#include "mis/Buffer.h"
#include "mis/Input.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MisRomInputPi
{
    _msoDeriveFrom( MisInput );
    u32		top_address;
    u32		size;
    u32		current_address;
    s8		io_request_count;
    u32		dma_size;
    OSMesgQueue	io_message_queue;
    OSMesg	message_buffer;
    OSIoMesg	io_message;
    MisBuffer	buffer;
} MisRomInputPi;

/* Declare functions */
extern void misRomInputPiInit( MisRomInputPi *rom_input_ptr );
extern void misRomInputPiOpen( MisRomInputPi *rom_input_ptr,
			       const u32 dev_addr, const u32 size );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mis_RomInputPi_h */
