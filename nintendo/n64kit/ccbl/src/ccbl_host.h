/*
 * [CCBL]
 *
 * ccbl_host.h
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#ifndef _CCBL_HOST_H_
#define _CCBL_HOST_H_

#define CCBL_COMMAND_IDEL 0x00
#define CCBL_COMMAND_DONE 0x01
#define CCBL_COMMAND_FAIL 0x02

#define CCBL_DATA_TO_TARGET 0x10
#define CCBL_DATA_FROM_TARGET 0x11

#define CCBL_NIFF_GBI_TO_TARGET 0x20
#define CCBL_TEXTURE_TO_TARGET 0x21
#define CCBL_BG_MODEL_TO_TARGET 0x22

#define CCBL_GBITEXT_FROM_TARGET 0x30
#define CCBL_GBITEXT_S_FROM_TARGET 0x31
/* ----- */
extern void init_ccbl_hostio(void);
extern void ccbl_hostio_main(void);
#endif /* !_CCBL_HOST_H_ */

