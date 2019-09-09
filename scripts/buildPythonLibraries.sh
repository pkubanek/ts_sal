#!/bin/bash

# Utility script that will copy files over from your xml directory, then call
# the salgenerator commands to build your SAL libraries. 
# optioanlly add  list or args to run after the Topic name e..g MTmount java lib 
# validate and htmlo will be run any way -- defaul is python c++ lib as it was before this change.
# Option -nc in FIRST position to not clean all the files from test
 
if [ -z ${XML_WORK_DIR}x ]; then
    XML_WORK_DIR="/gitdir/ts_xml" #Update to be the path to your xml repo.
fi

ALWAYS="validate html"
CMDS="$ALWAYS python  cpp lib"  #adding sal taken care of below
set -e
if [ -z "$1" ]
  then
    echo "Must run with subsystem name (e.g. $ buildPythonTopics Test)"
    exit 1
fi
CLEAN=1
if [ "$1" = "-nc" ]; then
	CLEAN=0
	shift
fi
T=$1

if [ $# -gt 1 ] # Take remainng argumets as which generator phases to run after validate html 
  then
    shift
    CMDS="$ALWAYS $*"
fi

echo "Running with CLEAN=$CLEAN TOPIC=$T and  $CMDS"
printf "\nEntering build directory, copying over xml files\n"
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -

cd ${SAL_WORK_DIR}
cp ${XML_WORK_DIR}/sal_interfaces/SALSubsystems.xml .
cp ${XML_WORK_DIR}/sal_interfaces/SALGenerics.xml .

for ft in "Telemetry" "Commands" "Events" ; do 
	fname="${XML_WORK_DIR}/sal_interfaces/${T}/${T}_$ft.xml"
	if [ -s $fname ]
	then
		cp $fname .
	else 
		echo "NOT FOUND  ${fname} "
	exit 3
	fi
done

printf "\nAll output redirected. Do tail -f ${SAL_WORK_DIR}/../scripts/salgenerator.out to follow output\n"
printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -

for c in   $CMDS  ; do  
	sal="sal"
        if [ -z "${ALWAYS##*$c*}" ]; then
	  sal="";
	fi
	printf "\nExecuting salgenerator $T $sal $c\n"
	printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -

	salgenerator $T $sal $c &>> ${SAL_WORK_DIR}/../scripts/salgenerator.out
	check=$?  #It seems salgernator does not provide an exit code other than 0
	if [ "$check" -eq 0 ]; then
	   echo "Generation ok"
	else
	   echo "******* SAL GENERATION FAILED************"
	   exit 2 
	fi
done


if [ $CLEAN -eq 1 ] ; then 
	printf "\nCleaning directory, leaving $T folder\n"
	printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
	rm ${SAL_WORK_DIR}/SALGenerics.xml
	rm ${SAL_WORK_DIR}/SALSubsystems.xml
	rm -rf ${SAL_WORK_DIR}/$T_*
	rm -rf ${SAL_WORK_DIR}/html
	rm -rf ${SAL_WORK_DIR}/idl-templates
	rm -rf ${SAL_WORK_DIR}/sql
	rm -rf ${SAL_WORK_DIR}/include
fi

printf "\nDone building libraries for $T from %s\n\n" "$SAL_WORK_DIR"
