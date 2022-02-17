/*
  mis/Input.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 7, 1998.
*/

#ifndef _mis_Input_h
#define _mis_Input_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MIS_INPUT_STATUS_OPEN_BIT	(1)
#define MIS_INPUT_STATUS_EOF_BIT	(2)
#define MIS_INPUT_STATUS_FAILURE_BIT	(4)

#define MIS_INPUT_GET_ERROR		(-1)	/* Return value of 'get' */

/* Declare prototype structures */
struct _MsoAllocator;
struct _MisInput;

/* Declare structures */
typedef int ( *MisInputGetFunc )( struct _MisInput *input );
typedef int ( *MisInputCloseFunc )( struct _MisInput *input );
typedef void ( *MisInputDestroyFunc )( struct _MisInput *input );

typedef struct _MisInput
{
    u8			status;
    MisInputGetFunc	get;
    MisInputCloseFunc	close;
    MisInputDestroyFunc	destroy;
} MisInput;

/* Declare functions */
extern void misInputInit( MisInput *input_ptr, MisInputGetFunc get_func,
			  MisInputCloseFunc close_func,
			  MisInputDestroyFunc destroy_func );
extern void misInputDestroy( MisInput *input_ptr );
extern u32 misInputRead( MisInput *input_ptr, const u32 byte_count,
			 void *buffer_ptr );
extern s8 misInputGetSChar( MisInput *input_ptr );
extern u8 misInputGetUChar( MisInput *input_ptr );
extern s16 misInputGetSShort( MisInput *input_ptr );
extern u16 misInputGetUShort( MisInput *input_ptr );
extern s32 misInputGetSLong( MisInput *input_ptr );
extern u32 misInputGetULong( MisInput *input_ptr );
extern float misInputGetFloat( MisInput *input_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros */
#define _misInputGet(input_ptr) ( (input_ptr)->get( (input_ptr) ) )

#define _misInputClose(input_ptr) ( (input_ptr)->close( (input_ptr) ) )

#define _misInputDestroy(input_ptr) { (input_ptr)->destroy( (input_ptr) ); }

#define _misInputSetStatus(input_ptr,status_bit) \
	{ (input_ptr)->status |= (status_bit); }

#define _misInputClearStatus(input_ptr,status_bit) \
	{ (input_ptr)->status &= ~(status_bit); }

#define _misInputIsOpened(input_ptr) \
	( (input_ptr)->status & MIS_INPUT_STATUS_OPEN_BIT )

#define _misInputIsEof(input_ptr) \
	( (input_ptr)->status & MIS_INPUT_STATUS_EOF_BIT )

#define _misInputIsFailure(input_ptr) \
	( (input_ptr)->status & MIS_INPUT_STATUS_FAILURE_BIT )

#define _misInputGetErrorStatus(input_ptr) \
	( (input_ptr)->status & ~MIS_INPUT_STATUS_OPEN_BIT )

#endif /* _mis_Input_h */
