#!/usr/bin/tclsh
#
#  Generate simple pub/sub programs for each data type
#
proc makesaldirs { base name } {
   exec mkdir -p [set base]_[set name]/python
   exec mkdir -p [set base]_[set name]/cpp/src
   exec mkdir -p [set base]_[set name]/cpp/standalone
   exec mkdir -p [set base]_[set name]/isocpp
   exec mkdir -p [set base]_[set name]/java/src/org/lsst/sal
   exec mkdir -p [set base]_[set name]/java/src/org/lsst/sal/$base/$name
   exec mkdir -p SALDDS/java/src/org/lsst/sal
   exec mkdir -p [set base]_[set name]/java/standalone
   exec mkdir -p SALDDS/cpp/src
}

proc makesalcode { idlfile base name lang} {
      puts stdout "Processing $base $name"
      makesaldirs $base $name
      set id [set base]_[set name]
      set frep [open /tmp/sreplace.sal w]
      puts $frep "#!/bin/sh"
      if { $lang == "cpp" } {
        exec cp Makefile-cpp.template [set id]/cpp/standalone/Makefile
        puts $frep "perl -pi -w -e 's/sacpp_SAL_types/sacpp_[set base]_types/g;' [set id]/cpp/standalone/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/cpp/standalone/Makefile"
        exec cp Makefile.sacpp_SAL_types.template [set id]/cpp/standalone/Makefile.sacpp_[set base]_types
        puts $frep "perl -pi -w -e 's/SALData.idl/[file tail $idlfile]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/sal_[set base]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/sacpp_SAL_types/sacpp_[set base]_types/g;' [set id]/cpp/standalone/Makefile.sacpp_[set base]_types"
        exec cp Makefile.sacpp_SAL_sub.template [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub"
        exec cp Makefile.sacpp_SAL_pub.template [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub"
        exec cp Makefile.saj_SAL_pub.template [set id]/java/standalone/Makefile.saj_[set id]_pub
        exec cp SALDataPublisher.cpp.template [set id]/cpp/src/[set id]DataPublisher.cpp
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/cpp/src/[set id]DataPublisher.cpp"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/cpp/src/[set id]DataPublisher.cpp"
        exec cp SALDataSubscriber.cpp.template [set id]/cpp/src/[set id]DataSubscriber.cpp
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/cpp/src/[set id]DataSubscriber.cpp"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/cpp/src/[set id]DataSubscriber.cpp"
        foreach f "CheckStatus.cpp CheckStatus.h SALData.cpp SALDataDcps.cpp SALDataDcps.h SALDataDcps_impl.cpp SALDataDcps_impl.h SALData.h SALDataSplDcps.cpp SALDataSplDcps.h ccpp_SALData.h" {
           exec cp $f [set id]/cpp/src/.
      }
      if { $lang == "java"}  {
        exec cp Makefile-java.template [set id]/java/standalone/Makefile
        puts $frep "perl -pi -w -e 's/saj_SAL_types/saj_[set base]_types/g;' [set id]/java/standalone/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile"
        exec cp Makefile.saj_SAL_types.template [set id]/java/standalone/Makefile.saj_[set base]_types
        puts $frep "perl -pi -w -e 's/SALData.idl/[file tail $idlfile]/g;' [set id]/java/standalone/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set id]/java/standalone/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set id]/java/standalone/Makefile.saj_[set base]_types"
        exec cp Makefile-java.template [set id]/java/Makefile
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile.saj_[set id]_pub"
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/standalone/Makefile.saj_[set id]_pub"
        exec cp Makefile.saj_SAL_sub.template [set id]/java/standalone/Makefile.saj_[set id]_sub
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile.saj_[set id]_sub"
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/standalone/Makefile.saj_[set id]_sub"
        exec cp SALTopicDataPublisher.java.template [set id]/java/src/[set id]DataPublisher.java
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/src/[set id]DataPublisher.java"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/src/[set id]DataPublisher.java"
        exec cp SALTopicDataSubscriber.java.template [set id]/java/src/[set id]DataSubscriber.java
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/src/[set id]DataSubscriber.java"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/src/[set id]DataSubscriber.java"
        exec cp -r java/standalone/SALData [set id]/java/standalone/.
      }
      if { $lang == "isocpp" } {
        exec cp Makefile-isocpp.template [set id]/isocpp/Makefile
        puts $frep "perl -pi -w -e 's/SAL_Typesupport/[set base]_TypeSupport/g;' [set id]/isocpp/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/isocpp/Makefile"
        exec cp Makefile.ISO_Cxx_SAL_Typesupport.template [set id]/isocpp/Makefile.ISO_Cxx_[set base]_Typesupport
        puts $frep "perl -pi -w -e 's/SALData.idl/[file tail $idlfile]/g;' [set id]/isocpp/Makefile.ISO_Cxx_[set base]_Typesupport"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set id]/isocpp/Makefile.ISO_Cxx_[set base]_Typesupport"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set id]/isocpp/Makefile.ISO_Cxx_[set base]_Typesupport"
        exec cp implementation.hpp.template [set id]/isocpp/implementation.hpp
        exec cp publisher.cpp.template [set id]/isocpp/publisher.cpp
        exec cp subscriber.cpp.template [set id]/isocpp/subscriber.cpp
        exec cp implementation.cpp.template [set id]/isocpp/implementation.cpp
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/isocpp/implementation.cpp"
        puts $frep "perl -pi -w -e 's/SALTopic/$name/g;' [set id]/isocpp/implementation.cpp"
      }
      if { $lang == "python" } {
        exec cp SALTopicPublisher.py.template [set id]/[set id]Publisher.py
        puts $frep "perl -pi -w -e 's/SALTopic/$id/g;' [set id]/[set id]Publisher.py"
        exec cp SALTopicSubscriber.py.template [set id]/[set id]Subscriber.py
        puts $frep "perl -pi -w -e 's/SALTopic/$id/g;' [set id]/[set id]Subscriber.py"
      }
      close $frep
      exec chmod 755 /tmp/sreplace.sal
      catch { set result [exec /tmp/sreplace.sal] } bad
      if { $bad != "" } {puts stdout $bad}
      addSALDDStypes $idlfile $id $lang
}


proc unittest { } { 
      makesalcode idl/sal_tcs.idl tcs kernel_TrackingTarget cpp
      makesalcode idl/sal_tcs.idl tcs kernel_TrackingTarget java
      makesalcode idl/sal_tcs.idl tcs kernel_TrackingTarget isocpp
      makesalcode idl/sal_tcs.idl tcs kernel_TrackingTarget python
}


proc salfullgen { } {
  set atypes [lsort [glob idl/*.idl]]
  foreach i $atypes {
    set base [lindex [exec grep module $i] 1]
    set ptypes [split [exec grep pragma $i] \n]
    foreach j $ptypes {
      set name [lindex $j 2]
      makesalcode $idlfile $base $name cpp
      makesalcode $idlfile $base $name java
      makesalcode $idlfile $base $name isocpp
      makesalcode $idlfile $base $name python
    }
  }
}

source /opt/lsstsal/scripts/gensalgetput.tcl


