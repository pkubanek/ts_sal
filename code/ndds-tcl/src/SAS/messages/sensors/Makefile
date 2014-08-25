CC = egcs
LD = egcs
AR = ar
ARFLAGS = r
NDDSGEN = nddsgen
SYSLIBS = -lm -lpthread

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = 

MODULE = Sensors

INCLUDES = -I$(NDDSHOME)/include/unix \
           -I$(NDDSHOME)/include/share \
	   -I$(INSTALL_DIR)/include

LIBS = 	$(NDDSHOME)/lib/i86Linux5.1/libndds.a    \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsip.a \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsxx.a \
	$(SYSLIBS)

SM_DRIVER_PUBLICATIONS = -publicationType sensorRequest \
			 -publicationType sensorReply \
			 -publicationType sensorReg

ARCHIVE      = lib$(MODULE)Ndds.a

all : $(ARCHIVE) #java
	/bin/rm -fr h/ objs/

install: all
	/bin/rm -fr h/ objs/
	cp $(ARCHIVE)  $(INSTALL_DIR)/lib/`uname`/.
	cp sensorMsgs.h $(INSTALL_DIR)/include/.
	cp -R $(MODULE) $(INSTALL_DIR)/java/.

java:
	java Jrpcgen -P $(MODULE) -n sensorMsgs.x
	cp Makefile.java.rules $(MODULE)/Makefile
	$(MAKE) -C $(MODULE)
	
$(ARCHIVE) : sensorMsgs.o
	$(AR) $(ARFLAGS) $(ARCHIVE) sensorMsgs.o 

sensorMsgs.o : sensorMsgs.c sensorMsgs.h
	$(CC) -o $@ $(DEFINES) $(INCLUDES) -c $<

sensorMsgs.c : sensorMsgs.x
	$(NDDSGEN) sensorMsgs.x $(SM_DRIVER_PUBLICATIONS) -replace

sensorMsgs.h : sensorMsgs.x
	$(NDDSGEN) sensorMsgs.x $(SM_DRIVER_PUBLICATIONS) -replace
clean:
	/bin/rm -f *.o core $(ARCHIVE) sensorMsgs.c sensorMsgs.h 
