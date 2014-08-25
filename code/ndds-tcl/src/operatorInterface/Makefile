# Makefile

# Project directory location
PROJECT_DIR := .
ifeq ($(shell domainname),img)
  PROJECT_DIR := /projects/nomad
endif
ifeq ($(shell domainname),frc.ri.cmu.edu)
  PROJECT_DIR := /afs/cs/project/lri-7
endif

# No specific module at this level
MODULE 	= operatorInterface

# Set target to be the same as host
TARGET_ARCH = $(HOST_ARCH)

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

# Subdirectories
SUB_DIRS	= 

# Sources and depend files
INCS	= 
SRCS	= 

# Objects, libraries, and executables
OBJS	= 
LIBS	= 
BINS	= go_nomad \
	  kill_nomad

# Install sources and objects
INSTALL_DIR	= ../..
INSTALL_INCS	=
INSTALL_LIBS	=
INSTALL_BINS	= $(BINS)

# Targets (all should be first)
all::	
	@echo "No compiled code, use \"make install\" to install scripts."







