/*======================================================================*/
/*		NIFFprev						*/
/*		tbmove.h						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
#ifndef __TBMOVE_H
#define __TBMOVE_H

/* ==========================================================================
	function
 ========================================================================== */
struct _Transform;
void tbReset(void);
void tbEmulate(EXCONTPAD *pad, struct _Transform *transform);
void tbBuildMatrix(struct _Transform *transform);

#endif /* #ifndef __TBMOVE_H */
