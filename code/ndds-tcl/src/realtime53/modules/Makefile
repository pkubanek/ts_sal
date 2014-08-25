# Makefile for modules

# LOCAL_DIR should be local rams directory like lri-7
LOCAL_DIR	= ../../..
INSTALL_DIR	= $(LOCAL_DIR)

ifdef LRI_ROOT
  PROJECT_DIR := $(LRI_ROOT)
endif

ifeq ($(PROJECT_DIR),)
  ECHO = $(shell echo "ERROR Cannot determine PROJECT_DIR")
endif

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.defines.m68kVx5.3.1

SUB_DIRS	= adc drive gpsCorr netcomm pendant pointing sm \
		  posest/src autonomy

SRCS		= modules.cxx
INCS		= modules.h
OBJS		= $(SRCS:.cxx=.o)
LIBS		= 

INSTALL_INCS	= $(INCS)
INSTALL_OBJS	= $(OBJS)
INSTALL_LIBS	= $(LIBS)

# Targets (all should be first)
all::  $(SRCS) $(OBJS) $(LIBS)
	$(RECUR)

modules.o:
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/g++68k -g -m68040 -nostdinc -fno-builtin -B/user/vxworks/vx5.3.1/host/sun4-solaris2/lib/gcc-lib/ -I/user/rti/ndds/makehome/headerFixes/vx -I/user/rti/ndds/include/vx/ndds -I/user/rti/ndds/include/vx -I/user/rti/ndds/include/share -I/include/share -I/include/vx -I/scope/include/share -I/scope/include/vx -I/usr/sib/rams/include -I/user/vxworks/vx5.3.1/target/h -DOS_VXWORKS -DRTI_VXWORKS -DRTS_VXWORKS -D__VX -DCPU=MC68060 -DVXWORKS_MAJOR_VERSION=5 -DVXWORKS_MINOR_VERSION=3 -c modules.cxx -o modules.o

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

depend::
	$(RECUR)

depend::
	makedepend -DCPU=MC68060 $(INC_PATH) -I$(VXWORKS_DIR)/h -f \
		makefile.depends *.cxx *.c *.cc *.c++ *.cpp
 
