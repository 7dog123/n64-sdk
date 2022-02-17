/*
  mhc/Reference.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Jan. 6, 1999.
*/

#ifndef _mhc_Reference_h
#define _mhc_Reference_h 1

#include "mhc/NodeHandle.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MHC_REFERENCE_TYPE_FLOAT	(0)
#define MHC_REFERENCE_TYPE_LONG		(1)

#define MHC_REFERENCE_RESOLVE		(1)
#define MHC_REFERENCE_ACTIVE		(2)

/* Declare prototype structure */
struct _MhcModule;
struct _MhcScene;

/* Declare types of a structure */
typedef void ( *MhcReferenceFunc )( void *dest_array, const void *src_array,
				    const u32 size );

typedef struct _MhcReference
{
    struct _MhcReference	*next_input_ptr;
    struct _MhcReference	*next_output_ptr;
    MhcNodeHandle		input_node_handle;
    MhcNodeHandle		output_node_handle;
    u8				input_type;
    u8				output_type;
    u8				flags;
    u8				size;
    u16				input_field_id;
    u16				input_index;
    u16				output_field_id;
    u16				output_index;
    void			*input_ptr;
    void			*output_ptr;
    MhcReferenceFunc		refer;
} MhcReference;

/* Declare Functions */
extern void mhcReferenceInit( MhcReference *reference_ptr, const u16 type,
							   const u16 size );

extern void mhcReferenceBind( MhcReference *reference_ptr,
		struct _MhcModule *module_ptr, struct _MhcScene *scene_ptr );

extern void mhcReferenceCopyValues( void *dest_array, const void *src_array,
				    const u32 size );
extern void mhcReferenceCopy3( void *dest_array, const void *src_array,
			       const u32 size );
extern void mhcReferenceCopy9( void *dest_array, const void *src_array,
			       const u32 size );
extern void mhcReferenceConvertI2F( void *dest_array, const void *src_array,
				    const u32 size );
extern void mhcReferenceConvertF2I( void *dest_array, const void *src_array,
				    const u32 size );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macro */
#define _mhcReferenceIsResolved(reference_ptr) \
	( (reference_ptr)->flags & MHC_REFERENCE_RESOLVE )

#define _mhcReferenceIsActive(reference_ptr) \
	( (reference_ptr)->flags & MHC_REFERENCE_ACTIVE )

#define _mhcReferenceActivate(reference_ptr) \
	( (reference_ptr)->flags |= MHC_REFERENCE_ACTIVE )

#define _mhcReferenceInactivate(reference_ptr) \
	( (reference_ptr)->flags &= ~MHC_REFERENCE_ACTIVE )

#define _mhcReferenceBeginEval(reference_ptr) \
	{ (reference_ptr)->flags &= ~MHC_REFERENCE_RESOLVE; }

#define _mhcReferenceResolve(reference_ptr,scene_ptr) \
{ \
    register MhcNode	*node_ptr; \
    if ( ( (reference_ptr)->input_ptr )&& \
	 !( (reference_ptr)->flags & MHC_REFERENCE_RESOLVE ) ) \
    { \
	node_ptr = (reference_ptr)->input_node_handle.node_ptr; \
	(reference_ptr)->flags |= MHC_REFERENCE_RESOLVE; \
	if ( !( --node_ptr->unresolve_count ) ) \
	{ \
	    mhcNodeResolve( node_ptr, (scene_ptr) ); \
	} \
	(reference_ptr)->refer( (reference_ptr)->input_ptr, \
				(reference_ptr)->output_ptr, \
				(reference_ptr)->size ); \
    } \
}

#endif /* _mhc_Reference_h */
