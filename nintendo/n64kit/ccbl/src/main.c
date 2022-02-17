/*
 * [CCBL]
 *
 * main.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include "mysys.h"
#include "graphics.h"
#include "pad.h"
#include "model_out.h"
#include "rcp_reg.h"
#include "cam.h"
#include "window.h"
#include "menu.h"
#include "light.h"
#include "rom_reg.h"
#include "ccbl_host.h"

void test_gtask(int );
void makeScreen(void);
void start_gtask(int );
void test_gtask(int );


void Main(void )
{

  init_gtask();
  init_pad();			/* Initialize pad utility. */
  initCam();			/* Initialize camera system. */
  cwInitWindowSystem();	/* Initialize menu manager. */
  menuInit();			/* Initialize menu bar creation. */
  init_light_sys();
  load_modelseg();
  init_rcpreg(&rcp_regs);	/* !!!! Call here to be certain. !!!! */
  init_ccbl_hostio();
  
#if 1
  for(;;){
    get_pad();
    makeScreen();
  }
#endif
  /* Halt */
  for(;;);
  /* not reached */
}


extern void onetri(void );
extern int micro_code;

void
makeScreen(void )
{
  extern void model_out(void );
  extern void hostio_test_code(void);

  ccbl_hostio_main();
  gfxSetupFirst();
  micro_code = 0;
  cwWindowMain();
  model_out();
  hostio_test_code();
  
  request_gtask();		/* Retrace Wait */

}

