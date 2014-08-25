# Makefile for top level

# LOCAL_DIR should be local rams directory like lri-7
LOCAL_DIR	= ../..
INSTALL_DIR	= $(LOCAL_DIR)

ifdef LRI_ROOT
  PROJECT_DIR := $(LRI_ROOT)
endif

ifeq ($(PROJECT_DIR),)
  ECHO = $(shell echo "ERROR Cannot determine PROJECT_DIR")
endif

# Include makefile defines, rules, and targets
include $(PROJECT_DIR)/src/makefiles/Makefile.defines.m68kVx5.3.1

SUB_DIRS	= common \
		components \
		devices \
		interfaces \
		modules \
		robot \
		test

SRCS		= 
INCS		= 
OBJS		= $(SRCS:.c=.o)
LIBS		= 

INSTALL_INCS	= $(INCS)
INSTALL_OBJS	= $(OBJS)
INSTALL_LIBS	= $(LIBS)

# Targets (all should be first)
all::  $(SRCS) $(OBJS) $(LIBS)
	$(RECUR)

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
	makedepend -DCPU=MC68060 $(INC_PATH) -f \
		makefile.depends *.cxx *.c *.cc *.c++ *.cpp

librobot_OLD:
	cd ../../obj/m68kVx5.3.1; \
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/ld68k -r \
	-o ../../lib/m68kVx5.3.1/librobot \
	-L../../lib/m68kVx5.3.1 -L${LRI_ROOT}/lib/m68kVx5.3.1 \
	adc.o              gpsCorr.o          robot.o            test_imu.o \
	adc_mod.o          gpsPort.o          scope2.o           test_point.o \
	amps.o             imu.o              serial.o           test_relay.o \
	cmdNdds.o          interface.o        smObjInit.o        traject.o \
	commonFunc.o       joy.o              sm_int.o           trajectvel.o \
	compass.o          independant.o                         vadc.o \
	components.o       modules.o          steerfunc.o        vadm.o \
	connectAtPort.o    moveNdds.o         telemNdds.o        vmio10.o \
	dac.o              netndds.o                             vmio14.o \
	device_hardware.o  odo.o              test_adc.o         vmio22.o \
	di.o               pass.o             test_compass.o     pos_task.o \
	do.o               pen_int.o          test_dac.o         vmio28.o \
	drive.o            pendant.o          test_di.o          dedRek.o \
	drivesys.o         pid.o              test_do.o          vser80Drv.o \
	encoder.o          point.o            test_drive.o       weather.o \
	fixedpoint.o       pointsys.o         test_enc.o \
	gps.o              relay.o            test_gps.o \
	assistedSteering.o calibSteering.o    waypoint.o
	-lNavNdds -lEventNdds -lTelemetryNdds -lRtNdds -lScienceNdds \
	-lCommonNdds

librobot:
	cd ../../obj/m68kVx5.3.1; \
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/ld68k -r \
	-o ../../lib/m68kVx5.3.1/librobot \
	-L../../lib/m68kVx5.3.1 \
	adc.o              gpsCorr.o          robot.o            test_imu.o \
	adc_mod.o          gpsPort.o          scope2.o           test_point.o \
	amps.o             imu.o              serial.o           test_relay.o \
	cmdNdds.o          interface.o        smObjInit.o        traject.o \
	commonFunc.o       joy.o              sm_int.o           trajectvel.o \
	compass.o          independant.o                         vadc.o \
	components.o       modules.o          steerfunc.o        vadm.o \
	connectAtPort.o    moveNdds.o         telemNdds.o        vmio10.o \
	dac.o              netndds.o                             vmio14.o \
	device_hardware.o  odo.o              test_adc.o         vmio22.o \
	di.o               pass.o             test_compass.o     pos_task.o \
	do.o               pen_int.o          test_dac.o         vmio28.o \
	drive.o            pendant.o          test_di.o          dedRek.o \
	drivesys.o         pid.o              test_do.o          vser80Drv.o \
	encoder.o          point.o            test_drive.o       weather.o \
	fixedpoint.o       pointsys.o         test_enc.o \
	gps.o              relay.o            test_gps.o \
	assistedSteering.o calibSteering.o    waypoint.o \
	joy_new.o \
	-lNavNdds -lEventNdds -lTelemetryNdds -lRtNdds -lScienceNdds \
	-lCommonNdds

librobot.so:
	cd ../../obj/m68kVx5.3.1; \
	/user/vxworks/vx5.3.1/host/sun4-solaris2/bin/ld68k -r \
	-o ../../lib/m68kVx5.3.1/librobot.so \
	-L../../lib/m68kVx5.3.1 -L${LRI_ROOT}/lib/m68kVx5.3.1 \
	adc.o              gpsCorr.o          robot.o            test_imu.o \
	adc_mod.o          gpsPort.o          scope2.o           test_point.o \
	amps.o             imu.o              serial.o           test_relay.o \
	cmdNdds.o          interface.o        smObjInit.o        traject.o \
	commonFunc.o       joy.o              sm_int.o           trajectvel.o \
	compass.o          independant.o      led.o              vadc.o \
	components.o       modules.o          steerfunc.o        vadm.o \
	connectAtPort.o    moveNdds.o         telemNdds.o        vmio10.o \
	dac.o              netndds.o          startup.o          vmio14.o \
	device_hardware.o  odo.o              test_adc.o         vmio22.o \
	di.o               pass.o             test_compass.o     pos_task.o \
	do.o               pen_int.o          test_dac.o         vmio28.o \
	drive.o            pendant.o          test_di.o          dedRek.o \
	drivesys.o         pid.o              test_do.o          vser80Drv.o \
	encoder.o          point.o            test_drive.o       weather.o \
	fixedpoint.o       pointsys.o         test_enc.o \
	gps.o              relay.o            test_gps.o \
	assistedSteering.o calibSteering.o    waypoint.o \
	joy_new.o \
	-lNavNdds -lEventNdds -lTelemetryNdds -lRtNdds -lScienceNdds \
	-lCommonNdds
