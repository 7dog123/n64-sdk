/*
 * truncate ---- Handmade Uty (not N64 source code)
 *
 */
#include "stdio.h"

int
main()
{
  FILE *rfp,*wfp;
  int i;

  printf(">> truncate boot segment <<\n");
  rfp = fopen("user_model","r");
  wfp = fopen("model.rom","w");

  fseek(rfp,0x1050L,SEEK_SET);
  for(;;){
    if((i = fgetc(rfp)) == EOF) break;
    fputc(i,wfp);
  }
  close(wfp);
  close(rfp);
  return 0;
}

