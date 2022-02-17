/*
  mrn/TextureLutList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 11, 1998.
*/

#ifndef _mrn_TextureLutList_h
#define _mrn_TextureLutList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnTextureLut);

#define _mrnTextureLutListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnTextureLutListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnTextureLutListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnTextureLutListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnTextureLutListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnTextureLutListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_TextureLutList_h */
