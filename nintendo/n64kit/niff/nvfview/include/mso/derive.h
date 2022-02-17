/*
  mso/derive.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Aug. 27, 1998.
*/

#ifndef _mso_derive_h
#define _mso_derive_h 1

/*
Macros which enables user to mount object's inheritance more easily. The derivatives may define the basic type as '_base##Base' member.
*/

/* Macro which defines 'base'. Should be used in the structure. */
#define _msoDeriveFrom(basetype) basetype _base##basetype

/* Macro which returns an offset of base as 'u8 ' unit. */
#define _msoBaseOffset(basetype,drvtype) \
	( ( u8 * )&( ( drvtype * )0 )->_base##basetype - ( u8 * )0 )

/* Macro which casts 'basetype' pointer ('ptr') into the derivative pointer. */
#define _msoDownCast(drvtype,basetype,ptr) \
	( ( drvtype * )( ( ( u8 * )(ptr) ) - \
			 _msoBaseOffset( basetype, drvtype ) ) )

/* Macro which casts a derivative pointer (ptr) into the 'basetype' pointer. */
#define _msoUpCast(basetype,ptr) ( &(ptr)->_base##basetype )

#endif /* _mso_derive_h */
