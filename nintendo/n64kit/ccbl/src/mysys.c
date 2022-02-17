/*
 * [CCBL]
 *
 * mysys.c
 *
 * Copyright (C) 1998, NINTENDO Co,Ltd.
 * Copyright (C) 1998, MONEGI CORPORATION.
 *
 */
#include "common_include.h"
#include <PR/ramrom.h>
#include <string.h>
#include "mysys.h"
#include <malloc.h>
#include "heap.h"


void Main(void );

void
mainproc(void )
{
  nuGfxInit();
  InitHeap((void *)system_heap,HEAP_LENGTH);
  Main();
  /* Halt -- actually not possible here */
  for(;;);
}


