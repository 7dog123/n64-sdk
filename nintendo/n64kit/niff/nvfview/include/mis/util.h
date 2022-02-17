/*
  mis/util.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 23, 1998.
*/

#ifndef _mis_util_h
#define _mis_util_h 1

#include "mis/Input.h"
#include "mvm/Matrix.h"
#include "mvm/Vector.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare functions */
extern u8 misInputReadVector2f( MisInput *input_ptr, MvmVector2f vector );
extern u8 misInputReadVector3f( MisInput *input_ptr, MvmVector3f vector );
extern u8 misInputReadVector4f( MisInput *input_ptr, MvmVector4f vector );

extern u8 misInputReadVector2sc( MisInput *input_ptr, MvmVector2sc vector );
extern u8 misInputReadVector3sc( MisInput *input_ptr, MvmVector3sc vector );
extern u8 misInputReadVector4sc( MisInput *input_ptr, MvmVector4sc vector );
extern u8 misInputReadVector2uc( MisInput *input_ptr, MvmVector2uc vector );
extern u8 misInputReadVector3uc( MisInput *input_ptr, MvmVector3uc vector );
extern u8 misInputReadVector4uc( MisInput *input_ptr, MvmVector4uc vector );

extern u8 misInputReadVector2ss( MisInput *input_ptr, MvmVector2ss vector );
extern u8 misInputReadVector3ss( MisInput *input_ptr, MvmVector3ss vector );
extern u8 misInputReadVector4ss( MisInput *input_ptr, MvmVector4ss vector );
extern u8 misInputReadVector2us( MisInput *input_ptr, MvmVector2us vector );
extern u8 misInputReadVector3us( MisInput *input_ptr, MvmVector3us vector );
extern u8 misInputReadVector4us( MisInput *input_ptr, MvmVector4us vector );

extern u8 misInputReadVector2sl( MisInput *input_ptr, MvmVector2sl vector );
extern u8 misInputReadVector3sl( MisInput *input_ptr, MvmVector3sl vector );
extern u8 misInputReadVector4sl( MisInput *input_ptr, MvmVector4sl vector );
extern u8 misInputReadVector2ul( MisInput *input_ptr, MvmVector2ul vector );
extern u8 misInputReadVector3ul( MisInput *input_ptr, MvmVector3ul vector );
extern u8 misInputReadVector4ul( MisInput *input_ptr, MvmVector4ul vector );

extern u8 misInputReadMatrix22f( MisInput *input_ptr, MvmMatrix22f matrix );
extern u8 misInputReadMatrix33f( MisInput *input_ptr, MvmMatrix33f matrix );
extern u8 misInputReadMatrix44f( MisInput *input_ptr, MvmMatrix44f matrix );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mis_util_h */
