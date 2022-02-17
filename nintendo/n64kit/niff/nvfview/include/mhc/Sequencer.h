/*
  mhc/Sequencer.h
    Copyright (C) 1999, NINTENDO Co,Ltd., MONEGI CORPORATION.
    May 15, 1999.
*/

#ifndef _mhc_Sequence_h
#define _mhc_Sequence_h 1

#include "mhc/Node.h"
#include "mhc/NodeHandle.h"
#include "mhc/Scene.h"
#include "mrn/Scene.h"
#include "mrn/Screen.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <ultra64.h>

/* type prototype declaration */
struct _MhcSeqInst;
struct _MhcSequencer;

/* type declaration */
typedef void ( *MhcSequencerCallback )( struct _MhcSequencer *seq_ptr );
typedef struct _MhcSeqInst *( *MhcSequencerEndCallback )(
					struct _MhcSequencer *seq_ptr );

typedef struct _MhcSeqInst
{
    u32				animation;
    u32				interpolation;
    float			start;
    float			end;
    float			pitch;
    struct _MhcSeqInst		*next_ptr;
    MhcSequencerCallback	on_start;
    MhcSequencerEndCallback	on_end;
    MhcSequencerCallback	on_stop;
    MhcSequencerCallback	callback;
} MhcSeqInst;

typedef struct _MhcSequencer
{
    MhcSeqInst	*inst_ptr;
    float	time;
    float	*anim_index_ptr;
    float	*time_ptr;
    void	*user_data;
} MhcSequencer;

extern void mhcSequencerInit( MhcSequencer *seq_ptr,
			      float *index_ptr, float *time_ptr,
			      void *user_data );
extern void mhcSequencerExecute( MhcSequencer *seq_ptr, MhcSeqInst *inst_ptr );
extern void mhcSequencerProgress( MhcSequencer *seq_ptr, const float step );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mhc_Sequence_h */
