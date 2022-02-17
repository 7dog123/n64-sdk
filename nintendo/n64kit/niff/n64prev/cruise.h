/*======================================================================*/
/*		NIFFprev						*/
/*		cruise.h						*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*		Copyright (C) 1998, MONEGI CORPORATION.			*/
/*									*/
/*======================================================================*/
/* Revision History							*/
/*  1998/ 6/18	Added crSetupUPR, so that it is easier to switch 	*/
/*		from other mode.					*/
/*======================================================================*/
#ifndef __CRUISE_H
#define __CRUISE_H

/* ==========================================================================
	function
 ========================================================================== */
void crReset(void);
void crSetupYPR(struct _Transform *transform);
void crMove(EXCONTPAD *pad);
void crBuildMatrix(struct _Transform *transform);

#endif /* #ifndef __CRUISE_H */
