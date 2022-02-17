Copyright (C) 1998 NINTENDO Co.,Ltd.
Copyright (C) 1998 MONEGI CORPORATION	


Files in this directory:
readme.txt	this file
quickprev.n64	ROM image(sample) for drawing
star.niff	NIFF data used to create above ROM image   
clean.bin	data for initializing  

Quick Preview Guide (8/22/98)

1. Overview of quickpreview  

With the n64prev Previewer function, a NINTENDO64 ROM image was created by compiling a C source file using the niff2gfx converter in the /64prev directory. The compiled file was then loaded to either an emulator board or IS-VIEWER for viewing.

With quickpreview you no longer need to compile the file before previewing. The first time quickpreview is used, a ROM image for drawing file is loaded and then only the binary data of the model created by niff2gfx is sent to a specified address. Since the file does not need to be compiled, previewing can be done quicker.
  
Caution
In order to perform quickpreview using IS-VIEWER, you must acquire version 1.02t of nload which can handle data which was not makemask. 


2. Create a ROM image for drawing

A ROM image for drawing can be created by compiling model.c from the /n64prev directory, in the same manner as the former preview. The ROM image resulting from the compile will be named "nuprev.n64" for the Windows version of the software, and "rom" for the SGI version, The resulting image can be used for drawing. The file name can be changed as needed.
 
model.c is data created by niff2gfx. Please create it from a sample, niff data, etc. 
When quickpreview model data is initialized, or when quickpreview fails, model.c data is displayed.    

When nd (the object manager for drawing) is tuned up, be sure to update the ROM image for drawing.  

3. Executing quickpreview

The procedure for executing quickpreview follows: 

   (1) Load the ROM image for drawing. 
   (2) Convert niff data for drawing to a binary model data.  
   (3) Load the binary model data created in step 2 above, to the address 0x200000.

The ROM image (referred to in step #1 above) need only be loaded one time. After that you can preview images by following steps 2 and 3.  

Specific commands for the emulator board and IS-VIEWER respectively, are illustrated below.  In the following example, the ROM image for drawing is quickprev.n64, niff data to be previewed is niffprev.nif, and binary model data is model.bin.   
 
Emulator board
   (1) gload -s quickprev.n64
   (2) niff2gfx -b niffprev.nif model.bin 
   (3) gload -s -o0x200000 model.bin

IS-VIEWER
   (1) nload -n -v quickprev.n64
   (2) niff2gfx(.exe) -b niffprev.nif model.bin 
   (3) nload -n -v -s0x200000 model.bin

Note:  Please add an argument for niff2gfx(.exe) as needed.

If "IMPORT" is displayed in the upper right portion of the screen, then quickpreview is being performed.  

4. Initializing quickpreview

Even with the availability of quickpreview, there may be times when you would like to use the former preview process. With n64prev previewer, if model data exist in the address 0x200000, that model data will be previewed. Therefore, it may not be possible to preview model data created by model.c. To avoid this problem, delete the model data in address 0x200000 before previewing (with the former compile & preview.) Deleting the model.c data initializes quickpreview.
   
Previewer recognizes the model data of address 0x200000 when 4bytes from the address 0x200000 is a character string of "niff".  Therefore, quickpreview can also be initialized by loading different data in the location of this character string.  For example, when clean.bin (a binary file in which 0xff is arranged for 8 bytes) is used.  

[Emulator board]   gload -s -o0x200000 clean.bin
[IS-VIEWER]        nload -n -v -s0x200000 clean.bin  

This process is called quickpreview initialization.  

 




