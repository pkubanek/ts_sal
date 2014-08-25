#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile - Ndds based Image multi-send, no retransmits

#
# REQUIREMENTS:
#       gmake, makedepend, makes/<lots>.mak
#
# USAGE:
#       make depend     # setup dependencies and sub directories (do first)
#       make all        # build all standard targets
#       make install    # install target(s) and fixes group and permissions
#       make clean      # remove intermediate files (for a full rebuild)
#       make clean-dist # remove all built files and directories
#------------------------------------------------------------------------------

# several rules rely on borne shell syntax/abilities
SHELL=/bin/sh
# Determine what operating system we are trying to build for
# Override this on the command line for cross compilation (e.g. OS=m68kVx5.1)
OS := $(shell uname -s)

include makes/site.mak		# get all those site specific pathes...

##############################################################################
################ Where to find/put things
# keep install directrories relative if possible
TOPDIR :=	../..
BINDIR :=	$(TOPDIR)/bin
LIBDIR :=	$(TOPDIR)/lib
INCDIR :=	$(TOPDIR)/include
TCLHOME :=	/usr/lib
MV1HOME :=	../mv1000
TARDIR :=	$(HOME)/bak

##############################################################################
################ Targets
SRCCS := mv.cc pt.cc
SRCS := 
EXECS = $(OS)/netgrab $(OS)/cgrab $(OS)/xgrab
INCS := scicamera.h

# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIB := cstereo
# shared library major version #s represent visible changes to the API
#LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install

# file name for make backup or export images
TARFILE :=	$(TARDIR)/cstereo.tar

# CDEBUG is often passed in on the command line for quick debugging
CDEBUG	:= -g -O

INCLUDES =	-I. -I$(INCDIR) -I$(MV1HOME)/inc $(X11_INCDIR)

LDLIBS  =	-L$(OS) -L$(LIBDIR)/$(OS) -L$(MV1HOME)/lib \
	-lcstereo -lmv1 \
	-lpicservo  -limageNdds -lutil \
	-lImagePacketNdds -lScienceNdds -lTelemetryNdds

#	$(LIBDIR)/$(OS)/libpicservo.a  $(LIBDIR)/$(OS)/libreadpnm.a \
#	$(LIBDIR)/$(OS)/libimageNdds.a $(LIBDIR)/$(OS)/libutil.a \


# get standard rules for compiling C files
include makes/c-rules.mak

# get all the architecture specific pathes and switches
include makes/$(OS).mak

include makes/ndds.mak

MVFLAGS := -Dlinux -D__i386__ -D_POSIX_SOURCE -D_BSD_SOURCE -D_GNU_SOURCE \
	-D_MTLINUX_ -DX_LOCALE  -DFUNCPROTO=15 -DNARROWPROTO

CPPFLAGS += -D_REENTRANT $(MVFLAGS)

LDLIBS  += -lssl -lm

# create the list of target objects from the list of sources
OBJS = $(SRCCS:.cc=.o) $(SRCS:.c=.o)

# convert name to reflect sub directories
OSOBJS =	$(OBJS:%.o=$(OS)/%.o)

TARGETS =	$(OS)/lib$(LIB).a

# Default build rule
all:	$(EXECS) $(TARGETS)

include makes/buildlib.mak

##############################################################################
################ Actual build rules

# create the main program
$(OS)/netgrab:	$(OS)/netgrab.o $(TARGETS)
	$(C++) -o $@ $(CPPFLAGS) $(CFLAGS) $(OS)/netgrab.o \
	 $(LDFLAGS) $(LDLIBS)

# create the NDDS test program
$(OS)/nddstest:	nddstest.cc
	$(C++) -o $@ $(CPPFLAGS) $(CFLAGS) nddstest.cc $(LDFLAGS) $(LDLIBS)

# create the test program
# cgrab uses no NDDS stuff
$(OS)/cgrab:	cgrab.cc $(TARGETS)
	$(C++) -o $@ $(CPPFLAGS) $(CDEBUG) \
	-I. -I$(INCDIR) -I$(MV1HOME)/inc $(X11_INCDIR) \
	 cgrab.cc  $(LDFLAGS) -L$(OS) -L$(MV1HOME)/lib -L$(LIBDIR)/$(OS) \
	-lcstereo -lmv1 -lpicservo $(LIBDIR)/$(OS)/libimageNdds.a -lutil \
	$(TCL_LIBDIR) -ltcl -ltk $(X11_LIBDIR) -lXext -lX11 -lssl -lm $(OSLIBS)

# create the original test program
# xgrab uses no NDDS or Tcl stuff
$(OS)/xgrab:	xgrab.c
	$(C++) -o $@ $(CDEBUG) $(CPPFLAGS) xgrab.c $(LDFLAGS) \
	 -L$(MV1HOME)/lib -lmv1 $(X11_LIBDIR) -lXext -lX11 -lm

test:	$(OS)/servotest

$(OS)/servotest:	$(OS)/servotest.o $(OS)/lib$(LIB).a
	$(C++) -o $@ $(CPPFLAGS) $(CDEBUG) \
	-I. -I$(INCDIR) $(OS)/servotest.o \
	$(LDFLAGS) -L$(OS) -L$(LIBDIR)/$(OS) \
	-lcstereo -lpicservo -lutil -lssl

# pick up library dependencies
$(OS)/servotest:	$(LIBDIR)/$(OS)/libutil.a \
	$(LIBDIR)/$(OS)/libssl.a \
	$(LIBDIR)/$(OS)/libpicservo.a

$(OS)/netgrab:	$(LIBDIR)/$(OS)/libutil.a \
	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libssl.a \
	$(LIBDIR)/$(OS)/libpicservo.a \
	$(LIBDIR)/$(OS)/libimageNdds.a \
	$(LIBDIR)/$(OS)/libScienceNdds.a \
	$(LIBDIR)/$(OS)/libTelemetryNdds.a \
	$(LIBDIR)/$(OS)/libImagePacketNdds.a


# Use this to rebuild targets even though dependencies don't show a need to
remake:
	rm -f $(EXECS) $(TARGETS)
	$(MAKE) all

install:	do_install

do_install:	$(EXECS) $(TARGETS) $(INCS)

depend:	netgrab.cc cgrab.cc xgrab.c servotest.cc

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
