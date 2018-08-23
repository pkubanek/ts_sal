# EupsPkg config file. Sourced by 'eupspkg'

config()
{
        # Copy XML topics into test directory, for SAL to wrap into C++.
        if [ -d "${SAL_WORK_DIR}" ] 
	then
	    /bin/rm -r "${SAL_WORK_DIR}"
	fi
	mkdir "${SAL_WORK_DIR}"

        cp -r ${TS_XML_DIR}/sal_interfaces/*/*xml "${SAL_WORK_DIR}"/.

}

build()
{
        # Build the libraries for each topic.
        (
	    cd "${SAL_WORK_DIR}"
	    
	    if [ -z "$SUBSYSTEMS" ]
		then 
		export SUBSYSTEMS="archiver camera catchuparchiver dome domeADB domeAPS domeLouvers 
                     domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster
                     rotator scheduler tcs"
		echo "Set SUBSYSTEM to "$SUBSYSTEMS
	    fi

	    for subsys in $(echo $SUBSYSTEMS)
	    do
		echo "Building topics for "$subsys"."
		( salgenerator $subsys validate && salgenerator $subsys sal cpp  && salgenerator $subsys sal python ) || echo "Skipping "$subsys
	    done
	)

        # copy libraries to workdir/lib location.
	(
            mkdir -p ${LSST_SDK_INSTALL}/lsstsal/lib
	 
	    for subsys in $(echo $SUBSYSTEMS)
            do
	       	cp ${SAL_WORK_DIR}/$subsys/cpp/src/*.so ${SAL_WORK_DIR}/lib/.
		cp ${SAL_WORK_DIR}/$subsys/cpp/*.so ${SAL_WORK_DIR}/lib/.
	    done
	    sal_version=`grep -i version $SAL_DIR/sal_version.tcl | awk '{print $3}'`
	    export SAL_VERSION=$sal_version
	    echo "LSST middleware toolset environment v"$sal_version" libraries have been built."
	)

}
