/**********************************************************************
 *  Sample Program to use NIFFAPI 
 * 
 * Write the NIFF binary file, file1 into a text file, file2, and read and
 * write file2 into the NIFF binary file, file3 using sample file1 file2 file3.
 *  
 ***********************************************************************/
/* $Id: sample.c,v 1.2 1999/01/20 07:21:50 yoshino Exp $ */
#include    "niffapi.h"

int
main(int argc, char *argv[])
{
  Nis *nis = niNewNis(nis);	/* initialize */
  Nis *nis2 = niNewNis(nis2);	/* initialize */

  if(argc != 4 
     || strcmp(argv[1],"-h") == 0
     || strcmp(argv[1],"-help") == 0)
  {
      fprintf(stderr,"Usage:\tsample file1 file2 file3\n");
      fprintf(stderr,"      \tfile1 is an input NIFF binary file.\n");
      fprintf(stderr,"      \tfile2 is an output text file.\n");
      fprintf(stderr,"      \tfile3 is an output NIFF binary file.\n");
      exit(-1);
  }
    
/* NIFF binary read */
  printf("read NIFF binary file.\n");
  printf("%s\n",(niOpenNb(argv[1],nis) ? "Read OK" : "Read Error."));
  printf("%x\n", nis->fh->version);
  printf("%d\n", nis->fh->file_size);

/* NIFF text write */
  printf("write NIFF text file.\n");
  niSaveAsNt(nis, argv[2]);

/* NIFF text read */
  printf("read NIFF text file.\n");
  printf("%s\n",(niOpenNt(argv[2], nis2) ? "OK" : "ERR"));

/* NIFF binary read */
  printf("write NIFF binary file.\n");
  niSaveAsNb(nis2, argv[3]);
}
