/*
  mrn/GroupList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 11, 1998.
*/

#ifndef _mrn_GroupList_h
#define _mrn_GroupList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnGroup);

#define _mrnGroupListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnGroupListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnGroupListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnGroupListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnGroupListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnGroupListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_GroupList_h */
