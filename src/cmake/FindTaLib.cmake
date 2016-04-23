# - header and library
# - Find talib
# -*- cmake -*-
# Find the native TaLib includes and library
#  TaLib_INCLUDE_DIR - where to find TaLib.h, etc.
#  TaLib_LIBRARY - the talib library
#  TaLib_FOUND       - True if TaLib found.
IF (TaLib_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(TaLib_FIND_QUIETLY TRUE)
ENDIF (TaLib_INCLUDE_DIR)

	# Include dir
FIND_PATH(TaLib_INCLUDE_DIR
	  NAMES ta_defs.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES ta-lib
	)
	# Library
SET(TaLib_NAMES libta_lib.a)
FIND_PATH(TaLib_LIBRARY_DIR
	  NAMES ${TaLib_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (TaLib_LIBRARY_DIR)
	set(TaLib_LIBRARY)
  file (GLOB TaLib_LIBRARY "${TaLib_LIBRARY_DIR}/libta_lib*")
endif(TaLib_LIBRARY_DIR)

	IF (TaLib_INCLUDE_DIR AND TaLib_LIBRARY)
	  SET(TaLib_FOUND TRUE)
	  SET( TaLib_LIBRARIES ${TaLib_LIBRARY} )
	ELSE (TaLib_INCLUDE_DIR AND TaLib_LIBRARY)
	  SET(TaLib_FOUND FALSE)
	  SET( TaLib_LIBRARIES )
	ENDIF (TaLib_INCLUDE_DIR AND TaLib_LIBRARY)


	IF (TaLib_FOUND)
	  IF (NOT TaLib_FIND_QUIETLY)
	    MESSAGE(STATUS "Found TaLib: ${TaLib_LIBRARY_DIR}")
	  ENDIF (NOT TaLib_FIND_QUIETLY)
	ELSE (TaLib_FOUND)
	  IF (TaLib_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for TaLib libraries named ${TaLib_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find TaLib library")
	  ENDIF (TaLib_FIND_REQUIRED)
	ENDIF (TaLib_FOUND)

	MARK_AS_ADVANCED(
	  TaLib_LIBRARY
	  TaLib_INCLUDE_DIR
	  )
