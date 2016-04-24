# - header and library
# - Find Rcpp
# -*- cmake -*-
# Find the native Rcpp includes and library
#  Rcpp_INCLUDE_DIR - where to find Rcpp.h, etc.
#  Rcpp_LIBRARY - the Rcpp library
#  Rcpp_FOUND       - True if Rcpp found.
IF (Rcpp_INCLUDE_DIR)
	  # Already in cache, be silent
  SET(Rcpp_FIND_QUIETLY TRUE)
ENDIF ()

	# gteset Include dir
FIND_PATH(Rcpp_INCLUDE_DIR
	  NAMES Rcpp.h
	  PATHS /usr/include /usr/local/include $ENV{PATH}/include/
	  /usr/lib/R/site-library/Rcpp/include
	)
#MESSAGE( "Found Rcpp include: ${Rcpp_INCLUDE_DIR}")

	# Rcpp Library
SET(Rcpp_NAMES Rcpp.so)
FIND_PATH(Rcpp_LIBRARY_DIR
	  NAMES ${Rcpp_NAMES}
	  PATHS /usr/lib /usr/local/lib  $ENV{PATH}/lib/
	  /usr/lib/R/site-library/Rcpp/libs
	)
if (Rcpp_LIBRARY_DIR)
	set(Rcpp_LIBRARY)
  file (GLOB Rcpp_LIBRARY "${Rcpp_LIBRARY_DIR}/Rcpp*")
endif()
#MESSAGE( "Found Rcpp library: ${Rcpp_LIBRARY}")


	IF (Rcpp_INCLUDE_DIR AND Rcpp_LIBRARY)
	  SET(Rcpp_FOUND TRUE)
	  SET( Rcpp_LIBRARIES ${Rcpp_LIBRARY} )
#	  MESSAGE( "Found Rcpp library")
	ELSE ()
	  SET(Rcpp_FOUND FALSE)
	  SET( Rcpp_LIBRARIES )
	ENDIF ()

	IF (Rcpp_FOUND)
	  IF (NOT Rcpp_FIND_QUIETLY)
	    MESSAGE(STATUS "Found Rcpp: ${Rcpp_LIBRARY_DIR}")
	  ENDIF ()
	ELSE ()
	  IF (Rcpp_FIND_REQUIRED)
	    MESSAGE(STATUS "Looked for Rcpp libraries named ${Rcpp_NAMES}.")
	    MESSAGE(FATAL_ERROR "Could NOT find Rcpp library")
	  ENDIF ()
	ENDIF ()

	MARK_AS_ADVANCED(
	  Rcpp_LIBRARY
	  Rcpp_INCLUDE_DIR
	  )
