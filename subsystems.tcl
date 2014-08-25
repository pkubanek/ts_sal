#!/usr/bin/tclsh 

set scriptdir $env(SAL_DIR)

proc calcshmid { subsys } {
  set fout [open /tmp/subsys.tmp w]
  puts $fout "$subsys"
  close $fout
  set id [string range [exec md5sum /tmp/subsys.tmp] 0 3]
  return $id
}

set COMMANDABLE "auxscope calibration camera dm enclosure environment lasercal m1m3 m2 mount network ocs power scheduler seeing_dimm seeing_mass skycam system tcs"

set FREQUENCY(enclosure)    1.0
set FREQUENCY(environment)  1.0
set FREQUENCY(m1m3)         1.0
set FREQUENCY(m2)           1.0
set FREQUENCY(mount)       10.0
set FREQUENCY(tcs)         10.0

set STREAMS [split [exec cat .salwork/datastreams.names] \n]
set includedir $scriptdir/include
foreach i $STREAMS { 
   if { [file exists shmem-$i/[set i]_cache.h] } {
      exec cp shmem-$i/[set i]_cache.h $includedir/.
   } else {
      puts stdout "No _cache include file for $i, rerun genshmem.tcl"
   }
}


set fcid [open svcSAL_shmProperties.c w]
puts $fcid "

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"

int svcSAL_shmProperties ( char *subsys, int *streamid, int *size ) \{

  streamid = 0;
  size = 0;
"
foreach s $STREAMS {
  set id1 [calcshmid [set s]]
  puts $fcid "
  if (strcmp(\"$s\",subsys) == 0 ) \{
     *streamid = 0x$id1;
     *size = sizeof([set s]_cache);
  \}"
}

set CSTREAMS ""
foreach s $COMMANDABLE {
  set id1 [calcshmid [set s]_command]
  lappend CSTREAMS [set s]_command
  puts $fcid "
  if (strcmp(\"[set s]_command\",subsys) == 0 ) \{
     *streamid = 0x$id1;
     *size = sizeof(svcSAL_command);
  \}"
  set id1 [calcshmid [set s]_response]
  lappend CSTREAMS [set s]_response
  puts $fcid "
  if (strcmp(\"[set s]_response\",subsys) == 0 ) \{
     *streamid = 0x$id1;
     *size = sizeof(svcSAL_response);
  \}"
}
puts $fcid "
  if (streamid == 0) \{
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

source .salwork/revCodes.tcl

set finc [open $includedir/svcSAL_caches.h w]
set fcid [open svcSAL_accessPrivate.c w]
puts $fcid "

#include \"svcSAL.h\"
#include \"svcSAL_caches.h\"

int svcSAL_accessPrivate ( int handle , char *operation, char *revCode , 
                           long *sndStamp, long *rcvStamp,
                           long *seqNum  , long *origin, long *host ) \{
"
foreach s "$STREAMS $CSTREAMS" {
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
        *host = [set s]_ref->private_host; 
     \}
     if (strcmp(operation,\"write\") == 0 ) \{
        [set s]_ref->private_sndStamp = *sndStamp; 
        [set s]_ref->private_rcvStamp = *rcvStamp; 
        [set s]_ref->private_seqNum = *seqNum; 
        [set s]_ref->private_origin = *origin; 
        [set s]_ref->private_host = *host; 
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

int svcSAL_accessSync ( int handle , int direction, int optype ) \{
  int status;
"
foreach s "$STREAMS $CSTREAMS" {
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





