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
	wget -nv ftp://ftp.noao.edu/pub/dmills/opensplice_latest.tgz
	tar xzf opensplice_latest.tgz

	echo "Installing Maven components"
	wget -nv ftp://ftp.noao.edu/pub/dmills/maven-sal-repos.tgz
	tar xzf maven-sal-repos.tgz

#	echo "Installing CentOS dependencies"
#	yum -y install tk tk-devel swig ncurses-libs xterm xorg-x11-fonts-misc java-1.8.0-openjdk-devel boost-python boost-python-devel maven python-devel

	mkdir -p $SAL_WORK_DIR
fi

export OSPL_HOME=$LSST_SDK_INSTALL/OpenSpliceDDS/V6.4.1/HDE/x86_64.linux
export OSPL_GATEWAY=$LSST_SDK_INSTALL/OpenSpliceGateway-1.0.3
export M2=$M2_HOME/bin
export RLM_HOME=$SAL_HOME/.m2/repository/org/opensplice/gateway/rlm/9.1.3
source $OSPL_HOME/release.com

cd $SAL_WORK_DIR

echo "Updating XML"
wget -nv https://github.com/lsst-ts/ts_xml/archive/master.zip -O master.zip
unzip -o master.zip
mv -v ts_xml-master/sal_interfaces/*/*.xml .

echo "Validating interfaces"
for subsys in archiver camera catchuparchiver dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster rotator scheduler tcs
do
   salgenerator $subsys validate
   salgenerator $subsys html
done

echo "Generating C++"
for subsys in archiver camera catchuparchiver dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster rotator scheduler tcs
do
   salgenerator $subsys sal cpp
done

echo "Generating Java"
for subsys in archiver camera catchuparchiver dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster rotator scheduler tcs
do
   salgenerator $subsys sal java
done

echo "Generating Python"
for subsys in archiver camera catchuparchiver dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster rotator scheduler tcs
do
   salgenerator $subsys sal python
done

echo "Generating LabVIEW"
for subsys in archiver camera catchuparchiver dome domeADB domeAPS domeLouvers domeLWS domeMONCS domeTHCS hexapod m1m3 m2ms MTMount ocs processingcluster rotator scheduler tcs
do
   salgenerator $subsys labview
done

salgenerator camera maven


