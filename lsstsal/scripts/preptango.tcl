      set frep [open /tmp/sreplace.sal w]
      puts $frep "#!/bin/sh"
      set all [glob *]
      foreach i $all {   
         puts $frep "perl -pi -w -e 's/Tango Generic/SALLV Generic/g;' $i"
         puts $frep "perl -pi -w -e 's/TANGO/SALLV/g;' $i"
         puts $frep "perl -pi -w -e 's/Tango/SALLV/g;' $i"
         puts $frep "perl -pi -w -e 's/tango/SALLV/g;' $i"
      }

