# - header and library
# - Find YamlCpp
# -*- cmake -*-
# Find the native YamlCpp includes and library
#  YamlCpp_INCLUDE_DIR - where to find YamlCpp.h, etc.
#  YamlCpp_LIBRARY - the YamlCpp library
#  YamlCpp_FOUND       - True if YamlCpp found.
IF (YamlCpp_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(YamlCpp_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(YamlCpp_INCLUDE_DIR
	  NAMES yaml.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES yaml-cpp
	)
#MESSAGE( "Found YamlCpp include: ${YamlCpp_INCLUDE_DIR}")

	# YamlCpp Library
SET(YamlCpp_NAMES libyaml-cpp.a)
FIND_PATH(YamlCpp_LIBRARY_DIR
	  NAMES ${YamlCpp_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (YamlCpp_LIBRARY_DIR)
	set(YamlCpp_LIBRARY)
  file (GLOB YamlCpp_LIBRARY "${YamlCpp_LIBRARY_DIR}/libyaml-cpp*")
endif()
#MESSAGE( "Found YamlCpp library: ${YamlCpp_LIBRARY}")


	IF (YamlCpp_INCLUDE_DIR AND YamlCpp_LIBRARY)
	  SET(YamlCpp_FOUND TRUE)
	  SET( YamlCpp_LIBRARIES ${YamlCpp_LIBRARY} )
#	  MESSAGE( "Found YamlCpp library")
	ELSE ()
	  SET(YamlCpp_FOUND FALSE)
	  SET( YamlCpp_LIBRARIES )
	ENDIF ()

	IF (YamlCpp_FOUND)
	  IF (NOT YamlCpp_FIND_QUIETLY)
	    MESSAGE(STATUS "Found YamlCpp: ${YamlCpp_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (YamlCpp_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for YamlCpp libraries named ${YamlCpp_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find YamlCpp library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  YamlCpp_LIBRARY
	  YamlCpp_INCLUDE_DIR
	  )
