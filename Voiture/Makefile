# MAKEFILE for TDA Voiture
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

#
# Object files
#

#
#-------- Mains ---------------
#

#
#-------- Modules -------------
#
MOD = voiture.o

voiture.o : voiture.c voiture.h  
	$(CCOBJ) $(FLAGS)  voiture.c -o voiture.o -I$(commun_dir) -I$(coord_dir) -I./


#
#-------- Modules externes -------------
#
include $(top_dir)/Makefile.depend

#
#-------- Headers -------------
#

voiture.h : $(coord_dir)/coords.h
	touch voiture.h

#
#-------- Clean objects -------
#

clean :
	- rm $(MOD)


#
#-------- All executables -------
#

all :

#
#-------- Tests -------
#

tests :

