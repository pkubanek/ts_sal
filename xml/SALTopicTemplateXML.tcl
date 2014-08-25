
proc writeXMLsubsys { dpath subsys {ftype subsystem} } {
global XMLTLM XMLTOPICS
  exec mkdir -p $dpath
  set fout [open $dpath/[set subsys]_Telemetry.xml w]
  set updatedate [exec date]
  if { $ftype == "subsystem" } {
    puts $fout "
<?xml version=\"1.0\"?>
<tlm:SALTelemetry xmlns:tlm=\"http://sal.lsst.org/SALTelemetry\" 
                  Version=\"1.0\"
                  Author=\"dmills@noao.edu\"
                  updateDate=\"$updatedate\">

   <Subsystem=\"$subsys\">
"
    puts $fout "   <Ttems>"
  }
  foreach i [lsort [array names XMLTOPICS]] {
    if { $i != "camera_" } {
     puts $fout "      <item>"
     foreach j "EFDB_Topic EFDB_Name Description Frequency Publishers Values_per_Publisher Size_in_bytes IDL_Type Units Conversion Sensor_location Count Instances_per_night Bytes_per_night Needed_by_DM  Needed_by_Camera Needed_by_OCS Needed_by_TCS Needed_by_EPO Explanation" {
            if { [info exists XMLTLM($i,$j)] } {
              puts $fout "          <$j>$XMLTLM($i,$j)</$j>"
#              puts stdout "<$j>$XMLTLM($i,$j)</$j>"
            }
     }
     puts $fout "      </item>"
    }
  }
  if { $ftype == "subsystem" } {
    puts $fout "   </Items>"
    puts $fout "</tlm:SALTelemetry>"
  }
  close $fout
}


proc test { subsys } {
global XMLTLM XMLTOPICS
    set XMLTOPICS($subsys) 1
    foreach j "EFDB_Topic EFDB_Name Description Frequency Publishers Values_per_Publisher Size_in_bytes IDL_Type Units Conversion Sensor_location Count Instances_per_night Bytes_per_night Needed_by_DM  Needed_by_Camera Needed_by_OCS Needed_by_TCS Needed_by_EPO Explanation" {
      set XMLTLM(test,$j) x
   }
   writeXMLsubsys $subsys
}


