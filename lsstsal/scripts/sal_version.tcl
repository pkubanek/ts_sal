set SALVERSION 3.0.2
set SAL_BASE_DIR $env(SAL_DIR)/scripts
set SAL_CMAKE_DIR $SAL_BASE_DIR/code/simd/cmake
set SAL_SID(auxscope) 		1000
set SAL_SID(calibration)	2000
set SAL_SID(camera) 		3000
set SAL_SID(dm) 		4000
set SAL_SID(dome) 		5000
set SAL_SID(environment) 	6000
set SAL_SID(hexapod) 		7000
set SAL_SID(lasercal) 		8000
set SAL_SID(m1m3) 		9000
set SAL_SID(m2ms) 		10000
set SAL_SID(MTMount) 		11000
set SAL_SID(network) 		12000
set SAL_SID(ocs) 		13000
set SAL_SID(power) 		14000
set SAL_SID(rotator) 		15000
set SAL_SID(scheduler) 		16000
set SAL_SID(seeing) 		17000
set SAL_SID(skycam) 		18000
set SAL_SID(system) 		19000
set SAL_SID(tcs) 		20000

set SAL_SUBSYSTEMS [lsort [array names SAL_SID]]


