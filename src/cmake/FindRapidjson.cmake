# - header only library
# - Find Rapidjson
# -*- cmake -*-
# Find the native Rapidjson includes
#  Rapidjson_INCLUDE_DIR - where to find Rapidjson.h, etc.
#  Rapidjson_FOUND       - True if Rapidjson found.
IF (Rapidjson_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Rapidjson_FIND_QUIETLY TRUE)
ENDIF ()

# Include dir
# since for these libraries, they are synced with github, and build by myself
# mostly, there is one more layer of folder due to gitrepo in the path_surfixes
FIND_PATH(Rapidjson_INCLUDE_DIR
	  NAMES rapidjson.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/ ~/Documents/Library
	  PATH_SUFFIXES rapidjson
	)

#MESSAGE(STATUS "Found Rapidjson: ${Rapidjson_INCLUDE_DIR}")

	IF (Rapidjson_INCLUDE_DIR)
	  SET(Rapidjson_FOUND TRUE)
	ELSE ()
	  SET(Rapidjson_FOUND FALSE)
	  SET( Rapidjson_LIBRARIES )
	ENDIF ()


	IF (Rapidjson_FOUND)
	  IF (NOT Rapidjson_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Rapidjson: ${Rapidjson_INCLUDE_DIR}")
	  ENDIF (NOT Rapidjson_FIND_QUIETLY)
	ELSE ()
	  IF (Rapidjson_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Rapidjson libraries named ${Rapidjson_INCLUDE_DIR}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Rapidjson library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Rapidjson_INCLUDE_DIR
	  )
