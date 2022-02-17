#-*-indented-text-*-
#
#   NIFFAPI Document		    
#
#	    Copyright (C) 1998, NINTENDO Co.,Ltd.
#	    Copyright (C) 1998, MONEGI CORPORATION
#
# $Id: README,v 1.3 1999/07/21 13:49:35 yoshino Exp $
#

[Term definitions]

NIS		Structure that is compatible with NIFF.  Defined with nis.h/nis2.h.   
NIS1.0		NIS that is compatible with NIFF Ver1.0.    
NIFF 
binary file	A file with the format that is defined in the NIFF specifications.  

NIFF text	NIFF binary file was changed to text and is readable. Made 
		possible to read and write this text using NIFFAPI.  Currently, 
		refer to the output of NIFFAPI niOutPutNt() for the definition. 
		     

[NIFFAPI functions list]   Refer to niffapi.h.   

[Usage]
	Refer to sample.c and Makefile.   
	Declare Nis structure and initialize it using niNewNis() first.
	Compile with the SGI version is done with the MPS Compiler on IRIX 6.2, 
	6.3, 6.5
	PC version is possible with Visual C++ 5.0

[Appendix]  
	niPrint*List() that outputs the contents of NIS is provided for debugging.  
	Refer to nidebugprint.c.

						    
	
	
		



	
