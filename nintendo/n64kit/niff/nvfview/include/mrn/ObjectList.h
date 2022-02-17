/*
  mrn/ObjectList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 10, 1998.
*/

#ifndef _mrn_ObjectList_h
#define _mrn_ObjectList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnObject);

#define _mrnObjectListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnObjectListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnObjectListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnObjectListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnObjectListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnObjectListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_ObjectList_h */
