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

include makes/site.mak		# get all those site specific pathes...

##############################################################################
################ Where to find/put things
# keep install directrories relative if possible
TOPDIR :=	../../../..
BINDIR :=	$(TOPDIR)/bin
LIBDIR :=	$(TOPDIR)/lib
INCDIR :=	$(TOPDIR)/include

##############################################################################
################ Targets
SRCCS := sender.cc itimer.cc
SRCS := headerAlloc.c packetAlloc.c
EXECS =  $(OS)/sendpnm $(OS)/imageroute
# Don't currently want to install this receive for nomad.
# It will clash with the imageReceiver module.
#EXECS = $(OS)/imageReceive

INCS := imageNdds.h imageTimer.h

# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIB := imageNdds
# shared library major version #s represent visible changes to the API
LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install

# CDEBUG is often passed in on the command line for quick debugging
CDEBUG	:= -g -O
#CDEBUG	:= -O

INCLUDES =	-I. -I$(INCDIR) \
	-I$(NDDSHOME)/include/unix -I$(NDDSHOME)/include/share

LDLIBS  = -L$(OS) -L$(LIBDIR)/$(OS) -limageNdds -lutil \
	$(LIBDIR)/$(OS)/libreadpnm.a -lImagePacketNdds $(NETLIBS)

# get standard rules for compiling C files
include makes/c-rules.mak

# get all the architecture specific pathes and switches
include makes/$(OS).mak

include makes/ndds.mak

#CPPFLAGS += -D_REENTRANT
# -DNDDS110

#LDLIBS  +=  -ltcl -lm $(OSLIBS)

ifdef LDSHARE
# this is a default, it will usually be overridden below
LIBMIN := 0
ifeq ($(OS)/lib$(LIB).$(LIBMAJ).v,$(wildcard $(OS)/l?b$(LIB).$(LIBMAJ).v))
include $(OS)/lib$(LIB).$(LIBMAJ).v
endif
TARGETS :=	$(OS)/lib$(LIB).a $(OS)/lib$(LIB).so.$(LIBMAJ).$(LIBMIN)
else
TARGETS :=	$(OS)/lib$(LIB).a
endif

# create the list of target objects from the list of sources
OBJS = $(SRCCS:.cc=.o) $(SRCS:.c=.o)

# convert name to reflect sub directories
OSOBJS =	$(OBJS:%.o=$(OS)/%.o)

# Default build rule
# build imageReceive, but dont have it installed
all:	$(EXECS) $(TARGETS) $(OS)/imageReceive

include makes/buildlib.mak

C++ += -DNDDS_1_11Q -DNDDS_2_0

##############################################################################
################ Actual build rules

# create the test program
$(OS)/sendpnm:	$(OS)/sendpgm.o $(TARGETS)
	$(C++) -o $@ $(CDEBUG) $(OS)/sendpgm.o \
	$(LDFLAGS) $(OS)/lib$(LIB).a $(LDLIBS)

# this is a stand alone image receiver that outputs to a .pgm file
$(OS)/imageReceive:	imageReceive.cc $(TARGETS)
	$(C++) -o $@ $(CDEBUG) imageReceive.cc \
	$(INCLUDES) $(RTIDEF) $(NDDS_INCDIR) $(LDFLAGS)  \
	-L$(OS) -L$(LIBDIR)/$(OS) $(OS)/libimageNdds.a -lImagePacketNdds \
	$(LIBDIR)/$(OS)/libimagetcl.a -lutil \
	$(NDDS_LIBDIR) $(NDDS_LIBS) $(X11_LIBDIR) -lX11 -lm \
	$(OSLIBS) $(NETLIBS)

#	-Xlinker -v -Xlinker --stats -Xlinker --verbose

# image cache and router
$(OS)/imageroute:	$(OS)/imageRoute.o $(TARGETS)
	$(C++) -o $@ $(CDEBUG) $(OS)/imageRoute.o \
	$(LDFLAGS) -L$(OS) -L$(LIBDIR)/$(OS) \
	-limageNdds -lImagePacketNdds -lEventNdds -lutil \
	$(NDDS_LIBDIR) $(NDDS_LIBS) $(NETLIBS)

# pick up library dependencies
$(OS)/sendpnm:	$(LIBDIR)/$(OS)/libutil.a \
	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libImagePacketNdds.a

$(OS)/imageReceive:	$(LIBDIR)/$(OS)/libutil.a \
	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libImagePacketNdds.a

$(OS)/imageroute:	$(LIBDIR)/$(OS)/libutil.a \
	$(LIBDIR)/$(OS)/libreadpnm.a \
	$(LIBDIR)/$(OS)/libImagePacketNdds.a

# Use this to rebuild targets even though dependencies don't show a need to
remake:
	rm -f $(EXECS) $(TARGETS)
	$(MAKE) all

install:	do_install

do_install:	$(EXECS) $(TARGETS) 

# add and extra file to the dependency search
depend:	sendpgm.cc imageReceive.cc imageRoute.cc

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
