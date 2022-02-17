[ How to compile so F3DEX2 micro code is used]
1. Method to rewrite Makefile  
   First, perform make clean.  
   Next, change the definition of Makefile or the variable GBI of Makefile.win.  

   If F3DEX is used, change as below:
      
     GBI =		F3DEX_GBI

   If F3DEX2 is used, change as below:

     GBI =		F3DEX_GBI_2

   

2. Method not to rewrite Makefile  
   Specify the value of a variable GBI directly in a command line. 

   If F3DEX is used, execute as below: 
     <WINDOWS>
       make clean
       make GBI=F3DEX_GBI -fMakefile.win

     <SGI>
       make clean
       make GBI=F3DEX_GBI -fMakefile

   If F3DEX2 is used, execute as below:

     <WINDOWS>
       make clean
       make GBI=F3DEX_GBI_2 -fMakefile.win

     <SGI>
       make clean
       make GBI=F3DEX_GBI_2 -fMakefile

    

In either method,  NuSYS also needs to be compiled for F3DEX2 in order to use F3DEX 2 by n64prev.   

Refer to NTSC-ONLINE for how to compile NuSYS for F3DEX2, or details of F3DEX2.  

				Copyright (C) 1997, 1998, NINTENDO Co,Ltd.
				Copyright (C) 1998, MONEGI CORPORATION.
