/*
 *	letters.h
 *
 *	Displays letters
 *
 *  Copyright (C) 1998-1999, NINTENDO Co.,Ltd.
 *  Copyright (C) 1998-1999, MONEGI CORPORATION
 */

#ifndef	_LETTERS
#define	_LETTERS

#include <ultra64.h>

static	unsigned char letter[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0, 0xf, 0xf, 0xf, 0x0, 0xf, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0xf, 0x0, 0xf, 0xf, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xf, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xff, 0xf0, 0xf0, 0x0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0xf, 0xf0, 0xff, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf0, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xf0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xff, 0xff, 0x0, 0x0, 0xf, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0xf, 0xff, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0xf0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xff, 0xff, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0,
	0x0, 0xff, 0xf0, 0x0, 0xf, 0xf0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0xf, 0x0, 0xf, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0xf, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf0, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0xf0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xff, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0xf, 0x0, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0xff, 0x0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xf0, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0xf, 0xff, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0xf, 0xf, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0xf, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xff, 0xf, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf, 0xff, 0x0, 0xf, 0xf, 0xf, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0xf, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf, 0xf, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0,
	0x0, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0xf, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xff, 0x0, 0x0, 0xf, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xf0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0xf, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0xf, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0xff, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0xf, 0xff, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0xff, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0xf0, 0xf, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0xf0, 0xf, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0xf, 0xf, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0,
	0xf, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0xf0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xf, 0x0, 0xf, 0xf0, 0xff, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0xf0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0xf, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0xf, 0xff, 0xff, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

static Gfx LettersInitDL[] = {
	gsSPSegment(0x0, 0x0),
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
	gsDPSetCombineKey(G_CK_NONE),

	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetColorDither(G_CD_DISABLE),
	gsDPSetBlendColor(0,0,0,0x01),

	gsDPSetTextureFilter(G_TF_POINT),
	gsDPSetTextureDetail(G_TD_CLAMP),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureLUT(G_TT_NONE),

	gsDPSetTexturePersp(G_TP_NONE),
	gsSPTexture(0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON),
	gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
	gsSPClearGeometryMode(0xffffffff),
	gsSPSetGeometryMode( G_SHADE|G_TEXTURE_ENABLE|G_ZBUFFER|G_SHADING_SMOOTH),
	gsDPLoadTextureTile_4b(&letter[0], G_IM_FMT_IA,
			  48, 128,
			  0, 0, 47, 127,
			  0,
			  G_TX_WRAP , G_TX_WRAP,
			  G_TX_NOMASK, G_TX_NOMASK,
			  G_TX_NOLOD, G_TX_NOLOD),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx *letters_init( Gfx *gp );
Gfx *letters_1_letter(Gfx *gp,short,short,unsigned char,u32);
Gfx *letters_set(Gfx *gp,short,short,unsigned char *letter,u32);
Gfx *letters_num( Gfx *gp,short,short,int,u32);
Gfx *letters_num_right( Gfx *gp,short,short,int,u32);
char	i2a(int,char *output);

#endif	/* _LETTERS */