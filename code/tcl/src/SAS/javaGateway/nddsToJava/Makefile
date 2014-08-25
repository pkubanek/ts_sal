# AUTHOR: Michael Wagner
# CREATED 4/15/99

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = -D_UNIX
SYSLIBS = -lm -lpthread

ARCH = $(shell uname)

LIBS =  $(NOMAD_HOME)/lib/$(ARCH)/libSensorsNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libDatabaseNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libTargetAcqNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libTelemetryNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libNewTelemetryNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libRealtimeNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libScienceNdds.a \
	$(NDDSHOME)/lib/$(ARCH)/libndds.a \
	$(NDDSHOME)/lib/$(ARCH)/libutilsip.a \
	$(NDDSHOME)/lib/$(ARCH)/libutilsxx.a \
	$(SYSLIBS)

INCS = 	-I$(NOMAD_HOME)/include/ \
	-I$(NDDSHOME)/include/share \
	-I$(NDDSHOME)/include/unix 

all: nddsToJava

install: all
	cp nddsToJava $(INSTALL_DIR)/bin/$(ARCH)/. 
	cp nddsToJava.h $(INSTALL_DIR)/include/.

nddsToJava: nddsToJava.cpp nddsToJava.h
	egcs -o nddsToJava nddsToJava.cpp $(LIBS) $(INCS) $(DEFINES) 

clean:
	/bin/rm -f nddsToJava






