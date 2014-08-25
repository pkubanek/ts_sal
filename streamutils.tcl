proc doitem { i fid name type n {unit none} {range none} {help "No comment"} } {
   puts $fid "<TR><TD><INPUT NAME=\"id$i\" VALUE=\"$name\"></TD>
<TD><select name=\"type$i\">"
   switch [string tolower $type] {
      byte   { puts $fid "<option value=\"byte\" selected>byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                           <option value=\"long\">long
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      short   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\" selected>short
                          <option value=\"int\">int
                          <option value=\"long\">long
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      int   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\" selected>int
                           <option value=\"long\">long
                         <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      long   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                          <option value=\"long\" selected>long
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      float   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                          <option value=\"long\">long
                          <option value=\"float\" selected>float
                          <option value=\"string\">string
                          </select></TD>"
             }
      string  { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                          <option value=\"long\">long
                          <option value=\"float\">float
                          <option value=\"string\" selected>string
                          </select></TD>"
             }
   }
   puts $fid "<TD><INPUT NAME=\"siz$i\" VALUE=\"$n\"></TD>"
   dounit $fid $i $unit
   puts $fid "<TD><INPUT NAME=\"range$i\" VALUE=\"$range\"></TD>
<TD><INPUT NAME=\"help$i\" VALUE=\"$help\"></TD>
<TD><INPUT TYPE=\"checkbox\" NAME=\"delete_$i\" VALUE=\"yes\"></TD></TR>"
}

proc dounit { fid id u} {
global UDESC
  set u [string tolower $u]
  if { [string trim $u] == "" } {set u none}
  puts $fid "<TD><select name=\"unit$id\">"
  puts $fid "<option value=\"$u\" selected>$u"
  foreach i [lsort [array names UDESC]] {
     if { $u != $i } {
       puts $fid "<option value=\"$i\">$i"
     }
  }
  puts $fid "</select></TD>"
}

proc dogen { fid id } {
   puts $fid "<TR><TD>$id</TD>
<TD><INPUT TYPE=\"checkbox\" NAME=\"sub_$id\" VALUE=\"yes\">
<TD><INPUT TYPE=\"checkbox\" NAME=\"pub_$id\" VALUE=\"yes\">
<TD><INPUT TYPE=\"checkbox\" NAME=\"issue_$id\" VALUE=\"yes\">
<TD><INPUT TYPE=\"checkbox\" NAME=\"proc_$id\" VALUE=\"yes\">"
}


proc idlpreamble { fid id } {
  puts $fid "struct [join [split $id .] _] \{
  string<32>	private_revCode; //private
  double	private_sndStamp; //private
  double	private_rcvStamp; //private
  long		private_seqNum; //private
  long		private_origin; //private" 
}

proc sqlpreamble { fid id } {
  puts $fid  "CREATE TABLE $id \{"
  puts $fid  "  date_time date time NOT NULL,
  private_revCode char(32),
  private_sndStamp double,
  private_rcvStamp double,
  private_seqNum int,
  private_origin int,"
}

set WORKING /home/shared/lsst/tests/api/streams
if { [info exists FormData(workingDir)] } {
   set WORKING $FormData(workingDir)
}
if { [info exists env(workingDir)] } {
   set WORKING $env(workingDir)
}



