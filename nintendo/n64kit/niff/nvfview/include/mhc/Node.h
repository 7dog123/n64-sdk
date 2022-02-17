/*
  mhc/Node.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Nov. 25, 1998.
*/

#ifndef _mhc_Node_h
#define _mhc_Node_h 1

#include "mhc/InstanceList.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant macro */
#define MHC_NODE_CAMERA_DEPENDENCY_BIT	(1)
#define MHC_NODE_ACTIVE_BIT		(2)

/* Declare prototype structure */
struct _MhcInstance;
struct _MhcModule;
struct _MhcNode;
struct _MhcReference;
struct _MhcScene;

/* Declare types of a structure */
typedef void ( *MhcNodeEvalFunc )( struct _MhcInstance *instance_ptr,
				   struct _MhcScene *scene_ptr );
typedef void ( *MhcNodeDestroyFunc )( struct _MhcNode *node_ptr );
typedef void *( *MhcNodeGetFieldPtrFunc )( struct _MhcNode *node_ptr,
					const int field_id, const int index );
typedef void ( *MhcNodeBindFunc )( struct _MhcNode *node_ptr,
		struct _MhcModule *module_ptr, struct _MhcScene *scene_ptr );

typedef struct _MhcNode
{
    struct _MhcNode		*next_ptr;
    struct _MhcNode		*prev_ptr;
    u32				type;
    char			*name;
    u8				flags;
    u8				group_index;	/* set only nodes for camera */
    u8				unresolve_count;
    u8				input_count;
    struct _MhcReference	*input_head_ptr;
    struct _MhcReference	*output_head_ptr;
    MhcInstanceList		instance_list;
    MhcNodeEvalFunc		evaluate;
    MhcNodeBindFunc		bind;
    MhcNodeGetFieldPtrFunc	get_field_ptr;
    MhcNodeDestroyFunc		destroy;
} MhcNode;

/* Declare Functions */
extern void mhcNodeInit( MhcNode *node_ptr,
			 const u32 type,
			 MhcNodeEvalFunc evaluate,
			 MhcNodeGetFieldPtrFunc get_field_ptr,
			 MhcNodeBindFunc bind,
			 MhcNodeDestroyFunc destroy );

extern int mhcNodeIsReadyToEvaluate( MhcNode *node_ptr,
				     struct _MhcScene *scene_ptr );

extern void mhcNodeComplete( MhcNode *node_ptr, struct _MhcScene *scene_ptr );

extern void mhcNodeAddInput( MhcNode *node_ptr,
			     struct _MhcReference *input_ptr );

extern void mhcNodeRemoveInput( MhcNode *node_ptr,
				struct _MhcReference *input_ptr );

extern void mhcNodeAddOutput( MhcNode *node_ptr,
			      struct _MhcReference *output_ptr );

extern void mhcNodeRemoveOutput( MhcNode *node_ptr,
				 struct _MhcReference *input_ptr );

extern void mhcNodeResolve( MhcNode *node_ptr, struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macro */
#define _mhcNodeActivate(node_ptr) \
	{ (node_ptr)->flags |= MHC_NODE_ACTIVE_BIT; }

#define _mhcNodeInactivate(node_ptr) \
	{ (node_ptr)->flags &= ~MHC_NODE_ACTIVE_BIT; }

#define _mhcNodeIsActive(node_ptr) ( (node_ptr)->flags & MHC_NODE_ACTIVE_BIT )

#define _mhcNodeIsReady(node_ptr) ( (node_ptr)->unresolve_count == 0 )

#define _mhcNodeSetName(node_ptr,name_str) { (node_ptr)->name = (name_str); }

#define _mhcNodeEvaluate(node_ptr,instance_ptr,scene_ptr) \
{ \
    (node_ptr)->evaluate( (instance_ptr), (scene_ptr) );	\
}

#define _mhcNodeGetFieldPtr(node_ptr,f_id,idx) \
	( (node_ptr)->get_field_ptr( (node_ptr), (f_id), (idx) ) )

#define _mhcNodeBind(node_ptr,module_ptr,scene_ptr) \
{ \
    (node_ptr)->bind( (node_ptr), (module_ptr), (scene_ptr) );	\
}

#define _mhcNodeDestroy(node_ptr) { (node_ptr)->destroy( (node_ptr) ); }

#define _mhcNodeBeginEval(node_ptr) \
	{ (node_ptr)->unresolve_count = (node_ptr)->input_count; }

#endif /* _mhc_Node_h */
