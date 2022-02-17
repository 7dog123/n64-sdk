/*
  mso/HeapAllocator.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 5, 1998.
*/

#ifndef _mso_HeapAllocator_h
#define _mso_heapAllocator_h 1

#include "mso/Allocator.h"
#include "mso/ListBase.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultratypes.h>

/* Declare structures */
typedef struct _MsoHeapAllocator
{
    _msoDeriveFrom( MsoAllocator );
    void			*heap_ptr;
    u32				heap_size;
    u32				number_of_pages;
    u32				max_threads;
    u32				number_of_threads;
    u16				*page_map;
    void			*thread_info_array;
    void			*page_array;
} MsoHeapAllocator;

/* Declare functions */
extern void msoHeapAllocatorInit( MsoHeapAllocator *heap_alloc_ptr,
				  void *heap_ptr, const u32 size );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_HeapAllocator_h */
