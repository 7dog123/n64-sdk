/*
  mhc/ExternalNode.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 7, 1998.
*/

#ifndef _mhc_ExternalNode_h
#define _mhc_ExternalNode_h 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare structures */
typedef struct _MhcExternalNode
{
    u32			module_id;
    const char		*node_name;
} MhcExternalNode;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* Declare macros */
#define _mhcExternalNodeInit(external_node_ptr) \
{ \
    (external_node_ptr)->module_id	= 0; \
    (external_node_ptr)->node_name	= NULL; \
}

#endif /* _mhc_ExternalNode_h */
