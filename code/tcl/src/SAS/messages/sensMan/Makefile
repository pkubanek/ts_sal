CC = egcs
LD = egcs
AR = ar
ARFLAGS = r
NDDSGEN = nddsgen
SYSLIBS = -lm -lpthread

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = 

MODULE = SensMan

INCLUDES = -I$(NDDSHOME)/include/unix \
           -I$(NDDSHOME)/include/share \
	   -I$(INSTALL_DIR)/include

LIBS = 	$(NDDSHOME)/lib/i86Linux5.1/libndds.a    \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsip.a \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsxx.a \
	$(SYSLIBS)

SENS_MAN_PUBLICATIONS  = -publicationType sensManRequest -publicationType sensManReply -publicationType sensManComplete 

ARCHIVE      = lib$(MODULE)Ndds.a

all : $(ARCHIVE) #java
	/bin/rm -fr h/ objs/

install: all 
	/bin/rm -fr h/ objs/
	cp $(ARCHIVE)  $(INSTALL_DIR)/lib/`uname`/.
	cp sensManMsgs.h $(INSTALL_DIR)/include/.
	cp -R $(MODULE) $(INSTALL_DIR)/java/.

java:
	java Jrpcgen -P $(MODULE) -n sensManMsgs.x
	cp Makefile.java.rules $(MODULE)/Makefile
	$(MAKE) -C $(MODULE)
	
$(ARCHIVE) : sensManMsgs.o
	$(AR) $(ARFLAGS) $(ARCHIVE) sensManMsgs.o 

sensManMsgs.o : sensManMsgs.c sensManMsgs.h
	$(CC) -o $@ $(DEFINES) $(INCLUDES) -c $<

sensManMsgs.c : sensManMsgs.x
	$(NDDSGEN) sensManMsgs.x $(SENS_MAN_PUBLICATIONS) -replace

sensManMsgs.h : sensManMsgs.x
	$(NDDSGEN) sensManMsgs.x $(SENS_MAN_PUBLICATIONS) -replace

clean:
	/bin/rm -f *.o core $(ARCHIVE) sensManMsgs.c sensManMsgs.h
