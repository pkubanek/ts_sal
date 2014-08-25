CC = egcs
LD = egcs
AR = ar
ARFLAGS = r
NDDSGEN = nddsgen
SYSLIBS = -lm -lpthread

INSTALL_DIR = $(NOMAD_HOME)

DEFINES = 

MODULE = Database

INCLUDES = -I$(NDDSHOME)/include/unix \
           -I$(NDDSHOME)/include/share \
	   -I$(INSTALL_DIR)/include

LIBS = 	$(NDDSHOME)/lib/i86Linux5.1/libndds.a    \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsip.a \
       	$(NDDSHOME)/lib/i86Linux5.1/libutilsxx.a \
	$(SYSLIBS)

ARCHIVE      = lib$(MODULE)Ndds.a

all : $(ARCHIVE) #java
	/bin/rm -fr h/ objs/

install: all
	/bin/rm -fr h/ objs/
	cp $(ARCHIVE)  $(INSTALL_DIR)/lib/`uname`/.
	cp dbMsgs.h $(INSTALL_DIR)/include/.
	cp dbRecord.h $(INSTALL_DIR)/include/.
	cp dbRecordDef.h $(INSTALL_DIR)/include/.
	#cp -R $(MODULE) $(INSTALL_DIR)/java/.

java:
	java Jrpcgen -P $(MODULE) -n dbMsgs.x
	java Jrpcgen -P $(MODULE) -n dbRecord.x	
	cp Makefile.java.rules $(MODULE)/Makefile
	$(MAKE) -C $(MODULE)
	
$(ARCHIVE) : dbRecord.o dbMsgs.o
	$(AR) $(ARFLAGS) $(ARCHIVE) dbMsgs.o dbRecord.o

dbMsgs.o : dbMsgs.c dbMsgs.h dbRecordDef.h
	$(CC) -o $@ $(DEFINES) $(INCLUDES) -c $<

dbMsgs.c : dbMsgs.x
	$(NDDSGEN) dbMsgs.x -replace

dbMsgs.h : dbMsgs.x
	$(NDDSGEN) dbMsgs.x -replace

dbRecord.o : dbRecord.c dbRecord.h dbRecordDef.h
	$(CC) -o $@ $(DEFINES) $(INCLUDES) -c $<

dbRecord.c : dbRecord.x
	$(NDDSGEN) dbRecord.x -replace

dbRecord.h : dbRecord.x
	$(NDDSGEN) dbRecord.x -replace

clean:
	/bin/rm -f dbMsgs.o core $(ARCHIVE) dbMsgs.c dbMsgs.h dbRecord.o dbRecord.c dbRecord.h $(MODULE)

