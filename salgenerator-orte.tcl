set stagingdir /tmp/salgenerator/lsst_SAL_c
catch { exec rm -fr $stagingdir }
exec mkdir -p $stagingdir 


proc genorte { pub sub s } {
global IDLCOMPILER stagingdir
   puts stdout "Subsystem $s : pub=$pub sub=$sub"
   catch {exec $IDLCOMPILER $s.idl
          exec mv $s.h $s_orte.h
          exec mv $s.c $s_orte.c
         } result
   set flist "[set s]_orte.h $s.idl [set s]_orte.c"
   if { $pub } {
     set fpout [open $stagingdir/[set s]_orte_publisher.c w]
     set topic $s
     puts $fpout " 
/* ORTE $topic Publisher */
#include \"orte.h\"
#include <stdio.h>
#include \"[set topic]_orte.h\"

ORTEDomain        *d=NULL;
[set topic]_type  [set topic]_instance;
int               counter=0;

void
sendCallBack_[set topic](const ORTESendInfo *info,void *vinstance, void *sendCallBackParam) \{
  [set topic]_type *instance=($topic *)vinstance;

  switch (info->status) \{
    case NEED_DATA:
      printf(\"$topic publication, count %d\n\", counter);
      instance.private_seqNum++;
      break;
    case CQL:  //criticalQueueLevel
      break;
  \}
\}

void *
publisherCreate_[set topic](void *arg) \{
  ORTEPublication     *p;
  NtpTime             persistence, delay;

  ORTETypeRegisterAdd(d,\"$topic\",NULL,NULL,NULL,sizeof([set topic]_type));
  NTPTIME_BUILD(persistence,3);
  NTPTIME_BUILD(delay,1); 
  p=ORTEPublicationCreate(
       d,
      \"Example $topic\",
      \"$topic\",
      &[set topic]_instance,
      &persistence,
      1,
      sendCallBack_$topic,
      NULL,
      &delay);
  return arg;
\}

int
main(int argc, char *args\[\]) \{
  ORTEInit();
  ORTEVerbositySetOptions(\"ALL.10\");
  d=ORTEDomainAppCreate(ORTE_DEFAULT_DOMAIN,NULL,NULL,ORTE_FALSE);
  if (!d) \{
    printf(\"ORTEDomainAppCreate failed!\n\");
    return 0;
  \}
  publisherCreate((void*)d);
  while(1) 
    ORTESleepMs(1000);

  ORTESleepMs(10000);
  printf(\"finished!\n\");
  ORTEDomainAppDestroy(d);
  return 0;
\}
"
      close $fpout
      lappend $flist [set s]_orte_publisher.c
   }
   if { $sub } {
     set fsout [open $stagingdir/[set s]_orte_subscriber.c w]
     puts $fsout " 
/* ORTE $topic Subscriber */

#include \"orte.h\"
#include <stdio.h>
#include \"[set topic]_orte.h\"

ORTEDomain        *d = NULL;

void
recvCallBack_[set topic](const ORTERecvInfo *info,void *vinstance, void *recvCallBackParam) \{
  [set topic]_type *instance=($topic *)vinstance;

  switch (info->status) \{
    case NEW_DATA:
      printf(\"$topic received: %s\n\",instance);
      break;
    case DEADLINE:
      printf(\"$topic deadline occurred\n\");
      break;
  \}
\}


void *
subscriberCreate_[set topic](void *arg) \{
  ORTESubscription    *s;
  NtpTime             deadline,minimumSeparation;

  ORTETypeRegisterAdd(d,\"$topic\",NULL,NULL,NULL,sizeof([set topic]_type));
  NTPTIME_BUILD(deadline,10);
  NTPTIME_BUILD(minimumSeparation,0);
  s=ORTESubscriptionCreate(
       d,
       IMMEDIATE,
       BEST_EFFORTS,
       \"Example $topic\",
       \"$topic\",
       &[set topic]_instance,
       &deadline,
       &minimumSeparation,
       recvCallBack_$topic,
       NULL,
       IPADDRESS_INVALID);
  return arg;
\}



int
main(int argc, char *args\[\]) \{
  ORTEInit();
  ORTEVerbositySetOptions(\"ALL.10\");
  d=ORTEDomainAppCreate(ORTE_DEFAULT_DOMAIN,NULL,NULL,ORTE_FALSE);
  if (!d) \{
    printf(\"ORTEDomainAppCreate failed!\n\");
    return 0;
  \}
  subscriberCreate(NULL);
  while (1)
    ORTESleepMs(1000);
  return 0;
\}"
     close $fsout
     lappend flist [set s]_orte_subscriber.c
   }
   set fsmak [open $stagingdir/makefile.orte w]
   puts $fsmak " 
CC = gcc
CC_FLAGS = -m32
CC_LDFLAGS = -m32
CXX = g++
CXX_FLAGS = -m32
CXX_LDFLAGS = -m32 -static-libgcc
SYSLIBS = -ldl -lnsl -lm -lpthread
DEFINES_ARCH_SPECIFIC = -DLINUX


DEFINES = \$(DEFINES_ARCH_SPECIFIC)  

INCLUDES = -I. -I\$(ORTEHOME)/include

LIBS = -L\$(ORTEHOME)/lib

CDRSOURCES    = $topic.idl
COMMONSOURCES = $flist
EXEC          = [set topic]_orte_publisher \\
		[set topic]_orte_subscriber \\
		orte_manager

COMMONOBJS    = \$(COMMONSOURCES:%.c=%.o)


%.out : %.o 
        \$(CC) \$(CC_LDFLAGS) -o \$(@:%.out=%) \$(@:%.out=%.o) \$(COMMONOBJS) \$(LIBS)

%.o : %.c [set topic]_orte.h 
        \$(CC) \$(CC_FLAGS)  -o \$@ \$(DEFINES) \$(INCLUDES) -c \$<


"
   close $fsmak
   lappend flist makefile.orte
   buildsalorte
   foreach f $flist {
      exec cp $f $stagingdir/.
   }
}

unset ORTEGEN
foreach sid [array names SUBS] {
   set s [join [split $sid .] _]
   if { [info exists PUBS($s)] } {
      genorte 1 1 $s
      set ORTEGEN($s) 1
   } else {
      genorte 0 1 $s
      set ORTEGEN($s) 1
   }    
}
foreach sid [array names PUBS] { 
   set s [join [split $sid .] _]
   if { [info exists ORTEGEN($s)] == 0 } {
      genorte 1 0 $s
      set ORTEGEN($s) 1
   }
}

set IDLCOMPILER /opt/lsstsal/bin/orte-idl


