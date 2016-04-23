# - header and library
# - Find Nanomsg
# -*- cmake -*-
# Find the native Nanomsg includes and library
#  Nanomsg_INCLUDE_DIR - where to find Nanomsg.h, etc.
#  Nanomsg_LIBRARY - the Nanomsg library
#  Nanomsg_FOUND       - True if Nanomsg found.
IF (Nanomsg_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Nanomsg_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(Nanomsg_INCLUDE_DIR
	  NAMES pubsub.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES nanomsg
	)
#MESSAGE( "Found Nanomsg include: ${Nanomsg_INCLUDE_DIR}")

	# Nanomsg Library
SET(Nanomsg_NAMES libnanomsg.a)
FIND_PATH(Nanomsg_LIBRARY_DIR
	  NAMES ${Nanomsg_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (Nanomsg_LIBRARY_DIR)
	set(Nanomsg_LIBRARY)
  file (GLOB Nanomsg_LIBRARY "${Nanomsg_LIBRARY_DIR}/libnanomsg*")
endif()
#MESSAGE( "Found Nanomsg library: ${Nanomsg_LIBRARY}")


	IF (Nanomsg_INCLUDE_DIR AND Nanomsg_LIBRARY)
	  SET(Nanomsg_FOUND TRUE)
	  SET( Nanomsg_LIBRARIES ${Nanomsg_LIBRARY} )
#	  MESSAGE( "Found Nanomsg library")
	ELSE ()
	  SET(Nanomsg_FOUND FALSE)
	  SET( Nanomsg_LIBRARIES )
	ENDIF ()

	IF (Nanomsg_FOUND)
	  IF (NOT Nanomsg_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Nanomsg: ${Nanomsg_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (Nanomsg_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Nanomsg libraries named ${Nanomsg_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Nanomsg library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Nanomsg_LIBRARY
	  Nanomsg_INCLUDE_DIR
	  )
