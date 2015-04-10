set SUBSYSTEMS camera*
set TARGETS [lsort [glob [file tail $SUBSYSTEMS].idl]]
set ORIGIN_DIR [pwd]
set SAL_DIR $env(SAL_DIR)
source $SAL_DIR/versioning.tcl
source $SAL_DIR/utilities.tcl
set SAL_WORK_DIR .
set IDL_DIR idl-templates/validated

set ddscmd "$DDSGEN -d ./ospl-$topic -c++ $topic.idl"
set SAL_SUBSYSTEMS "auxscope calibration camera dm enclosure environment lasercal 
		m1m3 m2ms mount network ocs power scheduler seeing_dimm seeing_mass skycam system tcs"


source $SAL_DIR/checkidl.tcl
set subsystems "auxscope calibration camera dm enclosure environment lasercal 
		m1m3 m2ms mount network ocs power scheduler seeing_dimm seeing_mass skycam system tcs"
mkdir -p validated
foreach s $subsystems {
   checkidl template-$s.idl
   puts stdout "Validated $s"
   exec rm validated/template-$s.idl
}


source $SAL_DIR/gensimdcode.tcl
checksimd $idldir



