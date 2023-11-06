# MAKEFILE for Exemples TP Route
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

fich_obj_ex_deplacement = ex_deplacement.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o \
	$(route_dir)/route.o

fich_obj_ex_depassement = ex_depassement.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o \
	$(route_dir)/route.o

#
#-------- Mains ---------------
#
BIN = ex_deplacement ex_depassement


ex_deplacement : $(fich_obj_ex_deplacement)
	$(CCLNK) $(fich_obj_ex_deplacement) $(FLAGS)  -o ex_deplacement 

ex_deplacement.o : ex_deplacement.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  ex_deplacement.c -o ex_deplacement.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)

ex_depassement : $(fich_obj_ex_depassement)
	$(CCLNK) $(fich_obj_ex_depassement) $(FLAGS)  -o ex_depassement 

ex_depassement.o : ex_depassement.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  ex_depassement.c -o ex_depassement.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir) 

#
#-------- Modules -------------
#


#
#-------- Modules externes -------------
#
include $(top_dir)/Makefile.depend

#
#-------- Headers -------------
#



#
#-------- Clean objects -------
#

clean :
	- rm *~
	- rm *.o
	- rm $(BIN)


#
#-------- All executables -------
#

all : ex_deplacement ex_depassement 

#
#-------- Tests -------
#

tests : 





