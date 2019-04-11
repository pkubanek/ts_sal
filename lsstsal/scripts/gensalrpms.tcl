#!/usr/bin/env tclsh

#
#   NOTE ~/.rpmmacros sets the rpmbuild root directory
#
#   On yum server do   createrepo --update /path-to-repo
#   On clients do      yum makecache fast
#
set SAL_WORK_DIR $env(SAL_WORK_DIR)
set OSPL_HOME $env(OSPL_HOME)
set SAL_DIR $env(SAL_DIR)
source $SAL_DIR/sal_version.tcl
source $SAL_DIR/add_system_dictionary.tcl
source $SAL_DIR/gengenericefd_array.tcl
source $SAL_DIR/ospl_version.tcl

set SYSDIC(forEFD) "ATAOS ATArchiver ATBuilding ATCalCS ATCamera ATDome ATDomeTrajectory ATEEC ATHeaderService ATHexapod ATMCS ATMonochromator ATPneumatics ATPtg ATSpectrograph ATTCS ATThermoelectricCooler ATWhiteLight EFD Electrometer"

proc copyasset { asset dest } {
    if { [file exists $asset] } {
       exec cp $asset $dest
    } else {
       puts stdout "ERROR : Asset required for rpm -  $asset does not exist"
#       exit
    }
}


proc updateruntime { subsys } {
global SAL_WORK_DIR SALVERSION SAL_DIR
  exec rm -fr [set subsys]-$SALVERSION/opt/lsst/ts_sal
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/BUILD
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/BUILDROOT
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/RPMS
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SOURCES
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SPECS
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SRPMS
  exec mkdir -p [set subsys]-$SALVERSION/opt/lsst/ts_sal
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/include
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/bin
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/scripts
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/lib
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/doc
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/labview
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/labview/lib
  exec mkdir [set subsys]-$SALVERSION/opt/lsst/ts_sal/jar
  exec mkdir -p [set subsys]-$SALVERSION/opt/lsst/ts_xml/sal_interfaces/[set subsys]
  foreach lib "libsacpp_[set subsys]_types.so SALPY_[set subsys].so libSAL_[set subsys].so" {
     copyasset $SAL_WORK_DIR/lib/$lib [set subsys]-$SALVERSION/opt/lsst/ts_sal/lib/.
  }
  foreach lib "SALLV_[set subsys].so" {
     copyasset $SAL_WORK_DIR/lib/$lib [set subsys]-$SALVERSION/opt/lsst/ts_sal/lib/.
  }
  foreach jar "saj_[set subsys]_types.jar" {
     copyasset $SAL_WORK_DIR/lib/$jar [set subsys]-$SALVERSION/opt/lsst/ts_sal/jar/.
  }
  copyasset $SAL_WORK_DIR/[set subsys]/labview/SALLV_[set subsys]_Monitor [set subsys]-$SALVERSION/opt/lsst/ts_sal/bin/.
  copyasset $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl [set subsys]-$SALVERSION/opt/lsst/ts_sal/scripts/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys].h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]C.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]LV.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/sal_[set subsys]Dcps.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/sal_[set subsys]Dcps_impl.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/sal_[set subsys].h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/ccpp_sal_[set subsys].h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_WORK_DIR/[set subsys]/cpp/sal_[set subsys]SplDcps.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  copyasset $SAL_DIR/code/templates/SAL_defines.h [set subsys]-$SALVERSION/opt/lsst/ts_sal/include/.
  foreach dtype "Commands Events Generics Telemetry" {
    if { [file exists $SAL_WORK_DIR/[set subsys]_[set dtype].xml] } {
       exec cp $SAL_WORK_DIR/[set subsys]_[set dtype].xml [set subsys]-$SALVERSION/opt/lsst/ts_xml/sal_interfaces/[set subsys]/.
    }
  }
  exec tar cvzf $SAL_WORK_DIR/rpmbuild/SOURCES/[set subsys]-$SALVERSION.tgz [set subsys]-$SALVERSION
  exec rm -fr $SAL_WORK_DIR/rpmbuild/BUILD/[set subsys]-$SALVERSION
  exec cp -r [set subsys]-$SALVERSION $SAL_WORK_DIR/rpmbuild/BUILD/.
  listfilesforrpm $subsys
  generaterpm $subsys
  set frpm [open /tmp/makerpm w]
  puts $frpm "#!/bin/sh
export QA_RPATHS=0x001F
rpmbuild -bi -bl -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_[set subsys].spec
rpmbuild -bb -bl -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_[set subsys].spec
"
  close $frpm
  exec chmod 755 /tmp/makerpm
  exec /tmp/makerpm  >& /tmp/makerpm.log
  exec cat /tmp/makerpm.log
}

proc updateddsruntime { version } {
  exec rm -fr /opt/lsst/ts_opensplice
  exec mkdir -p /opt/lsst/ts_opensplice/OpenSpliceDDS
  exec cp -r /data/gitrepo/ts_opensplice/OpenSpliceDDS/[set version] /opt/lsst/ts_opensplice/OpenSpliceDDS/.
}


proc listfilesforrpm { subsys } {
global SALVERSION env RPMFILES SAL_WORK_DIR
   set RPMFILES ""
   cd $SAL_WORK_DIR/rpmbuild/BUILD/[set subsys]-$SALVERSION
   set fl [split [exec find . -type f  -print] \n]
   foreach f $fl { 
       if { [string range $f 0 4] == "./opt" } {
          lappend RPMFILES [string range $f 1 end]
       }
   }
}

proc listfilesEFDrpm { } {
global SALVERSION env RPMFILES SAL_WORK_DIR SYSDIC
   set RPMFILES ""
   cd $SAL_WORK_DIR/rpmbuild/BUILD/ts_EFDruntime-$SALVERSION
   set fl [split [exec find . -type f  -print] \n]
   foreach f $fl { 
       if { [string range $f 0 4] == "./opt" } {
          lappend RPMFILES [string range $f 1 end]
       }
   }
   foreach subsys $SYSDIC(forEFD) {
     lappend RPMFILES "/etc/systemd/system/[set subsys]_command_efdwriter.service"
     lappend RPMFILES "/etc/systemd/system/[set subsys]_event_efdwriter.service"
     lappend RPMFILES "/etc/systemd/system/[set subsys]_telemetry_efdwriter.service"
   }
}

proc generateEFDrpm { } {
global SAL_WORK_DIR SALVERSION SAL_DIR SYSDIC
  exec rm -fr ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/*
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/BUILD
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/BUILDROOT
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/RPMS
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SOURCES
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SPECS
  exec mkdir -p $SAL_WORK_DIR/rpmbuild/SRPMS
  exec mkdir -p ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal
  exec mkdir -p ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/sql
  exec mkdir -p ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/bin
  exec mkdir -p ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/scripts
  exec mkdir -p ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/lib
  exec mkdir -p ts_EFDruntime-$SALVERSION/etc/systemd/system
  foreach subsys $SYSDIC(forEFD) {
     catch {genefdwriters $subsys}
     cd $SAL_WORK_DIR
     genefdsetup $subsys
     foreach type "command event telemetry" { 
        copyasset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_[set type]_efdwriter ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/bin/.
     }
     copyasset $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/scripts/.
     copyasset $SAL_WORK_DIR/lib/libsacpp_[set subsys]_types.so ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/lib/.
     copyasset $SAL_WORK_DIR/lib/libSAL_[set subsys].so ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/lib/.
     set fsql [open /tmp/dosql w]
     puts $fsql "cat $SAL_WORK_DIR/sql/[set subsys]_*.sqldef > ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/sql/[set subsys].sqldef"
     puts $fsql "cat $SAL_WORK_DIR/sql/[set subsys]_*.sqlwrt > ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/sql/[set subsys].sqlwrt"
     puts $fsql "cat $SAL_WORK_DIR/sql/[set subsys]_*.sql > ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/sql/[set subsys].sql"
     close $fsql
     exec chmod 755 /tmp/dosql
     exec /tmp/dosql
  }
  copyasset $SAL_WORK_DIR/EFD/cpp/src/sacpp_EFD_largeFileObjectAvailable_send ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/bin/.
  copyasset $SAL_WORK_DIR/EFD/cpp/src/sacpp_EFD_largeFileObjectAvailable_log ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/bin/.
  copyasset $SAL_DIR/migrateEFDtable.tcl ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/scripts/.
  copyasset $SAL_DIR/process_LFO_logevent ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/bin/.
  generateEFDenv
  exec tar cvzf $SAL_WORK_DIR/rpmbuild/SOURCES/ts_EFDruntime-$SALVERSION.tgz ts_EFDruntime-$SALVERSION
  exec rm -fr $SAL_WORK_DIR/rpmbuild/BUILD/ts_EFDruntime-$SALVERSION/*
  exec cp -r ts_EFDruntime-$SALVERSION $SAL_WORK_DIR/rpmbuild/BUILD/.
  listfilesEFDrpm
  generateEFDspec
  set frpm [open /tmp/makerpm w]
  puts $frpm "#!/bin/sh
export QA_RPATHS=0x001F
rpmbuild -bi -bl -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_EFDruntime.spec
rpmbuild -bb -bl -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_EFDruntime.spec
"
  close $frpm
  exec chmod 755 /tmp/makerpm
  exec /tmp/makerpm  >& /tmp/makerpm.log
  exec cat /tmp/makerpm.log
}

proc generateEFDenv { } {
global OSPL_VERSION SALVERSION
   set fenv [open ts_EFDruntime-$SALVERSION/opt/lsst/ts_sal/setupEFD.env w]
   puts $fenv "
export LSST_SDK_INSTALL=/opt/lsst/ts_sal
export OSPL_HOME=/opt/OpenSpliceDDS/V[set OSPL_VERSION]/HDE/x86_64.linux
export LSST_DDS_DOMAIN=auxtelpath
export SAL_HOME=\$LSST_SDK_INSTALL/lsstsal
export LD_LIBRARY_PATH=\$\{SAL_WORK_DIR\}/lib:\$\{SAL_HOME\}/lib
export PATH=\$\{SAL_HOME\}/bin:\$\{PATH\}
source \$OSPL_HOME/release.com
export SAL_VERSION=$SALVERSION
echo \"LSST middleware EFD environment v$SALVERSION is configured\"
"
   close $fenv
}


proc genefdsetup { subsys } {
global SALVERSION
   foreach wtype "command event telemetry" {
     set fout [open ts_EFDruntime-$SALVERSION/etc/systemd/system/[set subsys]_[set wtype]_efdwriter.service w]
     puts $fout "
\[Unit\]
Description=EFD $subsys $wtype writer
Wants=network-online.target
After=network-online.target

\[Service\]
Type=simple
WorkingDirectory=/opt/lsst/ts_sal/bin
ExecStart=/bin/bash -c 'source /opt/lsst/ts_sal/setup.env && ./sacpp_[set subsys]_[set wtype]_efdwriter'
Restart=on-failure
User=salmgr

\[Install\]
WantedBy=multi-user.target
"
     close $fout
  }
}


proc generatemetarpm { } {
global SYSDIC SALVERSION SAL_WORK_DIR OSPL_VERSION
   set fout [open $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_runtime.spec w]
   puts $fout "

%define name			ts_sal_runtime
%define summary			SAL runtime meta package
%define version			$SALVERSION
%define release			1
%define license			GPL
%define group			LSST Telescope and Site
%define vendor			LSST
%define packager		dmills@lsst.rog

Name:      %{name}
Version:   %{version}
Release:   %{release}
Packager:  %{packager}
Vendor:    %{vendor}
License:   %{license}
Summary:   %{summary}
Group:     %{group}
AutoReqProv: no
#Source:    %{source}
URL:       %{url}
Prefix:    %{_prefix}
Buildroot: %{buildroot}
Requires: OpenSpliceDDS = $OSPL_VERSION
"
   foreach subsys $SYSDIC(systems) {
      puts $fout "Requires: $subsys = $SALVERSION"
   }
   puts $fout "
%description
This metapackage is used to install all the SAL runtime packages at once

%setup -c -T

%install

%files
"
   close $fout
  set frpm [open /tmp/makerpm w]
  puts $frpm "#!/bin/sh
rpmbuild -ba -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_runtime.spec
"
  close $frpm
  exec chmod 755 /tmp/makerpm
  exec /tmp/makerpm  >& /tmp/makerpm.log
  exec cat /tmp/makerpm.log
}

proc generateATmetarpm { } {
global SYSDIC SALVERSION SAL_WORK_DIR
   set fout [open $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_ATruntime.spec w]
   puts $fout "

%define name			ts_sal_ATruntime
%define summary			SAL Aux Telescope runtime meta package
%define version			$SALVERSION
%define release			1
%define license			GPL
%define group			LSST Telescope and Site
%define vendor			LSST
%define packager		dmills@lsst.rog

Name:      %{name}
Version:   %{version}
Release:   %{release}
Packager:  %{packager}
Vendor:    %{vendor}
License:   %{license}
Summary:   %{summary}
Group:     %{group}
AutoReqProv: no
#Source:    %{source}
URL:       %{url}
Prefix:    %{_prefix}
Buildroot: %{buildroot}
Requires: OpenSpliceDDS = $OSPL_VERSION
"
   foreach subsys $SYSDIC(systems) {
      if { [string range $subsys 0 1] == "AT" } {
        puts $fout "Requires: $subsys = $SALVERSION"
      }
   }
   puts $fout "
%description
This metapackage is used to install all the SAL Aux telescope related runtime packages at once

%setup -c -T

%install

%files
"
   close $fout
  set frpm [open /tmp/makerpm w]
  puts $frpm "#!/bin/sh
rpmbuild -ba -v $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_ATruntime.spec
"
  close $frpm
  exec chmod 755 /tmp/makerpm
  exec /tmp/makerpm  >& /tmp/makerpm.log
  exec cat /tmp/makerpm.log
}

proc generaterpm { subsys } {
global SAL_WORK_DIR SALVERSION RPMFILES OSPL_VERSION
  exec rm -fr $SAL_WORK_DIR/rpm_[set subsys]
  exec mkdir -p $SAL_WORK_DIR/rpm_[set subsys]
  set fout [open $SAL_WORK_DIR/rpmbuild/SPECS/ts_sal_[set subsys].spec w]
  puts $fout "Name: $subsys
Version: $SALVERSION
Release: 1%\{?dist\}
Summary: SAL runtime for $subsys Subsystem
Vendor: LSST
License: GPL
URL: http://project.lsst.org/ts
Group: Telescope and Site SAL
AutoReqProv: no
Source0: [set subsys]-$SALVERSION.tgz
BuildRoot: $SAL_WORK_DIR/rpmbuild/%\{name\}-%\{version\}
Packager: dmills@lsst.org
Requires: OpenSpliceDDS = $OSPL_VERSION

%description
This is a SAL runtime and build environment for the LSST $subsys subsystem.
It provides shared libraries , jar files , include files and documentation
for the middleware interface.

%prep

%setup
 
%build
#source /opt/lsst/ts_sal/setup.env
#cp /opt/lsst/ts_xml/sal_interfaces/*.xml .
#cp /opt/lsst/ts_xml/sal_interfaces/[set subsys]/*.xml .
#salgenerator [set subsys] validate
#salgenerator [set subsys] html
#salgenerator [set subsys] sal cpp
#salgenerator [set subsys] sal python
#salgenerator [set subsys] sal java
#salgenerator [set subsys] labview
#salgenerator [set subsys] lib

%install
cp -fr * %{buildroot}/.

%files"
  foreach f $RPMFILES {
     puts $fout $f
  }
  puts $fout "

%clean
rm -fr \$RPM_BUILD_ROOT

%post
%postun
%changelog
"
  close $fout
  cd $SAL_WORK_DIR
#  set fxml [glob [set subsys]_*.xml]
#  set ctar "exec tar czf $SAL_WORK_DIR/rpmbuild/SOURCES/[set subsys]-$SALVERSION.tgz [set fxml] SALSubsystems.xml SALGenerics.xml"
#  eval $ctar
}

proc generateEFDspec { } {
global SAL_WORK_DIR SALVERSION RPMFILES OSPL_VERSION
  set fout [open $SAL_WORK_DIR/rpmbuild/SPECS/ts_EFDruntime.spec w]
  puts $fout "Name: ts_EFDruntime
Version: [set SALVERSION]
Release: 641%\{?dist\}
Summary: SAL runtime for EFD runtime Subsystem
Vendor: LSST
License: GPL
URL: http://project.lsst.org/ts
Group: Telescope and Site SAL
AutoReqProv: no
Source0: ts_EFDruntime-[set SALVERSION].tgz
BuildRoot: $SAL_WORK_DIR/rpmbuild/%\{name\}-%\{version\}
Packager: dmills@lsst.org
Requires: OpenSpliceDDS = $OSPL_VERSION


%description
This is a EFD runtime and environment for the LSST Telescope and Site subsystems.
It provides table definitions and database writers for all supported subsystems.

%prep

%setup
 
%build
#source /opt/lsst/ts_sal/setup.env

%install
cp -fr * %{buildroot}/.

%files"
  foreach f $RPMFILES {
     puts $fout $f
  }
  puts $fout "
%clean

%post
%postun
%changelog
"
  close $fout
}


proc generaterddsrpm { version } {
global SAL_WORK_DIR SALVERSION OSPL_HOME
  exec rm -fr $SAL_WORK_DIR/rpm_opensplice
  exec mkdir -p $SAL_WORK_DIR/rpm_opensplice
  set version [string trim [lindex [split [exec grep "PACKAGE_VERSION=" $OSPL_HOME/etc/RELEASEINFO] =] 1] "VS"]
  set fout [open $SAL_WORK_DIR/rpmbuild/BUILD/ts_opensplice.spec w]
  puts $fout "Name: ts_opensplice
Version: $version
Release: 1%\{?dist\}
Summary: DDS runtime for OpenSplice
Vendor: LSST
License: GPL
URL: http://project.lsst.org/ts
Group: Telescope and Site SAL
Source: opensplice_[set version].tgz
BuildRoot: $SAL_WORK_DIR/rpmbuild/%\{name\}-%\{version\}
Packager: dmills@lsst.org

%description
This is a OpenSplice DDS runtime and build environment for the LSST subsystems.
It provides shared libraries , jar files , include files and documentation
for the DDS interface.

%prep

%install
rm -fr $RPM_BUILD_ROOT
mkdir -p /opt/lsst/ts_opensplice
cp -fR * /opt/lsst/ts_opensplice

%files
/opt/lsst/ts_opensplice

%clean
rm -fr $RPM_BUILD_ROOT

%post
%postun
%changelog
"

}


