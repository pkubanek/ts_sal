#!/usr/bin/tclsh 

set scriptdir /usr/local/scripts/tcl

proc calcshmid { subsys } {
  set fout [open /tmp/subsys.tmp w]
  puts $fout "$subsys"
  close $fout
  set id [string range [exec md5sum /tmp/subsys.tmp] 0 3]
  return $id
}

set all [glob *_cache.h]
set STREAMS ""
foreach i $all {
   set id [string range $i 0 [expr [string length $i] - 9]]
   lappend STREAMS $id
}

set fmd5 [open revCodes.tcl w]
foreach i [lsort $STREAMS] {
  set c [lindex [exec md5sum $i.idl] 0]
  set s [file rootname $i]
  puts $fmd5 "set REVCODE($s) $c"
}
close $fmd5


set fcid [open svcSAL_shmProperties.c w]
puts $fcid "

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"

int svcSAL_shmProperties ( char *subsys, int *streamid, int *size ) \{

  *streamid = 0;
  *size = 0;
"
foreach s $STREAMS {
  set id1 [calcshmid [set s]]
  puts $fcid "
  if (strcmp(\"$s\",subsys) == 0 ) \{
     *streamid = 0x$id1;
     *size = sizeof(struct [set s]_cache);
  \}"
}

puts $fcid "
  if (*streamid == 0) \{
     return SAL__ERR;
  \}
  return SAL__OK;
\}
"


close $fcid


#
#  Add generic read/write for private properties
#
#  svcSAL_accessPrivate (char *topic , char *operation, char *revCode , 
#                        long *sndStamp, long *rcvStamp,
#                        long *seqNum  , long *origin )
#
#    operation=read/write/verify
#
# verify checks that revCode == compiled-in version
#                    seqNum increases
#                    rcvStamp-sndStamp
#                    origin is legal
#

source revCodes.tcl

set finc [open svcSAL_caches.h w]
set fcid [open svcSAL_accessPrivate.c w]
puts $fcid "

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"
extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];

int svcSAL_accessPrivate ( int handle , char *operation, char *revCode , 
                           long *sndStamp, long *rcvStamp,
                           long *seqNum  , long *origin ) \{
"
foreach s "$STREAMS" {
  set rev $REVCODE($s)
  puts $finc "#include \"[set s]_cache.h\""
  puts $fcid "
  if (strcmp(\"$s\",svcSAL_handle\[handle\].streamname) == 0 ) \{
     [set s]_cache *[set s]_ref;
     [set s]_ref  = ([set s]_cache *) svcSAL_handle\[handle\].ref;
     if (strcmp(operation,\"read\") == 0 ) \{
        *sndStamp = [set s]_ref->private_sndStamp; 
        *rcvStamp = [set s]_ref->private_rcvStamp; 
        *seqNum = [set s]_ref->private_seqNum; 
        *origin = [set s]_ref->private_origin; 
     \}
     if (strcmp(operation,\"write\") == 0 ) \{
        [set s]_ref->private_sndStamp = *sndStamp; 
        [set s]_ref->private_rcvStamp = *rcvStamp; 
        [set s]_ref->private_seqNum = *seqNum; 
        [set s]_ref->private_origin = *origin; 
     \}
     if (strcmp(operation,\"verify\") == 0 ) \{
        if ( strcmp(revCode,\"$rev\") != 0 ) { return SAL__ILLEGAL_REVCODE; }
     \}
     return SAL__OK;
  \}"
}

puts $fcid "
  return SAL__ERR;
\}
"


close $fcid
close $finc

set fcid [open svcSAL_datastreamRead.c w]
puts $fcid "
/* Sample datastream reader , intended to be called automatically
   from svcSAL_receiveDatastream on arrival of new data.
   Remove cases for non-applicable datastreams and add 
   stream dependent processing code.
 */

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"

int svcSAL_test_datastreamCallback (char *subsystem, int *shmdata_ref ) \{
   printf(\"%s command received\",subsystem);"
foreach s $STREAMS {
  puts $fcid "

   if (strcmp(\"$s\",subsystem) == 0 ) \{
     [set s]_cache *[set s]_ref;
     [set s]_ref = ([set s]_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     [set s]_ref->syncI = 0;
   \}
"
}
puts $fcid "
   return SAL__OK;
\}
"
set fcid [open svcSAL_accessSync.c w]
puts $fcid "

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"
extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];

int svcSAL_accessSync ( int handle , int direction, int optype ) \{
  int status;
"
foreach s $STREAMS {
  puts $fcid "
  if (strcmp(\"$s\",svcSAL_handle\[handle\].streamname) == 0 ) \{
    [set s]_cache *[set s]_ref;
    [set s]_ref  = ([set s]_cache *) svcSAL_handle\[handle\].ref;
     status = SAL__OK;
     if ( direction == SAL__SYNC_IN ) \{
        if ( optype == SAL__SYNC_SET ) \{
           [set s]_ref->syncI = 1;
        \}
        if ( optype == SAL__SYNC_CLEAR ) \{
           [set s]_ref->syncI = 0;
        \}
        if ( optype == SAL__SYNC_READ ) \{
           status = [set s]_ref->syncI;
        \}
     \}
     if ( direction == SAL__SYNC_OUT ) \{
        if ( optype == SAL__SYNC_SET ) \{
           [set s]_ref->syncO = 1;
        \}
        if ( optype == SAL__SYNC_CLEAR ) \{
           [set s]_ref->syncO = 0;
        \}
        if ( optype == SAL__SYNC_READ ) \{
           status = [set s]_ref->syncO;
        \}
     \}

     return status;
  \}"
}

puts $fcid "
  return SAL__ERR;
\}
"
close $fcid





