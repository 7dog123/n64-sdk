/*
  mhc/NodeList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 30, 1998.
*/

#ifndef _mhc_NodeList_h
#define _mhc_NodeList_h 1

#include "mso/BilistBase.h"
#include "mhc/Node.h"

_msoBilistBaseDefine(MhcNode);

#define _mhcNodeListBegin(list_ptr) _msoBilistBaseBegin(list_ptr)
#define _mhcNodeListEnd(list_ptr) _msoBilistBaseEnd(list_ptr)
#define _mhcNodeListIsEmpty(list_ptr) _msoBilistBaseIsEmpty(list_ptr)
#define _mhcNodeListInit(list_ptr) _msoBilistBaseInit(list_ptr)
#define _mhcNodeListInsert(list_ptr,node_ptr,new_node_ptr) \
	_msoBilistBaseInsert(list_ptr,node_ptr,new_node_ptr)
#define _mhcNodeListRemove(list_ptr,node_ptr) \
	_msoBilistBaseRemove(list_ptr,node_ptr)
#define _mhcNodeListPushFront(list_ptr,node_ptr) \
	_msoBilistBasePushFront(list_ptr,node_ptr)
#define _mhcNodeListPopFront(list_ptr) _msoBilistBasePopFront(list_ptr)
#define _mhcNodeListPushBack(list_ptr,node_ptr) \
	_msoBilistBasePushBack(list_ptr,node_ptr)
#define _mhcNodeListPopBack(list_ptr) _msoBilistBasePopBack(list_ptr)

#endif /* _mhc_NodeList_h */
