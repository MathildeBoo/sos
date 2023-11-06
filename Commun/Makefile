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

MOD = commun.o 

commun.o : commun.c commun.h 
	$(CCOBJ) $(FLAGS) commun.c -o commun.o -I./ 


#
#-------- Headers -------------
#


#
#-------- Clean objects -------
#

clean : 
	- rm $(OBJ)


#
#-------- All  -------
#

all : $(MOD) 

#
#-------- Tests -------
#

tests :





