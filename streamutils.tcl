proc doitem { i fid name type n {unit none} {range none} {help "No comment"} } {
   puts $fid "<TR><TD><INPUT NAME=\"id$i\" VALUE=\"$name\"></TD>
<TD><select name=\"type$i\">"
   switch [string tolower $type] {
      byte   { puts $fid "<option value=\"byte\" selected>byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      short   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\" selected>short
                          <option value=\"int\">int
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      int   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\" selected>int
                          <option value=\"float\">float
                          <option value=\"string\">string
                          </select></TD>"
             }
      float   { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\">int
                          <option value=\"float\" selected>float
                          <option value=\"string\">string
                          </select></TD>"
             }
      string  { puts $fid "<option value=\"byte\">byte
                          <option value=\"short\">short
                          <option value=\"int\">int
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
  puts $fid "<TD><select name=\"unit$id\">"
  switch [string tolower $u] {
      none   { puts $fid "<option value=\"none\" selected>none
			<option value=\"meter\">meter
			<option value=\"second\">second
			<option value=\"volt\">volt
			<option value=\"amp\">amp"
             }
      meter  { puts $fid "<option value=\"none\">none
			<option value=\"meter\" selected>meter
			<option value=\"second\">second
			<option value=\"volt\">volt
			<option value=\"amp\">amp"
             }
      second { puts $fid "<option value=\"none\">none
			<option value=\"meter\">meter
			<option value=\"second\ selected">second
			<option value=\"volt\">volt
			<option value=\"amp\">amp"
             }
      volt   { puts $fid "<option value=\"none\">none
			<option value=\"meter\">meter
			<option value=\"second\">second
			<option value=\"volt\" selected>volt
			<option value=\"amp\">amp"
             }
      amp    { puts $fid "<option value=\"none\">none
			<option value=\"meter\">meter
			<option value=\"second\">second
			<option value=\"volt\">volt
			<option value=\"amp\" selected>amp"
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

