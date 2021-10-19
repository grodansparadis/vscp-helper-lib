cmake_minimum_required(VERSION 3.10)

# set the project name
project(unittest LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET(CMAKE_SKIP_BUILD_RPATH  TRUE)
# SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
# SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# SET(CMAKE_SHARED_LIBRARY_RPATH_LINK_C_FLAG "-Wl,-rpath-link,/home/akhe/development/VSCP/vscp-helper-lib/build")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#SET(GCC_BIGTEST_COMPILE_FLAGS "-Wl,-rpath,/home/akhe/development/VSCP/vscp-helper-lib/build")

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# set the module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

message(STATUS "Build dir: " ${PROJECT_SOURCE_DIR})

find_package(GTest CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# pthreads
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# TODO Check SLL version and set variable accordingly
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DOPENSSL_API_1_1 ${GCC_BIGTEST_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DOPENSSL_API_1_1 ${GCC_BIGTEST_COMPILE_FLAGS}")

message(STATUS "CXX Flags dir: " ${CMAKE_CXX_FLAGS})

include(FindEXPAT)
find_package(EXPAT REQUIRED)
include_directories(${EXPAT_INCLUDE_DIRS})

# add the executable
add_executable(unittest 
    ${PROJECT_SOURCE_DIR}/unittest.cpp
)

if (WIN32)    
  find_package(pthreads REQUIRED)
  find_path(PTHREAD_INCLUDE_DIR pthread.h)

  target_include_directories(unittest PUBLIC 
    ${PROJECT_SOURCE_DIR}/../../src/
    ${OPENSSL_INCLUDE_DIR}
    ${EXPAT_INCLUDE_DIRS}
  )
else()
  target_include_directories(unittest PUBLIC 
    ${PROJECT_SOURCE_DIR}/../../src/
    ${OPENSSL_INCLUDE_DIR}
    ${EXPAT_INCLUDE_DIRS}
  )
endif()  
    
if (WIN32)
  target_link_libraries(unittest PRIVATE
    "${PROJECT_SOURCE_DIR}/../../build/libvscphelper15.so"
    GTest::gtest
    GTest::gmock
  )
else()
  target_link_libraries(unittest PRIVATE
    "${PROJECT_SOURCE_DIR}/../../build/libvscphelper15.so"
    GTest::gtest
    GTest::gmock
  )    
endif()


