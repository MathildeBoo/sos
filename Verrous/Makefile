# MAKEFILE for Exemples TP Route
#
#

#
# Directories
#
top_dir = ..
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

FLAGS_NO_USE=-Wno-unused-variable -Wno-unused-but-set-variable

#
# Object files
#
fich_obj_init_fich_route = init_fich_route.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o  \
	$(route_dir)/route.o

fich_obj_vision = vision.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o  \
	$(route_dir)/route.o  

fich_obj_voiture_v1 = voiture_v1.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o \
	$(route_dir)/route.o

fich_obj_voiture_v2 = voiture_v2.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o \
	$(route_dir)/route.o

fich_obj_voiture_test = voiture_test.o \
	$(commun_dir)/commun.o \
	$(coord_dir)/coord.o $(coord_dir)/coords.o \
	$(voiture_dir)/voiture.o \
	$(route_dir)/route.o

#
#-------- Mains ---------------
#
BIN = init_fich_route vision voiture_v1 voiture_v2 voiture_test

init_fich_route : $(fich_obj_init_fich_route)
	$(CCLNK) $(fich_obj_init_fich_route) $(FLAGS)  -o init_fich_route 

init_fich_route.o : init_fich_route.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  init_fich_route.c -o init_fich_route.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)

vision : $(fich_obj_vision)
	$(CCLNK) $(fich_obj_vision) $(FLAGS)  -o vision 

vision.o : vision.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  vision.c -o vision.o \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir) $(FLAGS_NO_USE)


voiture_v1 : $(fich_obj_voiture_v1)
	$(CCLNK) $(fich_obj_voiture_v1) $(FLAGS)  -o voiture_v1 

voiture_v1.o : voiture_v1.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  voiture_v1.c -o voiture_v1.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)  $(FLAGS_NO_USE)


voiture_v2 : $(fich_obj_voiture_v2)
	$(CCLNK) $(fich_obj_voiture_v2) $(FLAGS)  -o voiture_v2 

voiture_v2.o : voiture_v2.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  voiture_v2.c -o voiture_v2.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)  $(FLAGS_NO_USE)


voiture_test : $(fich_obj_voiture_test)
	$(CCLNK) $(fich_obj_voiture_test) $(FLAGS)  -o voiture_test 

voiture_test.o : voiture_test.c $(route_dir)/route.h
	$(CCOBJ) $(FLAGS)  voiture_test.c -o voiture_test.o -I./ \
	-I$(commun_dir) \
	-I$(coord_dir) \
	-I$(voiture_dir) \
	-I$(route_dir)  $(FLAGS_NO_USE)

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

all : init_fich_route vision voiture_v1 voiture_v2 voiture_test

#
#-------- Tests -------
#

tests : 





