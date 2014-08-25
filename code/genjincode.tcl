

proc genjnicode { topic } {
global JDK_DIR SAL_DIR
  catch { set result [exec swig -c++ -java -w401 ./svcSAL_[set topic]_onlyshm.i] } bad
  if { $bad != "" } {
     errorexit "JNI generation failed : \n $bad"
  }
  catch { set result [exec   c++ -c TopicId_onlyshm.cpp -I$SAL_DIR/code/include/sal svcSAL_[set TopicId]_onlyshm_wrap.cxx -I$JDK_DIR/include/linux -I$JDK_DIR/include] } bad
  if { $bad != "" } {
     errorexit "JNI compile step failed : \n $bad"
  }
  catch { set result [exec gcc -o libswig[set TopicId].so TopicId_onlyshm.o svcSAL_[set TopicId]_onlyshm_wrap.o] } bad
  if { $bad != "" } {
     errorexit "JNI linker step failed : \n $bad"
  }
}


