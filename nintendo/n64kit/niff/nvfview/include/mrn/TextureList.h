/*
  mrn/TextureList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 16, 1998.
*/

#ifndef _mrn_TextureList_h
#define _mrn_TextureList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnTexture);

#define _mrnTextureListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnTextureListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnTextureListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnTextureListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnTextureListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnTextureListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_TextureList_h */
