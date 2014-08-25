#
#  Generate Java JIN interface for a DDS topic
#

proc genjnicode { topic} {
global SAL_DIR SAL_WORK_DIR
   cd $SAL_WORK_DIR/ospl-$topic
   set fout [open /tmp/ddsjni w]
   puts $fout "$DDSGEN -d ./gen -S -l java [set topic].idl"
   close $fout
   exec chmod a+x /tmp/ddsjni
   catch { set result [exec /tmp/ddsjni } bad
   exec mv svcSAL_[set topic]-onlyshm.i gen/.
   cd gen
   catch { set result [exec swig -c++ -java -w401 svcSAL_[set topic]-onlyshm.i] } bad
   catch { set result [exec g++ -c -g svcSAL_camera_TC_zone3_wrap.cxx -I. -I$SAL_DIR/code/include/sal -I$SAL_WORK_DIR/include -I/usr/lib/jvm/java-6-openjdk/include] } bad
   return 0
}

