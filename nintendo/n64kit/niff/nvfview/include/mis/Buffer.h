/*
  mis/Buffer.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 24, 1998.
*/

#ifndef _mis_Buffer_h
#define _mis_Buffer_h 1

#include "mvm/Color.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros   */
#define MIS_BUFFER_ERROR_EOF_BIT	(1)
#define MIS_BUFFER_ERROR_FAILURE_BIT	(2)

#define MIS_BUFFER_GET_ERROR		(-1)	/* Return value of 'get' */

/* Declare prototype structures */
struct _MsoAllocator;
struct _MisBuffer;

/* Declare structures */
typedef int ( *MisBufferGetFunc )( struct _MisBuffer *buffer );

typedef struct _MisBuffer
{
    u32				size;
    u32				get_capacity;
    u32				get_cursor;
    u32				put_cursor;
    u8				*buffer_ptr;
    struct _MsoAllocator	*allocator_ptr;
} MisBuffer;

/* Declare functions */
extern void misBufferInit( MisBuffer *buffer_ptr );
extern void misBufferAllocate( MisBuffer *buffer_ptr, const u32 size,
			       struct _MsoAllocator *allocator_ptr );
extern void misBufferAttach( MisBuffer *buffer_ptr, const u32 size,
			     void *mem_ptr );
extern void misBufferDestroy( MisBuffer *buffer_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros */
#define _misBufferGetCapacity(buffer_ptr) ( (buffer_ptr)->get_capacity )

#define _misBufferPutCapacity(buffer_ptr) \
	( (buffer_ptr)->size - (buffer_ptr)->get_capacity )

#define _misBufferIsEmpty(buffer_ptr) ( (buffer_ptr)->get_capacity == 0 )

#define _misBufferIsFull(buffer_ptr) \
	( (buffer_ptr)->size == (buffer_ptr)->get_capacity )

#define _misBufferGetCursor(buffer_ptr) ( (buffer_ptr)->get_cursor )

#define _misBufferPutCursor(buffer_ptr) ( (buffer_ptr)->put_cursor )

#define _misBufferGetPtr(buff_ptr) \
	( &(buff_ptr)->buffer_ptr[ (buff_ptr)->get_cursor ] )

#define _misBufferPutPtr(buff_ptr) \
	( &(buff_ptr)->buffer_ptr[ (buff_ptr)->put_cursor ] )

#define _misBufferPeek(buff_ptr) \
	( (buff_ptr)->buffer_ptr[ (buff_ptr)->get_cursor ] )

#define _misBufferMoveGetCursor(buffer_ptr,count) \
{\
    (buffer_ptr)->get_capacity -= (count);			\
    (buffer_ptr)->get_cursor += (count);			\
    if ( (buffer_ptr)->get_cursor >= (buffer_ptr)->size )	\
		(buffer_ptr)->get_cursor -= (buffer_ptr)->size;	\
}

#define _misBufferMovePutCursor(buffer_ptr,count) \
{\
    (buffer_ptr)->get_capacity += (count);			\
    (buffer_ptr)->put_cursor += (count);			\
    if ( (buffer_ptr)->put_cursor >= (buffer_ptr)->size )	\
		(buffer_ptr)->put_cursor -= (buffer_ptr)->size;	\
}

#endif /* _mis_Buffer_h */
