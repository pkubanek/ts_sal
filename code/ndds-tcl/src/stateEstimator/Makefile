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

# Module 
MODULE = stateEstimator

# Set target architecture
TARGET_ARCH = vxWorks

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.include

<<<<<<< Makefile
# Additions
CPPFLAGS	+= -DNO_NOMAD
INC_PATH	+= -I/projects/nomad/include
LIB_PATH	+= -L/projects/nomad/lib/$(TARGET)

LDLIBS		+= -lTelemetryNdds
=======
# Path additions
LIB_PATH	+= -L$(COMPILER_PATH)

# Build additions
CPPFLAGS	+= -DNO_NOMAD -DNO_MULTICAST
LDFLAGS		+= -Ur
LDLIBS		+= -lTelemetryNdds -lgcc
>>>>>>> 1.3

# Sources
INCS	= telemNdds.h
SRCS	= telemNdds.cc

# Objects, libraries, and executables
OBJS	= $(SRCS:%.cc=$(TARGET_ARCH)/%.o)
#LIBS	= $(TARGET_ARCH)/libtelemNdds.a
BINS	= $(TARGET_ARCH)/telemNdds.lo

# Install sources and objects
INSTALL_DIR 	= ../..
INSTALL_INCS	= 
#INSTALL_LIBS	= $(TARGET_ARCH)/libtelemNdds.a
INSTALL_BINS	= $(TARGET_ARCH)/telemNdds.lo

# Targets
all::	$(TARGET_ARCH) $(OBJS) $(LIBS) $(BINS)

$(TARGET_ARCH)/telemNdds.lo:	$(OBJS)

$(TARGET_ARCH)/libtelemNdds.a:	$(OBJS)





