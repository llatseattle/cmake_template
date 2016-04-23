# cmake requirement
cmake_minimum_required (VERSION 3.0)
# Project name
set(ROOT_PROJ_NAME "bitcoinEngine")
project (${ROOT_PROJ_NAME})
message("-- The root directory of project: ${CMAKE_BINARY_DIR}")
# add common cmake setting and libraries
set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR})

# set install information
# TRUE: install
# other: do not install
set(INST_FLAG "TRUE")
set(INSTALL_RPATH /usr/local/ )

include("${SRCPATH}/CMakeLists_INC.txt")

# add subdirectory and subprojects

# common includes and headers
add_subdirectory(${SRCPATH}/common)
# core project
add_subdirectory(${SRCPATH}/core)
# sub project
add_subdirectory(${SRCPATH}/algorithm)

