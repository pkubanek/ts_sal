# Makefile for modules/netcomm

# LOCAL_DIR should be local rams directory like lri-7
LOCAL_DIR	= ../../../..
INSTALL_DIR	= $(LOCAL_DIR)

ifdef LRI_ROOT
  PROJECT_DIR := $(LRI_ROOT)
endif

ifeq ($(PROJECT_DIR),)
  ECHO = $(shell echo "ERROR Cannot determine PROJECT_DIR")
endif

# Include makefile defines, rules, and targets
#include $(PROJECT_DIR)/src/makefiles/Makefile.defines.m68kVx5.3.1
include $(PROJECT_DIR)/src/makefiles/Makefile.defines.vxWorks5.3

SUB_DIRS	= 

C_SRCS		= moveNdds.c netndds.c telemNdds.c
CXX_SRCS	= cmdNdds.cxx
INCS		= cmdNdds.h moveNdds.h netndds.h telemNdds.h rtExtras.h
OBJS		= $(C_SRCS:.c=.o)  $(CXX_SRCS:.cxx=.o)
LIBS		= 

INSTALL_INCS	= $(INCS)
INSTALL_OBJS	= $(OBJS)
INSTALL_LIBS	= $(LIBS)

# Targets (all should be first)
all::  $(C_SRCS) $(CXX_SRCS) $(OBJS) $(LIBS)
	$(RECUR)

# Hack by MDW on 6/8/99
cmdNdds.o:
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/g++68k -Dboolean="unsigned char" -g -m68040 -nostdinc -fno-builtin -B/user/vxworks/vx5.3.1/host/sun4-solaris2/lib/gcc-lib/ -I/user/rti/ndds/makehome/headerFixes/vx -I/user/rti/ndds/include/vx/ndds -I/user/rti/ndds/include/vx -I/user/rti/ndds/include/share -I/include/share -I/include/vx -I/scope/include/share -I/scope/include/vx -I/usr/sib/rams/include -I/user/vxworks/vx5.3.1/target/h -DOS_VXWORKS -DRTI_VXWORKS -DRTS_VXWORKS -D__VX -DCPU=MC68060 -DVXWORKS_MAJOR_VERSION=5 -DVXWORKS_MINOR_VERSION=3 -c cmdNdds.cxx -o cmdNdds.o 

netndds.o:
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/cc68k -Dboolean="unsigned char" -g -m68040 -nostdinc -fno-builtin -B/user/vxworks/vx5.3.1/host/sun4-solaris2/lib/gcc-lib/ -I/user/rti/ndds/makehome/headerFixes/vx -I/user/rti/ndds/include/vx/ndds -I/user/rti/ndds/include/vx -I/user/rti/ndds/include/share -I/include/share -I/include/vx -I/scope/include/share -I/scope/include/vx -I/usr/sib/rams/include -I/user/vxworks/vx5.3.1/target/h -DOS_VXWORKS -DRTI_VXWORKS -DRTS_VXWORKS -D__VX -DCPU=MC68060 -DVXWORKS_MAJOR_VERSION=5 -DVXWORKS_MINOR_VERSION=3 -c netndds.c -o netndds.o 

clean::
	$(RM) $(GEN_INCS)

# Special targets


install::
	$(RECUR)

install::	$(INSTALL_INCS) $(INSTALL_LIBS) $(INSTALL_OBJS)
	@if [ ! -d $(INC_DIR) ]; then $(MKDIR) $(INC_DIR);fi
	$(foreach INC, $(INSTALL_INCS), $(INSTALL) -m 664 \
		-g $(INSTALL_GROUP) $(INC) $(INC_DIR);)
	@if [ ! -d $(LIB_DIR) ]; then $(MKDIR) $(LIB_DIR);fi
	$(foreach LIB, $(INSTALL_LIBS), $(INSTALL) -m 664 \
		-g $(INSTALL_GROUP) $(LIB) $(LIB_DIR);)
	@if [ ! -d $(OBJ_DIR) ]; then $(MKDIR) $(OBJ_DIR);fi
	$(foreach OBJ, $(INSTALL_OBJS), $(INSTALL) -m 775 \
		-g $(INSTALL_GROUP) $(OBJ) $(OBJ_DIR);)

install.incs::
	$(RECUR)

install.incs::	$(INSTALL_INCS)
	@if [ ! -d $(INC_DIR) ]; then $(MKDIR) $(INC_DIR);fi
	$(foreach INC, $(INSTALL_INCS), $(INSTALL) -m 664 \
		-g $(INSTALL_GROUP) $(INC) $(INC_DIR);)

depend:
	makedepend -DCPU=MC68060 $(INC_PATH) -I$(VXWORKS_DIR)/h -f \
		makefile.depends *.cxx *.c *.cc *.c++ *.cpp
 
