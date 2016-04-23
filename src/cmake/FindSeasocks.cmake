# - header and library
# - Find Seasocks
# -*- cmake -*-
# Find the native Seasocks includes and library
#  Seasocks_INCLUDE_DIR - where to find Seasocks.h, etc.
#  Seasocks_LIBRARY - the Seasocks library
#  Seasocks_FOUND       - True if Seasocks found.
IF (Seasocks_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Seasocks_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(Seasocks_INCLUDE_DIR
	  NAMES ResponseCodeDefs.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES seasocks
	)
#MESSAGE( "Found Seasocks include: ${Seasocks_INCLUDE_DIR}")

	# Seasocks Library
SET(Seasocks_NAMES libseasocks.a)
FIND_PATH(Seasocks_LIBRARY_DIR
	  NAMES ${Seasocks_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (Seasocks_LIBRARY_DIR)
	set(Seasocks_LIBRARY)
  file (GLOB Seasocks_LIBRARY "${Seasocks_LIBRARY_DIR}/libseasocks*")
endif()
#MESSAGE( "Found Seasocks library: ${Seasocks_LIBRARY}")


	IF (Seasocks_INCLUDE_DIR AND Seasocks_LIBRARY)
	  SET(Seasocks_FOUND TRUE)
	  SET( Seasocks_LIBRARIES ${Seasocks_LIBRARY} )
#	  MESSAGE( "Found Seasocks library")
	ELSE ()
	  SET(Seasocks_FOUND FALSE)
	  SET( Seasocks_LIBRARIES )
	ENDIF ()

	IF (Seasocks_FOUND)
	  IF (NOT Seasocks_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Seasocks: ${Seasocks_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (Seasocks_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Seasocks libraries named ${Seasocks_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Seasocks library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Seasocks_LIBRARY
	  Seasocks_INCLUDE_DIR
	  )
