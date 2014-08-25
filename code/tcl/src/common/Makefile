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
  ECHO = $(shell echo "ERROR Cannot determine PROJECT_DIR")
endif
endif

# No specific module at this level
MODULE 	= common

# Set target architecture
TARGET_ARCH = $(HOST_ARCH)

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

# Sources and depend files
GEN_INCS =	nomadUnitsC.h nomadUnitsXDR.h

INCS  = \
	cameraDimensions.h \
	libc.h \
	nomadDefs.h \
	nomadDimensions.h \
	nomadLimits.h \
	nomadNddsDomain.h \
	nomadNddsMessages.h \
	proximityDimensions.h \

# Install sources and objects
INSTALL_DIR	= ../..
INSTALL_INCS	= $(INCS) $(GEN_INCS)

# Targets (all should be first)
all::   $(TARGET_ARCH) $(GEN_INCS)

clean::
	$(RM) $(GEN_INCS)

# Special targets
$(GEN_INCS):  nomadUnits.TypeMap genNomadUnits.awk
	$(AWK) -f genNomadUnits.awk <nomadUnits.TypeMap




