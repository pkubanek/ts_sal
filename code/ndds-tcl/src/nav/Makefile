#############################################################################
#   $Source: /afs/cs/project/lri-7/Master/src/nav/Makefile,v $
# $Revision: 1.2 $
#     $Date: 1997/07/02 20:30:22 $
#   $Author: jl $
#    $State: Exp $
#   $Locker:  $
#
##############################################################################
###  Lunar Rover Makefile Template
###
###
###	EXPORTS
###		INC_PATH_LOCAL
###		DEFINES_LOCAL
###		LIB_PATH_LOCAL
###		LIBS_LOCAL
###		CFLAGS_LOCAL
###		PURIFY				[if set, compile using purify]
###
###	IMPORTS
###		THIS_OS		Operating system, all caps
###				(e.g., SUNOS, SOLARIS, LINUX)
###		this_os		Operating system, lower case
###				(e.g., sunos, solaris, linux)
###		OS_REVISION	Version number of the operating system
###				(e.g., 4.1.4, 1.3.85)
###		HOSTNAME	Fully-qualified domain name of the current
###				system, in lower case
###		CVSROOT		Location of the CVS Master repository.
###		CVS		Location of the cvs command for this project
###		INSTALLROOT	Root directory for binary, library, and man
###				page installations
###		INSTALL_BIN_DIR	Directory for installing binaries
###		INSTALL_LIB_DIR	Directory for installing libraries
###		INSTALL_MAN_DIR	Directory for installing man pages
###		INSTALL_INCLUDE_DIR
###				Directory for installing header files
###		BDIR		Name of the local binary directory into which
###				newly-compiled executables will be placed.
###				Since we want to support multiple
###				architectures, this will include the name of
###				the current operating system to aid
###				disambiguation.
###		LDIR		Name of the local library directory into which
###				newly-generated libraries will be placed.
###				See notes for BDIR.
###		ODIR		Name of the local object directory into which
###				newly-compiled object files will be placed.
###				See notes for BDIR.
###		TCA_DIR		Root directory for TCA.
###		X11_DIR		Root directory for X11 libraries and includes.
###		MOTIF_DIR	Root directory for Motif libraries and
###				includes.
###		GIL_DIR		Root directory for the GIL, or empty string.
###		XGL_DIR		Root directory for XGL, or the empty string.
###		INC_PATH	List of "-I" options for the C compiler.  But
###				see CFLAGS.
###		DEFINES		List of "-D" options for the C compiler.  But
###				see CFLAGS.
###		CPPFLAGS	List of options for the C preprocessor.  But
###				see CFLAGS.
###		CFLAGS		List of options for the C compiler.  May be
###				extended using INC_PATH_LOCAL, and
###				DEFINES_LOCAL.
###		LIB_PATH	Library search path.  May be extended using
###				LIB_PATH_LOCAL.
###		LIBRARIES	List of libraries.  May be extended using
###				LIBS_LOCAL
###		LINK.c		Link command

##############################################################################


##############################################################################
### Module name
##############################################################################

MODULE:=nav
##############################################################################
###  Include standard definitions
##############################################################################

ifndef LRI_ROOT
LRI_ROOT := $(shell echo ====== LRI_ROOT not defined 1>&2; echo ====== LRI_ROOT should point to the master checked out copy 1>&2; echo ====== Perhaps you want /afs/cs/project/lri-7 1>&2; echo ====== Quitting with separator error 1>&2)
exit 1		###  This is just a syntax error, but it gives the same effect
endif

##############################################################################
###  Figure out the root of the currently checked-out directory.  It's defined
###  to be at the same level as the rightmost "src" component of the current
###  directory.
##############################################################################

CHECKOUTDIR := $(shell pwd | sed 's:^.*/src/*:src/:' | tr / ' ' | wc -w | awk '{ for (i = 0; i < $$1; i++) { if (i>0) printf "/"; printf ".."}}')



##############################################################################
###  Look for the standard Make header file.  If it's not in the current
###  directory, try the local installed directory, then the local etc module,
###  then the global directory.
##############################################################################

D1 = $(CHECKOUTDIR)/etc
D2 = $(CHECKOUTDIR)/src/nav/etc
D3 = $(LRI_ROOT)/etc

ifndef MAKE_HEAD
	MAKE_HEAD := $(shell if [ -f Makefile.head ]; then echo Makefile.head; fi)
	ifeq ($(MAKE_HEAD),)

		MAKE_HEAD = $(shell if [ -f $(D1)/Makefile.head ]; then echo $(D1)/Makefile.head; fi)
	endif
	ifeq ($(MAKE_HEAD),)
		MAKE_HEAD = $(shell if [ -f $(D2)/Makefile.head ]; then echo $(D2)/Makefile.head; fi)
	endif
	ifeq ($(MAKE_HEAD),)
		MAKE_HEAD = $(shell if [ -f $(D3)/Makefile.head ]; then echo $(D3)/Makefile.head; fi)
	endif
	ifeq ($(MAKE_HEAD),)
		MAKE_HEAD := $(shell echo ===== WARNING Cannot find Makefile.head)
	endif
endif

ifndef MAKE_TAIL
	MAKE_TAIL := $(shell if [ -f Makefile.tail ]; then echo Makefile.tail; fi)
	ifeq ($(MAKE_TAIL),)
		MAKE_TAIL := $(shell if [ -f $(D1)/Makefile.tail ]; then echo $(D1)/Makefile.tail; fi)
	endif
	ifeq ($(MAKE_TAIL),)
		MAKE_TAIL := $(shell if [ -f $(D2)/Makefile.tail ]; then echo $(D2)/Makefile.tail; fi)
	endif
	ifeq ($(MAKE_TAIL),)
		MAKE_TAIL := $(shell if [ -f $(D3)/Makefile.tail ]; then echo $(D3)/Makefile.tail; fi)
	endif
	ifeq ($(MAKE_TAIL),)
		MAKE_TAIL := $(shell echo ===== WARNING Cannot find Makefile.tail)
	endif
endif

include $(MAKE_HEAD)


##############################################################################
###  Define the C compiler
##############################################################################

CC=gcc

##############################################################################
###  Define the include path for each operating system
##############################################################################

INC_PATH_LOCAL += 

##############################################################################
###  Add symbols to be #defined using the C preprocessor
##############################################################################

DEFINES_LOCAL :=

##############################################################################
###  Library search paths; necessarily OS-specific
##############################################################################

LIB_PATH_LOCAL += 

##############################################################################
###  Libraries used in all architechtures; note that these are included BEFORE
###  the system-dependent libraries.
##############################################################################


LIBS_LOCAL_sunos := 
LIBS_LOCAL_linux := 

LIBS_LOCAL	+=

CFLAGS_LOCAL	= -O -g -fpcc-struct-return -Wstrict-prototypes

LINTFLAGS	= -abch
ARFLAGS		= rv

# Generated files - installed
PUBLIC_BINS	= 
PUBLIC_LIBS	= 
PUBLIC_LINTS	= 

# Source files - installed
PUBLIC_INCS	= 
PUBLIC_MANS	= 
PUBLIC_DOCS	= 
PUBLIC_ETCS	=

MODULE_INCS	= 
MODULE_LINTS	=
MODULE_LIBS	= 


INCS		= $(PUBLIC_INCS)

# Generated files - not installed
PRIVS		=  

SRCS		= 
_OBJS		= $(SRCS:.c=.o)
OBJS		= $(addprefix $(ODIR)/,$(_OBJS))

# Source files - not installed 
PRIVATE_INCS	=  
MISC		= Makefile README

SUBDIRS	= etc tiff readline-2.0 matrix X2d common controller arbiter pair 
SUBDIRS+= stereo morphin uiBridge
#SUBDIRS+= simulator dstar uiBridge
##########
# Default Target
##########

all: $(SUBDIRS) srcs libs privs bins

##########
# User Defined Targets
##########

# Define rules for all files listed in BINS, LIBS, and LINTS in this section.
# Example executable, object, library, and combined objects are shown below:
# If no rule commands are shown, none are required.
#
#  $(BDIR)/sample: file1.o file2.o
#
#  $(ODIR)/alternateName.o: file1.c
#	$(COMPILE.c) -o $@ file1.o
#
#  $(LDIR)/libsample.a: file1.o file2.o
#
#  combined.o: part1.o part2.o
#	$(LD) -r -o $@ part1.o part2.o; chmod a-x $@

##########
# Include standard target definitions and RCS rules
##########

include $(MAKE_TAIL)

# DO NOT DELETE THIS LINE -- make depend depends on it.

