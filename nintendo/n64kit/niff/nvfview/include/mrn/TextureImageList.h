/*
  mrn/TextureImageList.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 11, 1998.
*/

#ifndef _mrn_TextureImageList_h
#define _mrn_TextureImageList_h 1

#include "mso/ListBase.h"

_msoListBaseDefine(MrnTextureImage);

#define _mrnTextureImageListBegin(list_ptr) _msoListBaseBegin(list_ptr)
#define _mrnTextureImageListEnd(list_ptr) _msoListBaseEnd(list_ptr)
#define _mrnTextureImageListIsEmpty(list_ptr) _msoListBaseIsEmpty(list_ptr)
#define _mrnTextureImageListInit(list_ptr) _msoListBaseInit(list_ptr)
#define _mrnTextureImageListPushFront(list_ptr,node_ptr) \
	_msoListBasePushFront(list_ptr,node_ptr)
#define _mrnTextureImageListPopFront(list_ptr) _msoListBasePopFront(list_ptr)

#endif /* _mrn_TextureImageList_h */
