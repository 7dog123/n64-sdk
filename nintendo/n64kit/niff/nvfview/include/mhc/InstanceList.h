/*
  mhc/InstanceList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 8, 1998.
*/

#ifndef _mhc_InstanceList_h
#define _mhc_InstanceList_h 1

#include "mso/BilistBase.h"
#include "mhc/Instance.h"

_msoBilistBaseDefine(MhcInstance);

#define _mhcInstanceListBegin(list_ptr) _msoBilistBaseBegin(list_ptr)
#define _mhcInstanceListEnd(list_ptr) _msoBilistBaseEnd(list_ptr)
#define _mhcInstanceListIsEmpty(list_ptr) _msoBilistBaseIsEmpty(list_ptr)
#define _mhcInstanceListInit(list_ptr) _msoBilistBaseInit(list_ptr)
#define _mhcInstanceListInsert(list_ptr,node_ptr,new_node_ptr) \
	_msoBilistBaseInsert(list_ptr,node_ptr,new_node_ptr)
#define _mhcInstanceListRemove(list_ptr,node_ptr) \
	_msoBilistBaseRemove(list_ptr,node_ptr)
#define _mhcInstanceListPushFront(list_ptr,node_ptr) \
	_msoBilistBasePushFront(list_ptr,node_ptr)
#define _mhcInstanceListPopFront(list_ptr) _msoBilistBasePopFront(list_ptr)
#define _mhcInstanceListPushBack(list_ptr,node_ptr) \
	_msoBilistBasePushBack(list_ptr,node_ptr)
#define _mhcInstanceListPopBack(list_ptr) _msoBilistBasePopBack(list_ptr)
#define _mhcInstanceListPushListFront(list_ptr,node_ptr) \
	_msoBilistBasePushListFront(list_ptr,node_ptr)
#define _mhcInstanceListPushListBack(list_ptr,node_ptr) \
	_msoBilistBasePushListBack(list_ptr,node_ptr)

#endif /* _mhc_InstanceList_h */
