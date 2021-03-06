###################################################################################################
# Common Project Settings
# 09/10/2011 	Luoting Fu created this file
# 04/22/2016	Lei Liu modified this file, finally
###################################################################################################
# set debug postfix
set(CMAKE_DEBUG_POSTFIX "_debug")

# check source and binary locations
# if (NOT PRIMARY_DEVELOPER)
	# set(PRIMARY_DEVELOPER "luotingf")
# endif()

###################################################################################################
# prevent in-source build
###################################################################################################
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message (SEND_ERROR "Building in the source directory is prohibited.")
	# Otherwise, the Qt4_auto_moc goes into infinite loop when moc files are moc-ed
    message (FATAL_ERROR "Please remove the created \"CMakeCache.txt\" file, the \"CMakeFiles\" directory and create a build directory and call \"${CMAKE_COMMAND} <path to the sources>\".")
endif ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")

###################################################################################################
# check if source or binary are in dropbox
###################################################################################################
# STRING(FIND "${CMAKE_SOURCE_DIR}" "Dropbox" SOURCE_IN_DROPBOX)
# STRING(FIND "${CMAKE_BINARY_DIR}" "Dropbox" BINARY_IN_DROPBOX)
# STRING(FIND "${CMAKE_BINARY_DIR}"  ${PRIMARY_DEVELOPER} IN_PRIMARY_DEVELOPER)

# if (${SOURCE_IN_DROPBOX} EQUAL -1)
	# MESSAGE( STATUS "The source code is not located in Dropbox. Ok." )
# else ()
	# if ($(IN_PRIMARY_DEVELOPER) EQUAL -1)
		# MESSAGE( WARNING "The source codes is located in Dropbox. Ignore this warning only if you could make sure that the codebase is not being concurrently modified by other programmers." )
	# else()
		# MESSAGE( STATUS "The source code is located in the Dropbox of the primary developer. Ok." )
	# endif()
# endif ()

# if (${BINARY_IN_DROPBOX} EQUAL -1)
	# MESSAGE( STATUS "The binary output will not be located in Dropbox. Ok." )
# else ()
	# MESSAGE( FATAL_ERROR "The binary output will be located in Dropbox. Building in Dropbox is prohibited." )
	#Otherwise, many intermediate project files (pch, qch, sdf, obj, pdb) will generate meaningless traffic between the build machine and Dropbox.
# endif ()

###################################################################################################
# only build Debug and Release
###################################################################################################
# set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Build Types" FORCE)
# mark_as_advanced (CMAKE_CONFIGURATION_TYPES)

# set Debug as default build target, such that Makefile builds are in release mode
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the default type of build, options are: Debug, Release."
      FORCE)
endif ()

###################################################################################################
# Additional link library for MSVS
###################################################################################################
function (target_link_library_dirs _TARGET)
	set(_LIB_DIRS ${ARGV})
	list(REMOVE_AT _LIB_DIRS 0)

	get_target_property(_OLD_LINK_FLAGS ${_TARGET} LINK_FLAGS)
	if (${_OLD_LINK_FLAGS} STREQUAL "_OLD_LINK_FLAGS-NOTFOUND")
		set(_OLD_LINK_FLAGS "")
	endif()
	# message(STATUS "Old link flags = ${_OLD_LINK_FLAGS}")

	set (_LIBPATH_FLAGS "")
	foreach(_lib_dir ${_LIB_DIRS})
		# message(STATUS ${_lib_dir})
		set(_LIBPATH_FLAGS "${_LIBPATH_FLAGS} /LIBPATH:\"${_lib_dir}\"")
	endforeach()
	# message(STATUS ${_LIBPATH_FLAGS})
	set(_OLD_LINK_FLAGS "${_OLD_LINK_FLAGS}${_LIBPATH_FLAGS}")
	set_target_properties(${_TARGET} PROPERTIES LINK_FLAGS "${_OLD_LINK_FLAGS}")

	# get_target_property(_NEW_LINK_FLAGS ${_TARGET} LINK_FLAGS)
	# message(STATUS "New link flags = ${_NEW_LINK_FLAGS}")
endfunction()

###################################################################################################
# File list gatherer
###################################################################################################
# gather all files with extension "ext" in the "dirs" directories to "ret"
# excludes all files starting with a '.' (dot)
# excludes all the files ending with a '~' (wave from linux system)
macro (gather_list_by_extension ret ext)
	foreach (_dir ${ARGN})
		file (GLOB _files "${_dir}/${ext}")
		foreach (_file ${_files})
			get_filename_component (_neatname ${_file} ABSOLUTE)
			get_filename_component (_filename ${_file} NAME)
			if (_filename MATCHES "^[.]" OR _filename MATCHES "[~]$")
				list (REMOVE_ITEM _files ${_file})
			else()
				list (REMOVE_ITEM _files ${_file})
				list (APPEND _files ${_neatname})
			endif ()
		endforeach ()
		list (APPEND ${ret} ${_files})
	endforeach ()

	if (GATHER_LIST_DEBUG)
		message(STATUS "List gathered by extension ${ext} in ${ARGN}")
		foreach (_filepath ${${ret}})
			message(STATUS "    ${_filepath}")
		endforeach()
	endif()
endmacro ()

# gather all files with "ext" and "keyword" in the "dirs" directories to "ret"
# excludes all files starting with a '.' (dot)
macro (gather_list_by_extension_keyword ret ext keyword)
	foreach (_dir ${ARGN})
		file (GLOB _files "${_dir}/${ext}")
		foreach (_file ${_files})
			get_filename_component (_neatname ${_file} ABSOLUTE)
			get_filename_component (_filename ${_file} NAME)

			# first remove the relative path
			list (REMOVE_ITEM _files ${_file})
			# then conditionally add its absolute path back
			if (_filename MATCHES "^[.]" OR _filename MATCHES "[~]$")
				list (REMOVE_ITEM _files ${_file})
			else()
				list (REMOVE_ITEM _files ${_file})
				file (READ ${_neatname} _contents)
					if (_filename MATCHES ${keyword})
						list (APPEND _files ${_neatname})
					endif()
			endif ()

		endforeach ()
		list (APPEND ${ret} ${_files})
	endforeach ()

	if (GATHER_LIST_DEBUG)
		message(STATUS "List gathered by extension ${ext} and keyword " "${keyword}" " in ${ARGN}")
		foreach (_filepath ${${ret}})
			message(STATUS "    ${_filepath}")
		endforeach()
	endif()
endmacro ()

# gather all files except "keyword" in the "dirs" directories to "ret"
# excludes all files starting with a '.' (dot)
macro (gather_list_by_extension_excpet_keyword ret ext keyword)
	foreach (_dir ${ARGN})
		file (GLOB _files "${_dir}/${ext}")
		foreach (_file ${_files})
			get_filename_component (_neatname ${_file} ABSOLUTE)
			get_filename_component (_filename ${_file} NAME)

			# first remove the relative path
			list (REMOVE_ITEM _files ${_file})
			# then conditionally add its absolute path back
			if (_filename MATCHES "^[.]" OR _filename MATCHES "[~]$")
				list (REMOVE_ITEM _files ${_file})
			else()
				list (REMOVE_ITEM _files ${_file})
				file (READ ${_neatname} _contents)
					if (NOT _filename MATCHES ${keyword})
						list (APPEND _files ${_neatname})
					endif()
			endif ()
		endforeach ()
		list (APPEND ${ret} ${_files})
	endforeach ()

	if (GATHER_LIST_DEBUG)
		message(STATUS "List gathered by extension ${ext} except keyword " "${keyword}" " in ${ARGN}")
		foreach (_filepath ${${ret}})
			message(STATUS "    ${_filepath}")
		endforeach()
	endif()
endmacro ()


macro(source_group_by_dir source_files)
set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
	foreach(sgbd_file ${${source_files}})
 		string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
		string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
		string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
		string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
		if(sgbd_nogroup)
			set(sgbd_group_name "\\")
		endif(sgbd_nogroup)
		source_group(${sgbd_group_name} FILES ${sgbd_file})
	endforeach(sgbd_file)
endmacro(source_group_by_dir)

# absolute paths can cause trouble viewing file properties in VS
# https://connect.microsoft.com/VisualStudio/feedback/details/635294/using-absolute-path-in-clcompile-item-prevents-property-pages-from-showing
macro(relative_path_from_absolute ret_with_rel_path)
	foreach (_file ${ARGN})
		file(RELATIVE_PATH _relativename ${CMAKE_CURRENT_BINARY_DIR} ${_file})
		list (APPEND ret_with_rel_path ${_relativename})
		#message(STATUS "${_file} -> ${_relativename}")
	endforeach()
endmacro ()

