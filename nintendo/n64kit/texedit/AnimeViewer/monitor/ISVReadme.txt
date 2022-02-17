                                                12/17/1997
                                            	Intelligent Systems Co.,Ltd.


                    IS-VIEWER64 nload/nload.exe Manual


Introduction
______________________________________________________________________________

IS-VIEWER 64 (ISV) is equipped with a command that can be operated using CUI 
format. Application names for Windows95/NT 4.0 and IRIX5.3 are "nload.exe" and 
"nload" respectively.  This descriptions in this manual are divided into those 
that are operating-system dependent and those common to all the OSs.  Please 
read the appropriate sections.


Arguments for the application
______________________________________________________________________________

Application displays Usage by adding "-h" to an arguments. We will explain the 
details displayed by Usage here. (for Indy, the prompt display will be different, 
but you can use it the same way.)

C:\>nload -h
nload (IS-VIEWER64) verX.XX
Copyright (c) 1997 Intelligent Systems Co.,Ltd.

nload [-s0x??] [-l0x??] [-r] [-h] [-v] [-n] [-b0x??] [-z0x??] [-w] [filename]
-- Command -------------------- Default ------------
-s : load start address(even) : 0x00000000
-l : load length(even)        : file size
-r : reset only               : off
-v : verbose mode             : off
-n : no debug mode(load only) : off
-h : usage print              : off
-w : NUS -> FILE              : FILE -> NUS
-e : load only(no reset)      : off
-b : Debug communicate address: 0xb1ff0000   (4KB segment)
-z : Debug size               : 0x10000      (4KB segment,max 64KB)
-i : host,id                  : auto search  (example -i04 host=0, id=4)
C:\>

The following is a description of the arguments.

-s
Specifies load (save) start address. Default is 0. The address must be an even 
number.

-l
Specifies load size. 
Default at the time of loading is file size
Default at the time of saving is 16MB.

-r
Specified when the file has already been downloaded and only a reset is desired. 
Other commands are invalid when this command has been specified. 

-v
Mode for detailed display. Displays downloading status.

-n
If not specified, goes to a debug print loop after downloading. If specified, 
nload will end after downloading and execution.

-h
Display Usage

-w
Outputs the contents of NINTENDO64 to a file. If not specified, downloading from 
a file will be executed. 

-e
Resets after downloading. If specified, reset will not be done.  

-b
Sets debug communication address. The address must be specified in 4KB units. 
(Like being masked by 0xFFFFF000)  Default is 0xB1FF0000. (The last 64KB of 32MB)

-z
Sets debug communication size. Size must be specified by 4KB unit.				
Default is 0x10000. The debug communication address and the debug communication 
size must not exceed 64KB. (i.e., you cannot specify 0xBLE08000 ~ 0xBLE18000)

-i
Specifies SCSI host adapter and SCSI-ID. If default is used, SCSI-ID will 
automatically be detected. SCSI-ID can also be specified directly.
(For example, if-04, then adapter=0 and ID=4.)


Return Values for the Application 
______________________________________________________________________________

The following values are returned on exiting the application. 

0 ... Normal termination
1 ... Abnormal termination 
2 ... Updated the ISV Pak. When the Pak is updated, the program is exited 
      without executing the commands specified by the arguments. Enter the 
      commands again if necessary. 


ISV Pak Update
______________________________________________________________________________

When the ISV Pak is older than NLOAD.EXE/NLOAD, any command arguments are 
ignored and the Pak is automatically updated.  Messages are displayed to the 
screen during the update.  Following the update, NLOAD.EXE exits and returns a 
value of 2. 


Multiple ISVs
______________________________________________________________________________

Using a multiple SCSI host adaptor allows multiple ISVs to be used. 
NLOAD.EXE/NLOAD automatically detects and uses ISVs in ascending order of the 
SCSI host and SCSI ID numbers.  In addition, using the -i option allows direct 
setting of the ISVs used. 


For Windows 98/NT 4.0 users:
______________________________________________________________________________

If you are using Windows NT4.0, make sure the path to "wnaspi32.dll" in the 
Installed Directory is set.


For IRIX users:
______________________________________________________________________________

To use ISV, general users must obtain privilege to use ISV as a SCSI device 
from the system administrator.  For more information, see chapter 5, Installing 
on Irix, in the Setup Manual. 


Examples of Usage
______________________________________________________________________________

nload filename      ... Downloads and executes filename.
nload -v filename   ... Downloads and executes filename. 
			Displays downloading status.
nload -l0x10000 -w filename
                    ... Saves the contents of address from
			b0000000 to 0x10000 in filename
nload -r            ... Resets NINTENDO64

nload -n filename   ... Exits the application immediately after filename is 
			downloaded. 

nload -b0xb1000000  ... Uses debug communication address
			from 0xb1000000. This specification
			requires knowledge of debug print. 
			Please refer to Debug print in the
			sample directory.


Obtaining the Latest Version and Information
______________________________________________________________________________

The latest versions of IS-VIEWER64 software can always be obtained using a Web 
browser.  The Web site also provides a FAQ and the latest software information. 
We urge that any suggestions or problems be conveyed to the following ISV 
support e-mail address.

Web site URL:  http://www.noa-engineering.com
E-mail address:  support@noa.com

