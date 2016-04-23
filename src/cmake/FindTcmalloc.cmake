# - header and library
# - Find Tcmalloc
# -*- cmake -*-
# Find the native Tcmalloc includes and library
#  Tcmalloc_INCLUDE_DIR - where to find Tcmalloc.h, etc.
#  Tcmalloc_LIBRARY - the Tcmalloc library
#  Tcmalloc_FOUND       - True if Tcmalloc found.
IF (Tcmalloc_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Tcmalloc_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(Tcmalloc_INCLUDE_DIR
	  NAMES tcmalloc.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES gperftools
	)
#MESSAGE( "Found Tcmalloc include: ${Tcmalloc_INCLUDE_DIR}")

	# Tcmalloc Library
SET(Tcmalloc_NAMES libtcmalloc.a)
FIND_PATH(Tcmalloc_LIBRARY_DIR
	  NAMES ${Tcmalloc_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (Tcmalloc_LIBRARY_DIR)
	set(Tcmalloc_LIBRARY)
  file (GLOB Tcmalloc_LIBRARY "${Tcmalloc_LIBRARY_DIR}/libtcmalloc*")
endif()
#MESSAGE( "Found Tcmalloc library: ${Tcmalloc_LIBRARY}")


	IF (Tcmalloc_INCLUDE_DIR AND Tcmalloc_LIBRARY)
	  SET(Tcmalloc_FOUND TRUE)
	  SET( Tcmalloc_LIBRARIES ${Tcmalloc_LIBRARY} )
#	  MESSAGE( "Found Tcmalloc library")
	ELSE ()
	  SET(Tcmalloc_FOUND FALSE)
	  SET( Tcmalloc_LIBRARIES )
	ENDIF ()

	IF (Tcmalloc_FOUND)
	  IF (NOT Tcmalloc_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Tcmalloc: ${Tcmalloc_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (Tcmalloc_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Tcmalloc libraries named ${Tcmalloc_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Tcmalloc library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Tcmalloc_LIBRARY
	  Tcmalloc_INCLUDE_DIR
	  )
