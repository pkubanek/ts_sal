
proc topicitem { fid topic item type } {
  puts $fid "<UML:Attribute name=\"$item\" changeable=\"none\" visibility=\"public\" ownerScope=\"instance\"  targetScope=\"instance\">
<UML:Attribute.initialValue><UML:Expression/>
</UML:Attribute.initialValue>
<UML:StructuralFeature.type>
<UML:Classifier xmi.idref=\"$topic$item\"/>
</UML:StructuralFeature.type>
<UML:ModelElement.taggedValue>
<UML:TaggedValue tag=\"type\" value=\"$type\"/>
<UML:TaggedValue tag=\"derived\" value=\"0\"/>
<UML:TaggedValue tag=\"containment\" value=\"Not Specified\"/>
<UML:TaggedValue tag=\"ordered\" value=\"0\"/>
<UML:TaggedValue tag=\"collection\" value=\"false\"/>
<UML:TaggedValue tag=\"position\" value=\"0\"/>
<UML:TaggedValue tag=\"lowerBound\" value=\"1\"/>
<UML:TaggedValue tag=\"upperBound\" value=\"1\"/>
<UML:TaggedValue tag=\"duplicates\" value=\"0\"/>
<UML:TaggedValue tag=\"styleex\" value=\"volatile=0;\"/>
</UML:ModelElement.taggedValue>
</UML:Attribute>"
}

proc buildxml { sid } {
global stagingdir saldir xmldir idldir
 set fin [open $saldir/scripts/xml/template.xml r]
 set fout [open $stagingdir/[set sid]_eamodel.xml w]
 while { [gets $fin rec] > -1 } {
  if { [string range $rec 0 2] == "###" } {
    if { $rec == "###classname" } {
      puts $fout "<UML:TaggedValue tag=\"ea_targetName\" value=\"$sid\"/>"
    }
    if { $rec == "###role" } {
      puts $fout "<UML:ClassifierRole name=\"$sid\" visibility=\"public\">"
    }
    if { $rec == "###type" } {
      puts $fout "<UML:Class name=\"my[set sid]Type\" visibility=\"public\" isRoot=\"false\" isLeaf=\"false\" isAbstract=\"false\" isActive=\"false\">"
    }
    if { $rec == "###items" } {
         set fidl [open $idldir/$sid.idl r]
         gets $fidl rec
         while { [gets $fidl rec] > -1 } {
           if { [string length $rec] > 3 } {
              set t [lindex [lindex [split $rec "\<"] 0] 0]
              set n [string trim [lindex $rec 1] ";"]
              topicitem $fout $sid $n $t
           }
         }
         close $fidl
       }
    }
    if { $rec == "###listener" } {
      puts $fout "<UML:Class name=\"my[set sid]TypeListener\" visibility=\"public\" isRoot=\"false\" isLeaf=\"false\" isAbstract=\"false\" isActive=\"false\">"
    }
    if { $rec == "###header1" } {
      puts $fout "<UML:TaggedValue tag=\"header1\" value=\"#include \&lt;stdio.h\&gt;\&#xA;#include \&lt;stdlib.h\&gt;\&#xA;#include \&quot;ndds/ndds_cpp.h\&quot;\&#xA;#include \&quot;my[set sid]Type.h\&quot;\&#xA;#include \&quot;my[set sid]TypeSupport.h\&quot;\&#xA;\"/>"
    }
    if { $rec == "###code" } {
      puts $fout "<UML:TaggedValue tag=\"code\" value=\"my[set sid]TypeDataReader *my[set sid]Type_instance = NULL;\&#xA;my[set sid]TypeSeq data_seq;\&#xA;DDS_SampleInfoSeq info_seq;\&#xA;DDS_ReturnCode_t retcode;\&#xA;int i;\&#xA;\&#xA;my[set sid]Type_instance = my[set sid]TypeDataReader::narrow(reader);\&#xA;if (my[set sid]Type_instance == NULL) \{\&#xA;	printf(\&quot;DataReader narrow error\\n\&quot;);\&#xA;	return;\&#xA;\}\&#xA;\&#xA;retcode = my[set sid]Type_instance-\&gt;take (\&#xA;	data_seq, info_seq, DDS_LENGTH_UNLIMITED,\&#xA;	DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);\&#xA;\&#xA;if (retcode == DDS_RETCODE_NO_DATA) \{\&#xA;	return;\&#xA;\} else if (retcode != DDS_RETCODE_OK) \{\&#xA;	printf(\&quot;take error %d\\n\&quot;, retcode);\&#xA;	return;\&#xA;\}\&#xA;\&#xA;for (i = 0; i \&lt; data_seq.length(); ++i) \{\&#xA;	if (info_seq\[i\].valid_data) \{\&#xA;		my[set sid]TypeTypeSupport::print_data(\&amp;data_seq\[i\]);\&#xA;	\}\&#xA;\}\&#xA;\&#xA;retcode = my[set sid]Type_instance-\&gt;return_loan(data_seq, info_seq);\&#xA;if (retcode != DDS_RETCODE_OK) \{\&#xA;	printf(\&quot;return loan error %d\\n\&quot;, retcode);\&#xA;\}\"/>"
    }
  } else {
    puts $fout $rec
  }
 }
 close $fin
 close $fout
}

proc doxmlsubsys { subsys } {
global idldir
   set all [lsort [glob $idldir/$subsys*.idl]]
   foreach i $all { 
      set base [file rootname [file tail $i]]
      buildxml $base
      puts stdout "Processed $base"
   }
}


set saldir /opt/lsstsal
set stagingdir /efdb1/test/xml
set xmldir  /opt/lsstsal/scripts/xml
set idldir /efdb1/test/idl-templates/validated

#buildxml topic


