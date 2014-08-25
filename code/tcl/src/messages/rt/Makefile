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

# Sources and depend files
XDRS  = rtChassisConfig.x \
	rtDrive.x \
	rtLaser.x \
	rtSetActuator.x \
	rtSetBroadcastFreq.x \
	rtSetParamFloat.x rtSetParamInt.x \
	rtSetPosEstParams.x     \
	rtSetServoParams.x \
	rtSignalCondition.x \
	rtAmpState.x \
	rtControlState.x \
	rtEmergencySignals.x

INCS	= $(XDRS:.x=.h)
# MDW: These features removed for NDDS 2.1e (6/7/99)
#ifneq ($(TARGET_ARCH),vxWorks5.3)
# ifneq ($(TARGET_ARCH), i86Win32)
# INCS   += $(XDRS:.x=_tclndds.h)
# endif
#endif

SRCS    = $(XDRS:.x=.c) #\
# MDW: These features removed for NDDS 2.1e (6/7/99)
#          $(XDRS:.x=_ndds.c) \
#          $(XDRS:.x=_print.c)
#ifneq ($(TARGET_ARCH),vxWorks5.3)
# ifneq ($(TARGET_ARCH), i86Win32)
# SRCS   += $(XDRS:.x=_tclndds.c)
# endif
#endif

# Objects, libraries, and executables
DEPS	= 
OBJS	= $(SRCS:%.c=$(TARGET_ARCH)/%.o)
ifneq ($(TARGET_ARCH), i86Win32)
 LIBS	= $(TARGET_ARCH)/libRtNdds.a
else
 LIBS	= $(TARGET_ARCH)/libRtNdds.lib
endif
BINS	= 

# Install sources and objects
INSTALL_DIR	= ../../..
INSTALL_INCS	= $(INCS)
INSTALL_LIBS	= $(LIBS)
INSTALL_BINS	= 

# Targets (all should be first)
all::   $(TARGET_ARCH) $(SRCS) $(OBJS) $(LIBS)

realclean::
	$(RM) $(INCS) $(SRCS)

# Pull in dependancies if they exist
ifneq ($(DEPS),)
ifeq (.make.$(TARGET_ARCH).depend,$(wildcard .make.$(TARGET_ARCH).depend))
include .make.$(TARGET_ARCH).depend
endif
endif


