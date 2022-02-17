/*
  mhc/NodeHandle.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 7, 1998.
*/

#ifndef _mhc_NodeHandle_h
#define _mhc_NodeHandle_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare constant value macros  */
#define MHC_NODE_HANDLE_NULL_INDEX	(0xFFFFFFFF)
#define MHC_NODE_HANDLE_EXTERN_BIT	(0x80000000)

/* Declare prototype structures  */
struct _MhcModule;
struct _MhcNode;
struct _MhcScene;

/* Declare type of structure */
typedef struct _MhcNodeHandle
{
    u32			index;
    struct _MhcNode	*node_ptr;
} MhcNodeHandle;

/* Declare functions */
extern void mhcNodeHandleBind( MhcNodeHandle *handle_ptr,
			       struct _MhcModule *module_ptr,
			       struct _MhcScene *scene_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros  */
#define _mhcNodeHandleInit(handle_ptr) \
{ \
    (handle_ptr)->index		= MHC_NODE_HANDLE_NULL_INDEX; \
    (handle_ptr)->node_ptr	= NULL; \
}

#define _mhcNodeHandleSetIndex(handle_ptr,idx) \
	{ (handle_ptr)->index = MHC_NODE_HANDLE_NULL_INDEX; }

#define _mhcNodeHandleIsExternal(handle_ptr) \
	( (handle_ptr)->index & MHC_NODE_HANDLE_EXTERN_BIT )

#endif /* _mhc_NodeHandle_h */
