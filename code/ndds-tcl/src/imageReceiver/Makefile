#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile - Ndds based Image multi-send to w/retransmits
#	This is an odd build, we have a multi-threaded library and application
#	and a single threaded application.
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

##############################################################################
################ Where to find/put things
# keep install directrories relative if possible
TOPDIR :=	../..
BINDIR :=	$(TOPDIR)/bin
LIBDIR :=	$(TOPDIR)/lib
INCDIR :=	$(TOPDIR)/include
ifdef USE_TCL
TCLHOME :=	/apps/supported
endif

GCC := gcc
G++ := gcc

##############################################################################
################ Targets
SRCCS := queue.cc 
SRCS := sleep_us.c headerAlloc.c packetAlloc.c sharedMem.c 
# if not on VxWorks, also compile applications
ifeq (,$(findstring Vx5.,$(OS)))
EXECS = $(OS)/imageReceive
endif
				# HACK only compile threaded stuff if available
# INCS := imageNdds.h fifo.h

#
# Shared lib building is turned off.  Clashes with the real imageNdds library.
#


# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIB := imageReceiver
# major version represent visible changes to the API
#LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install

# CDEBUG is often passed in on the command line for quick debugging
CDEBUG	:= -g -O

INCLUDES =	-I. -I$(INCDIR) \
	-I$(NDDSHOME)/include/unix -I$(NDDSHOME)/include/share \

#	-I/home/artemis/usr1/dac/include
#last line above are two hacks!

SUMMUS_INC := 	-I/projects/nomad/packages/summus/IRIX

#LDLIBS  = $(LIBDIR)/$(OS)/libimgControllerNdds.a \
LDLIBS  = /home/artemis/usr1/dac/lib/IRIX/libimgControllerNdds.a \
	$(LIBDIR)/$(OS)/libreadpnm.a \
	-lpthread

# get standard rules for compiling C files
include makes/c-rules.mak

# get all the architecture specific pathes and switches
include makes/$(OS).mak

include makes/ndds.mak

CPPFLAGS += -D_REENTRANT

#LDLIBS  +=  -ltcl -lm $(OSLIBS)

# Use ld_old if this is an IRIX 6.X machine
ifeq ($(shell uname -r > opsys; sed 's/\..*//' < opsys; /bin/rm opsys),6)
LDFLAGS  += -ld_old
endif

ifdef LDSHARE
# this is a default, it will usually be overridden below
LIBMIN := 0
ifeq ($(OS)/lib$(LIB).$(LIBMAJ).v,$(wildcard $(OS)/l?b$(LIB).$(LIBMAJ).v))
include $(OS)/lib$(LIB).$(LIBMAJ).v
endif
TARGETS :=	$(OS)/lib$(LIB).a # $(OS)/lib$(LIB).so.$(LIBMAJ).$(LIBMIN)
else
TARGETS :=	$(OS)/lib$(LIB).a
endif

# create the list of target objects from the list of sources
OBJS = $(SRCCS:.cc=.o) $(SRCS:.c=.o)

# convert name to reflect sub directories
OSOBJS =	$(OBJS:%.o=$(OS)/%.o)

# Default build rule
all:	$(OS)/imageReceive $(OS)/IPCclean $(OS)/testRcv  \
	$(EXECS) $(TARGETS)

# Added summus code when possible.  libSWI32
ifeq ($(OS),IRIX)
  ifeq (5.3,$(shell uname -r))
  endif
  ifeq (6.2,$(shell uname -r))
# Can't seem to figure out how to build summus here.
  endif
  ifeq (6.3,$(shell uname -r))
# Geb's O2
all:: $(OS)/testDcmpRcv
  endif
  ifeq (6.4,$(shell uname -r))
all:: $(OS)/testDcmpRcv
  endif
else
all:
endif

include makes/buildlib.mak

##############################################################################
################ Actual build rules

# Temporarily force building with tcl/tk
USE_TCL := true

ifdef USE_TCL
TCL_CPPFLAGS := -DUSE_TCL $(TCL_INCDIR)
TCL_LDFLAGS  := $(TCL_LIBDIR) $(TCL_LIBS) $(X11_LIBDIR) -lX11 -lm
endif


# Temporarily force building with position info.
USE_POSITION := true

ifdef USE_POSITION
POS_CFLAGS := -DUSE_POSITION
POS_LDFLAGS := -lTelemetryNdds
CFLAGS += $(POS_CFLAGS)
endif



# this is a stand alone image receiver that outputs to a .pgm file
$(OS)/imageReceive.o:	imageReceive.cc
	$(C++) -c $< -o $@ $(CDEBUG) $(CPPFLAGS) $(INCLUDES) \
	$(RTIDEF) $(RTI_DEF) $(TCL_CPPFLAGS) $(POS_CFLAGS)

$(OS)/imageReceive:	$(OS)/irParseArgs.o

$(OS)/IPCclean: IPCclean.cc sharedMem.h $(OS)/sharedMem.o
	$(C++) -g -o $@ $(CDEBUG) IPCclean.cc $(POS_CFLAGS)

$(OS)/testRcv: testRcv.cc sharedMem.h $(OS)/sharedMem.o
	$(C++) -g -o $@ $(CDEBUG) -D$(OS) testRcv.cc $(OS)/sharedMem.o \
		$(POS_CFLAGS)

$(OS)/testSeqRcv: testSeqRcv.cc sharedMem.h $(OS)/sharedMem.o
	$(C++) -g -o $@ $(CDEBUG) -D$(OS) testSeqRcv.cc $(OS)/sharedMem.o \
		$(POS_CFLAGS)

$(OS)/testDcmpRcv: testDcmpRcv.cc sharedMem.h $(OS)/sharedMem.o
	$(C++) -g -o $@ $(CDEBUG) -D$(OS) testDcmpRcv.cc $(INCLUDES) \
	$(OS)/sharedMem.o \
	$(LDFLAGS) -L/projects/nomad/packages/summus/IRIX \
	-lSWI32 $(OS)/libimageNdds.a \
	/home/artemis/usr1/dac/lib/IRIX/libimgControllerNdds.a \
	$(POS_CFLAGS) \
	$(NDDS_LIBDIR) $(NDDS_LIBS) $(X11_LIBDIR) -lX11 -lm $(OSLIBS)

$(OS)/irParseArgs.o: irParseArgs.c irParseArgs.h
	$(CC) $(CFLAGS) -I$(INCDIR) \
		$(RTIDEF) $(NDDS_INCDIR) \
		-o $@ -c $<

$(OS)/imageReceive:	$(OS)/sharedMem.o $(OS)/imageReceive.o $(TARGETS)
	$(G++) -o $@ $(CDEBUG) \
	$(OS)/irParseArgs.o $(OS)/imageReceive.o \
	$(LDFLAGS) -L$(OS) $(OS)/lib$(LIB).a \
	-L$(LIBDIR)/$(OS) \
	-lImagePacketNdds \
	$(POS_LDFLAGS) \
	$(NDDS_LIBDIR) $(NDDS_LIBS) $(TCL_LDFLAGS) $(OSLIBS)

# Hacked above.
#	-Xlinker -v -Xlinker --stats -Xlinker --verbose

install:	$(TARGETS) do_install

# add and extra file to the dependency search
depend:	imageReceive.cc sharedMem.c

# This isn't making it in the dependencies for some reason.
$(OS)/sharedMem.o: sharedMem.c sharedMem.h

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
