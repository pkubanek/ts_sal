# Makefile

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
  DUMMY = $(shell echo "ERROR Cannot determine PROJECT_DIR")
endif
endif

# No specific module at this level
MODULE 	= 

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

# Subdirectories
SUB_DIRS	= utilities \
		  messages \
		  common \
		  operatorInterface \
		  robotInterface \
		  robotManager \
		  telemetryRouter \
		  terrainMapper \
		  visualInterface

# Sources and depend files
INCS	=
DEPS	=
SRCS	=

# Objects, libraries, and executables
OBJS	= 
LIBS	= 
BINS	= 

# Install sources and objects
INSTALL_DIR	= ..
INSTALL_INCS	= 
INSTALL_LIBS	= 
INSTALL_BINS	= 

# Targets (all should be first)
all::

tags::
	etags  */*.h */*.c */*.cc







