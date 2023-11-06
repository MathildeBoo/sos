# MAKEFILE for TDA Coord (coordonnees d'une case)
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

MOD = coord.o coords.o

coord.o : coord.c coord.h 
	$(CCOBJ) $(FLAGS) coord.c -o coord.o -I./ -I$(commun_dir)

coords.o : coords.c coords.h 
	$(CCOBJ) $(FLAGS) coords.c -o coords.o -I./ -I$(commun_dir)

#
#-------- Modules externes -------------
#
include $(top_dir)/Makefile.depend

#
#-------- Headers -------------
#

coord.h : $(commun_dir)/commun.h
	touch coord.h

coords.h : coord.h
	touch coords.h 

#
#-------- Clean objects -------
#

clean : 
	- rm $(MOD)


#
#-------- All executables -------
#

all : $(MOD) 

#
#-------- Tests -------
#

tests : 








