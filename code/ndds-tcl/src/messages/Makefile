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
ifeq ($(PROJECT_DIR),)
ifeq ($(shell domainname),img)
  PROJECT_DIR := /projects/nomad
endif
ifeq ($(shell domainname),frc.ri.cmu.edu)
  PROJECT_DIR := /afs/cs/project/lri-7
endif
ifdef LRI_ROOT
  PROJECT_DIR := $(LRI_ROOT)
endif
ifeq ($(PROJECT_DIR),)
  ECHO = $(shell echo "ERROR: Cannot determine PROJECT_DIR")
endif
endif

# Module
MODULE 	= messages

# Set target architecture
ifeq ($(TARGET_ARCH),)
  TARGET_ARCH = $(HOST_ARCH)
endif

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

# MDW: These features removed for NDDS 2.1d (6/7/99)
# Define all the subdirectories to make
#ifneq ($(TARGET_ARCH),vxWorks)
#ifneq ($(TARGET_ARCH),vxWorks5.3)
# ifneq ($(TARGET_ARCH), i86Win32)
#  SUB_DIRS = tclndds
# endif
#endif
#endif
#SUB_DIRS += common database event hiRes images mission_planner \
#	    nav navPlan panoramic rt science sensorMan spectrometer \
#	    telemetry

SUB_DIRS += common event nav rt telemetry


# Location of the install directory
INSTALL_DIR = ../..

# Targets (all should be first)
all:: 

