#
#  Replace paths with generic ones
#

set flist [exec find ./CMakeFiles/. -type f -print]
set fout [open /tmp/replace w]
puts $fout "#!/bin/sh"
foreach f $flist {
   puts $fout "perl -pi -w -e 's/\\/opt\\/OpenSplice\\/HDE\\/x86.linux2.6/OSPL_HDE/g;' $f"
   puts $fout "perl -pi -w -e 's/\\/opt\\/simd-cxx-v0.9\\/cmake/SAL_CMAKE_DIR/g;' $f"
   puts $fout "perl -pi -w -e 's/\\/opt\\/simd-cxx-v0.9\\/demo\\/TopicId/SAL_WORK_DIR/g;' $f"
   puts $fout "perl -pi -w -e 's/\\/opt\\/simd/SIMD_BASE_DIR/g;' $f"
}
close $fout
exec chmod +x /tmp/replace
exec /tmp/replace


