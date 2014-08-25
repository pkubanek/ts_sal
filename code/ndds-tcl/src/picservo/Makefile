#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile
# ABSTRACT: Makefile for McDonell Douglas arm kinematics
#	    Be sure to link -lm when using this library... ?
#
#	This is a good example Makefile for multiple operating system support
#	and backups on installation
#
# REQUIREMENTS:
#       gmake
#       makedepend
#	make.$OS
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
TCLHOME :=	/apps/supported
TARDIR :=	$(HOME)/bak

##############################################################################
################ Targets
SRCCS := picservo.cc
INCS := picservo.h
EXECS := $(OS)/servo

# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIB := picservo
# major version represent visible changes to the API
#LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install

# file name for make backup or export images
TARFILE :=	$(TARDIR)/$(LIB).tar

LDLIBS  = -L$(LIBDIR)/$(OS) -lssl  -lutil

INCLUDES =	-I. -I$(INCDIR)


# CDEBUG is often passed in on the command line for quick debugging
CDEBUG	:= -O -g

# get standard rules for compiling C files
include makes/c-rules.mak

# get all the architecture specific pathes and switches
include makes/$(OS).mak


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
OBJS = $(SRCS:.c=.o) $(SRCCS:.cc=.o)

# convert name to reflect sub directories
OSOBJS =	$(OBJS:%.o=$(OS)/%.o)

# Default build rule
all:	$(TARGETS) $(EXECS)

include makes/buildlib.mak

##############################################################################
################ Actual build rules

# BUG makefile know how to build test by default, so this try to build twice
test:	$(OS)/ktest

# create the test program
$(OS)/servo:	$(OS)/servo.o $(TARGETS)
	$(CC) -o $@ $(OS)/servo.o -L$(OS) -l$(LIB) $(LDLIBS)

install:	do_install

do_install:	$(TARGETS) 

# add and extra file to the dependency search
depend:	servo.cc

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
