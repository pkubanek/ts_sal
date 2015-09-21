#!/bin/sh

SAL_DIR=${SAL_HOME}/scripts
PATH=${PATH}:${SAL_DIR}
SAL_WORK_DIR=${LSST_SDK_INSTALL}/test
export PATH
export SAL_DIR
export SAL_WORK_DIR
echo "SAL development environment is configured"

