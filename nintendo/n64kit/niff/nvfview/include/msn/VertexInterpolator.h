/*
  msn/VertexInterpolator.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 19, 1998.
*/

#ifndef _msn_VertexInterpolator_h
#define _msn_VertexInterpolator_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mif/ChunkParser.h"
#include "mso/Allocator.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros */
#define MSN_VERTEX_INTERPOLATOR_INTERP_CONSTANT	(0)
#define MSN_VERTEX_INTERPOLATOR_INTERP_LINEAR	(1)

/* Declare structures */
typedef struct _MsnVertexInterpolatorTable
{
    u16		interpolation_type;
    u16		number_of_keys;
    u32		key_size;
    float	*time_array;
    s16		*key_data;
} MsnVertexInterpolatorTable;

typedef struct _MsnVertexInterpolatorVertex
{
    u16	coord_index;
    u16	normal_index;
    u16	tex_coord_index;
} MsnVertexInterpolatorVertex;

typedef struct _MsnVertexInterpolator
{
    _msoDeriveFrom( MhcNode );
    MsnVertexInterpolatorTable	coord_table;
    MsnVertexInterpolatorTable	normal_table;
    MsnVertexInterpolatorTable	tex_coord_table;
    s16				*coord_array;
    s16				*normal_array;
    s16				*tex_coord_array;
    u32				segment;
    u32				number_of_vertices;
    MsnVertexInterpolatorVertex	*vertex_setup_table;
    Gfx				*gfx_array;
} MsnVertexInterpolator;

/* Declare functions */
extern void msnVertexInterpolatorInit( MsnVertexInterpolator *interpolator_ptr
				     );

/* Declare a global variable */
extern MifChunkParser gMsnVertexInterpolatorChunkParser;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare Macro */
#define _msnVertexInterpolatorTableInit(table_ptr) \
{ \
    (table_ptr)->interpolation_type	= 0;	\
    (table_ptr)->number_of_keys		= 0;	\
    (table_ptr)->key_size		= 0;	\
    (table_ptr)->time_array		= NULL;	\
    (table_ptr)->key_data		= NULL;	\
}

#define _msnVertexInterpolatorTableDestroy(table_ptr) \
{ \
    msoFree( (table_ptr)->time_array );	\
}

#endif /* _msn_VertexInterpolator_h */
