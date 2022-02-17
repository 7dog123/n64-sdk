/*
  mrn/util.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Sep. 22, 1998.
*/

#ifndef _mrn_util_h
#define _mrn_util_h 1

/* Declare macros */
#define _mrnGfxCopy(dest_ptr,src_ptr) \
{\
    (dest_ptr)->words.w0 = (src_ptr)->words.w0;	\
    (dest_ptr)->words.w1 = (src_ptr)->words.w1;	\
}

#endif /* _mrn_util_h */
