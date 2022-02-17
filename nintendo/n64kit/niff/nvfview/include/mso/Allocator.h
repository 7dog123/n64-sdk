/*
  mso/Allocator.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 2, 1998.
*/

#ifndef _mso_Allocator_h
#define _mso_Allocator_h 1

#include <ultratypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Declare structures */
struct _MsoAllocator;
typedef void *( *MsoAllocatorAllocFunc )( struct _MsoAllocator *allocator_ptr,
					const u32 size, const u16 alignment );
typedef void ( *MsoAllocatorFreeFunc )( struct _MsoAllocator *allocator_ptr,
					void *mem_ptr );
typedef void ( *MsoAllocatorDestroyFunc )( struct _MsoAllocator *allocator_ptr
					 );

typedef struct _MsoAllocator
{
    MsoAllocatorAllocFunc	allocate;
    MsoAllocatorFreeFunc	free;
    MsoAllocatorDestroyFunc	destroy;
    u32				debug_cookie;
    u32				is_debug_mode;
} MsoAllocator;

/* Declare functions */
extern void msoAllocatorInit( MsoAllocator *allocator,
			      MsoAllocatorAllocFunc allocate,
			      MsoAllocatorFreeFunc free,
			      MsoAllocatorDestroyFunc destroy );
extern void msoAllocatorEnableDebugMode( MsoAllocator *allocator_ptr,
					 const u32 enable );
extern u32 msoAllocatorIsDebugMode( const MsoAllocator *allocator_ptr );
extern void msoAllocatorSetDebugCookie( MsoAllocator *allocator_ptr,
					const u32 cookie );
extern u32 msoAllocatorGetDebugCookie( const MsoAllocator *allocator_ptr );
extern void *msoAllocatorAllocate( MsoAllocator *allocator_ptr,
				   const u32 size );
extern void *msoAllocatorAllocateAligned( MsoAllocator *allocator_ptr,
					const u32 size, const u16 alignment );
extern void msoAllocatorFree( MsoAllocator *allocator_ptr, void *mem_ptr );

/* A special function which uses 'default allocator'. */
extern void msoSetDefaultAllocator( MsoAllocator *allocator_ptr );
extern MsoAllocator *msoGetDefaultAllocator( void );
extern void *msoMalloc( const u32 size );
extern void *msoMallocAligned( const u32 size, const u16 align );
extern void msoFree( void *mem_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_Allocator_h */
