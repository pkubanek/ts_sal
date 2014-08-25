#!gmake		# Tell emacs it is a -*- Makefile -*-
# (c) Copyright 1996. National Aeronautics and Space Administration.
#     Ames Research Center, Moffett Field, CA 94035-1000 
#
# FILE:     Makefile
#	Makefile for all subdirectories in utilities
#	the "makes" directories provide common make stuff
#	The version under image/imageNdds is the right one.
#	We automatically make the appropriate links to it
#	You may have to nuke out of date makes in other directories and 
#	link them to imageNdds
#
# REQUIREMENTS (of the sub directories):
#       Gnu make (gmake)
#       makedepend
#
# USAGE:	See default rule below
#	"make install" should do everything needed in the right order
#
# REVISION HISTORY:
# $Id: Makefile,v 1.1 1997/05/15 21:56:35 dac Exp $
#------------------------------------------------------------------------------

# several rules rely on borne shell syntax/abilities
SHELL=/bin/sh

# it would be simpler to pull in site.make, but the links dont exist yet.
# set OS (if not passed in on command line) (usually done in makes/site.mak)
OS := $(shell uname -s)
# set the OS revision, we need this in a couple places
OSREV := $(shell uname -r)

#if we are building for Solaris, we need to figure that out now
ifeq (SunOS,$(findstring SunOS,$(OS)))
ifeq (5.,$(findstring 5.,$(OSREV)))
# overwrite OS to be separate from SunOS
OS :=	sparcSolaris2
ifeq (5.5.,$(findstring 5.5.,$(OSREV)))
#Solaris2.5
RTIARCH :=	sparcSol2.5
else
#Solaris
RTIARCH :=	sparcSol2
endif
endif
endif

# keep install directrories relative if possible
TOPDIR=../..
INCDIR=$(TOPDIR)/include
LIBDIR=$(TOPDIR)/lib

# order is important here.  latter stuff depends on earlier libraries
SUBDIRS = libutil ssl image/readpnm image/imageNdds image/imageTcl tcl

default:
	@echo	"Use one of the following:"
	@echo	"gmake depend		Build all dependencies"
	@echo	"gmake all		Build all targets"
	@echo	"gmake install		Build/install all targets"
	@echo	"gmake clean		Remove intermediate files"
	@echo	"gmake clean-dist	Remove all created files/directories"

depend:
	@set +x; [ -d makes ] || ln -s image/imageNdds/makes .
	@([ -d image/makes ] || (set +x; cd image && ln -s imageNdds/makes .))
	-for d in $(SUBDIRS) ; do \
		echo "Making $@ in $$d" ; \
		(cd $$d &&  [ -d makes ] || ln -s ../makes .) || break; \
		(cd $$d && $(MAKE) $(MFLAGS) $@ ) || break; \
	done

all:
	@set +x; [ -d makes ] || ln -s image/imageNdds/makes .
	@([ -d image/makes ] || (set +x; cd image && ln -s imageNdds/makes .))
	-for d in $(SUBDIRS) ; do \
		echo "Making $@ in $$d" ; \
		(cd $$d &&  [ -d makes ] || ln -s ../makes .) || break; \
		(cd $$d && \
		([ -f $(OS)/.make.dep ] \
			|| $(MAKE) -fMakefile $(MFLAGS) depend) && \
		$(MAKE) $(MFLAGS) $@ ) || break; \
	done

install:
	@set +x; [ -d makes ] || ln -s image/imageNdds/makes .
	@([ -d image/makes ] || (set +x; cd image && ln -s imageNdds/makes .))
	-for d in $(SUBDIRS) ; do \
		echo "Making $@ in $$d" ; \
		(cd $$d &&  [ -d makes ] || ln -s ../makes .) || break; \
		(cd $$d && \
		([ -f $(OS)/.make.dep ] \
			|| $(MAKE) -fMakefile $(MFLAGS) depend) && \
		$(MAKE) $(MFLAGS) $@ ); \
	done

clean:
	-for d in $(SUBDIRS) ; do \
		echo "Making $@ in $$d" ; \
		(cd $$d && $(MAKE) $(MFLAGS) $@ ); \
	done

clean-dist:
	-for d in $(SUBDIRS) ; do \
		echo "Making $@ in $$d" ; \
		(cd $$d && $(MAKE) $(MFLAGS) $@ ); \
	done

