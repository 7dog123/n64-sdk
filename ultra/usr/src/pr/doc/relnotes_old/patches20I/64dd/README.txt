
This patch addresses all of the currently known issues in version 2.0I of 
ultra.dev and adds new functions. Please refer to Changefiles.txt for a list of files affected by the installation of this patch.

Changes Affected by this Patch

98/10/21
        * The software version returned by the LeoInquiry function is now 6.

        * A reboot function has been added.  The function is mainly for booting a different game stored on the disk from the Game Pak.  For details, please read the revised section 15 of the 64DD Programming Manual.

        * In line with the addition of the reboot function, a "reboot" sample program has been added.  For details, see /usr/src/PR/demos/README_DEMO_64DD.jp

        * mild has been changed.  To see how it has been changed and to read about precautions, please see doc/mild/README.jp in the patch package.

        * When the application faced a prolonged interrupt mask during disk access, and when extra unprocessed messages were sent to the internal queue of the OS and afterward a read command, for example, was issued, a termination message would be sent to the application before the read was completed.  That problem has now been fixed.

        * Changed the method by which LeoCreateLeoManager() checks the connection of the drive.  Now it checks for the existence of DDROM, so it will assume the "drive is not connected" if DDROM is removed during development.  Please take note of this change.

        * Added the function LeoDriveExist() to check for the existence of the drive.  The function has no arguments and the return value is type u32.  If the drive exists, 1 is returned.  If not, 0 is returned.  Please do not omit the check for the value returned by LeoCreateLeoManager() even when booting leo manager after confirming the existence of the drive with this function.

        * Added a new error number.  LEO_ERROR_WAITING_NMI is now error number 37.  This error is returned for commands executed at the time LeoReset is executed and for commands issued henceforth.  Please never have the application display this error number.  

        * In line with the addition of error 37, corrected the diskproc.c: DiskOtherErrors() function of ddspgame so that error number 37 is not displayed as an error on the screen.

        * Corrected the problem that generated exceptions when LeoReset() is called before LeoCreateLeoManager() is executed.
          
        * It used to be that when the osDriveRomInit() function was called the first time, the PI bus access speed would change in accordance with the set value that was obtained, but would not change when the function was called subsequent times.  That has now been changed so that the access speed is not changed even when the function is called for the first time.  In relation to this change, the last part of DOC_handle.jp in /usr/src/PR/doc/patches/ultra has also been corrected.  Please reference this file.
 

        * The 98/08/10 fix of calcncc was imperfect, with the result that an error termination would arise when calcncc used master data not used in the RAM area.  That problem has been corrected.  The version is now 1.11

        * Bugs and things that need to be corrected have been found in the error handling sequences.  For details, please see DOC_errseq.jp.


98/08/10
        * A library for audio recognition system was added.  Accordingly, a sample for audio recognition system,voice was added.

        * Changed so that the status OS_GBPAK_RSTB_DETECTION is checked after accessing an extended RAM using a sample for 64GB Pak, gbpak.
   
        * If an initialization function for 64DD is executed before the first execution of osCartRomInit(), a handler could not be acquired properly.  The problem was fixed.  Refer to DOC_handle.txt for details. 


98/07/08
        * osInitialize() was changed as follows:
                (1) Changed so unmap of TLB is done inside osInitialize.      
                (2) Changed so a process equivalent to osAiSetFrequency() is done internally to handle the noise bug.
  
        * If a wave name was not specified in the spec file, makerom caused core dump and termination.  The bug was fixed.  And now an error message (no wave name specified) will be output.  The version is 2.3.
  
        * A description of onetri-fpal was added to /usr/src/PR/demos/README_DEMOS.txt.
   
        * The version of F3DEX2 series micro code became 2.05.  Refer to /usr/src/PR/doc/gfxucode.F3DEX2/README.txt for details.            


98/06/10
        * A library for 64GB Pak was added.  Accordingly, a sample for 64GB Pak,gbpak was added. 
          
        * When accessing the controller pak, CRC error occurred.  The problem with retrying process was fixed.   
         
        * When using n_audio micro code with MPAL, the application stopped if the reset button was pressed.  Refer to DOC_prenmi.txt for details.  

        * The version for F3DEX2 series micro code became 2.04.  Refer to /usr/src/PR/doc/gfxucode.F3DEX2/README.txt for details.   

        * SP library to process sprites with 3D micro code virtually is now supported by F3DEX/F3DEX2 micro code.  By defining F3DEX_GBI/F3DEX_GBI_2 in the same manner as F3DEX/F3DEX2, SP library becomes available.   

        * Changed so that ultratypes.h is included at the top of gbi.h, gs2dex.h, gt.h, gzsort.h.  This is because a type such as u32 is used in these files. 


98/04/23	
	* The ISR (Interrupt Service Routine) used for N64 Disk Drive has been 
	changed.  The changes only concern matters related to N64 Disk Drive 
	development.

	* Regarding the PI bus settings, the bus speed accessed by the software
 	is now read from the RCP register.

	* The F3DEX2 Series microcode has been added.  For details, please refer
 	to /usr/src/PR/doc/gfxucode.F3DEX2\README.txt.  The version is 2.02.

	* The gSPBgRectCopy command of the S2DEX microcode now functions 
	normally.  The version is now 1.07.  The same is true for S2DEX2 (included with the F3DEX2 Series).



98/03/05
	* /usr/src/PR/README.txt has been changed, since documents related to the patch are now stored in /usr/src/PR/doc

	* FPAL mode and the osViExtendVStart function have been added so that 
	images will fill the entire PAL format television screen. For details, 
	please refer to the file /usr/src/PR/doc/patches/ultra/DOC_fpal.txt

	* A sample called onetri.fpal has been added to demonstrate FPAL and 
	osViExtendVStart. Execute make using "makeFPAL= YES" to display the 
	sample in FPAL mode. When make is executed, 32 lines are added by osVoEx	tendStart and the resolution will be 320 x 272.

        * onetri-fpal was added as a sample of FPAL mode and osViExtendVStart.  With this sample, when make is executed by "make FPAL=", the display will be in FPAL mode, and when make  is simply executed, a display is made when 32lines are added by osViExtendVStart (Resolution 320 x 272). 

        * When a file name is specified for an argument using ROM image file/load function for Partner, uhGload(),  the file name did not become effective, and always a file called "rom" was loaded.  The bug was fixed.   

        * The SI functions (Controller Pak function and Rumble Pak functions) 
	have been revised, increasing processing speed.

	  * Data region is no longer zero-cleared when Controller Pak game notes 
	are created or deleted.

        * When the Inode region of the Controller Pak gets damaged, it is now 
	repaired correctly from the mirror Inode.

        * Correct values are now returned when the osContStartQuery() and 
	osContGetQuery()functions are called immediately after the 
	osEpromProbe() function.
	
	  * An error in the C source for the sample nosPAK reference was corrected. 	Makefile was added to create libnos*.a from the C source.
