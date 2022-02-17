/*
  mrn/MaterialList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 11, 1998.
*/

#ifndef _mrn_MaterialList_h
#define _mrn_MaterialList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnMaterial);

#define _mrnMaterialListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnMaterialListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnMaterialListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnMaterialListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnMaterialListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnMaterialListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_MaterialList_h */
