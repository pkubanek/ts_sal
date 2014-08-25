#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile
#	Makefile for loadable NDDS image reception in Tcl/Tk
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
#------------------------------------------------------------------------------

# several rules rely on borne shell syntax/abilities
SHELL=/bin/sh

# set OS (if not passed in on command line)
OS := $(shell uname -s)

include makes/site.mak		# get all those site specific pathes...

# keep install directrories relative if possible
TOPDIR=../../../..
BINDIR=$(TOPDIR)/bin
LIBDIR=$(TOPDIR)/lib
INCDIR=$(TOPDIR)/include

###############################################################################
################# Targets
# major version represent visible changes to the API
LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install
# this is a default, it will usually be overridden later
LIBMIN := 0
LIB :=	imagetcl

#CSMatTclNddsDriver.c 
SRCS := nddsImage.c  imagetcl.c

INCLUDES = -I$(INCDIR) $(X11_INCDIR) $(TCL_INCDIR)

CPPFLAGS   = $(INCLUDES)
LDSHARELIBS  = -L../$(LIBDIR)/$(OS) -L$(LIBDIR)/$(OS) \
	-lImagePacketNdds ../$(LIBDIR)/$(OS)/libimageNdds.a -lutil \
	$(TCL_LIBDIR) $(TCL_LIBS) $(X11_LIBDIR) -lX11 $(OSLIBS)

# get standard rules for compiling C files
include makes/c-rules.mak

# pull in NDDS compile stuff
include makes/ndds.mak

# make sure these are last on the list
LDLIBS +=  -lX11 $(OSLIBS)

# get all the architecture specific pathes and switches
include makes/$(OS).mak
# force gcc
CC=gcc -fPIC -Wall -DNDDS_1_11Q -DNDDS_2_0
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
all: $(TARGETS)

include makes/buildlib.mak

# pick up library dependencies
$(OS)/libimagetcl.so.$(LIBMAJ).$(LIBMIN):	$(LIBDIR)/$(OS)/libutil.so \
	$(LIBDIR)/$(OS)/libimageNdds.so \
	$(LIBDIR)/$(OS)/libImagePacketNdds.a

# Use this to rebuild targets even though dependencies don't show a need to
remake:
	rm -f $(EXECS) $(TARGETS)
	$(MAKE) all

# do_install always does all file installs
install:	do_install

do_install:	$(TARGETS) $(EXECS) 

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
