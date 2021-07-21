# - Try to find Likwid
# Once done this will define
#  LIKWID_FOUND - System has Likwid
#  LIKWID_INCLUDE_DIRS - The Likwid include directories
#  LIKWID_LIBRARIES - The libraries needed to use Likwid
#  LIKWID_DEFINITIONS - Compiler switches required for using Likwid


include( FindPackageHandleStandardArgs )
if( DEFINED ENV{LIKWID_DIR} )
    set( LIKWID_DIR "$ENV{LIKWID_DIR}" )
endif()

find_path(
    LIKWID_INCLUDE_DIR
    likwid-marker.h
  HINTS
  ${LIKWID_DIR}
)

find_library( LIKWID_LIBRARY
  NAMES likwid
  HINTS ${LIKWID_DIR}
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS( Likwid DEFAULT_MSG
    LIKWID_INCLUDE_DIR
    LIKWID_LIBRARY
)


if (LIKWID_FOUND)
    message(STATUS "Found likwid at ${LIKWID_DIR}")
    set( LIKWID_INCLUDE_DIRS ${LIKWID_INCLUDE_DIR} )
    set( LIKWID_LIBRARIES ${LIKWID_LIBRARY} )

  mark_as_advanced(
    LIKWID_LIBRARY
    LIKWID_INCLUDE_DIR
    LIKWID_DIR
  )
else()
    message(FATAL_ERROR "Likwid not found (-DLIKWID_DIR)")
endif()


#find_package(PkgConfig)
#pkg_check_modules(PC_LIKWID QUIET likwid)
#set(LIKWID_DEFINITIONS ${PC_LIKWID_CFLAGS_OTHER})

#find_path(LIKWID_INCLUDE_DIR likwid-marker.h
    #HINTS ${PC_LIKWID_INCLUDEDIR} ${PC_LIKWID_INCLUDE_DIRS}
          #PATH_SUFFIXES likwid )


#if(NOT Likwid_REQUESTED_VERSION)
    #message(FATAL_ERROR "LIKWID_REQUESTED_VERSION is not defined.")
#endif()


#include(ExternalProject)
#ExternalProject_Add(Likwid 
    #URL https://github.com/RRZE-HPC/likwid/archive/refs/tags/v${LIWKID_REQUESTED_VERSION}.tar.gz
#)
