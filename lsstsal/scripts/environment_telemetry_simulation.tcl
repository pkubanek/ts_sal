#
#   The routine named simulate_[some-telemetry-item-name]_value
#   will be called each time a new value is needed. In case there
#   is more than one topic using the same name, then the topic 
#   argument can be used to determine which is being asked for
#

proc simulate_humidity_value { topic } {
  if { $topic == "environment_weather" } {
     return 100.0
  }  else {
     return 0.0
  }
}


