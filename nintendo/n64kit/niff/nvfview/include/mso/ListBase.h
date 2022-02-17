/*
  mso/ListBase.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 22, 1998.
*/

#ifndef _mso_ListBase_h
#define _mso_ListBase_h 1

/*
 Macros which enable user to mount 'list' more easily.
In member, 'node' should have 'next_ptr' for the following pointer.
*/

#include <ultratypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define _msoListBaseDefine(nodetype) \
typedef struct _##nodetype##List \
{ \
    struct _##nodetype *head_ptr; \
} nodetype##List

#define _msoListBaseBegin(list_ptr) ( (list_ptr)->head_ptr )

#define _msoListBaseEnd(list_ptr) ( NULL )

#define _msoListBaseIsEmpty(list_ptr) ( (list_ptr)->head_ptr == NULL )

#define _msoListBaseInit(list_ptr) \
{ \
    (list_ptr)->head_ptr = NULL; \
}

#define _msoListBasePushFront(list_ptr,node_ptr) \
{ \
    (node_ptr)->next_ptr = (list_ptr)->head_ptr; \
    (list_ptr)->head_ptr = (node_ptr); \
}

#define _msoListBasePopFront(list_ptr) \
{ \
    if ( (list_ptr)->head_ptr ) \
	(list_ptr)->head_ptr = (list_ptr)->head_ptr->next_ptr; \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_ListBase_h */
