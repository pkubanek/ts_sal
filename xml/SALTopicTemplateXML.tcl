
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
              puts $fout "          <$j>$XMLTLM($i,$j)</$j>"
#              puts stdout "<$j>$XMLTLM($i,$j)</$j>"
            }
     }
     puts $fout "      </item>"
    }
  }
  puts $fout "</SALTelemetry>"
  close $fout
}

proc writeXMLtelemetry { subsys } { 
global SAL_WORK_DIR
  set fout [open $SAL_WORK_DIR/xml/[set subsys]_Telemetry.xml w]
  puts $fout "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<?xml-stylesheet type=\"text/xsl\" href=\"SALTelemetrySet.xsl\"?>
<SALTelemetrySet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:noNamespaceSchemaLocation=\"SALTelemetrySet.xsd\">"
  set all [glob $SAL_WORK_DIR/xml/[set subsys]_*.xml]
  foreach i $all { 
     set id [lindex [split [file tail $i] "_."] 1]
     if { $id != "Telemetry" && $id != "Commands" && $id != "Events" } {
puts stdout "processing $id"
         set fin [open $i r]
         while { [gets $fin rec] > -1 } { 
            puts $fout $rec
         }
         close $fin
     }
  }
  puts $fout "</SALTelemetrySet>"
  close $fout
}

proc writeXMLcommands { dpath subsys } {
global CMDS CMD_ALIASES
  exec mkdir -p $dpath
  set fout [open $dpath/[set subsys]_Commands.xml w]
  set updatedate [exec date]
  puts $fout "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<?xml-stylesheet type=\"text/xsl\" href=\"SALCommandSet.xsl\"?>
<SALCommandSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:noNamespaceSchemaLocation=\"SALCommandSet.xsd\">"
  foreach i [lsort $CMD_ALIASES($subsys)] {
     puts $fout "
<SALCommand>
 <Subsystem>[set subsys]</Subsystem>
 <Version>2.4</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set subsys]_command_[set i]</EFDB_Topic>
 <Alias>$i</Alias>
 <Device>[lindex $CMDS($subsys,$i) 0]</Device>
 <Property>[lindex $CMDS($subsys,$i) 1]</Property>
 <Action>[lindex $CMDS($subsys,$i) 2]</Action>
 <Value>[lindex $CMDS($subsys,$i) 3]</Value>
 <Explanation>http://sal.lsst.org/SAL/Commands/[set subsys]_command_$i.html</Explanation>"
     if { [info exists CMDS($subsys,$i,param)] } {
        foreach j $CMDS($subsys,$i,param) {
           puts $fout "    <item>"
           set name [string trim [lindex $j 1] "()0123456789"]
           set type [lindex $j 0]
           set count [lindex [split [lindex $j 1] "()"] 1]
           if { $count == ""} { set count 1}
           puts $fout "      <EFDB_Name>$name</EFDB_Name>"
           puts $fout "      <Description> </Description>"
           puts $fout "      <IDL_Type>$type</IDL_Type>"
           puts $fout "      <Units> </Units>"
           puts $fout "      <Count>$count</Count>"
           puts $fout "    </item>"
        }
     }
     puts $fout "</SALCommand>"
  }
  puts $fout "</SALCommandSet>"
  close $fout
}

proc writeXMLevents { dpath subsys } {
global EVTS EVENT_ALIASES
  exec mkdir -p $dpath
  set fout [open $dpath/[set subsys]_Events.xml w]
  puts $fout "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<?xml-stylesheet type=\"text/xsl\" href=\"SALEventSet.xsl\"?>
<SALEventSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:noNamespaceSchemaLocation=\"SALEventSet.xsd\">"
  set updatedate [exec date]
  foreach i [lsort $EVENT_ALIASES($subsys)] {
     puts $fout "
<SALEvent>
 <Subsystem>[set subsys]</Subsystem>
 <Version>2.4</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set subsys]_logevent_[set i]</EFDB_Topic>
 <Alias>$i</Alias>
 <Explanation>http://sal.lsst.org/SAL/Events/[set subsys]_logevent_$i.html</Explanation>"
     if { [info exists EVTS($subsys,$i,param)] } {
        puts $fout "    <item>"
        puts $fout "      <EFDB_Name>priority</EFDB_Name>"
        puts $fout "      <Description>Severity of the event</Description>"
        puts $fout "      <IDL_Type>long</IDL_Type>"
        puts $fout "      <Units>NA</Units>"
        puts $fout "      <Count>1</Count>"
        puts $fout "    </item>"
        foreach j $EVTS($subsys,$i,param) {
           puts $fout "    <item>"
           set name [string trim [lindex $j 1] "()0123456789"]
           set type [lindex $j 0]
           set count [lindex [split [lindex $j 1] "()"] 1]
           if { $count == ""} { set count 1}
           puts $fout "      <EFDB_Name>$name</EFDB_Name>"
           puts $fout "      <Description> </Description>"
           puts $fout "      <IDL_Type>$type</IDL_Type>"
           puts $fout "      <Units> </Units>"
           puts $fout "      <Count>$count</Count>"
           puts $fout "    </item>"
        }
     }
     puts $fout "</SALEvent>"
  }
  puts $fout "</SALEventSet>"
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


