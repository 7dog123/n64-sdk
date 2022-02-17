/*
  mso/BilistBase.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 13, 1998.
*/

#ifndef _mso_BilistBase_h
#define _mso_BilistBase_h 1

/*
Macros which enable user to mount the bi-directional list more easily.
In member, 'node' should have 'next_ptr' for the following pointer, and have 'prev_ptr' for the previous pointer. Also, node types should be defined prior to listing.
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define _msoBilistBaseDefine(nodetype) \
typedef struct _##nodetype##List \
{ \
    nodetype	null;	\
} nodetype##List

#define _msoBilistBaseBegin(list_ptr) ( (list_ptr)->null.next_ptr )

#define _msoBilistBaseEnd(list_ptr) ( &(list_ptr)->null )

#define _msoBilistBaseIsEmpty(list_ptr) \
	( (list_ptr)->null.next_ptr == &(list_ptr)->null )

#define _msoBilistBaseInit(list_ptr) \
{ \
    (list_ptr)->null.next_ptr = (list_ptr)->null.prev_ptr = \
						&(list_ptr)->null; \
}

#define _msoBilistBaseInsert(list_ptr,node_ptr,new_node_ptr) \
{ \
    (new_node_ptr)->next_ptr = (node_ptr); \
    (new_node_ptr)->prev_ptr = (node_ptr)->prev_ptr; \
    (node_ptr)->prev_ptr->next_ptr = (new_node_ptr); \
    (node_ptr)->prev_ptr = (new_node_ptr); \
}

#define _msoBilistBaseRemove(list_ptr,node_ptr) \
{ \
    (node_ptr)->prev_ptr->next_ptr = (node_ptr)->next_ptr; \
    (node_ptr)->next_ptr->prev_ptr = (node_ptr)->prev_ptr; \
}

#define _msoBilistBasePushFront(list_ptr,node_ptr) \
{ \
    (node_ptr)->next_ptr = (list_ptr)->null.next_ptr; \
    (node_ptr)->prev_ptr = &(list_ptr)->null; \
    (list_ptr)->null.next_ptr->prev_ptr = (node_ptr); \
    (list_ptr)->null.next_ptr = (node_ptr); \
}

#define _msoBilistBasePushBack(list_ptr,node_ptr) \
{ \
    (node_ptr)->next_ptr = &(list_ptr)->null; \
    (node_ptr)->prev_ptr = (list_ptr)->null.prev_ptr; \
    (list_ptr)->null.prev_ptr->next_ptr = (node_ptr); \
    (list_ptr)->null.prev_ptr = (node_ptr); \
}

#define _msoBilistBasePushListFront(list_ptr,push_list_ptr) \
{ \
    if ( !_msoBilistBaseIsEmpty(push_list_ptr) ) \
    { \
	(push_list_ptr)->null.next_ptr->prev_ptr = &(list_ptr)->null; \
	(push_list_ptr)->null.prev_ptr->next_ptr = (list_ptr)->null.next_ptr;\
	(list_ptr)->null.next_ptr->prev_ptr = (push_list_ptr)->null.prev_ptr; \
	(list_ptr)->null.next_ptr = (push_list_ptr)->null.next_ptr; \
	(push_list_ptr)->null.next_ptr = &(push_list_ptr)->null; \
	(push_list_ptr)->null.prev_ptr = &(push_list_ptr)->null; \
    } \
}

#define _msoBilistBasePushListBack(list_ptr,push_list_ptr) \
{ \
    if ( !_msoBilistBaseIsEmpty(push_list_ptr) ) \
    { \
	(push_list_ptr)->null.next_ptr->prev_ptr = (list_ptr)->null.prev_ptr;\
	(push_list_ptr)->null.prev_ptr->next_ptr = &(list_ptr)->null; \
	(list_ptr)->null.prev_ptr->next_ptr = (push_list_ptr)->null.next_ptr; \
	(list_ptr)->null.prev_ptr = (push_list_ptr)->null.prev_ptr; \
	(push_list_ptr)->null.next_ptr = &(push_list_ptr)->null; \
	(push_list_ptr)->null.prev_ptr = &(push_list_ptr)->null; \
    } \
}

#define _msoBilistBasePopFront(list_ptr) \
{ \
    (list_ptr)->null.next_ptr->next_ptr->prev_ptr = &(list_ptr)->null; \
    (list_ptr)->null.next_ptr = (list_ptr)->null.next_ptr->next_ptr; \
}

#define _msoBilistBasePopBack(list_ptr) \
{ \
    (list_ptr)->null.prev_ptr->prev_ptr->next_ptr = &(list_ptr)->null; \
    (list_ptr)->null.prev_ptr = (list_ptr)->null.prev_ptr->prev_ptr; \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mso_BilistBase_h */
