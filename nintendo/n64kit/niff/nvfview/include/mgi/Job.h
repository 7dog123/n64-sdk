/*
  mgi/Job.h
    Copyright (C) 1998, NINTENDO Co,Ltd., MONEGI CORPORATION.
    Oct. 29, 1998.
*/

#ifndef _mgi_Job_h
#define _mgi_Job_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mso/derive.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* Declare prototype structures */
struct _MgiApp;
struct _MgiJob;

/* Declare type of structures */
typedef void ( *MgiJobCallback )( struct _MgiJob *job_ptr,
				  struct _MgiApp *app_ptr );

typedef struct _MgiJob
{
    struct _MgiJob	*next_ptr;
    struct _MgiJob	*prev_ptr;
    MgiJobCallback	callback;
    void		*user_data;
} MgiJob;

/* Declare functions */
extern void mgiJobInit( MgiJob *job_ptr, MgiJobCallback callback,
					 void *user_data );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mgi_Job_h */
