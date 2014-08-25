
proc add_bandwidth_appendix { fout } {
   set all "datastreams-bandwidths-by-subsystem.html
datastreams-bandwidths-by-blobs.html
datastreams-bandwidths-auxscope.html
datastreams-bandwidths-calibration.html
datastreams-bandwidths-camera.html
datastreams-bandwidths-enclosure.html
datastreams-bandwidths-environment.html
datastreams-bandwidths-lasercal.html
datastreams-bandwidths-m1m3.html
datastreams-bandwidths-m2.html
datastreams-bandwidths-mount.html
datastreams-bandwidths-network.html
datastreams-bandwidths-operations.html
datastreams-bandwidths-power.html
datastreams-bandwidths-scheduler.html
datastreams-bandwidths-seeing.html
datastreams-bandwidths-seeing_dimm.html
datastreams-bandwidths-seeing_mass.html
datastreams-bandwidths-skycam.html
datastreams-bandwidths-tcs.html
datastreams-bandwidths.html"
  foreach i $all { 
     set fin [open bandwidth/$i r]
     gets $fin rec
     while { [gets $fin rec] > -1 } {
        if { [string range $rec 0 18] == "This table does not" } {
           gets $fin rec
           gets $fin rec
        }
        if { $rec != "</TABLE><P></BODY></HTML>" } {
           puts $fout $rec
        } else {
           puts $fout "</TABLE><P>"
        }
     }
     close $fin
  }
}



