##############################################################################
# Looks for the DDS_PSM_Cxx library installation and defines:
#
#  DDS_PSM_Cxx_FOUND - system has DDS_PSM_Cxx.
#  DDS_PSM_Cxx_INCLUDE_DIRS - the DDS_PSM_Cxx include directory.
#  DDS_PSM_Cxx_LIBRARIES - Link these to use DDS_PSM_Cxx.
#
# You need the environment variable $DDS_PSM_CXX_INSTALL_DIR to be set to your DDS_PSM_Cxx
# installation directory.
##############################################################################

FIND_PATH(DDS_PSM_Cxx_INCLUDE_DIR
	NAMES
		dds/qos.hpp
	PATHS
		$ENV{DDS_PSM_CXX_INSTALL_DIR}/include
)

IF (DDS_PSM_Cxx_INCLUDE_DIR)
	MESSAGE(STATUS "Found DDS_PSM_Cxx include dir: ${DDS_PSM_Cxx_INCLUDE_DIR}")
ELSE (DDS_PSM_Cxx_INCLUDE_DIR)
  MESSAGE(FATAL_ERROR "Could not find DDS_PSM_Cxx include dir")
ENDIF (DDS_PSM_Cxx_INCLUDE_DIR)

SET(DDS_PSM_Cxx_INCLUDE_DIRS 
	${DDS_PSM_Cxx_INCLUDE_DIR} 
)

# Find libraries
FIND_LIBRARY(DDS_PSM_Cxx_LIBRARY
	NAMES
		DDS-PSM-Cxx
	PATHS
		$ENV{DDS_PSM_CXX_INSTALL_DIR}/lib
)

SET(DDS_PSM_Cxx_LIBRARIES
		${DDS_PSM_Cxx_LIBRARY}
)


IF (DDS_PSM_Cxx_INCLUDE_DIRS AND DDS_PSM_Cxx_LIBRARIES)
	SET(DDS_PSM_Cxx_FOUND TRUE)
ENDIF (DDS_PSM_Cxx_INCLUDE_DIRS AND DDS_PSM_Cxx_LIBRARIES)

IF (DDS_PSM_Cxx_FOUND)
	MESSAGE(STATUS "Found DDS_PSM_Cxx C++ libraries: ${DDS_PSM_Cxx_LIBRARIES}")
ELSE (DDS_PSM_Cxx_FOUND)
	IF (DDS_PSM_Cxx_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find DDS_PSM_Cxx")
	ENDIF (DDS_PSM_Cxx_FIND_REQUIRED)
ENDIF (DDS_PSM_Cxx_FOUND)

MARK_AS_ADVANCED(DDS_PSM_Cxx_INCLUDE_DIRS DDS_PSM_Cxx_LIBRARIES)

