/*
  msn/EnvelopeVertex.h
    Copyright (C) 1998-1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Apr. 5, 1999.
*/

#ifndef _msn_EnvelopeVertex_h
#define _msn_EnvelopeVertex_h 1

#include "mvm/Vector.h"
#include "mvm/Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype */
struct _MsnEnvelopeGeometry;
struct _MsnEnvelopeVertexN;

/* Declare type */
typedef struct _MsnEnvelopeVertexRigidGroup
{
    u16	joint_index;
    u16	number_of_vertices;
    Vtx	*vtx_array;
} MsnEnvelopeVertexRigidGroup;

typedef struct _MsnEnvelopeVertexCVertex
{
    u32 coord_index;
    u32	packed_color;
    u16	s;
    u16	t;
} MsnEnvelopeVertexCVertex;

typedef struct _MsnEnvelopeVertexNVertex
{
    u16	coord_index;
    u16	normal_index;
    u16	s;
    u16	t;
} MsnEnvelopeVertexNVertex;

typedef union _MsnEnvelopeVertexSetupTable
{
    MsnEnvelopeVertexCVertex	*c_array;
    MsnEnvelopeVertexNVertex	*n_array;
} MsnEnvelopeVertexSetupTable;

typedef struct _MsnEnvelopeVertexMorphGroup
{
    u16				joint_index[ 2 ];
    u16				number_of_vertices;
    u16				number_of_coords;
    u16				number_of_normals;
    u16				table_size;
    u16				vertex_offset;

    MvmVector3ss		*coord_table;
    MvmVector3sc		*normal_table;
    MsnEnvelopeVertexSetupTable	setup_table;
} MsnEnvelopeVertexMorphGroup;

typedef struct _MsnEnvelopeVertexCoord
{
    u32			coord_index;
    MvmVector3ss	coord;
    u16			weight;
} MsnEnvelopeVertexCoord;

typedef struct _MsnEnvelopeVertexNormal
{
    u16			normal_index;
    MvmVector3ss	normal;
} MsnEnvelopeVertexNormal;

typedef struct _MsnEnvelopeVertexJointTable
{
    u32				joint_index;
    u16				number_of_coords;
    u16				number_of_normals;
    MsnEnvelopeVertexCoord	*coord_array;
    MsnEnvelopeVertexNormal	*normal_array;
} MsnEnvelopeVertexJointTable;

typedef struct _MsnEnvelopeVertexCombineGroup
{
    u16				number_of_vertices;
    u16				number_of_joints;
    u16				number_of_coords;
    u16				number_of_normals;
    u32				vertex_offset;

    MsnEnvelopeVertexJointTable	*table_array;
    MsnEnvelopeVertexSetupTable	setup_table;
} MsnEnvelopeVertexCombineGroup;

typedef struct _MsnEnvelopeVertex
{
    u32					segment;
    u16					number_of_joints;
    u16					number_of_rigid_groups;
    u16					number_of_morph_groups;
    u16					number_of_combine_groups;
    u16					number_of_matrices;
    u16					number_of_vertices;

    MsnEnvelopeVertexRigidGroup		*rigid_group_array;
    MsnEnvelopeVertexMorphGroup		*morph_group_array;
    MsnEnvelopeVertexCombineGroup	*combine_group_array;

    u32					vector_size;
    void				*vector_buffer;

    u32					segment_base;
    Gfx					*gfx_array;
} MsnEnvelopeVertex;

/* Declare functions */
extern void msnGenerateMtx( Mtx *mtx_ptr,
			    const MvmMatrix33f orientation,
			    const MvmVector3f position,
			    const MvmVector3f scale );
extern void msnGenerateTranslationMtx( Mtx *mtx_ptr,
			const float x, const float y, const float z );
extern void msnEnvelopeVertexInit( MsnEnvelopeVertex *env_ptr );
extern void msnEnvelopeVertexInit( MsnEnvelopeVertex *env_ptr );
extern void msnEnvelopeVertexDestroy( MsnEnvelopeVertex *env_ptr );
extern int msnEnvelopeVertexReadHeader( MsnEnvelopeVertex *env_ptr,
					struct _MisInput *input_ptr );
extern int msnEnvelopeVertexReadRigidGroups( MsnEnvelopeVertex *env_ptr,
					     struct _MisInput *input_ptr );
extern int msnEnvelopeVertexReadVertexGroups( MsnEnvelopeVertex *env_ptr,
					struct _MisInput *input_ptr );
extern void msnEnvelopeVertexNEvaluateCombineGroup(
		MsnEnvelopeVertexCombineGroup *group_ptr,
		struct _MsnEnvelopeGeometry *geometry_ptr,
		Mtx *mtx_ptr,
		Vtx *vtx_array,
		void *vector_buffer );
extern void msnEnvelopeVertexNEvaluateCombineGroups(
		struct _MsnEnvelopeVertexN *env_ptr,
		struct _MsnEnvelopeGeometry *geometry_ptr,
		Mtx *mtx_ptr,
		Vtx *vtx_array );
extern void msnEnvelopeVertexCombineCoords( MvmVector3f *coord_array,
			const MvmMatrix33f orientation,
			const float tx,
			const float ty,
			const float tz,
			const MsnEnvelopeVertexCoord *coord_table_array,
			const int number_of_coords );
extern void msnEnvelopeVertexCombineNormals( MvmVector3f *normal_array,
			const MvmMatrix33f orientation,
			const MsnEnvelopeVertexNormal *normal_table_array,
			const int number_of_normals );
extern void msnEnvelopeVertexInitMorphGroup(
			MsnEnvelopeVertexMorphGroup *group_ptr );
extern void msnEnvelopeVertexInitCombineGroup(
			MsnEnvelopeVertexCombineGroup *group_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _msn_EnvelopeVertex_h */
