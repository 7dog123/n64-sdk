//////////////////////////////////////////////////////////////////////////
//							                //         	//
//		MultiFileSystem Simple Manual		                //        //
//					                                //     	//
//		Copyright (C) 1998, NINTENDO Co,Ltd.                 	//	//
//	Ver0.1	1998/02/12 by K.Ohki(SLANP)	              		//
//	   0.3	1998/02/27 by K.Ohki(SLANP)	              		//
//	   0.4	1998/04/04 by K.Ohki(SLANP)	             		//
//	   0.5	1998/05/02 by K.Ohki(SLANP)	              		//
//	   0.6	1998/05/09 by K.Ohki(SLANP)	             		//
//	   0.65	1998/06/17 by K.Ohki(SLANP)	             		//
//	   1.00	1998/07/08 by K.Ohki(SLANP)  Official version     	//
//	   1.10 1998/09/03 by K.Ohki(SLANP)				//
//							                //        	//
//////////////////////////////////////////////////////////////////////////




[1] Introduction

The NINTENDO64 Disk Drive (hereafter, referred to as the 64DD) has a relatively large rewritable area (hereafter, referred to as the RAM area) with a maximum size of approximately 38M bytes.

However, as you may have learned from reading the 64DD Programming Manual, the 64DD libraries provide only a means of accessing media in terms of physical units.  Although this does not present a significant problem for the read area (hereafter, referred to as the ROM area), it is a major problem for the RAM area.

To actually access the RAM area to store or sort data efficiently or retrieve required data, file management must be performed logically in a manner the user can easily understand. A file system provides the user with a convenient means of organizing and accessing data.

From this perspective, a file system is essential for the RAM area.  Therefore, the MultiFileSystem (MFS) has been prepared as the recommended file system by Nintendo.  Using the MFS enables the standard 64DD RAM area to be accessed for the mutual use of data.

If, on the other hand, you do not want to allow access from other software that supports MFS, the MFS can be protected (through software) so that it can be used as a closed file system.

Moreover, if data in the ROM area is also managed in terms of file units as the physical units, it can be managed efficiently in an easy-to-understand manner.  And since libraries are provided, the effort required for writing disk control code in programs can be significantly reduced.

Nintendo plans to use the MFS in all its 64DD-compatible software.

Although MFS is the recommended format, you can, of course, create and use your own original file system.  A special-purpose format is certainly better from the viewpoint of speed or recording efficiency.  An original file system is also probably safer from a data-concealment viewpoint.  You should carefully consider both of these factors when selecting a file system.

[2] Overview of MultiFileSystem Specifications

(1) Areas on disk

As shown in Figure 2.1, the MFS manages files separately in the ROM area and the RAM area of the disk.  Each of these areas has a header area.  This "header area" contains disk information and information to manage the files that are stored in the data area.  The "data area" contains the actual file contents.
The RAM area has a copy of the RAM area header so that the header can be repaired if it becomes corrupted.  If an error 23 (an error for which error correction cannot be performed) or a header area checksum error occurs, the header can be repaired to some degree by moving header information from the copy area.


         --+-----+==================================+------- LBA 0
           |     |                                  |    
           |     |                                  |
           |     |            ROM data area         |  
        ROM area |                                  |
           |     |                                  |
           |     +----------------------------------+------- RAM START LBA - m
           |     |           ROM header area        |  m  (Varies according to
           |                                        |       the number of files)
         --+-----+==================================+------- RAM START LBA
           |     |                                  |    (Varies according to
           |     |                                  |          DiskType)
           |     |           RAM header area        |  3 Blocks
           |     |                                  |
           |     +----------------------------------+------- RAM START LBA + 3
           |     |                                  |
       RAM area  |       RAM header area copy       |  3 Blocks
           |     |                                  |
           |     +----------------------------------+------- RAM START LBA + 6
           |     |                                  |
           |     |                                  | 
           |     |            RAM data area         |  n Blocks
           |     |                                  |
           |     |                                  |
         --+-----+==================================+------- RAM END LBA
                   Figure 2.1  Block Diagram         (LBA 4291)


(2) File handling

With the MultiFileSystem, file management is performed using files and directories in the same way as in UNIX and DOS.  Names can be assigned to files or directories, and management can be performed according to these names.  However, from a processing standpoint, it is more efficient to distinguish files according to numbers.  Therefore, internally, each file or directory has a unique number, and management is performed by using this number.  This number is called the "directory ID."

For example, if there is a file named multi and a directory named akari under the root directory, the tree structure would be as follows according to file names.

	'/'-+--'akari'-+--
	    |
	    +--'multi'

Here, '/' represents the root directory.
When this structure is represented using directory IDs, it appears as follows.

	0 -+-- 1 -+--
	   |
	   +-- 2

The directory ID of the root directory is always 0 and the directory name is '/'.

(3) File attributes

Files and directories have the following kinds of information:

1. File name
This is the name of the file or directory.  It can be specified using ASCII or shift JIS code, and its size is 20 ASCII characters.

2. File type
This is specified using five ASCII characters.  It cannot be specified for a directory.

3. Attribute
This is a property of the file or directory.  The following attributes can be specified:

"Write protected"	  File or directory cannot be written to, deleted, or renamed.
"Read protected"	  File or directory only accessible if the company code
                    and game code are equal to the specified codes.
"Hidden file"	  File not visible to the user.  The process of actually
                    hiding the file must be performed by the application.
"Encode"		  Encoded file.  (* Unsupported)
"Copy limited"	  Limits the number of copies that can be made to the value
                    specified by the copy count.

4. Company code and game code
This is the company code and game code issued by Nintendo.

5. File size
This is the size of the file.  Since file management is performed in terms of block units, the size reserved on disk is larger than the file size.

6. Copy count
This is the number of times a copy can be made.  It is decremented each time a copy is made, and when the copy count is 0, the file or directory cannot be copied.  However, this operation must be performed by the application.

7. Update counter
This is 0 when the file or directory is created and is incremented whenever some change is made.  The maximum value to which the update counter can be incremented is 255, at which point is stops.  In addition to when data is written to a file, the update counter is also incremented when attributes or the name is changed.  The update counter of the parent directory is also incremented at the same time.

8. Date
This is the last date that the file or directory was changed.

9. Parent directory
This is the directory ID of the directory one level higher in which some the files and directories belong.  Files and directories are affected by the attribute of the one-level-higher directory in which they belong.  For example, if the attribute of the directory to which a given file belongs is write protected, data cannot be written to that file.
	
(4) Limit on number of files that can be recorded

MFS has a table of files and directories in the header area.  Although this is advantageous from an access-speed perspective, there is an upper limit to the total number of files and directories that can be recorded because the number of blocks in the header area is fixed.  Also, because the block size of the header area differs according to the disk type, the total number of files and directories that can be recorded also varies according to the disk type.

Table 2.1 shows the total number of directories and files that can be recorded.

   Table 2.1:  Disk Type and Number of Files
	          +----------------+------------+
	          |    Disk        |   Number   |
                |    type        |  of files  |
	          +================+============+
	          |      0         |    899     |
	          |      1         |    814     |
	          |      2         |    729     |
	          |      3         |    644     |
	          |      4         |    559     |
	          |      5         |    474     |
	          |      6         |     -      |
	          +----------------+------------+

(5) Pathname restrictions

Since the following characters have special meanings, they cannot be used in file names or directory names.

		'/'	Directory delimiter
		'.'	Extension delimiter
		':'	Drive delimiter

Also, the maximum length of a pathname is 127 characters.

(6) Disk attributes

Attribute information is saved for each individual disk.  The attributes are saved separately in the RAM area and the ROM area.

1. Volume name
The name of the volume can be specified using ASCII or shift JIS code, and its size is 20 ASCII characters

2. Attribute
The following attributes can be specified:

   "Volume write protected"
      Writing from another game is prohibited.
      Data can be written to the disk only when the company code and game code specified in the library match the company code and game code that are written in the system ID area of the disk.

   "Volume read protected"
      Reading from another game is prohibited.
      Data can be read from the disk only when the company code and game code specified in the library match the company code and game code that are written in the system ID area of the disk.

   "Write protected"
      Writing from all games is prohibited.

3. Destination code
This specifies the destination.

4. Update counter
The update counter is incremented when file, directory, or disk information has been changed in some way.  Therefore, it can be used, for example, to check whether the disk contents have been changed illegally, or as a random number seed.  The update counter is a 16-bit unsigned positive number.  It is incremented starting from 0x0000, and is returned to 0x0000 when it reaches 0xFFFF.

5. Date
This is the volume date.  Normally, it is the date that the volume was formatted.

(7)  Disk ID
	
	When RAM area is used by the MFS, the RAM Area Use setting for Disk ID must always be set to 1.  For more information, see Chapter 6 of the 64DD Programming Manual. 

[3] The MultiFileSystem Library

The MultiFileSystem Library is a special-purpose library for the handling of MFS disks.  It can be broadly divided into the following six types of functions:

	1. Disk manipulation functions
	2. Low-level directory manipulation functions
	3. Low-level input/output operation functions
	4. High-level directory manipulation functions
	5. High-level input/output operation functions
	6. Support functions

- The low-level functions use the directory ID for file and directory specifications.
- Leo functions are used for disk access.
- The high-level functions enable specifications using a path + file name.
- The high-level library uses the low-level library for disk access.

These libraries are related hierarchically as follows:
                +--------------------------+
                |                          |
                |    Application           |
                |                          |
                +------------------------+ |
                | MFS high-level library | | 
                +------------------------+-+
                | MFS low-level library  | |	
                +------------------------+-+
                |    Leo library           |
                +==========================+
                |  64 Disk Drive (Hardware)|
                +--------------------------+


For explanations of these functions, refer to the Function Manual (mfsfuncman.euc or mfsfuncman.sjis).

Details concerning the handling of files and directories can be found in books about DOS or UNIX programming.  Since anyone having programming experience can use files and directories in exactly the same way, an explanation is omitted here.

This package contains the following files:

	mfs.h			Include file
	libmfs.a		MultiFileSystem library for ROM * 
	libmfs_d.a		MultiFileSystem library for debugging * 
	readme.euc		This file (euc code)
	readme.sjis		This file (Shift-jis code)
	mfsfuncman.euc	Function manual (euc code)
	mfsfuncman.sjis	Function manual (Shift-jis code)
	history.euc		Modification history (euc code)
	history.sjis	Modification history (Shift-jis code)

	* The GNU-gcc library files are libgmfs.a and libgmfs_d.a.

Use these files by including mfs.h and linking libmfs.a or libmfs_d.a.


[4] How to use the MultiFileSystem Library's high-level library

(1) Handling files with the high-level library

The high-level library can handle the file system for both the ROM area and the RAM area of the disk.  However, the ROM and RAM areas are independent in the file system, and if they are not logically separated, not only will access efficiency drop, but problems also will occur concerning file management.
Therefore, the MFS Library handles the ROM and RAM areas logically as separate drives.  The drive assignments for the ROM and RAM area are as follows:

		ROM area		A drive
		RAM area		B drive

Unlike the low-level library, the high-level library can specify file names and directories using a full path.  A full path consists of a drive name, pathname, file name, and extension.  The drive name and pathname are separated by ':'.  Directory names are separated by '/'.  The file name and extension are separated by '.'.  (Example:  A:/big/sports/sosa/homer.text)

However, the files to be accessed often are collected in a single directory, and it is inconvenient to have to specify the drive name and path name every single time.  Therefore, the MFS Library enables the current drive and current directory to be set.  If the drive name or path name is not specified, then the current drive or current directory is used.  Currently, relative paths are not supported.

(2) Library initialization

The first step is to initialize the overall library.  There are initialization functions for starting up a Game Pak and for staring up a disk.  Game Pak initialization differs according to whether the game is Japan-oriented or US-oriented.  The three types of initialization functions are show below:

	mfsHInitDiskBoot()		Disk boot
	mfsHInitCasBootJP()		Game Pak boot (for Japan)
	mfsHInitCasBootUS()		Game Pak booting (for US)

These functions first initialize the lower-level Leo library.
If an MFS_ERR_DEVICE error occurs, the Leo*CreateManager() return value is returned.

(3) File access

To access a file, first open the file and obtain a file handle by using mfsHFopen().  The file handle is the pointer to the structure that contains information required to read from or write to the file.

When mfsHFopen() is used to open a file, the file access method can be specified:

	MFS_OPEN_READ		Open for reading
	MFS_OPEN_WRITE		Open for writing

Either or both of these can be specified.  When MFS_OPEN_WRITE is specified, either of the following can be specified:

	MFS_OPEN_UPDATE		Open in overwrite (update) mode
	MFS_OPEN_APPEND		Open in append mode

The following also can be specified:

	MFS_OPEN_CREATE		Create file if it does not already exist.

To read a file, use mfsHFread().  To write to a file, use mfsHFwrite().

When file access is finished, use the mfsHFclose() function to release the file handle.

(4) File search

To find a file or directory in a given directory, use the following functions:

	mfsHFindFirst()		First find
	mfsHFindNext()		Next find

A file search looks to see whether or not an attribute or a specified file exists.  If the file is found, MFS_ERR_NO is returned, and the information is stored in the specified MfsFfblk structure.

Specify the search-target file by using a character string that consists of a drive, path, and a file name.  A wild card character (? or *) can be specified only in the file name portion.

If the file is not found, MFS_ERR_SEARCHEND is returned.

	
[5] How to use the MultiFileSystem Library's low-level library

The low-level library has a group of functions for the ROM area and a group of functions for the RAM area.  The library for the ROM area contains functions having names that begin with mfsRom*.  The library for the RAM area contains functions having names that begin with mfsRam*.

If a function from the ROM area library and a function from the RAM area library have the identical name following the mfsRom*/mfsRam* portion, then they have the same functionality.  However, since data cannot be written to the ROM area, the ROM area library has no functions related to writing.

In the explanations below, a function that exists for both the ROM area and the RAM area is expressed as mfsR?m.
	
(1) Library initialization

First, initialize the library.  The initialization function differs according to whether Disk booting, ROM booting (Japan-oriented) or ROM booting (US-oriented) is to be used.  In addition, you can select whether only ROM is to be used, only RAM is to be used, or both are to be used.  Within these functions, Leo*CreateManager() is called and leo manager is initialized.  The six initialization functions are shown below:

	mfsInitDiskRom()	      Disk booting, ROM area
	mfsInitDiskRam()	      Disk booting, RAM area
	mfsInitDiskRomRam()	Disk booting, ROM and RAM areas
	mfsInitCasRom()		Game Pak booting, ROM area
	mfsInitCasRam()		Game Pak booting, RAM area
	mfsInitCasRomRam()	Game Pak booting, ROM and RAM areas

The reason why these functions are separated in such detail for the ROM and RAM areas is that 19,720 bytes are reserved internally as a buffer for the ROM area, and 48,960 bytes are reserved internally as a buffer for the RAM area.  If either of these libraries is unnecessary, the corresponding buffer will not be linked.
	
(2) Disk access procedure

To access a disk, first call a media check function to check whether or not a disk is inserted and whether or not that disk has been MFS formatted.

	mfsR?mMediaCheck()

If the return value of this function is MFS_ERR_NO, the disk is an MFS-formatted disk.  The header area is read into the buffer, and files can be accessed.
If the return value is MFS_ERR_NOHEADER, the disk cannot be accessed since it is not an MFS-formatted disk.  Also, if no medium has been loaded, then MFS_ERR_DEVICE is returned and LEO_ERROR_MEDIUM_NOT_PRESENT is entered in mfsError.

Next, obtain the directory ID for the file or directory you want to access.  For the parent directory of the root directory, this is MFS_DIRID_ROOTUP.
	
	mfsR?mGetDirID();		Obtains directory ID of directory
	mfsR?mGetFileID();	Obtains directory ID of file

To obtain the files or directories that belong to a given directory, use the following functions:
	
	mfsR?mGetDirListFirst();	First find
	mfsR?mGetDirListNext();		Next find

To create a file or directory, specify the directory in which it is to belong by using the directory ID.  For the root directory, this is MFS_DIRID_ROOT.

	mfsRamMakeDir();	      Creates a directory in the specified directory
	mfsRamCreateFile();	Creates a file in the specified directory

To read or write a file, use the following functions:

	mfsR?mReadFile();		Reads a file
	mfsRamWriteFile();	Writes a file

With the exception of file writing functions, the low-level library functions perform file or directory operations in the buffer within the MFS Library.  Therefore, when a series of operations is completed, the buffer contents must be written to disk.  This is done with the following function:

	mfsRamFlash();	Writes header information

However, if the information within the buffer has not been changed, nothing is written to the disk.

	
(3) Disk protection

An MFS-formatted disk can be write-protected or volume-protected.  If the disk is write protected, data can be read from the disk but no data can be written to the disk.  If it is volume protected, data can be read or written only when the company code and game code are matched.
	
	mfsR?mGetVolumeAttr();	Obtains RAM area attribute
	mfsRamSetVolumeAttr();	Sets RAM area attribute


[6] Errors

When the MFS library return value is negative, an error has occured.  Therefore, when the return value is negative, you should check the type of error and perform error processing.

Errors can be broadly divided into two types: errors returned by the Leo library, and errors returned by the MFS library.

Errors returned by the Leo library are device level errors.  Various measures have been devised to improve the reliability of media for the 64DD, and numerous kinds of errors are returned by the Leo library.  Therefore, error processing is rather complicated.  However, if errors are divided into fatal errors, recoverable errors, and warnings, then error processing can be performed relatively easily.

The errors returned by the MFS library can be divided into device errors like Leo library errors (MFS_ERR_DEVICE), and file system errors.

Please incorporate error processing that is sensibly classified in this way.

The MFS library has the following types of errors:

	MFS_ERR_NO		     0	Normal termination
	MFS_ERR_ARG		    -1	Argument error
	MFS_ERR_DEVICE	    -2	Device error
	MFS_ERR_NOINIT	    -3	Uninitialized library error
	MFS_ERR_NAME	    -4	File name error
	MFS_ERR_NOTFOUND	    -5	File or directory not found
	MFS_ERR_FULL	    -6	Disk full
	MFS_ERR_FILEEXIST	    -7	File (directory) with same name exists
	MFS_ERR_PROTECT	    -8	Write protected
	MFS_ERR_REFUSE	    -9	Illegal operation
	MFS_ERR_HEADER	   -10	Header area is corrupted
	MFS_ERR_SEARCHEND	   -13	End of file search
	MFS_ERR_FATAL	   -14	Fatal error
	MFS_ERR_LENGTH	   -16	Insufficient buffer for storing characters
	MFS_ERR_NOTMFSDISK   -17	Not an MFS disk
	MFS_ERR_DISKCHANGE   -18	Medium was exchanged
	MFS_ERR_VERSION	   -19	Unsupported version

These errors are explained below.  Check the error number and perform error processing .


MFS_ERR_NO	Normal termination
			The function terminated normally.

MFS_ERR_ARG	Argument error
			There is a problem in the arguments assigned for the function.

MFS_ERR_DEVICE	Device error
			An error occurred in an internally called Leo function.
			Check the global variable mfsError.

MFS_ERR_NOINIT	Uninitialized error
			High-level functions have not been initialized.  Call the
                  mfsHInit* function to initialize the library.

MFS_ERR_NAME	File name error
			The file name contains a character that cannot be used.

MFS_ERR_NOTFOUND  File or directory not found
			The specified file or directory does not exist.  This error
                  will also occurs when the file or directory is read-protected.

MFS_ERR_FULL	Disk full
			The disk has no free space or the directory entries are full.

MFS_ERR_FILEEXIST There is a file (directory) with same name
			A file or directory with the same name already exists.

MFS_ERR_PROTECT 	Write protected
			Either the file or directory attribute is write-protected,
                  or the parent directory attribute is write-protected, 
                  or the volume attribute is write-protected.

MFS_ERR_REFUSE	Illegal operation
			This error occurs when an attempt is made using a high-level
                  function to write to the ROM area or to delete or change a
                  file or directory.

MFS_ERR_HEADER	Header area is corrupted
			The header area of the RAM area is corrupted.  Try
                  using mfsRamRepairHeader to repair the header area.

MFS_ERR_SEARCHEND End of file search
			This error is returned at the completion of a file
                  search performed using mfsHFindFirst, mfsHFindNext,
                  mfsR*mGetDirListFirst, or mfsR*mGetDirListNext.
		
MFS_ERR_FATAL	Fatal error
			An attempt was made to perform an operation using a file
                  handler that has not been opened by a high-level function.

MFS_ERR_LENGTH	Buffer insufficient for storing characters
			This error is returned when the pathname length is longer than
                  the length specified by mfsHGetCwd.

MFS_ERR_NOTMFSDISK   Not an MFS disk
			   The disk is not an MFS-format disk.

MFS_ERR_DISKCHANGE   Medium was exchanged
			   The medium was exchanged.  For a high-level function, close
                     the file handler and then open it again.  For a low-level 
                     function, begin processing by obtaining the disk ID again.

MFS_ERR_VERSION	Unsupported version
			The medium has been MFS-formatted, but the version is 
                  different so it cannot be handled.


[7] Access using LBA

The following lower level functions are provided:

	mfsReadLBA(u);
	mfsWriteLBA();
	mfsReadDiskID();
	mfsRezero();
	mfsSeekLBA();

These functions make the asynchronous Leo functions somewhat easier to deal with.  They can be used directly from an application to access ROM.

[8] Exclusive control

With MFS, you can register callback functions to be called before an asynchronous Leo function is called and after a Leo function operation is completed to enable exclusive PI control when accessing the 64DD disk, accessing DD-ROM, or accessing a Game Pak.

If exclusive control functions that use the message mechanism are registered here, exclusive control can be implemented relatively easily.

Callback function registration functions:

	mfsSetLeoBusyFunc()	Function called before calling a Leo function
	mfsSetLeoReadyFunc()	Function called after a Leo function call

Example:

	OSMesgQueue	      piSemaphoreQ;
	OSMesg		piSemaphoreBuf

	/* Lock the PI */
	void lockPi(void)
	{
		osRecvMesg(&piSemaphoreQ, NULL, OS_MESG_BLOCK);
	}

	/* Unlock the PI */
	void unlockPi(void)
	{
		osSendMesg(&piSemaphoreQ, NULL, OS_MESG_BLOCK);
	}

	/* Initialize and set exclusive control mechanism */
	void initLock(void)
	{
		osCreateMesgQueue(&piSemaphoreQ, &piSemaphoreBuf, 1);
		osSendMesg(&piSemaphoreQ, NULL, OS_MESG_BLOCK);
		mfsSetLeoBusyFunc(lockPi);
		mfsSetLeoReadyFunc(unlockPi);
	}

[9] Requests, impressions, questions, reports of problems, and support

Although Ver1.0 has been designated the first official version, please post any requests, impressions, questions, or reports of problems to the "64DD page" on NTSC-ONLINE (https://ntsc.nintendo.co.jp).

