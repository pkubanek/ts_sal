#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile - Common utilities with no other module dependencies
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
TOPDIR :=	../../..
BINDIR :=	$(TOPDIR)/bin
LIBDIR :=	$(TOPDIR)/lib
INCDIR :=	$(TOPDIR)/include

##############################################################################
################ Targets
SRCCS := queue.cc
SRCS := sleep_us.c getdate.c
INCS := fifo.h


# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIB := util
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

LDLIBS  = -L$(OS) -L$(LIBDIR)/$(OS) -limageNdds \
	$(LIBDIR)/$(OS)/libreadpnm.a -lImagePacketNdds -lpthread $(NETLIBS)

# get standard rules for compiling C files
include makes/c-rules.mak

# get all the architecture specific pathes and switches
include makes/$(OS).mak

# this library may get used on mult-threaded applications
CPPFLAGS += -D_REENTRANT

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
all:	$(EXECS) $(TARGETS)

include makes/buildlib.mak

##############################################################################
################ Actual build rules

install:	do_install

do_install:	$(EXECS) $(TARGETS) 

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
