#!gmake 	# Tell emacs about this file: -*- Makefile -*-  
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile
# ABSTRACT: Makefile for libssl, a serial and socket I/O library.
#	    Be sure to link -lm when using this library...
#
#           note: have to link in NIS appropriately...
#
# REQUIREMENTS:
#       OS environment variable MUST be set (usually 'setenv OS=`uname`')
#       gmake
#       makedepend
#
# USAGE:
#       make depend     # setup dependencies and sub directories
#       make all        # build all standard targets
#       make install    # install target(s) and fixes group and permissions
#       make clean      # remove intermediate files (for a full rebuild)
#       make clean-dist # remove all built files and directories
#
# REVISION HISTORY:
# $Id: Makefile,v 1.2 1997/05/07 15:02:19 dac Exp $
#
#------------------------------------------------------------------------------

# several rules rely on borne shell syntax/abilities
SHELL=/bin/sh
# Determine what operating system we are trying to build for
# Override this on the command line for cross compilation (e.g. OS=m68kVx5.1)
OS := $(shell uname -s)

include makes/site.mak		# get all those site specific pathes...

# keep install directrories relative if possible
TOPDIR=../../..
BINDIR=$(TOPDIR)/bin
LIBDIR=$(TOPDIR)/lib
INCDIR=$(TOPDIR)/include

###############################################################################
################# Targets

INCS = ssl.h sslCommon.h sslSocket.h sslSerial.h sslKeyboard.h sslSelect.h
# sources needed by all operating systems
SRCS     = sslSerial.c sslCommon.c sslSelect.c 
# if not on VxWorks, also compile extra Unix files
ifeq (,$(findstring Vx5.,$(OS)))
SRCS += sslKeyboard.c sslSocket.c
endif

# build lib$(LIB).a (for VxWorks build lib$(LIB).so, the loadable version)
LIBMAJ := 1
# minor versions are transparent functionality improvements or bug fixes
# minor version number are kept in lib$(LIB).$(LIBMAJ).v and incremented
#  after each install
# this is a default, it will usually be overridden later
LIBMIN := 0
LIB :=	ssl

# get standard rules for compiling C files
include makes/c-rules.mak

INCLUDES = -I. -I$(INCDIR) $(XVME_INC)

# get all the architecture specific pathes and switches
include makes/$(OS).mak

ifdef LDSHARE
ifeq ($(OS)/lib$(LIB).$(LIBMAJ).v,$(wildcard $(OS)/l?b$(LIB).$(LIBMAJ).v))
include $(OS)/lib$(LIB).$(LIBMAJ).v
endif
TARGETS=	$(OS)/lib$(LIB).a $(OS)/lib$(LIB).so.$(LIBMAJ).$(LIBMIN)
else
TARGETS=	$(OS)/lib$(LIB).a
endif

# create the list of target objects from the list of sources
OBJS = $(SRCS:.c=.o)
# convert name to reflect sub directories
OSOBJS :=	$(OBJS:%.o=$(OS)/%.o)

# Default build rule
all:	$(TARGETS)

# default rules to assemble static and shared libraries
include makes/buildlib.mak


# do_install always does all file installs
install:	$(TARGETS) do_install

include makes/install.mak
include makes/clean.mak
include makes/depend.mak
