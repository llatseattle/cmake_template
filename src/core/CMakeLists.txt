# Set the name of the project

SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

SET(PROJ_NAME "core")
PROJECT(${PROJ_NAME})

# include common settings
INCLUDE("../CMakeLists_INC.txt")

# this common includes should be included by other projects
# useful for private libraries, or headers of internal projects

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

include_directories(${SRCPATH}/algorithm)
#include_directories(${VENPATH}/cereal)
#include_directories(${VENPATH}/rapidjson)
#include_directories(${VENPATH}/googletest)
#include_directories(${VENPATH}/mlpack/include/mlpack/)

##############################################################################
# Gather headers and source files
##############################################################################
GATHER_LIST_BY_EXTENSION (PROJ_HEADERS "*.h**" ${CMAKE_CURRENT_SOURCE_DIR})
GATHER_LIST_BY_EXTENSION (PROJ_CPPS "*.c*" ${CMAKE_CURRENT_SOURCE_DIR})

##############################################################################
# Set library put directory
##############################################################################
# set this variable to specify a common place where CMake should put all
# libraries (instead of CMAKE_CURRENT_BINARY_DIR)
# PROJECT_BINARY_DIR: contains the full path to the top level directory of
#		      your build tre

# PROJECT_BINARY_DIR contains full path to the top level directory of build tree
# set to the root of this project
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# set to the build folder of the whole project
#SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

##############################################################################
# Set execuable put directory
##############################################################################
#set this variable to specify a common place where CMake should put all
# execuable  files (instead of CMAKE_CURRENT_BINARY_DIR)

# set to the root of this project
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# set to the build folder of the whole project
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

##############################################################################
# Generate executable
# Set properties
# Link required libraries
# For debug and realse mode // to be added
##############################################################################
ADD_EXECUTABLE(${PROJ_NAME} ${PROJ_HEADERS} ${PROJ_CPPS})
SET_TARGET_PROPERTIES(${PROJ_NAME} PROPERTIES OUTPUT_NAME ${PROJ_NAME})

# Link project libraries
TARGET_LINK_LIBRARIES(${PROJ_NAME} ${common})
# Link package libraries
TARGET_LINK_LIBRARIES(${PROJ_NAME} ${boost_system})
TARGET_LINK_LIBRARIES(${PROJ_NAME} ${boost_date_time})

##############################################################################
# Install the project
##############################################################################
if(UNIX)
  if( INST_FLAG STREQUAL "TRUE" )
    INSTALL(TARGETS ${PROJ_NAME}
      LIBRARY DESTINATION lib
      RUNTIME DESTINATION bin
      ARCHIVE DESTINATION lib)
    INSTALL(FILES ${PROJ_HEADERS} DESTINATION include/${ROOT_PROJ_NAME})
  endif()
endif()

##############################################################################
# Print some messages
##############################################################################
MESSAGE("-- The ${PROJ_NAME} project is generated.")


