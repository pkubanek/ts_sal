#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile
#	Makefile for nddswish (multi-architecture)
#	Makefile for nddstcl (multi-architecture)
#
# REQUIREMENTS:
#	OS environment variable MUST be set (usually 'setenv OS=`uname`')
#	gmake (Sun make may work)
#	makedepend
#
# USAGE:
#	make depend	# setup dependencies and sub directories
#	make all	# build all standard targets
#	make install	# install target(s) and fixes group and permissions
#	make clean	# remove intermediate files (for a full rebuild)
#	make clean-dist	# remove all built files and directories
#
#------------------------------------------------------------------------------

# several rules rely on borne shell syntax/abilities
SHELL=/bin/sh

include makes/site.mak          # get all those site specific pathes...

# keep install directrories relative if possible
TOPDIR=../../..
BINDIR=$(TOPDIR)/bin
LIBDIR=$(TOPDIR)/lib
INCDIR=$(TOPDIR)/include

###############################################################################
################# Targets
EXECS = $(OS)/nddswish $(OS)/nddstcl
# major version represent visible changes to the API
#LIBMAJ := 2
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install
# this is a default, it will usually be overridden later
LIBMIN := 0
LIB :=	nddstcl

#CSMatTclNddsDriver.c 
SRCS := nddsInit.c getdate.c

# Libraries that do depend on OS
NOMAD_NDDS_LIBS	:= \
		-lCommonNdds \
		-lDatabaseNdds \
		-lEventNdds \
		-lHiResNdds \
		-lMissionPlannerNdds \
		-lNavNdds \
		-lPanoramicNdds \
		-lRtNdds \
		-lScienceNdds \
		-lSensorManNdds \
		-lSpectrometerNdds \
		-lTelemetryNdds 

INCLUDES = -I$(INCDIR) $(X11_INCDIR) $(TCL_INCDIR)

# compile in the imagendds command -DINCLUDE_IMAGE_TCL
CPPFLAGS   =  $(INCLUDES)

# add these in if INCLUDE_IMAGE_TCL is defined
#	 -limagetcl -lutil \
#
ifeq (,$(findstring IRIX,$(OS)))
# Linux/soloris wont load libimagetcl unless we link these in now
# (even though never called)
LDLIBS  = -L$(LIBDIR)/$(OS) $(NOMAD_NDDS_LIBS) -lreadpnm -lutil \
	 -limagetcl \
	$(TCL_LIBDIR) $(TCL_LIBS)
else
LDLIBS  = -L$(LIBDIR)/$(OS) $(NOMAD_NDDS_LIBS) -lreadpnm -lutil \
	$(TCL_LIBDIR) $(TCL_LIBS)
endif

# get standard rules for compiling C files
include makes/c-rules.mak

# pull in NDDS compile stuff
include makes/ndds.mak

# make sure these are last on the list
LDLIBS +=  $(X11_LIBDIR) -lX11 -lm $(OSLIBS) $(NETLIBS)

# get all the architecture specific pathes and switches
include makes/$(OS).mak

# use gcc to avoid link problems with C++ libraries
CC=gcc -Wall -DNDDS_1_11Q -DNDDS_2_0
CDEBUG = -g -O

ifdef LDSHARE
ifeq ($(OS)/lib$(LIB).$(LIBMAJ).v,$(wildcard $(OS)/l?b$(LIB).$(LIBMAJ).v))
include $(OS)/lib$(LIB).$(LIBMAJ).v
endif
TARGETS=	$(OS)/lib$(LIB).a $(OS)/lib$(LIB).so.$(LIBMAJ).$(LIBMIN)
else
TARGETS=	$(OS)/lib$(LIB).a
endif

# create the list of target objects from the list of sources
OBJS := $(SRCS:.c=.o)
# convert name to reflect sub directories
OSOBJS :=	$(OBJS:%.o=$(OS)/%.o)

###############################################################################
#			         Build rules
###############################################################################
all: $(EXECS) $(TARGETS)

libs: $(TARGETS)

$(OS)/nddswish:	$(OS)/nddswish.o $(TARGETS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OS)/nddswish.o -L./$(OS) -l$(LIB) $(LDLIBS)

$(OS)/nddstcl:	$(OS)/nddstcl.o $(TARGETS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OS)/nddstcl.o -L./$(OS) -l$(LIB) $(LDLIBS)

# pull in library dependencies
$(OS)/nddswish:	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libCommonNdds.a \
	$(LIBDIR)/$(OS)/libDatabaseNdds.a \
	$(LIBDIR)/$(OS)/libEventNdds.a \
	$(LIBDIR)/$(OS)/libHiResNdds.a \
	$(LIBDIR)/$(OS)/libMissionPlannerNdds.a \
	$(LIBDIR)/$(OS)/libNavNdds.a \
	$(LIBDIR)/$(OS)/libPanoramicNdds.a \
	$(LIBDIR)/$(OS)/libRtNdds.a \
	$(LIBDIR)/$(OS)/libScienceNdds.a \
	$(LIBDIR)/$(OS)/libSensorManNdds.a \
	$(LIBDIR)/$(OS)/libSpectrometerNdds.a \
	$(LIBDIR)/$(OS)/libTelemetryNdds.a

$(OS)/nddstcl:	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libCommonNdds.a \
	$(LIBDIR)/$(OS)/libDatabaseNdds.a \
	$(LIBDIR)/$(OS)/libEventNdds.a \
	$(LIBDIR)/$(OS)/libHiResNdds.a \
	$(LIBDIR)/$(OS)/libMissionPlannerNdds.a \
	$(LIBDIR)/$(OS)/libNavNdds.a \
	$(LIBDIR)/$(OS)/libPanoramicNdds.a \
	$(LIBDIR)/$(OS)/libRtNdds.a \
	$(LIBDIR)/$(OS)/libScienceNdds.a \
	$(LIBDIR)/$(OS)/libSensorManNdds.a \
	$(LIBDIR)/$(OS)/libSpectrometerNdds.a \
	$(LIBDIR)/$(OS)/libTelemetryNdds.a

# Use this to rebuild targets even though dependencies don't show a need to
remake:
	rm -f $(EXECS) $(TARGETS)
	$(MAKE) all

include makes/buildlib.mak

# do_install always does all file installs
install:	$(EXECS) do_install

# add and extra file to the dependency search
depend:	nddswish.c nddstcl.c

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
