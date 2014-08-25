# AUTHOR: Michael Wagner
# CREATED 4/15/99

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = -D_UNIX -g

SYSLIBS = -lm -lpthread

ARCH = $(shell uname)

LIBS =  $(NOMAD_HOME)/lib/$(ARCH)/libSensorsNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libDatabaseNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libTargetAcqNdds.a \
	$(NOMAD_HOME)/lib/$(ARCH)/libCommonNdds.a \
	$(NDDSHOME)/lib/$(ARCH)/libndds.a \
	$(NDDSHOME)/lib/$(ARCH)/libutilsip.a \
	$(NDDSHOME)/lib/$(ARCH)/libutilsxx.a \
	$(SYSLIBS)

INCS = 	-I$(NOMAD_HOME)/include/ \
	-I$(NDDSHOME)/include/share \
	-I$(NDDSHOME)/include/unix 

all: javaToNdds

install: all
	cp javaToNdds $(INSTALL_DIR)/bin/$(ARCH)/. 
	cp javaToNdds.h $(INSTALL_DIR)/include/.

javaToNdds: javaToNdds.cpp
	g++ -o javaToNdds javaToNdds.cpp $(LIBS) $(INCS) $(DEFINES) 

clean:
	/bin/rm -f javaToNdds






