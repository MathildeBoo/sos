# MAKEFILE for TP Route
#
#



#
# Directories
#

top_dir = .
include $(top_dir)/Makefile.dir
include $(top_dir)/Makefile.compilation

all , clean  :
	cd $(commun_dir) ; make -f Makefile $@ 
	cd $(coord_dir) ; make -f Makefile $@  
	cd $(voiture_dir) ; make -f Makefile $@ 
	cd $(route_dir) ; make -f Makefile $@
	cd $(verrous_dir) ; make -f Makefile $@
	cd $(exemples_dir) ; make -f Makefile $@ 
