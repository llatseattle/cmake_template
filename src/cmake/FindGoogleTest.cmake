# - header and library
# - Find GTest and Gmock
# -*- cmake -*-
# Find the native GTest includes and library
#  GTest_INCLUDE_DIR - where to find GTest.h, etc.
#  GTest_LIBRARY - the GTest library
#  GTest_FOUND       - True if GTest found.
IF (GTest_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(GTest_FIND_QUIETLY TRUE)
ENDIF ()

IF (GMock_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(GMock_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(GTest_INCLUDE_DIR
	  NAMES gtest.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES gtest
	)
#MESSAGE( "Found GTest include: ${GTest_INCLUDE_DIR}")
	# gmock Include dir
FIND_PATH(GMock_INCLUDE_DIR
	  NAMES gmock.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  PATH_SUFFIXES gmock
	)
#MESSAGE( "Found GMock include: ${GMock_INCLUDE_DIR}")
	# gtest Library
SET(GTest_NAMES libgtest.a)
FIND_PATH(GTest_LIBRARY_DIR
	  NAMES ${GTest_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (GTest_LIBRARY_DIR)
	set(GTest_LIBRARY)
  file (GLOB GTest_LIBRARY "${GTest_LIBRARY_DIR}/libgtest*")
endif()
#MESSAGE( "Found GTest library: ${GTest_LIBRARY}")

#gmock library
SET(GMock_NAMES libgmock.a)
FIND_PATH(GMock_LIBRARY_DIR
	  NAMES ${GTest_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	)
if (GMock_LIBRARY_DIR)
	set(GMock_LIBRARY)
  file (GLOB GMock_LIBRARY "${GMock_LIBRARY_DIR}/libgmock*")
endif()
#MESSAGE( "Found GMock library: ${GMock_LIBRARY}")


	IF (GTest_INCLUDE_DIR AND GTest_LIBRARY)
	  SET(GTest_FOUND TRUE)
	  SET( GTest_LIBRARIES ${GTest_LIBRARY} )
#	  MESSAGE( "Found GTest library")
	ELSE ()
	  SET(GTest_FOUND FALSE)
	  SET( GTest_LIBRARIES )
	ENDIF ()

	IF (GMock_INCLUDE_DIR AND GMock_LIBRARY)
	  SET(GMock_FOUND TRUE)
	  SET( GMock_LIBRARIES ${GMock_LIBRARY} )
#	  MESSAGE( "Found GMock library")
	ELSE ()
	  SET(GMock_FOUND FALSE)
	  SET( GMock_LIBRARIES )
	ENDIF ()

	IF (GTest_FOUND)
	  IF (NOT GTest_FIND_QUIETLY)
	    MESSAGE(STATUS "Found GTest: ${GTest_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (GTest_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for GTest libraries named ${GTest_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find GTest library")
	  ENDIF ()
	ENDIF ()

	IF (GMock_FOUND)
	  IF (NOT GMock_FIND_QUIETLY)
	    MESSAGE(STATUS "Found GMock: ${GMock_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (GMock_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for GMock libraries named ${GMock_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find GMock library")
	  ENDIF ()
	ENDIF ()


	MARK_AS_ADVANCED(
	  GTest_LIBRARY
	  GTest_INCLUDE_DIR
	  )

	MARK_AS_ADVANCED(
	  GMock_LIBRARY
	  GMock_INCLUDE_DIR
	  )
