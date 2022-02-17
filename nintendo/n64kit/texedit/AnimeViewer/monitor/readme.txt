#=======================================================================#
#               Texture Editor Anime Viewer                             #
#               anmview.man                                             #
#                                                                       #
#               Copyright (C) 1998, NINTENDO Co,Ltd.                    #
#                                                                       #
#-----------------------------------------------------------------------# 

Last update:
March 4, 1999 Version 0.91A Edition

******************************************************************************

      		            Texture Editor  
                2D Texture Anime Viewer Program Description

             (*Camera angle animation not yet included)

			   Version 0.91A Edition

******************************************************************************

			+ + + + Contents + + + +

	1. Viewer Program Specifications

		Purpose
		Implementation

	2. Viewer Operation

		Common Methods of Operation
		1. 2D Texture Anime Viewer
		2. Camera Angle Anime Viewer

	3. Anime Display Controller

		Overview
		Specifications

	4. Modifying the Program
		Anime Display Controller
		Camera Angle Anime Viewer

	5. Using anmview.exe

==============================================================================
		   1. Viewer Program Specifications
==============================================================================

Purposes
----
This previewer is a tool that enables color image bitmaps (texture palettes) 
which were created using the Texture Editor, to be animated and checked on Nintendo 64. 

To increase the speed of a game, 3D pictures may first be rendered as 2D 
bitmaps, displayed as if they were 3D, and their animation speed then increased. 
CI Texture Editor can be used to display and check these pictures and bitmaps on 
the Nintendo 64.


Implementation
----
The previewer is built on NuSystem and consists of a minimum amount of source 
code.

The source files are broadly divided into the following blocks.

	a. Startup, main
		main.c

	b. Service routines (includes the NuSystem interface)
		is_debug.c	... debug module for IS-VIEWER64
		gfxinit.c	... display initialization data
		graphic.c	... initializes the display 
		stage00.c	... the 2D texture anime stage
		stage01.c	... the camera angle anime stage
		teapi.c		... Texture viewer program

	c. Anime controller
		anmview.c	... displays data created with anmdata.c

	d. Anime data
		anmdata.c	... created with anmview.exe

==============================================================================
		    2. Viewer Operation
==============================================================================

Common Methods of Operation
------------
Show/Hide parameters with the Z trigger
Change the viewer modes with the Start button

1. 2D Texture Anime Viewer
---------------------------------
  A 2D texture in the center of the screen is animated according to the user's 
  specifications.
* A texture can be moved to any position on the screen using the Control Stick.


2. Camera Angle Viewer
-----------------------
Displays 2D texture based upon the angle data specified by the user in the center of the screen.
* The camera angle can be changed using the with 3D control stick
* The camera angle can be changed with control pad.
(When the "A" button is held down, the camera angle changes faster.)

==============================================================================
		    3. Anime Display Controller
==============================================================================

Overview
----
The purpose of the Animation Display Controller is to display 2D animation.

The Animation Display Controller consists of only anmview.c/anmview.h.

(Note:  Service functions for performing instance linking operations are 
        currently not available.)


Specifications
----
Allows checking of 8- and 4-bit color images.

==============================================================================
		     4. Modifying the Program
==============================================================================

Anime Controller
-------------------
All Anime Controller source is contained in anmview.c and anmview.h.

Anime Controller is written in C++-like language. Its initial argument (pSelf) 
passes an instance. This is usually adequate for displaying a single anime.  
Multiple anime can be displayed simply by creating multiple instances. 

Camera Angle Animation
------------------



==============================================================================
		     5. Using anmview.exe
==============================================================================

Overview
-------------
* anmview.exe loads any *.taf file (anime definition file) and outputs as 
  C-language source the texture, palette, and anime data needed to display the 
  specified anime.  Previewing is performed by compiling this source along with 
  the viewer source.

Options
----
-h / -?
Display help on using anmview.exe

-o<filename>
Enables the name of the ouput file to be specified. The default setting directs 
the output to standard output.

-e<filename>
Enables the corresponding header file to be output. The default setting is for 
no output.

-v
Verbose mode (displays the details of processing as it occurs).  The default 
setting is not to display this.


TAF File Example
----

#Shared by 2D Texture Anime Viewer and Camera Angle Anime Viewer
NIFF_DIR	=	c:\temp\niff
TPF_DIR		=	$(NIFF_DIR)/tex_data/tpf
TAF_PREV_DIR	=	$(NIFF_DIR)/taf_prev

TPF.NUM		=	2                     # No. of TPF files used
TPF.0.FILE	=	$(TPF_DIR)/test0.tpf  # First TPF file
TPF.1.FILE	=	$(TPF_DIR)/test1.tpf  # Secound TPF file

# Used by 2D Texture Anime Viewer
FRAME_ANIM	=	1		# Animate the texture (=1)
FRAME_LENGTH	=	60              # Specify the number of frames
FRAME_KEY	=	3               # No. of instances of FRAME_KEY*
FRAME_KEY0	=	0,0,Picture0    # No. of frames, TPF number, PICTURE name
FRAME_KEY1	=	10,0,Picture1   # 
FRAME_KEY2	=	40,0,Picture2   #

# Used by Camera Angle Anime Viewer
CAM_ANIM		=	1
CAM_Y_NUM		=	2
CAM_XZ_NUM		=	2
CAM.0,0.KEY0		=	TPF.0.TMF.4
CAM.POLE.0.KEY.0	=	TPF.1.TMF.0
CAM.POLE.1.KEY.0	=	TPF.1.TMF.1


