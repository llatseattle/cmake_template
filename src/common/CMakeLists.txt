# Set the name of the library
SET(LIB_NAME "common")
PROJECT(${LIB_NAME})

# include common settings
INCLUDE("../CMakeLists_INC.txt")

# this common includes should be included by other projects
# useful for private libraries

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

##############################################################################
# Specific includes
##############################################################################

# installed open libraries

# mysql
#include_directories( /usr/include/mysql/ )
# nanomsg
#include_directories( /usr/local/include/nanomsg/ )

# installed a little private libraries

#include_directories(${VENPATH}/talib)
#include_directories(${VENPATH}/cereal)
#include_directories(${VENPATH}/rapidjson)
#include_directories(${VENPATH}/googletest)
#include_directories(${VENPATH}/mlpack/include/mlpack/)

##############################################################################
# Gather headers and source files
##############################################################################
GATHER_LIST_BY_EXTENSION (LIB_HEADERS "*.h*" ${CMAKE_CURRENT_SOURCE_DIR})
GATHER_LIST_BY_EXTENSION (LIB_CPPS "*.c*" ${CMAKE_CURRENT_SOURCE_DIR})

##############################################################################
# Set library put directory
##############################################################################
# set this variable to specify a common place where CMake should put all
# libraries (instead of CMAKE_CURRENT_BINARY_DIR)
# PROJECT_BINARY_DIR: contains the full path to the top level directory of
#		      your build tre

# set to the root of this project
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# set to the build folder of the whole project
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

##############################################################################
# Set execuable put directory
##############################################################################
#set this variable to specify a common place where CMake should put all
# execuable  files (instead of CMAKE_CURRENT_BINARY_DIR)

# set to the root of this project
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# set to the build folder of the whole project
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

##############################################################################
# Generate library
##############################################################################
# 1. static library
# TATIC libraries are archives of object files for use when linking other
# targets

ADD_LIBRARY(${LIB_NAME} STATIC ${LIB_HEADERS} ${LIB_CPPS})

# 2. shared library
# SHARED libraries are linked dynamically and loaded at runtime

#ADD_LIBRARY(LIB_NAME SHARED ${LIB_HEADERS} ${LIB_CPPS})

# 3. module library
# MODULE libraries are plugins that are not linked into other targets but
# may be loaded dynamically at runtime using dlopen-like functionality.

#ADD_LIBRARY(LIB_NAME MODULE ${LIB_HEADERS} ${LIB_CPPS})

# 4. all in one

#ADD_LIBRARY(LIB_NAME STATIC|SHARED ${LIB_HEADERS} ${LIB_CPPS})

##############################################################################
# Install the project
##############################################################################
if(UNIX)
  if( INST_FLAG STREQUAL "TRUE" )
    INSTALL(TARGETS ${LIB_NAME}
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin
      ARCHIVE DESTINATION lib)
    INSTALL(FILES ${LIB_HEADERS} DESTINATION include/${ROOT_PROJ_NAME})
  endif()
endif()

##############################################################################
# Print some messages
##############################################################################
MESSAGE("-- The ${LIB_NAME} library is generated.")
MESSAGE(${LIB_HEADERS} )


