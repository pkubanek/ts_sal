#
# Generate Labview Daemon interface for a subsystem topic
#
# 
#  export OSPL_HDE=/opt/OpenSplice/HDE/x86.linux2.6
#


proc genlvdaemon { topic } {
global SAL_WORK_SIR OSPL_HDE LVD_FILES SAL_DIR
   exec mkdir -p $SAL_WORK_DIR/ospl-$topic/lv
   set wdir $SAL_WORK_DIR/ospl-$topic/lv
   set odir $SAL_DIR/scripts/code/labview
   set pcmd [open /tmp/pcmd w]
   puts $pcmd "#!/bin/sh"
   exec cp $odir/generic_DDS_commLib.c.template $wdir/generic_DDS_commLib.c
   exec cp $odir/generic_DDS_commLib.h.template $wdir/generic_DDS_commLib.h
   exec cp $odir/Makefile_SALTOPIC.template $wdir/Makefile_[set topic]
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/Makefile_[set topic]"
   exec cp $odir/MakefileSH_SALTOPIC.template $wdir/MakefileSH_[set topic]
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/MakefileSH_[set topic]"
   exec cp $odir/SALTOPIC_DDS_commLib.c.template $wdir/[set topic]_DDS_commLib.c
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_DDS_commLib.c"
   exec cp $odir/SALTOPIC_DDS_commLib.h.template $wdir/[set topic]_DDS_commLib.h
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_DDS_commLib.h"
   exec cp $odir/SALTOPIC_Gen_Daemon.c.template $wdir/[set topic]_Gen_Daemon.c
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_Gen_Daemon.c"
   exec cp $odir/SALTOPIC_Daemon.c.template $wdir/[set topic]_Daemon.c
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_Daemon.c"
   exec cp $odir/SALTOPIC_Daemon.h.template $wdir/[set topic]_Daemon.h
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_Daemon.h"
   exec cp $odir/SALTOPIC_publisher.c.template $wdir/[set topic]_publisher.c
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_publisher.c"
   exec cp $odir/SALTOPIC_subscriber.c.template $wdir/[set topic]_subscriber.c
   puts $pcmd "perl -pi -w -e 's/SALTOPIC/$topic/g;' $wdir/[set topic]_subscriber.c"
   close $pcmd
   exec chmod a+x /tmp/pcmd
   catch { set result [exec /tmp/pcmd] } bad
   exec cp $SAL_WORK_DIR/shmem-[set topic]/[set topic]_cache.h $wdir/.
}




