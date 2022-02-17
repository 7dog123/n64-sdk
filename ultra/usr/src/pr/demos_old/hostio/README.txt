------------------------------------------------------------------
Explanation of HostIO in the PC environment.
------------------------------------------------------------------

When you run PARTNER-N64 (Windows 95 version) on a PC, you can 
make use of HOSTIO capabilities with the following functions.

	
The following functions are supported on the Host (PC) side:

	int uhOpenGame(char *);
	int uhCloseGame(int);
	int uhReadGame(int hfd,void *buf,int count);
	int uhWriteGame(int hfd,void *buf,int count);
	int uhReadRamrom(int hfd,void *ramrom_adr,void *buf,int 
	    count);
	int uhWriteRamrom(int hfd,void *ramrom_adr,void *buf,int 
	    count);
	int uhPartnerCmd(int hfd,char *ptcmd);
	int uhGload(int hfd,char *loadfile);

The following functions are supported on the Game (N64) side:

		void osReadHost(void *adr, u32 count);
		void osWriteHost(void *adr, u32 count);


With the exeception of uhPartnerCmd() and uhGload(), the above-
listed functions are compatible with the conventional system 
(HOSTIO on the Indy) functions.
	
uhPartnerCmd() and uhGload() are newly added functions.  Their 
specifications are described below.


uhGload() function specification:

	int uhGload (int hfd, char *loadfile);

	hfd :	The descriptor of HOSTIO opened with the
		uhOpenGame function.
	loadfile :	Name of program to load.

This function reads the file specified by loadfile into the ROM 
header (address 0xb0000000) as an N64 program and then executes 
the program.  When a path is not specified with loadfile for the 
executed file it is executed from the current directory.   When 
the function terminates normally it returns 0.  If the file 
cannot be found it returns -1.

	
uhPartnerCmd() function specification:

	int uhPartnerCmd (int hfd,char *ptcmd);

	hfd :	The descriptor of HOSTIO opened with the 
		uhOpenGame function.
	ptcmd : PARTNER-N64 command.

This function executes the character string specified by ptcmd as
a PARTNER-64 command (debug command).  As previously explained 
for the uhGload() function, the following sends the command to 
PARTNER:

	uhPartnerCmd (hfd, "rd FILENAME,0xb0000000\nreset\ng\n");

	
The uhGload()and uhPartnerCmd functions can be used in the same 
ways on the SGI platform with PARTNER-N64 (NW) Ver 1.02 and 2.0H'
or later.

You can use Microsoft Visual C Ver 4.2 or Borland C Ver 5.0 for 
the compiler when creating PC-side programs.   PC-side support 
functions are provided in Windows 95 DDL form 
(ultra\usr\sbin\hostiopc.dll).   Please locate the DDL in the 
Windows system directory (c:\windows\system  etc) or another 
directory in the path.  When ultra\setup.bat  is run ultra\sbin 
is set in the path so please refer to setup.bat.


If you are going to make use of the HOSTIO function, please refer
to the sample programs hostio and host_test.  The sample programs
can be actually run by compiling an N64-use program and a PC 
program in the microsoft of borland directory.


Note: If you are going to compile a sample, first set the 
compiler's install directory in setup.bat's MSVC or BCC 
environment variable.


Example where Microsoft Visual C installed in d:\msvc

	rem set Microsoft Visual C Ver 4.2 install directory
	set MSVC=d:\msvc

Example where Borland C installed in d:\bc5

	rem set Borland C Ver 5.0 install directory
	set BCC=d:\bc5