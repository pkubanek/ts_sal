CC = egcs
LD = egcs
AR = ar
ARFLAGS = r
NDDSGEN = nddsgen
SYSLIBS = -lm -lpthread

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = 

MODULE = TargetAcq

INCLUDES = -I$(NDDSHOME)/include/unix \
           -I$(NDDSHOME)/include/share \
	   -I$(INSTALL_DIR)/include

PUBLICATIONS = -publicationType targetAcqRequest \
    	       -publicationType targetAcqReply \
	       -publicationType targetAcqComplete
ARCHIVE      = lib$(MODULE)Ndds.a

all : $(ARCHIVE) #java
	/bin/rm -fr h/ objs/

install: all
	/bin/rm -fr h/ objs/
	cp $(ARCHIVE)  $(INSTALL_DIR)/lib/`uname`/.
	cp targetAcqMsgs.h $(INSTALL_DIR)/include/.
	cp -R $(MODULE) $(INSTALL_DIR)/java/.

java:
	java Jrpcgen -P $(MODULE) -n targetAcqMsgs.x
	cp Makefile.java.rules $(MODULE)/Makefile
	$(MAKE) -C $(MODULE)
	
$(ARCHIVE) : targetAcqMsgs.o 
	$(AR) $(ARFLAGS) $(ARCHIVE) targetAcqMsgs.o

targetAcqMsgs.o : targetAcqMsgs.c targetAcqMsgs.h
	$(CC) -o $@ $(DEFINES) $(INCLUDES) -c $<

targetAcqMsgs.c : targetAcqMsgs.x
	$(NDDSGEN) targetAcqMsgs.x $(PUBLICATIONS) -replace

targetAcqMsgs.h : targetAcqMsgs.x
	$(NDDSGEN) targetAcqMsgs.x $(PUBLICATIONS) -replace

clean:
	/bin/rm -f *.o core $(ARCHIVE) targetAcqMsgs.c targetAcqMsgs.h
