/*
  mrn/LightSetList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 11, 1998.
*/

#ifndef _mrn_LightSetList_h
#define _mrn_LightSetList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnLightSet);

#define _mrnLightSetListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnLightSetListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnLightSetListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnLightSetListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnLightSetListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnLightSetListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_LightSetList_h */
