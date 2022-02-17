Partner-N64 PC Ver. 1.08d

readme.txt

1. Differential Load

With differential load, when a file previously loaded from the address values of the ROM segment inside the debug information (for example, codeSegmentRomStart,codeSegmentRomEnd) matches the configuration of a ROM segment, only the ROM segment (DISK segment) specified by the .dld file (the description protocol for this file is explained below) will load.  However, Release 1.1 of exeGCC (N64) is required when using this function in the PC environment. 

Also, to effectively use this differential load function with a ROM program, the ROM program must be set so that the ROM segment configuration will change as little as possible even if a part of the program is changed.  Because of this, a function to specify the alignment of the specified segments has been added to mild as a new function.  Specifically, the romalign alignment value is specified in the segment portion that specifies alignment in the spec file.  It is possible to specify romalign in multiple segments in a spec file.  Consequently, specify romalign for all segments that might be altered by the user.

The following is an example of a 0x1000 alignment in a portion of a code segment.

beginseg
	romalign		0x1000 <--- add this part
	name "code"
	flags BOOT OBJECT
	entry boot
	stack bootStack - STACKSIZEBYTES
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspFast3D.o"
	include "$(ROOT)/usr/lib/PR/gspFast3D.dram.o"
	include "$(ROOT)/usr/lib/PR/aspMain.o"
endseg

As larger alignment values are used, gaps in the ROM images become larger, and the configuration of the ROM segment area will not change as the result of small modifications to the program, increasing the chances that the differential load function can be used.  However, this also increases the amount of wasted space in the ROM images.  Conversely, as smaller alignment values are used, the wasted space in the ROM images likewise decreases, but there is an increased possibility that the ROM image configuration will be changed as the result of program modifications, decreasing the chances that the differential load function can be used.  Please keep the above in mind when selecting the alignment values specified by romalign.

Since segments are configured in DISK LBA units in programs used for N64DISK, there are gaps between each segment and it is possible to effectively use the differential load function, even if there is no alignment specified, as in ROM programs. 

The description protocol for .dld files is shown below.  Use the following format in .dld files to specify segments which absolutely must be loaded during a differential load (normally the segment(s) for which romalign was set in the spec file). 

DIFF LOAD SEGMENT <segment name>

Make the .dld filename the same as the debug data file name, only use the .dld extension.

As a typical example, to specify the code, cafe segments of tile_rect3d (tile_rect3d.disk):

File name tile_rect.dld

DIFF LOAD SEGMENT code
DIFF LOAD SEGMENT cafe

The following commands have been added or altered through the addition of the differential load function.  Because of N64DISK differential load support, the L command automates the series of operations, laoding the DISK program, starting IPL4, and other operations up to the debugging enabled status.  Consequently, a file can be immediately debugged and executed once it has been loaded with the L command in N64DISK program as well.

L command (l <load file>)
When the <load file>.dld file exists and the differential load conditions have been met (previous load and ROM (DISK) segment configuration are unchanged), executes differential load.  
If there is no .dld file, operation will be the same as before.

LA command (la <load file>)
Loads all ROM (DISK) images regardless of whether or not a .dld file exists.  (Differential load is not executed even if the conditions have been met.)

FS command (fs)
Displays the ROM (DISK) segment ranges and segment names of files which have been loaded.

2. Commands for which N64DD Support has been Added

DDW <FNAME>,<SLBA>[,<ELBA>][,/ID:<IDFILE>][,/S:<FSIZE>]

[,/O:<FOFFS>][,/A:<SADDR][,/F][,/T:<TYPE>]
	DDR <FNAME>,<SLBA>[,<ELBA>][,/S:<FSIZE>]
	DDR /I
	RESETDD

Meaning of each segment
	/ID:<idfile>		disk ID file specification
	/S: <FSIZE>		file size specification
	/O:<FOFFS>		file segment specification
	/A:<SADDR>		start address specification
	/F			disk format specification
	/T:<TYPE>		disk type specification
	/I			disk information display specification

	<FNAME>		file name
	<SLBA>		first LBA number
	<ELBA>		last LBA number
	<FSIZE>		file size
	<FOFFS>		file offset
	<SADDR>		start address
	<TYPE>		disk type

The DDW command writes the file contents specified by <FNAME> from the LBA specified by <SLBA> to the DD64.  Unless specified otherwise by options <ELBA>, /S:<FSIZE>, /O:<FOFFS>, /A:<SADDR>, /F, or /T:<TYPE>, the file size of <FNAME> will be written.

>ddw rom, 10<CR>

The DDR command writes the contents from the LBA specified by the DD64's <SLBA> to the file specified by <FNAME>.  Unless specified otherwise by options <ELBA> or /S:<FSIZE>, 1LBA will be written.

>ddr data, 10, 100<CR>

The DDR command also displays DISK information when only the /I option is specified. 

The RESETDD command reads the contents of the IPL4ROM and starts the IPL4. 

These are all of the added commands.  Note that when executing these DISK-related commands, the contents of the PARTNER emulation ROM area (from 0xb0000000 to 0xb05fffff) will be destroyed.

	leowrite [-fi] [-L LBA] [-t Type] [-w [start]-[end]]
					[-a address] [-I idfile] file 

    Explanation of each option
	-L: Specifies from which block to write using LBA. Specify                 value between 0 and 4291. By default, it's 0.   
	-t: Specifies a disk type.[0-6]  If omitted, the disk type                 currently written on the disk will not be changed.  
	-w: Specifies which part of file to write.  Please note it                 is specified by the offset from the head.(the head is 0.) 
	    If "start" is omitted, "from the start to "end"" is             written. 
	    If "end" is omitted, "from "start" to the end" is written. 
	-a: Specifies load address. IPL(see the 64DD Programming                   Manual.) will jump to the address shown in here after                  booting up the game.
	-f: Formats a disk logically.  If a disk is not formatted,                 leowrite normally detects that automatically and formats               it.  In case it cannot access a disk properly due to some             problem,  try this option.     
	-i: Reads disk information (disk types, ID, etc.) and display              them.  
	-I: Writes the head 32 byte of idfile in a disk as an ID.  
	    However, as for a factory line number and production time             (see 64DD Programming Manual, P.6-1), "ptn64" and current             time are used respectively. 

leowrite is one of commands to be input for a command window for PARTNER, and is for writing data in 64DD. It writes all or part of the file specified by "file" from the specified block.  
 

(Cautions)
	In case of writing from LBA 0, leowrite recognizes the file is         a file that is read by IPL, corrects its file size to block            number automatically, and writes it in system area of a disk as         IPL size.  Therefore, if a file to be read by IPL is divided         and then written,  activation will not be done properly.
        Be aware of that.  
	  
	The portion that does not reach the LBA boundary will be filled         with 0xff.   

	At the time of executing, leowrite overwrites a portion of             factory line number and production time of the ID. (However,           when executing with a script file such as gwrite and mwrite,           the second line or later will not be overwritten.)  
	"ptn64" and the current time will be used respectively.
	
        Even when ID is written using the -I option,  for a factory         line number and production time, not the specified ones but  
	"ptn64" and the current time are used respectively.  

	Other than -i option, file cannot be omitted.  


3. Commands Added to Thread Display

THREAD
PS

The THREAD or PS command displays the status of the user thread managed by the N64OS and, when the status is WAIT, displays the queue and the address which is currently being executed.  The thread names and queues that can be displayed with this command are, with some exceptions, only those names which have been globally defined.  Consequently, as long as the thread queue is defined in the user program as a global variable, this command can be used to make the display easier to understand.  An execution example of the THREAD command is given below.

	>THREAD<CR>
	PID Pri Thread			Status 		Queue
Address
	   3    10  &mainThread		WAITING	diskQ(E)
main.c:546
	   1      0  &idleThread		RUNNING
main.c:382

4.  Additional function of ZROM command

       By enabling to write using ZROM command,  it will become possible to write in the
       emulation ROM area using functions osPiWriteIo() and osPiRawWriteIo().   To
       enable/disable to write,  please specify using the fourth parameter of ZROM command.
       Please refer to the examples shown below:

		>ZROM ,,, ON 		Enabling to write in ROM space
		>ZROM ,,, OFF		Disabling to write in ROM space (initial value)

	TRANSLATION


