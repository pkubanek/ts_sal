#!/usr/bin/wish

proc readshm { t } {
  puts stdout "testing : readshm $t"
}

proc writeshm { t } {
  puts stdout "testing : writeshm $t"
}


proc switchstream { id } {
}

proc checknewdata { } {
global FROMSAL TOMPG
  foreach t [array names FROMSAL] {
     if { $FROMSAL($t) } {
        readshm $t
        publish_$t
     }
  }
  after 1000 checknewdata
}

proc createidl { s } {
global MPG_ROUTER TOPIC CONFIG_DIR
  set t $TOPIC($s)
  set fidl [open $CONFIG_DIR/$t.idl w]
  set items [lsort [$MPG_ROUTER info $s]]
  puts $fidl "struct \{
  string<32>	private_revCode; //private
  long		private_sndStamp; //private
  long		private_rcvStamp; //private
  long		private_seqNum; //private
  long		private_origin; //private"
  foreach i $items {
    set desc [$MPG_ROUTER info $s.$i]
    set type [lindex $desc 1]
    switch $type {
          integer {
                    puts $fidl "  long		$i;"
                  }
          float   -
          double  {
                    puts $fidl "  float		$i;"
                  }
          string  {
                    puts $fidl "  string<128>	$i;"
                  }
    }
  }
  puts $fidl "\};
"
  close $fidl
}



proc mpgnewdata { t } {
global SHM$t MPG_ROUTER TOPIC STREAM FROMMPG
  foreach i [array names FROMMPG] {
    set SHM[set t]($i) [lindex [$MPG_ROUTER info $STREAM($t).$i] 0]
  }
  writeshm $t
}


proc publishtompg { t } {
global SHM$t MPG_ROUTER CONFIG_DIR
  set fout [$CONFIG_DIR/open publish_$t.tcl w]
  set s [join [split $t _] .]
  puts $fout "
proc publish_$t { } {
global SHM$t MPG_ROUTER"
  set all [array names SHM$t]
  foreach i $all {
    puts stdout "SHM[set t]($i) = [set SHM[set t]($i)]"
    puts $fout "global MPGVARS_[set t]_$i"
  }
  puts $fout "  if \{ \$SHM[set t](syncI) \} \{"
  foreach i $all {
    puts $fout "    set MPGVARS_[set t]_[set i](value) \$SHM[set t]($i)"
  }
  puts $fout "    $MPG_ROUTER cput $s
  set SHM[set t](syncI) 0
  \}
\}
"
  close $fout
}


set MPG_ROUTER $env(MPG_SYSTEM)
set CONFIG_DIR  $env(MPG_SAL_CONFIG)

frame .frommpg -width 200 -height 500 -bg gray
frame .tompg   -width 200 -height 500 -bg gray
pack  .frommpg -side left  
pack  .tompg -side right  
label .frommpg.t -text "From MPG" -bg gray
place .frommpg.t -x 35 -y 0
label .tompg.t -text "From DDS" -bg gray
place .tompg.t -x 35 -y 0

set dy 30

set fmpg [open $CONFIG_DIR/mpg_streams.dat r]
while { [gets $fmpg rec] > -1 } {
   if { [string range $rec 0 0] != "#" && $rec != "" } {
      set topic [join [split [lindex $rec 0] .] _]
      set FROMMPG($topic) 1
      set STREAM($topic) [lindex $rec 0]
      checkbutton .frommpg.$topic -bg gray -width 20 -variable FROMMPG($topic) -text "$topic 0" -command "switchstream $topic" -anchor w
      place .frommpg.$topic -x 5 -y $dy
      incr dy 20
   }
}
close $fmpg

set dy 30
set fsal [open $CONFIG_DIR/sal_streams.dat r]
while { [gets $fsal rec] > -1 } {
   if { [string range $rec 0 0] != "#" && $rec != "" } {
      set topic [join [split [lindex $rec 0] .] _]
      set FROMSAL($topic) 1
      set TOPIC([lindex $rec 1]) $topic
      checkbutton .tompg.$topic -bg gray -width 20 -variable FROMSAL($topic) -text "$topic 0" -command "switchstream $topic" -anchor w
      place .tompg.$topic -x 5 -y $dy
      incr dy 20
   }
}
close $fsal


connect $MPG_ROUTER mpgSAL_bridge

foreach t [lsort [array names FROMSAL]] {
   set fin [open $CONFIG_DIR/$t.idl r]
   set stream [join [split $t _] .]
   set TOMPG($stream) 1
   gets $fin rec; gets $fin rec;gets $fin rec;gets $fin rec;gets $fin rec;gets $fin rec
   while { [gets $fin rec] > -1 ] {
      set dt [string trim [lindex [split $rec "<>"] 0]]
      set name [string trim [lindex $rec 1] ";"]
      switch $dt {
         short -
         long  {
                 $MPG_ROUTER newwvar $stream MPGVAR_$stream_$name integer  $name yes public
                }
         float {
                 $MPG_ROUTER newwvar $stream MPGVAR_$stream_$name float  $name yes public
                }
         string {
                 $MPG_ROUTER newwvar $stream MPGVAR_$stream_$name string  $name yes public
                }
      }
   }
   publishtompg $t
   source $CONFIG_DIR/publish_$t.tcl
}

wm title . "MPG router - SAL DDS bridge"
$MPG_ROUTER set restartdelay 10 100000

foreach s [array names FROMMPG] {
   $MPG_ROUTER subscribe $s
   $MPG_ROUTER stevent $s "mpgnewdata $s" always
   if { [file exists $TOPIC($s).idl] == 0 } {
      createidl $s
      set it [ tk_dialog .d "New TOPIC" "WARNING: Created $TOPIC($s).idl file\nPlease use the SAL VM\nto generate libSALshmtcl\nsupport." {} -1 "OK"]           
   }
}

foreach s [array names TOMPG] {
   $MPG_ROUTER subscribe $s
}


