/*
  mgi/Character.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Dec. 18, 1998.
*/

#ifndef _mgi_Character_h
#define _mgi_Character_h 1

#include "mgi/Job.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MgiCharacter;
struct _MgiControl;
struct _MhcModule;

/* Declare type of structures  */
typedef struct _MgiCharacter
{
    MgiJob			job;

    struct _MhcModule		*module_ptr;

    u32				number_of_controls;
    struct _MgiControl		*control_array;

    void			*user_data;
} MgiCharacter;

/* Declare functions */
extern void mgiCharacterInit( MgiCharacter *char_ptr, MgiJobCallback callback,
			      void *user_data );

extern void mgiCharacterActivate( MgiCharacter *char_ptr );

extern void mgiCharacterInactivate( MgiCharacter *char_ptr );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mgi_Character_h */
