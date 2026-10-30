cmake_minimum_required(VERSION 3.14)

# set the project name
project(test LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Third party code (downloaded at configure time)
include("${CMAKE_SOURCE_DIR}/../../../cmake/VscpHelperDependencies.cmake")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Build dir: " ${CMAKE_SOURCE_DIR})
SET(GCC_BIGTEST_COMPILE_FLAGS "-Wl,-rpath=../../../build")

# add the executable
add_executable(bigtest 
    bigtest.c
    ${vscp_SOURCE_DIR}/src/vscp/common/guid.h
)

target_include_directories(bigtest PUBLIC 
    ${CMAKE_SOURCE_DIR}/../../../src
    ${vscp_SOURCE_DIR}/src/vscp/common
)

target_link_libraries(bigtest PRIVATE
    vscphelper15
)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_BIGTEST_COMPILE_FLAGS}")

#add_library(MathFunctions mysqrt.cxx)
