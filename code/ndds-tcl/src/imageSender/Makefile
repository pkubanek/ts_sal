#
# 
#
# FILE:     Makefile
#
# ABSTRACT: Unix makefile for sensdata programs. This will automatically 
#	    detect and build for SunOS, IRIX or Linux.
#
# REVISION HISTORY:
#
# $Id: Makefile,v 1.5 1997/05/05 04:03:36 nomad Exp $
#
# 25-Mar-1997  Kurt Schwehr.  Derived from Makefile from Laurent Piguet.
#
#----------------------------------------------------------------------------


#
# determine what operating system we are trying to build for
#
OS := $(shell uname -s)
ifeq ($(OS),IRIX64)
  OS := IRIX
endif

NDDSVER := ndds.1.11b
RTILIBVER := rtilib.3.7d

ifeq ($(OS),CYGWIN32/NT) # Yes, this is i586/NT
  NDDSARCH = i86Win32
  CC       = CL		# "CL /help" for command line options.
  LINK     = LINK

  # Need the quotes to handle the space in the directory name
  GNUBIN   = "c:/Program Files/gnu/H-i386-cygwin32/bin"

  OBJSUF   = .obj
  EXESUF   = .exe
  OUT      =/OUT:
  RM       =$(GNUBIN)/rm -f
  #RM       =/gnu/bin/rm -f

  # location of the NDDS library
  # Hard code ndds version #... NT does not have symbolic links
  RTIHOME = "c:/program files/rti"
  NDDSHOME = $(RTIHOME)/ndds.1.11d
  RTILIBHOME = $(RTIHOME)/rtilib.3.7d
  RTIMAKEHOME := $(NDDSHOME)/makehome

  NDDS_LIB_DIR = $(NDDSHOME)/lib/$(NDDSARCH)

  NDDS_LIBS = \
	$(NDDS_LIB_DIR)/libndds.lib \
	$(NDDS_LIB_DIR)/libutilsip.lib \
	$(NDDS_LIB_DIR)/libxdr_fixes.lib \
	$(NDDS_LIB_DIR)/libxdr.lib \
	netapi32.lib

  IMGSENDHOME = "c:/users/schwehr/imageSend"

  RTILIBINC := /I$(RTILIBHOME)/include/win32 /I$(RTILIBHOME)/include/share
  NDDSINC   := /I$(NDDSHOME)/include/win32 /I$(NDDSHOME)/include/share
  RTIMAKEINC:= /I$(RTIMAKEHOME)/headerFixes/win32/$(NDDSARCH)

  INCLUDES =    /I$(IMGSENDHOME) \
		$(RTILIBINC) \
		$(NDDSINC) \
		$(RTIMAKEINC)

  # /nologo suppress copyright message.
  # /MD link with MSVCRT.LIB 
  # /W<n> set warning level (default n=1)
  # /GX[-] enable C++ EH

  CFLAGS   := /nologo /MD /W3 /GX \
	     /D"WIN32" /D"_CONSOLE" /D"_POSIX_" /D"i486_nt" /D"OPENGL" \
	     /D"RTI_WIN32" $(INCLUDES)

  # Uncomment this when everything is VERY stable and you want a  little extra speed.
  # Probably does not speed things up that much on fast machines like the PPro.
  #CFLAGS += /D"NDEBUG"

  # winmm.lib if for the multimedia timer.
  LDLIBS   =  $(NDDS_LIBS) wsock32.lib winmm.lib

  MOVE     = $(GNUBIN)/mv -f *.obj $(NDDSARCH)

endif


ifeq ($(OS),IRIX)
  TOPDIR   = ../..
  INCDIR   = $(TOPDIR)/include

  NDDSARCH = mipsIRIX5
  CC       = gcc
  C++      = CC
  LINK     = gcc

  OBJSUF   = .o
  EXESUF   = 
  OUT      =-o 
  RM       =/bin/rm -f

  # location of the NDDS library
  RTIHOME = /usr/misc/rti
  NDDSHOME = $(RTIHOME)/ndds
  RTILIBHOME = $(RTIHOME)/rtilib
  RTIMAKEHOME := $(NDDSHOME)/makehome

  NDDS_LIBS = \
	$(NDDSHOME)/lib/$(NDDSARCH)/libndds.a \
	$(NDDSHOME)/lib/$(NDDSARCH)/libutilsip.a \
	$(syslibs_$(NDDSARCH))

  RTILIBINC := -I$(RTILIBHOME)/include/unix -I$(RTILIBHOME)/include/share
  NDDSINC   := -I$(NDDSHOME)/include/unix -I$(NDDSHOME)/include/share
  RTIMAKEINC:= -I$(RTIMAKEHOME)/headerFixes/unix/$(NDDSARCH)

  INCLUDES =    $(RTILIBINC) \
		$(NDDSINC) \
		$(RTIMAKEINC)

  RTIDEFINES := -DRTI_UNIX -DRTI_IRIX -DSVR5
  CFLAGS     := -g -O -Wall $(INCLUDES) $(RTIDEFINES)
  C++FLAGS   := -g -ansi -fullwarn $(INCLUDES) $(RTIDEFINES)

  LDFLAGS  = 
  LDLIBS   = $(NDDS_LIBS) -lm

endif


ifeq ($(OS),Linux)
  NDDSARCH = i86Linux
  CC       = gcc
  LINK     = gcc

  OBJSUF   = .o
  EXESUF   = 
  OUT      =-o 
  RM       =/bin/rm -f

  # location of the NDDS library
  NDDSHOME = /usr/misc/rti/ndds

  NDDS_LIBS = \
	$(NDDSHOME)/lib/$(NDDSARCH)/libndds.a \
	$(NDDSHOME)/lib/$(NDDSARCH)/libutilsip.a \
	$(syslibs_$(NDDSARCH))


  INCLUDES = -I$(COMMOBJ_HOME) -I$(NDDSHOME) \
		-I$(NDDSHOME)/include/unix \
		-I$(NDDSHOME)/include/share 

  CFLAGS   = -g -ansi -Wall -pedantic $(INCLUDES)

  LDFLAGS  = #-L
  LDLIBS   = $(NDDS_LIBS) -lm
endif


EXECS    = imageSend
CSRCS    = ImagePacket.c ImagePacket_ndds.c ImagePacket_print.c \
		isParseArgs.c
CPPSRCS  = imageSend.cpp fifo.cpp
SOURCES  = $(CPPSRCS) $(CSRCS)
HEADERS = ImagePacket.h fifo.h imageSend.h irParseArgs.h nomadNddsDomain.h
#HEADERS  = $(SOURCES:.c=.h)
#OBJECTS  = $(SOURCES:.c=$(OBJSUF))
OBJECTS  = $(CSRCS:.c=$(OBJSUF)) $(CPPSRCS:.cpp=$(OBJSUF))
EXEC	 = $(EXECS)$(EXESUF)


#------------------------------------------------------------------------------
# shouldn't have to change anything below this line
#------------------------------------------------------------------------------
syslibs_mipsIRIX5 = 
syslibs_sun4 	  = -ldl
syslibs_i86Linux  =

#
# compilation rules
#
OBJECTS := $(patsubst %$(OBJSUF), $(NDDSARCH)/%$(OBJSUF), $(OBJECTS))
EXEC    := $(patsubst %$(EXESUF), $(NDDSARCH)/%$(EXESUF), $(EXEC))

# object file compilation
$(NDDSARCH)/%$(OBJSUF) : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	$(MOVE)

ifeq ($(OS),IRIX)
# Hack for on IRIX 5.3: object file compilation for NT c++ files
$(NDDSARCH)/%$(OBJSUF) : %.cpp
	$(C++) -woff 3262 $(C++FLAGS) -o $@ -c $<
	$(MOVE)
else
# object file compilation for NT c++ files
$(NDDSARCH)/%$(OBJSUF) : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
	$(MOVE)
endif

# Unix executable linking
$(NDDSARCH)/%$(EXESUF) : $(NDDSARCH)/%$(OBJSUF)
	$(LINK) $(LDFLAGS) $(OBJECTS) $(LDLIBS) $(OUT)$@

#	$(LINK) $(LDFLAGS) $< $(LDLIBS) $(OUT)$@ $(OBJECTS)


#
# targets
#
all: showarch $(NDDSARCH) $(EXEC) 

showarch:
	@echo
	@echo compiling $(EXEC) for $(NDDSARCH)
	@echo   Objects:
	@echo     $(OBJECTS)
	@echo   Exec:
	@echo     $(EXEC)
#	@echo $(NDDSARCH)/%$(OBJSUF) : %.c
#	@echo $(CC) $(CFLAGS) -o $@ -c $<
#	@echo $(MOVE)


$(NDDSARCH):
	mkdir $(NDDSARCH)

$(EXEC): $(OBJECTS)

tags:
	find . -name \*.\[ch] -print | xargs etags -o TAGS

clean:
	-$(RM) $(EXEC) $(OBJECTS) *~ TAGS core *.bak #*#


#
#  Funky rules done by hand.
#

# Don't check this in to CVS
nomadNddsDomain.h: $(INCDIR)/nomadNddsDomain.h
	install $< $@

# Dependencies done by hand:

fifo.cpp: fifo.h
