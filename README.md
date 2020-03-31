# Service Access Layer package

Provides tools to turn ts_xml interface description into C++, Python, Java and
LabView interfaces. Turns XMLs with the interface description into Data
Distribution Service (DDS) messages and language bindings. Binding for the
following primitives are generated:

* **Telemetry** - data flowing from one process to another
* **Commands** - messages to do something in another process
* **Events** - changes in process state, with extra arguments to detail what's
   going on

# Dependencies

* **ts_openslice** for ADLink OpenSliceDDS to generate C++, Python, Java and LabView interfaces
* **ts_idl** for IDL generation, needed for **ts_salobj**

**The following works with ts_opensplice compiled for Centos:7. Please consider
Centos:8 once ts_opensplice is updated.**

On centos:7 docker image, the following shall by run (as root):

```bash
yum -y update
yum -y install git python3 which make java-1.8.0-openjdk-devel
```

# Usage

To get needed github projects and setup environment variables, do:

```bash
git clone https://github.com/lsst-ts/ts_opensplice
git clone https://github.com/lsst-ts/ts_sal
source ts_sal/setup.env
```

You will need then populate ts_sal/test directory with XML schema:

```bash
git clone https://github.com/lsst-ts/ts_xml
cp ts_xml/sal_interfaces/*.xml ts_sal/test
cp ts_xml/sal_interfaces/MTMount/*.xml ts_sal/test
```

## C++

For C++ development, install gcc-c++:

```bash
yum install -y gcc-c++
```

To generate C++ interface for MTMount, do the following:

```bash
cd ts_sal/test
salgenerator MTMount generate cpp
```

## Java

```bash
cd  ts_sal/test
salgenerator MTMount generate python
```

## Python

For Python (please note you are encouraged to use
[ts_salobj](https://github.com/lsstts/ts_salobj)):

```bash
cd  ts_sal/test
salgenerator MTMount generate python
cd MTMount/cpp
make -f Makefile.sacpp_MTMount_types
```


