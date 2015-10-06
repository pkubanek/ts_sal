#!/usr/bin/tclsh

#
#  To convert legacy IDL Telemetry definitions to XML
#

source $env(SAL_DIR)/checkidl.tcl
source $env(SAL_DIR)/SALTopicTemplateXML.tcl
source $env(SAL_DIR)/versioning.tcl

set idl [glob [set argv]*.idl]
checkidl $idl
writeXMLsubsys ./xml $argv

