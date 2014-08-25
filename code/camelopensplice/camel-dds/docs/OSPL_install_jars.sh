#!/bin/sh

if [ -z "${OSPL_HOME}" ]; then ## Succeeds if VAR is unset or empty
    echo "OSPL_HOME environment variable not set"
    exit 1
fi

if [ -z "${M2_HOME}" ]; then ## Succeeds if VAR is unset or empty
    echo "M2_HOME environment variable not set"
    exit 1
fi

if [ -z "${M2}" ]; then ## Succeeds if VAR is unset or empty
    echo "M2 environment variable not set"
    exit 1
fi

# What's the name of the mvn script file on Linux?
if [ ! -e "${M2_HOME}/bin/mvn" ]
then
    echo "ERROR: M2_HOME is set to an invalid directory.":
    echo "M2_HOME =" ${M2_HOME}
    echo "Please set the M2_HOME variable in your environment to match the"
    echo "location of the Maven installation."
    exit 1
fi

echo "Installing Opensplice Jar Files..."
mvn install:install-file -Dfile=${OSPL_HOME}/jar/dcpssaj.jar -DgroupId=org.opensplice.dds -DartifactId=dcpssaj -Dversion=4.1 -Dpackaging=jar
