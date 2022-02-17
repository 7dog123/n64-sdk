The Standard Function Library V1.3 (libnustd.a) 

The standard function library, libnustd.a, is an ANSI-compliant function
library. The library was created as a supplement to the N64 OS/Library, 
which contains only a portion of the functions of the ANSI library.

With the exception of console input/output, most of the functions 
conform to the ANSI standard and are included with the source code so 
they can be customized by the user.

The numerical computation functions come in double and float versions. 
The memory allocation routine incorporates an alignment adjustment 
function, but there is also a routine to check the consistency of 
memory allocations.

For details about each of the functions, see the standard function 
reference in the NuSYSTEM manual or the comments in the source code 
for each function.



Procedure For Using the SGI Compiler

In order to use the standard function library, you must specify the 
following include and library paths in the Makefile.


  N64KITDIR    = /usr/local/n64kit
  NUSTDINCDIR  = $(N64KITDIR)/nustd/include
  NUSTDLIBDIR  = $(N64KITDIR)/nustd/lib
 
    .
    .
    .

  LCINCS =     -I$(NUSTDINCDIR)
  LDFLAGS =    $(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib -L$(NUSTDLIBDIR) \
		-u sprintf -lultra_d -lnustd_d
 
When making a ROM version, define LDFLAGS as follows:

  LDFLAGS =    $(MKDEPOPT) -nostdlib -L$(ROOT)/usr/lib L$(NUSTDLIBDIR) \
		-lultra_rom -lnustd

Because sprintf is internally called by some functions including 
malloc_memcheck(), mt_malloc_memcheck(), malloc_memdsp(), and 
mt_malloc_memdsp(), it is necessary to indicate -u sprintf when these 
functions are used.



Procedure For Using exeGCC (N64)

exeGCC comes with an ANSI standard library, so there will probably be 
little need for libnustd.a.  However, because the function names and 
include names are the same as those used by exeGCC, the following 
options must be attached if the library is going to be used.

  N64KITDIR    = c:\nintendo\n64kit
  NUSTDINCDIR  = $(N64KITDIR)/nustd/include
  NUSTDLIBDIR  = $(N64KITDIR)/nustd/lib

  .c.o:
	$(CC) -g -G 0 -c -nostdinc -I- -I$(NUSTDINCDIR) -I$(INC)/PR \
	-I$(INC)  -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 $<

    .
    .
    .

  LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSTDLIBDIR) -L$(GCCDIR)/mipse/lib \
		-lgultra_d -lnustd_d -lkmc


The "-nostdinc -I-"  option is added to .c.o: so the routine will not 
look in the exeGCC ANSI standard library include file.


When making a ROM version, define LDFLAGS as follows:

LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSTDLIBDIR) -L$(GCCDIR)/mipse/lib \
		-lgultra_rom -lnustd -lkmc



Rebuilding the Standard Function Library

You can rebuild the standard library by running 'make' in the nustd/src
directory. Running 'make' builds the ROM version library (libnustd.a).
Running 'make deb' builds the debug version library (libnustd_d.a).
(It is safer to delete all of *.o and *.a files before using 'make') 

The difference between the ROM version and Debug version in Ver1.3 
includes the optimization levels that each has and whether debug 
information is contained.
 


Library Search Order

The linker will search for functions in the order declared with the -l 
option. Note that if the same function is contained in different 
libraries, the linked object will differ depending on the order in 
which the libraries were searched.

Some functions were provided in both this library, Ver1.1 or previous 
versions and the N64OS library. However, in Ver1.3 these functions are 
renamed to avoid confusion. These functions and their corresponding new 
function names are shown below.

  sqrtf()  --> _nsqrtf()
  strchr() --> _nstrchr()
  strlen() --> _nstrlen()
  memcpy() --> _nmemcpy()
  ldiv()   --> _nldiv()
  sinf()   --> _nsinf()
  cosf()   --> _ncosf()



Notes Regarding the Standard Function Library

* errno is not available.
* It is not guaranteed how the functions sin() and cos() behave when 
  values close to the maximum value for each argument are specified. 
  Because there is also a problem regarding floating point precision, 
  please design your program so as not to make the resulting angles 
  significantly large.
* malloc() does not support simultaneous access from multiple threads. 
  mt-malloc() supporting multiple threads is provided for malloc().
* malloc() uses 16-byte alignment.
* Alignment is not guaranteed if realloc is performed to the area 
  reserved using memalign().
* setjmp() does not support saving the FPU register.

