# - header and library
# - Find Mlpack
# -*- cmake -*-
# Find the native Mlpack includes and library
#  Mlpack_INCLUDE_DIR - where to find Mlpack.h, etc.
#  Mlpack_LIBRARY - the Mlpack library
#  Mlpack_FOUND       - True if Mlpack found.
IF (Mlpack_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Mlpack_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(Mlpack_INCLUDE_DIR
	  NAMES core.hpp
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES mlpack
	)
#MESSAGE( "Found Mlpack include: ${Mlpack_INCLUDE_DIR}")

	# Mlpack Library
SET(Mlpack_NAMES mlpack_cf)
FIND_PATH(Mlpack_LIBRARY_DIR
	  NAMES ${Mlpack_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (Mlpack_LIBRARY_DIR)
	set(Mlpack_LIBRARY)
  file (GLOB Mlpack_LIBRARY "${Mlpack_LIBRARY_DIR}/mlpack*")
endif()
#MESSAGE( "Found Mlpack library: ${Mlpack_LIBRARY}")


	IF (Mlpack_INCLUDE_DIR AND Mlpack_LIBRARY)
	  SET(Mlpack_FOUND TRUE)
	  SET( Mlpack_LIBRARIES ${Mlpack_LIBRARY} )
#	  MESSAGE( "Found Mlpack library")
	ELSE ()
	  SET(Mlpack_FOUND FALSE)
	  SET( Mlpack_LIBRARIES )
	ENDIF ()

	IF (Mlpack_FOUND)
	  IF (NOT Mlpack_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Mlpack: ${Mlpack_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (Mlpack_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Mlpack libraries named ${Mlpack_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Mlpack library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Mlpack_LIBRARY
	  Mlpack_INCLUDE_DIR
	  )
