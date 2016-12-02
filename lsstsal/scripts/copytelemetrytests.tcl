#!/usr/bin/tclsh

foreach subsys "camera dm dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS environment hexapod m1m3 m2ms MTMount network ocs operations power rotator scheduler seeing skycam system tcs" {
    set all [glob [set subsys]_*/cpp]
    foreach i $all {
       set tlm [lindex [split $i "/"] 0]
       set top [join [lrange [split $tlm "_"] 1 end] "_"]
       exec cp -v $i/standalone/sacpp_[set subsys]_pub $subsys/cpp/src/sacpp_[set subsys]_[set top]_publisher
       exec cp -v $i/standalone/sacpp_[set subsys]_sub $subsys/cpp/src/sacpp_[set subsys]_[set top]_subscriber
       puts stdout "Done $subsys $top"
    }
}


