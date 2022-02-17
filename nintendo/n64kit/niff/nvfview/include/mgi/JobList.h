/*
  mgi/JobList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 30, 1998.
*/

#ifndef _mgi_JobList_h
#define _mgi_JobList_h 1

#include "mso/BilistBase.h"
#include "mgi/Job.h"

_msoBilistBaseDefine(MgiJob);

#define _mgiJobListBegin(list_ptr) _msoBilistBaseBegin(list_ptr)
#define _mgiJobListEnd(list_ptr) _msoBilistBaseEnd(list_ptr)
#define _mgiJobListIsEmpty(list_ptr) _msoBilistBaseIsEmpty(list_ptr)
#define _mgiJobListInit(list_ptr) _msoBilistBaseInit(list_ptr)
#define _mgiJobListInsert(list_ptr,node_ptr,new_node_ptr) \
	_msoBilistBaseInsert(list_ptr,node_ptr,new_node_ptr)
#define _mgiJobListRemove(list_ptr,node_ptr) \
	_msoBilistBaseRemove(list_ptr,node_ptr)
#define _mgiJobListPushFront(list_ptr,node_ptr) \
	_msoBilistBasePushFront(list_ptr,node_ptr)
#define _mgiJobListPopFront(list_ptr) _msoBilistBasePopFront(list_ptr)
#define _mgiJobListPushBack(list_ptr,node_ptr) \
	_msoBilistBasePushBack(list_ptr,node_ptr)
#define _mgiJobListPopBack(list_ptr) _msoBilistBasePopBack(list_ptr)
#define _mgiJobListPushListFront(list_ptr,node_ptr) \
	_msoBilistBasePushListFront(list_ptr,node_ptr)
#define _mgiJobListPushListBack(list_ptr,node_ptr) \
	_msoBilistBasePushListBack(list_ptr,node_ptr)

#endif /* _mgi_JobList_h */
