#!gmake -*- Makefile -*-
# FILE:     Makefile
#
# USAGE:
#       make depend     # setup dependencies and sub directories
#       make all        # build all standard targets
#       make install    # install target(s) and fixes group and permissions
#       make clean      # remove intermediate files (for a full rebuild)
#       make realclean  # remove all built files and directories

# Determine project directory location 
include ../Makefile.paths

# Module
MODULE  = messages

# Set target architecture
TARGET_ARCH = $(HOST_ARCH)

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

# Flex / Bison specifics
LEXFLAGS  = -f -Ca              # -b -7 -Cr
LEX	  = $(FLEX)

YACCFLAGS = --defines           # --debug --verbose 
YACC	  = $(BISON)

LDFLAGS   += -L$(GNU_LIB_DIR)
LDLIBS	  += -lfl

# Sources and depend files
Y_SRCS  = XDR.y
L_SRCS  = XDR.l
INCS	= $(Y_SRCS:.y=.tab.h) $(L_SRCS:.l=.h)
SRCS 	= $(Y_SRCS:.y=.tab.c) $(L_SRCS:.l=.yy.c) XDRmain.c 

# Objects, libraries, and executables
DEPS	= 
OBJS	= $(SRCS:%.c=$(TARGET_ARCH)/%.o)
LIBS	= 
BINS	= $(TARGET_ARCH)/tclndds

# Install sources and objects
INSTALL_DIR	= ../../..
INSTALL_INCS	= 
INSTALL_LIBS	= 
INSTALL_BINS	= $(BINS)

# Targets (all should be first)
all::   $(TARGET_ARCH) $(BINS)

realclean::
	$(RM) *.tab.c *.tab.h *.yy.c


$(TARGET_ARCH)/tclndds:	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

XDR.tab.c XDR.tab.h: XDR.y XDR.h
	$(YACC) $(YACCFLAGS) XDR.y

$(TARGET_ARCH)/XDR.tab.o: XDR.tab.c XDR.tab.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) XDR.tab.c -o $@

XDR.yy.c: XDR.l XDR.tab.h
	$(LEX) $(LEXFLAGS) -oXDR.yy.c XDR.l 

$(TARGET_ARCH)/XDR.yy.o: XDR.yy.c XDR.tab.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) XDR.yy.c -o $@

# Pull in dependancies if they exist
ifneq ($(DEPS),)
ifeq (.make.$(TARGET_ARCH).depend,$(wildcard .make.$(TARGET_ARCH).depend))
include .make.$(TARGET_ARCH).depend
endif
endif


