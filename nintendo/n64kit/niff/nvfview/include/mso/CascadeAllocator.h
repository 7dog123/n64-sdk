/*
  mso/CascadeAllocator.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 4, 1998.
*/

#ifndef _mso_CascadeAllocator_h
#define _mso_cascadeAllocator_h 1

#include "mso/Allocator.h"
#include "mso/Allocator.h"
#include "mso/ListBase.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultratypes.h>

/* Declare a constant value macro */
#define MSO_CASCADE_ALLOCATOR_MAX_CHILDREN	(2)

/* Declare structures */
typedef struct _MsoAllocatorInfo
{
    MsoAllocator	*alloc_ptr;
    u32			start_addr, end_addr;
} MsoAllocatorInfo;

typedef struct _MsoCascadeAllocator
{
    _msoDeriveFrom( MsoAllocator );
    MsoAllocatorInfo	child_array[ MSO_CASCADE_ALLOCATOR_MAX_CHILDREN ];
} MsoCascadeAllocator;

/* Declare functions */
extern void msoCascadeAllocatorInit( MsoCascadeAllocator *cascade_alloc_ptr,
				     MsoAllocator *primary_ptr,
				     const u32 primary_start_addr,
				     const u32 primary_end_addr,
				     MsoAllocator *secondary_ptr,
				     const u32 secondary_start_addr,
				     const u32 secondary_end_addr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_CascadeAllocator_h */
