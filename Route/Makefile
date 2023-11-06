# MAKEFILE for TDA Route
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
fich_obj_init_fich_route = init_fich_route.o route.o  \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o


#
#-------- Mains ---------------
#
BIN = init_fich_route 

init_fich_route : $(fich_obj_init_fich_route)
	$(CCLNK) $(fich_obj_init_fich_route) $(FLAGS)  -o init_fich_route 

init_fich_route.o : init_fich_route.c route.h
	$(CCOBJ) $(FLAGS)  init_fich_route.c -o init_fich_route.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)

#
#-------- Modules -------------
#
MOD = route.o

route.o : route.c route.h 
	$(CCOBJ) $(FLAGS)  route.c -o route.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)

#
#-------- Modules externes -------------
#
include $(top_dir)/Makefile.depend

#
#-------- Headers -------------
#

route.h : $(voiture_dir)/voiture.h
	touch route.h

#
#-------- Clean objects -------
#

clean : 
	- rm $(MOD)


#
#-------- All executables -------
#

all : init_fich_route

#
#-------- Tests -------
#

tests : 





