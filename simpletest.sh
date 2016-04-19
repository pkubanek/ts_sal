#!/bin/sh

export LSST_SDK_INSTALL=$HOME/workspace/ts_sal
export SAL_HOME=$LSST_SDK_INSTALL/lsstsal
export SAL_WORK_DIR=$LSST_SDK_INSTALL/test
export SAL_CPPFLAGS=-m64
source $SAL_HOME/salenv.sh
export JAVA_HOME=/etc/alternatives/java_sdk_openjdk
export LD_LIBRARY_PATH=${SAL_HOME}/lib
export TCL_LIBRARY=${SAL_HOME}/lib/tcl8.5
export TK_LIBRARY=${SAL_HOME}/lib/tk8.5
export LD_PRELOAD=/etc/alternatives/java_sdk_openjdk/jre/lib/amd64/libjsig.so
export PATH=$JAVA_HOME/bin:${M2}:${SAL_HOME}/bin:${PATH}
export PYTHONPATH=$PYTHONPATH:${SAL_WORK_DIR}/lib
mkdir -p $LSST_SDK_INSTALL/lsstsal/lib
echo "LSST testing middleware toolset environment is configured"

if [ "$1" = "CI" ]; then
	echo "Configuring Continuous Integration host"

	echo "Installing OpenSplice"
	wget ftp://ftp.noao.edu/pub/dmills/opensplice_latest.tgz
	tar xzf opensplice_latest.tgz

	echo "Installing Maven components"
	wget ftp://ftp.noao.edu/pub/dmills/maven-sal-repos.tgz
	tar xzf maven-sal-repos.tgz

#	echo "Installing CentOS dependencies"
#	yum -y install tk tk-devel swig ncurses-libs xterm xorg-x11-fonts-misc java-1.8.0-openjdk-devel boost-python boost-python-devel maven python-devel

	mkdir -p $SAL_WORK_DIR
fi

