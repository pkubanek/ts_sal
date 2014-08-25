#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# OS independent stuff to pull to compile programes that use NDDS
# the OS dependent file may be pulled in before or after this

# top directory for RTI stuff
NDDSHOME = $(RTIHOME)/ndds
#NDDSHOME = $(RTIHOME)/ndds.1.10c

#NOTE that RTIARCH and RTIDEF get defined in the os specific make files.

ifeq (,$(findstring Vx5.,$(OS)))	# get Unix includes
NDDS_INCDIR =	-I$(NDDSHOME)/makehome/headerFixes/unix/$(RTIARCH) \
	-I$(NDDSHOME)/include/unix -I$(NDDSHOME)/include/share \
	-I$(RTIHOME)/rtilib/include/share \
	-I$(RTIHOME)/rtilib/include/unix
#NDDS_INCDIR =	-I$(NDDSHOME)/include/unix -I$(NDDSHOME)/include/share
else					# get vxWorks includes
NDDS_INCDIR =	-I$(NDDSHOME)/include/vx -I$(NDDSHOME)/include/share
endif
NDDS_LIBDIR =	-L$(NDDSHOME)/lib/$(RTIARCH) \
		-L$(NDDSHOME)/lib/$(RTIARCH)/nddstypes
NDDS_LIBS =	-lndds -lutilsip

CPPFLAGS +=	$(RTIDEF) $(NDDS_INCDIR)
LDLIBS +=	$(NDDS_LIBDIR) $(NDDS_LIBS)
