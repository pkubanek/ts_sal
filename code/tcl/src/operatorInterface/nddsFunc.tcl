# nddsFunc.tcl: Additional NDDS functions needed.
# Michael Wagner, 8/12/98


# This procedure converts a \0 terminated string in
# an NDDS character array to a Tcl string.

proc NddsStr_to_TclStr { NddsString } {
    set TclStr "";
    set i 0;
    set element [lindex $NddsString $i]
    while {[expr ($element != 0) && ($element != -1)]} {
	if {$element != " "} {
	    set tmp [format "%c" $element]
	    append TclStr $tmp;
	}
	incr i;
	set element [lindex $NddsString $i];
    }

    return $TclStr;
}
