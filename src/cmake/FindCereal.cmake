# - header only library
# - Find Cereal
# -*- cmake -*-
# Find the native Cereal includes
#  Cereal_INCLUDE_DIR - where to find Cereal.h, etc.
#  Cereal_FOUND       - True if Cereal found.
IF (Cereal_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Cereal_FIND_QUIETLY TRUE)
ENDIF (Cereal_INCLUDE_DIR)

# Include dir
# since for these libraries, they are synced with github, and build by myself
# mostly, there is one more layer of folder due to gitrepo in the path_surfixes
FIND_PATH(Cereal_INCLUDE_DIR
	  NAMES cereal.hpp
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/ ~/Documents/Library
	  PATH_SUFFIXES cereal/include/cereal
	)

#MESSAGE(STATUS "Found Cereal: ${Cereal_INCLUDE_DIR}")

	IF (Cereal_INCLUDE_DIR)
	  SET(Cereal_FOUND TRUE)
	ELSE (Cereal_INCLUDE_DIR)
	  SET(Cereal_FOUND FALSE)
	  SET( Cereal_LIBRARIES )
	ENDIF (Cereal_INCLUDE_DIR)


	IF (Cereal_FOUND)
	  IF (NOT Cereal_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Cereal: ${Cereal_INCLUDE_DIR}")
	  ENDIF (NOT Cereal_FIND_QUIETLY)
	ELSE (Cereal_FOUND)
	  IF (Cereal_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Cereal libraries named ${Cereal_INCLUDE_DIR}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Cereal library")
	  ENDIF (Cereal_FIND_REQUIRED)
	ENDIF (Cereal_FOUND)

	MARK_AS_ADVANCED(
	  Cereal_INCLUDE_DIR
	  )
