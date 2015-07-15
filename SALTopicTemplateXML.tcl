#!/usr/bin/tclsh

proc writeXMLsubsys { dpath subsys {ftype subsystem} } {
global XMLTLM XMLTOPICS
  exec mkdir -p $dpath
  set fout [open $dpath/[set subsys]_Telemetry.xml w]
  set updatedate [exec date]
  set base [lindex [split $subsys "_"] 0]
  puts $fout "<SALTelemetry>
<Subsystem>[set base]</Subsystem>
<Version>2.4</Version>
<Author>salgenerator</Author>
<EFDB_Topic>$subsys</EFDB_Topic>
<Explanation></Explanation>"
  foreach i [lsort [array names XMLTOPICS]] {
    if { $i != "camera_" } {
     puts $fout "      <item>"
     foreach j "EFDB_Name Description Frequency Publishers Values_per_Publisher Size_in_bytes IDL_Type Units Conversion Sensor_location Count Instances_per_night Bytes_per_night Needed_by_DM  Needed_by_Camera Needed_by_OCS Needed_by_TCS Needed_by_EPO" {
            if { [info exists XMLTLM($i,$j)] } {
              if { $j == "IDL_Type" } {
                 if { [llength [split $XMLTLM($i,$j) "<>"]] > 1 } {
                    set spl [split $XMLTLM($i,$j) "<>"]
                    puts $fout "          <$j>[lindex $spl 0]</$j>"
                    puts $fout "          <IDL_Size>[lindex $spl 1]</IDL_Size>"
                 } else {
                    puts $fout "          <$j>$XMLTLM($i,$j)</$j>"
                    puts $fout "          <IDL_Size>1</IDL_Size>"
                 }
              } else {
                puts $fout "          <$j>$XMLTLM($i,$j)</$j>"
              }
            }
     }
     puts $fout "      </item>"
    }
  }
  puts $fout "</SALTelemetry>"
  close $fout
}



proc testXMLtlm { subsys } {
global XMLTLM XMLTOPICS
    set XMLTOPICS($subsys) 1
    foreach j "EFDB_Topic EFDB_Name Description Frequency Publishers Values_per_Publisher Size_in_bytes IDL_Type Units Conversion Sensor_location Count Instances_per_night Bytes_per_night Needed_by_DM  Needed_by_Camera Needed_by_OCS Needed_by_TCS Needed_by_EPO Explanation" {
      set XMLTLM(test,$j) x
   }
   writeXMLsubsys $subsys
}


