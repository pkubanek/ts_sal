proc checkURL { url } {
  catch { exec wget --spider $url] >& /tmp/checkurl } bad
  set res [exec cat /tmp/checkurl]
  if { [lsearch $res broken] > -1 } {
    return 1
  }
  return 0
}
