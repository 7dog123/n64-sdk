12/12/98
This patch addresses all of the currently known issues in version 2.0I 
of ultra.dev and adds new functions.  Please refer to Changefiles.txt for a list of files affected by the installation of this patch.

Changes Affected by this Patch

98/10/21

* Fixed the bug that caused the system to hang on the N64 Game Boy Pak connector check function osGbpackCheckConnector() when contact was poor.  

* Changed the specifications of the Controller Pak functions osPfsInitPak() and osPfsRepairId().  When the Rumble Pak or the N64 Game Boy Pak is connected, a PFS_ERR_DEVICE error is now returned instead of a PFS_ERR_ID_FATAL error.
For details, please refer to DOC_cpak.txt.  

Note: This is a very important change, especially when multiple types of paks are used in a game (such as the Controller Pak and the Rumble Pak).  Thus, please read the documentation.  

* Changed the sample program "motortest" in accordance with the specification changes of the Controller Pak functions osPfsInitPak() and osPfsRepairId().   

* Fixed a problem where the system didn't always detect when the Controller Pak was removed when data was being read it.  

* Fixed the bug that caused a Warning message to appear when compiling the audio 
library source.  

* #ifdef _DEBUG - - #endif was used for call the assert() function located in the library source file. 

* Fixed the bug in the OS interrupt mask process.  In the past, when an interrupt occurred during a global int mask change, the process was moved to another thread.  But if the global int mask change was also performed there, the change did npt always take effect.  

* Changed the Pi/EPi Raw functions into OS internal functions.  For details, please see DOC_piraw.txt.   

* Changed all Pi functions in the sample programs to EPi functions.  Also, changed the Pi Raw functions to non-Raw functions.  

* ROM image files can now be created in a format that will work with Nintendo 64 Controller by specifying "make FINAL=YES" when compiling the sample programs (with some exceptions).  Also modified usr/src/PR/demos/README_DEMOS.txt in accordance with this change.

* There was a problem with the DMA callback routine of the "soundmonkey" sample program, in that the routine sometimes performed an unnecessary DMA from ROM even though data was already in RAM.  Soundmonkey was thus changed to use the same DMA callback routine used by playseq.  

* Changed the sample program "playseq" so the number of physical voices could be switched to 16 or 32, corresponding to Define.  For details, see /usr/src/PR/demos/README_DEMOS.txt.

* Removed rmon-related code from the sample programs. 

* Deleted the Clock Rate Change function in osInitialize.  For details, please see DOC_clock.txt.  

* The following changes were made so as not to miss a reset preNMI: 

    (1) Changed osInitialize to check internally whether a preNMI has
        occurred and, if so, to stop the program. 
    (2) Changed osSetEventMesg to check whether preNMI has occurred
        when performed for OS_EVENT_PRENMI, and to send a message if 
        preNMI has already occurred.  

With these changes, messages will not be missed, even when a preNMI has occurred.  However, since the NMI event does not happen any slower, the preNMI routine must be activated as quickly as possible.      

* Changed the osGetMemSize memory check routine. 
In the past, the existence of expanded memory was checked by writing specific data to a specific address in the expanded memory area, and then checking whether the data was actually written.  In this version, the existence of expanded memory is assessed by checking whether written data can be changed. With this modification, when an effort is made to read expanded memory, when expanded memory does not exist, there is no longer any possibility of reading the test-use data.

* Previously, the access speed of the PI bus was changed in accordance with the value obtained by the osCartRomInit() function when it was called for the first time, but not on subsequent occasions when the function was called.  This has been modified so the value of access speed setting is never changed, even on the first time the function is called.  Note that DOC_handle.txt was also corrected in accordance with this modification.  

* The exception handler no longer operates incorrectly if an Int1 occurs even though an external device (such as 64DD) is not connected.

* The F3DEX2 series microcode version is now 2.06.  For details, please see /usr/src/PR/doc/gfxucode.F3DEX2/README.txt.

* Three 64DD-related object files which in patchNg980708 were changed to be placed in libleo, were deleted from libgultra.  The three files: driverominit.o, leodiskinit.o, and leointerrupt.o are now incorporated in libleo.


98/08/28

* Previously, when the OS_VI_DITHER_FILTER_OFF bit was specified for the osViSetSpecialFeature function in libgultra_d, the program did not run well if any other bit was raised at the same time.  This problem was fixed.

* Made the following changes to "voice," the sample program for the voice recognition system:
     (1) Messages corresponding to the error codes are now displayed.  
     (2) The program now operates no matter which Controller port the sound
         recognition system and the standard Controller are connected to.   
     (3) Four warnings are displayed, instead of just one.    
     (4) Added a README document explaining the sample.  


98/08/10
	* A library for audio recognition system was added.  
	Accordingly, a sample for audio recognition system, voice was added.
        
	* Changed so that the status OS_GBPAK_RSTB_DETECTION is checked 
	after accessing an extended RAM using a sample for 64GB Pak, gbpak.
        
	* If an initialization function for 64DD is executed before the 
	first execution of osCartRomInit(), a handler could not be acquired properly.  
	The problem was fixed.  Refer to DOC_handle.txt for details. 

98/07/08
        * osInitialize() was changed as follows:
          (1) Changed so unmap of TLB is done inside osInitialize.
          (2) Changed so a process equivalent to 
	  osAiSetFrequency() is done internally to handle the noise bug.  
        
	  * A description of onetri-fpal was added to 
	  /usr/src/PR/demos/README_DEMOS.txt.   
        
	  * The version of F3DEX2 series micro code became 2.05.  Refer to 
	  /usr/src/PR/doc/gfxucode.F3DEX2/README.txt for details.            

98/06/10
	* A library for N64 Game Boy Pak was added.  
	Accordingly, a sample for 64GB Pak, "gbpak" was added. 
        
	* When accessing the Controller Pak, CRC error occurred.  The 
	problem with retrying process was fixed.
        
	* When using n_audio microcode with MPAL, the application 
	stopped if the reset button was pressed.  Refer to DOC_prenmi.txt for
        details.  
        
	* The version for F3DEX2 series micro code became 2.04.  Refer 
	to /usr/src/PR/doc/gfxucode.F3DEX2/README.txt for details.   
        
	* SP library to process sprites with 3D micro code virtually is 
	now supported by F3DEX/F3DEX2 micro code.  By defining 
        F3DEX_GBI/F3DEX_GBI_2 in the same manner as F3DEX/F3DEX2, SP library
        becomes available.   
        
	* Changed so that ultratypes.h is included at the top of gbi.h, 
	gs2dex.h, gt.h, gzsort.h.  This is because a type such as u32 is used in
        these files. 

98/04/23	
	* The ISR (Interrupt Service Routine) used for N64 Disk Drive has 
	been changed.  The changes only concern matters related to N64 
	Disk Drive development.
	
	* Regarding the PI bus settings, the bus speed accessed by the software is
	now read from the RCP register.
	
	* The F3DEX2 Series microcode has been added.  For details, please refer	
	to /usr/src/PR/doc/gfxucode.F3DEX2\README.txt.  The version is 2.02.
	
	* The gSPBgRectCopy command of the S2DEX microcode now functions 
	normally.  The version is now 1.07.  The same is true for S2DEX2
	(included with the F3DEX2 Series).

98/03/05
	* /usr/src/PR/README.txt has been changed, since documents related to
	the patch are now stored in /usr/src/PR/doc
	
	* FPAL mode and the osViExtendVStart function have been added so 
	that images will fill the entire PAL format television screen.   For
	details, refer to the file /usr/src/PR/doc/patches/ultra/DOC_fpal.txt.
	
	* A sample called onetri.fpal has been added to demonstrate FPAL 
	and osViExtendVStart. Execute make using "makeFPAL= YES" to 
	display the sample in FPAL mode. When make is executed, 32 lines 
	are added by osVoExtendStart and the resolution will be 320 x 272.
      
	* onetri-fpal was added as a sample of FPAL mode and osViExtendVStart.
 	With this sample, when make is executed as "make FPAL=", the display will
  	be in FPAL mode, and when make  is simply executed, a display is made when
 	32lines are added by osViExtendVStart (Resolution 320 x 272).
         
	* The SI functions (Controller Pak function and Rumble Pak 
	functions) have been revised, increasing processing speed.
	
	* Data region is no longer zero-cleared when Controller Pak game 
	notes are created or deleted.
        
	* When the Inode region of the Controller Pak gets damaged, it is 
	now repaired correctly from the mirror Inode.
        
	* Correct values are now returned when the osContStartQuery() and 
	osContGetQuery()functions are called immediately after the 
	osEpromProbe() function.
	
	* An error in the C source for the sample nosPAK reference was corrected.
	Makefile was added to create libnos*.a from the C source.
