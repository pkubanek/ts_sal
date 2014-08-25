set SALVERSION 1.1
set SAL_BASE_DIR /opt/lsstsal/scripts
set SAL_CMAKE_DIR $SAL_BASE_DIR/code/simd/cmake
set SAL_SID(auxscope) 1000
set SAL_SID(calibration) 2000
set SAL_SID(camera) 3000
set SAL_SID(dm) 4000
set SAL_SID(enclosure) 5000
set SAL_SID(environment) 6000
set SAL_SID(lasercal) 7000
set SAL_SID(m1m3) 8000
set SAL_SID(m2) 9000
set SAL_SID(mount) 10000
set SAL_SID(network) 11000
set SAL_SID(ocs) 12000
set SAL_SID(power) 13000
set SAL_SID(scheduler) 14000
set SAL_SID(seeing_dimm) 15000
set SAL_SID(seeing_mass) 16000
set SAL_SID(skycam) 17000
set SAL_SID(system) 18000
set SAL_SID(tcs) 19000

set SAL_SUBSYSTEMS [lsort [array names SAL_SID]]


