cmake_minimum_required(VERSION 3.10)
project(omptlikwid VERSION 0.1 DESCRIPTION "OMPT launcher of likwid")


if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using LLVM ${CMAKE_CXX_COMPILER_VERSION}")
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Using GNU ${CMAKE_CXX_COMPILER_VERSION}")
endif()


find_package(OpenMP 5.0 REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Likwid REQUIRED)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(omptlikwid SHARED OmptLikwid/mytool.c)
target_compile_options(omptlikwid PRIVATE -DLIKWID_PERFMON)
set_target_properties(omptlikwid PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(omptlikwid PRIVATE OpenMP::OpenMP_CXX ${LIKWID_LIBRARIES})

add_executable(simpleTest App/simpleTest.c)
target_compile_options(simpleTest PRIVATE "${OpenMP_CXX_FLAGS}" -DLIKWID_PERFMON)
target_link_libraries(simpleTest PRIVATE OpenMP::OpenMP_CXX ${LIKWID_LIBRARIES})
