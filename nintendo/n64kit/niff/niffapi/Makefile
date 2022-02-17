# -*-makefile-*-
#                                                            
#    NIFF API sample program
#		    Copyright (C) 1998 NINTENDO Co.,Ltd.     
#		    Copyright (C) 1998 MONEGI CORPORATION    
###############################################################
NIFFROOT = $(HOME)/NIFF
TARGET = sample
INCLUDES = -I.
DEPEND = depend

#CFLAGS = -g -xansi $(INCLUDES) -MDupdate $(DEPEND)
#CFLAGS = -g -xansi $(INCLUDES) -MDupdate $(DEPEND) -DDEBUG
CFLAGS = -O2 -xansi $(INCLUDES) -MDupdate $(DEPEND)

$(TARGET): $(TARGET).o libnis.a
	cc $(TARGET).o -o $(TARGET) -lnis -L.

clean: 
	rm -f *.o *~ $(TARGET) $(DEPEND)
	touch $(DEPEND)

include $(DEPEND)
# DO NOT DELETE
