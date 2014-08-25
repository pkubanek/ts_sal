cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(psm-macros)

find_package (Boost REQUIRED)
find_package (DDSPSMCxx REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${BOOST_INCLUDE_DIRS}
  ${DDS_PSM_Cxx_INCLUDE_DIRS}
)

add_definitions (
 ${DEFINITIONS}
)


set (SOURCES
  writer.cpp RadarTrack.cpp
)

set (EXE writer)

add_executable (${EXE} ${SOURCES})


target_link_libraries (${EXE}
 ${DDS_PSM_Cxx_LIBRARIES}
)

install (TARGETS writer DESTINATION bin)
