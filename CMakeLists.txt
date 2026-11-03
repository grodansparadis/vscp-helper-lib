# CMakeLists.txt
#
# Build instructions for VSCP Works.
#
# Copyright (C) 2000-2026 Åke Hedman and contributors, the VSCP Project
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#

cmake_minimum_required(VERSION 3.14)

set(PACKAGE_AUTHOR "Ake Hedman, the VSCP Project")

file(STRINGS "${CMAKE_SOURCE_DIR}/src/libversion.h" LIBVSCPHELPER_VERSION_DEFINE
  REGEX "^#define[ \\t]+VSCP_HELPER_LIB_VERSION[ \\t]+\"[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\"[ \\t]*$")
if(NOT LIBVSCPHELPER_VERSION_DEFINE)
  message(FATAL_ERROR "Unable to read a four-part VSCP_HELPER_LIB_VERSION from src/libversion.h")
endif()
string(REGEX REPLACE ".*\"([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)\".*" "\\1"
  LIBVSCPHELPER_VERSION "${LIBVSCPHELPER_VERSION_DEFINE}")
string(REPLACE "." ";" LIBVSCPHELPER_VERSION_PARTS "${LIBVSCPHELPER_VERSION}")
list(GET LIBVSCPHELPER_VERSION_PARTS 0 MAJOR_VERSION)
list(GET LIBVSCPHELPER_VERSION_PARTS 1 MINOR_VERSION)
list(GET LIBVSCPHELPER_VERSION_PARTS 2 REVISION_VERSION)
list(GET LIBVSCPHELPER_VERSION_PARTS 3 PATCH_VERSION)

file(STRINGS "${CMAKE_SOURCE_DIR}/src/libversion.h" LIBVSCPHELPER_REVISION_DEFINE
  REGEX "^#define[ \\t]+VSCP_HELPER_LIB_VERSION_REVISION[ \\t]+(0|[1-9][0-9]*)[ \\t]*$")
if(NOT LIBVSCPHELPER_REVISION_DEFINE)
  message(FATAL_ERROR "VSCP_HELPER_LIB_VERSION_REVISION must be an unpadded decimal integer between 0 and 255")
endif()
string(REGEX REPLACE "^#define[ \\t]+VSCP_HELPER_LIB_VERSION_REVISION[ \\t]+([0-9]+)[ \\t]*$" "\\1"
  LIBVSCPHELPER_MANUAL_REVISION "${LIBVSCPHELPER_REVISION_DEFINE}")
if(LIBVSCPHELPER_MANUAL_REVISION GREATER 255)
  message(FATAL_ERROR "VSCP_HELPER_LIB_VERSION_REVISION must be between 0 and 255")
endif()
if(NOT "${REVISION_VERSION}" STREQUAL "${LIBVSCPHELPER_MANUAL_REVISION}")
  message(FATAL_ERROR "The library version and manual revision disagree; run python3 tools/update_libversion.py")
endif()

set(APP_VERSION "${LIBVSCPHELPER_VERSION}")
project(libvscphelper VERSION "${LIBVSCPHELPER_VERSION}" LANGUAGES CXX C)

if(WIN32 AND PATCH_VERSION GREATER 65535)
  message(FATAL_ERROR "Windows VERSIONINFO cannot store a patch greater than 65535")
endif()

function(vscp_set_macho_compatibility_version target major minor revision patch)
  if(NOT APPLE)
    return()
  endif()

  # Mach-O cannot encode the full Git count; retain the previous compatibility
  # version within its 8-bit limit without lowering the manual revision.
  set(macho_component "${patch}")
  if(macho_component GREATER 255)
    set(macho_component 255)
  endif()
  if(revision GREATER macho_component)
    set(macho_component "${revision}")
  endif()
  set(macho_version "${major}.${minor}.${macho_component}")
  set_target_properties("${target}" PROPERTIES VERSION "${macho_version}" SOVERSION "${macho_version}")
  message(STATUS "Mach-O binary version: ${macho_version} (library version: ${LIBVSCPHELPER_VERSION})")
endfunction()

# Set compiler options
if(WIN32)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()

endif()

SET(CPACK_PACKAGE_DESCRIPTION "VSCP Helper library")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Helper functionality for VSCP applications")
SET(CPACK_PACKAGE_VENDOR "the VSCP Project")
SET(CPACK_PACKAGE_CONTACT "akhe@vscp.org")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/resources/nsis ${CMAKE_MODULE_PATH})
#${CMAKE_BINARY_DIR}_CPack_Packages${CPACK_TOPLEVEL_TAG}${CPACK_GENERATOR}

if(NOT DEFINED APP_LOW_NAME)
set(APP_LOW_NAME "libvscphelper")
endif()

if(NOT DEFINED APP_NAME)
set(APP_NAME "LIBVSCPHELPER")
endif()

if(NOT DEFINED APP_URL)
set(APP_URL "https://github.com/grodansparadis/vscp-helper-lib")
endif()

if(NOT DEFINED APP_VERSION)
set(APP_VERSION "${MAJOR_VERSION}-${MINOR_VERSION}-${REVISION_VERSION}-${PATCH_VERSION}")
endif()

# --- System Libraries ---
include(GNUInstallDirs)

# --- Third party code (downloaded at configure time) ---
include("${PROJECT_SOURCE_DIR}/cmake/VscpHelperDependencies.cmake")
include("${PROJECT_SOURCE_DIR}/cmake/VscpHelperTransport.cmake")

# Man build and install
if(NOT DEFINED WIN32)
    add_subdirectory(man)
endif()

option(USE_SSL "Use SSL" TRUE)

## --- C++17 build flags ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Build locations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_ALLTEST "Build the alltest test executable" OFF)
option(BUILD_RAW_TRANSPORT_SAMPLES "Build the raw TCP/TLS transport samples" OFF)

# Default location for VSCP level II drivers
set(VSCP_LEVEL2_DRV_DIR /var/lib/vscp/drivers/level2/)

# Generate position-independent code (-fPIC on UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_LIBRARY_ARCHITECTURE=${CMAKE_LIBRARY_ARCHITECTURE}")
message(STATUS "CMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}")

if(WIN32)
  add_definitions(-DHELPERLIB_EXPORTS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-DWIN32_LEAN_AND_MEANS)
  add_definitions(-DOPENSSL_API_1_1)
  add_definitions(-D_POSIX_C_SOURCE)    
  add_definitions(-DVCPKG_TARGET_TRIPLET=x64-windows)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  set(LIBS_SYSTEM ws2_32)
endif(WIN32)

if(UNIX)
  set(LIBS_SYSTEM c stdc++)
endif(UNIX)

set(CMAKE_INSTALL_PREFIX "/")

#   ===========================  cpack  ===========================
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

  include(InstallRequiredSystemLibraries)

  set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA 
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/debpkg/shlibs;"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/debpkg/triggers;" )

  SET(CPACK_SET_DESTDIR OFF)

  IF(WIN32)
    SET(CPACK_GENERATOR "NSIS" "ZIP")
  ELSE()
    SET(CPACK_GENERATOR "DEB" "RPM" "TGZ" "ZIP")
  ENDIF(WIN32)
 
  SET(CPACK_PACKAGE_NAME "libvscphelper")
  SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "libvscphelper")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
  set(CPACK_PACKAGE_VENDOR "The VSCP Project")

  SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  SET(CPACK_PACKAGE_VERSION_PATCH "${REVISION_VERSION}")
  SET(CPACK_PACKAGE_VERSION "${LIBVSCPHELPER_VERSION}")

  if(NOT DEFINED PACKAGE_OS)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      set(PACKAGE_OS "macos")
    else()
      string(TOLOWER "${CMAKE_SYSTEM_NAME}" PACKAGE_OS)
    endif()
  endif()

  string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" PACKAGE_PROCESSOR)
  if(PACKAGE_PROCESSOR STREQUAL "x86_64" OR PACKAGE_PROCESSOR STREQUAL "amd64")
    set(PACKAGE_ARCHITECTURE "x64")
  elseif(PACKAGE_PROCESSOR STREQUAL "aarch64" OR PACKAGE_PROCESSOR STREQUAL "arm64")
    set(PACKAGE_ARCHITECTURE "arm64")
  elseif(PACKAGE_PROCESSOR STREQUAL "armv7l" OR PACKAGE_PROCESSOR STREQUAL "armhf")
    set(PACKAGE_ARCHITECTURE "armhf")
  else()
    set(PACKAGE_ARCHITECTURE "${PACKAGE_PROCESSOR}")
  endif()

  set(PACKAGE_FILE_QUALIFIER "")
  if(DEFINED PACKAGE_QUALIFIER AND NOT PACKAGE_QUALIFIER STREQUAL "")
    set(PACKAGE_FILE_QUALIFIER "_${PACKAGE_QUALIFIER}")
  endif()

  SET(CPACK_PACKAGE_FILE_NAME
      "${CMAKE_PROJECT_NAME}_${PACKAGE_OS}_${PACKAGE_ARCHITECTURE}_${LIBVSCPHELPER_VERSION}${PACKAGE_FILE_QUALIFIER}")
  SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${LIBVSCPHELPER_VERSION}")
#  SET(CPACK_IGNORE_FILES "\\.psd$;/CVS/;/\\.svn/;/\\.git/;\\.swp$;/CMakeLists.txt.user;\\.#;/#;\\.tar.gz$;/CMakeFiles/;CMakeCache.txt;\\.qm$;/build/;\\.diff$;.DS_Store'")
#  SET(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})

  SET(CPACK_NSIS_INSTALLED_ICON_NAME "libvscphelper.ico")
  SET(CPACK_NSIS_HELP_LINK "https://www.vscp.org")
  SET(CPACK_NSIS_URL_INFO_ABOUT "https://www.vscp.org")
  set(CPACK_NSIS_CONTACT "info@vscp.org")

  if(NOT DEFINED WIN32)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS " libexpat-dev, libssl-dev ")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "network")
    SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
  endif()

  # For component selection during install - If used
  # need to specify components in the install part to
  #SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)

  # Configure file with custom definitions for NSIS.
  if(WIN32)
    # Configure file with custom definitions for NSIS.
    # configure_file(
    #   ${PROJECT_SOURCE_DIR}/resources/nsis/NSIS.definitions.nsh.in
    #   ${CMAKE_CURRENT_BINARY_DIR}/resources/nsis/NSIS.definitions.nsh)  
  else()
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS 
                "lsb-base (>=4.1+Debian3), libc6-dev (>= 2.14), libstdc++6 (>= 5.2), libgcc1 (>= 1:3.0), libssl-dev (>=1.0.0),  libexpat1-dev (>=2.0), libz-dev")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "network")
    SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
    set(CPACK_STRIP_FILES "bin/vscpd")
    set(CPACK_SOURCE_STRIP_FILES "")      
  endif()

  # Load packaging facilities.
  include(CPack) 

endif()


set(CMAKE_INCLUDE_CURRENT_DIR ON)

# pthreads
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#openssl
find_package(OpenSSL REQUIRED)

# Windows Libs
if (WIN32)
  # Expat C library
  find_package(expat CONFIG REQUIRED)
else()
  # expat
  include(FindEXPAT)
  find_package(EXPAT REQUIRED)
  include_directories(${EXPAT_INCLUDE_DIRS})
endif(WIN32)

set(OPENSSL_VER "OPENSSL_API_${OPENSSL_VERSION_MAJOR}_${OPENSSL_VERSION_MINOR}")
message(STATUS "OPENSSL Version: ${OPENSSL_VER}")
add_definitions(-D${OPENSSL_VER}) 

# 1.1.0 / 1.1.1 / 3.0.0 / 3.1.0
string(FIND "${OPENSSL_VERSION}" "1.0" SSL_VER_POS)
if(${SSL_VER_POS})
  #set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DOPENSSL_API_1_0")
  #add_definitions(-DOPENSSL_API_1_0)
endif()    

string(FIND "${OPENSSL_VERSION}" "1.1" SSL_VER_POS)
if(${SSL_VER_POS})
  #set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -DOPENSSL_API_1_1")
  #add_definitions(-DOPENSSL_API_1_1)
endif()

string(FIND "${OPENSSL_VERSION}" "3.0" SSL_VER_POS)
if(NOT SSL_VER_POS EQUAL -1)
  #add_definitions(-DOPENSSL_API_3_0)
  message(STATUS "openssl test ${SSL_VER_POS}")
endif()  

string(FIND "${OPENSSL_VERSION}" "3.1" SSL_VER_POS)
if(NOT SSL_VER_POS EQUAL -1)
  add_definitions(-DOPENSSL_API_3_0)
  message(STATUS "Open ssl version is 3.1 but set to 3.0 ${SSL_VER_POS} fir Civetweb. That is OK")
endif()

set(RESOURCE_FILES
        README.md
        forms/index.html)

if(WIN32)
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/windows")
    configure_file(
        "${PROJECT_SOURCE_DIR}/windows/vscphelper.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/windows/vscphelper.rc"
        @ONLY)
endif()

# Add files to library 
if(WIN32)
add_library(libvscphelper SHARED
    ./src/vscphelperlib.h
    ./src/vscphelperlib.cpp
    ./windows/libvscphelper.h
    ./windows/libvscphelper.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscp.h
    ${VSCP_HELPER_CLIENT_DIR}/vscpremotetcpif.h
    ${VSCP_HELPER_CLIENT_DIR}/vscpremotetcpif.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscpdatetime.h
    ${vscp_SOURCE_DIR}/src/vscp/common/vscpdatetime.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/guid.h
    ${vscp_SOURCE_DIR}/src/vscp/common/guid.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscp-guid-parser.c
    ${vscp_SOURCE_DIR}/src/vscp/common/vscphelper.h
    ${vscp_SOURCE_DIR}/src/vscp/common/vscphelper.cpp
    ${vscp_SOURCE_DIR}/src/common/vscphelper-common.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/canal.h
    ${vscp_SOURCE_DIR}/src/common/vscpbase64.h
    ${vscp_SOURCE_DIR}/src/common/vscpbase64.c
    ${vscp_SOURCE_DIR}/src/common/vscp-aes.h
    ${vscp_SOURCE_DIR}/src/common/vscp-aes.c
    ${vscp_SOURCE_DIR}/src/common/crc.h
    ${vscp_SOURCE_DIR}/src/common/crc.c
    ${vscp_SOURCE_DIR}/src/common/crc8.h
    ${vscp_SOURCE_DIR}/src/common/crc8.c
    ${vscp_SOURCE_DIR}/src/common/vscpmd5.h
    ${vscp_SOURCE_DIR}/src/common/vscpmd5.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows/vscphelper.rc
  ) 
else()
  add_library(libvscphelper SHARED   
    ./src/vscphelperlib.h
    ./src/vscphelperlib.cpp 
    ./linux/libvscphelper.h
    ./linux/libvscphelper.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscp.h
    ${VSCP_HELPER_CLIENT_DIR}/vscpremotetcpif.h
    ${VSCP_HELPER_CLIENT_DIR}/vscpremotetcpif.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscpdatetime.h
    ${vscp_SOURCE_DIR}/src/vscp/common/vscpdatetime.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/guid.h
    ${vscp_SOURCE_DIR}/src/vscp/common/guid.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/vscp-guid-parser.c
    ${vscp_SOURCE_DIR}/src/vscp/common/vscphelper.h
    ${vscp_SOURCE_DIR}/src/vscp/common/vscphelper.cpp
    ${vscp_SOURCE_DIR}/src/common/vscphelper-common.cpp
    ${vscp_SOURCE_DIR}/src/vscp/common/canal.h
    ${vscp_SOURCE_DIR}/src/common/vscpbase64.h
    ${vscp_SOURCE_DIR}/src/common/vscpbase64.c
    ${vscp_SOURCE_DIR}/src/common/vscp-aes.h
    ${vscp_SOURCE_DIR}/src/common/vscp-aes.c
    ${vscp_SOURCE_DIR}/src/common/crc.h
    ${vscp_SOURCE_DIR}/src/common/crc.c
    ${vscp_SOURCE_DIR}/src/common/crc8.h
    ${vscp_SOURCE_DIR}/src/common/crc8.c
    ${vscp_SOURCE_DIR}/src/common/vscpmd5.h
    ${vscp_SOURCE_DIR}/src/common/vscpmd5.c       
  ) 
endif()

  #set_target_properties(libvscphelper PROPERTIES LIBRARY_OUTPUT_NAME "vscphelper.so.${LIBVSCPHELPER_VERSION}")

if(WIN32)
  set_target_properties(libvscphelper
    PROPERTIES
    LIBRARY_OUTPUT_NAME "libvscphelper"
    PREFIX ""
    SUFFIX "${MAJOR_VERSION}.dll"
    VERSION "${LIBVSCPHELPER_VERSION}"
    SOVERSION "${LIBVSCPHELPER_VERSION}")
else()
  set_target_properties(libvscphelper
    PROPERTIES
    LIBRARY_OUTPUT_NAME "libvscphelper"
    PREFIX ""
    SUFFIX "${MAJOR_VERSION}.so"
    VERSION "${LIBVSCPHELPER_VERSION}"
    SOVERSION "${LIBVSCPHELPER_VERSION}"
    NO_SONAME 1)
endif()    

vscp_set_macho_compatibility_version(
  libvscphelper "${MAJOR_VERSION}" "${MINOR_VERSION}" "${REVISION_VERSION}" "${PATCH_VERSION}")

set_target_properties(libvscphelper PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/src/vscphelperlib.h")

if (WIN32)
    find_package(pthreads REQUIRED)
    find_path(PTHREAD_INCLUDE_DIR pthread.h)

    include_directories( PUBLIC src/
        ./windows/
        ${VSCP_HELPER_CLIENT_DIR}/
        ${vscp_SOURCE_DIR}/src/vscp/common/
        ${vscp_SOURCE_DIR}/src/common
        ${nlohmann_json_SOURCE_DIR}/include/
        ${spdlog_SOURCE_DIR}/include/
        ${PThreads4W_INCLUDE_DIR}
        ${CMAKE_BINARY_DIR}
        ${OPENSSL_INCLUDE_DIR}
        ${LOCAL_WIN_INCLUDE}
        ${LOCAL_SYSLOG_INCLUDE} )
else()
    include_directories( PUBLIC src/
        ${VSCP_HELPER_CLIENT_DIR}/
        ${vscp_SOURCE_DIR}/src/vscp/common/
        ${vscp_SOURCE_DIR}/src/common
        ${nlohmann_json_SOURCE_DIR}/include/
        ${spdlog_SOURCE_DIR}/include/
        ${CMAKE_BINARY_DIR}
        ${OPENSSL_INCLUDE_DIR}
        ${LOCAL_SYSLOG_INCLUDE} )
 endif()   

if (WIN32)
    target_link_libraries(libvscphelper PRIVATE     
        PThreads4W::PThreads4W_CXXEXC
        OpenSSL::SSL 
        OpenSSL::Crypto
        expat::expat
        ws2_32
    )
        
else()
    target_link_libraries(libvscphelper PRIVATE     
        m
        dl
        Threads::Threads
        OpenSSL::SSL 
        OpenSSL::Crypto
        ${EXPAT_LIBRARIES}
    )
endif()

if(NOT WIN32)
configure_file("${PROJECT_SOURCE_DIR}/resources/linux/libvscphelper.pc.in" 
  libvscphelper.pc @ONLY)
endif()

# Install
if(WIN32)

    # Runtime files
    install(TARGETS libvscphelper
            RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    
    # Install the dependencies dll's
    file(GLOB deps_files "${CMAKE_BINARY_DIR}/CMAKE_BUILD_TYPE/*.dll")

    # Dependency files
    install(FILES ${deps_files} 
            DESTINATION ${CMAKE_INSTALL_BINDIR}../deps)

    # LICENSE
    install(FILES ${CMAKE_SOURCE_DIR}/LICENSE 
            DESTINATION ${CMAKE_INSTALL_BINDIR}/..)

    # README
    install(FILES ${CMAKE_SOURCE_DIR}/README.md 
            DESTINATION ${CMAKE_INSTALL_BINDIR}/..)

    # Headers
    INSTALL( FILES "${vscp_SOURCE_DIR}/src/vscp/common/vscp.h"
            "${CMAKE_SOURCE_DIR}/src/vscphelperlib.h" 
            "${vscp_SOURCE_DIR}/src/vscp/common/canal.h"
            "${vscp_SOURCE_DIR}/src/vscp/common/vscp-class.h"
            "${vscp_SOURCE_DIR}/src/vscp/common/vscp-type.h"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})  

else()

    INSTALL(TARGETS libvscphelper 
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${CMAKE_LIBRARY_ARCHITECTURE}/"
            PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_MANDIR}"
            RESOURCE DESTINATION "${CMAKE_INSTALL_FULL_}/var/lib/vscp/")

    install(FILES ${CMAKE_BINARY_DIR}/libvscphelper.pc
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)      

    # Headers        
    INSTALL(FILES "${vscp_SOURCE_DIR}/src/vscp/common/vscp.h"
            "${PROJECT_SOURCE_DIR}/src/vscphelperlib.h" 
            "${vscp_SOURCE_DIR}/src/vscp/common/canal.h"
            "${vscp_SOURCE_DIR}/src/vscp/common/vscp-class.h"
            "${vscp_SOURCE_DIR}/src/vscp/common/vscp-type.h"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})        
endif()

if(BUILD_ALLTEST)
  add_subdirectory(tests/alltest)
endif()

if(BUILD_RAW_TRANSPORT_SAMPLES)
  add_library(vscphelper_sample_transport STATIC linux/samples/raw_transport.c)
  target_link_libraries(vscphelper_sample_transport PUBLIC OpenSSL::SSL OpenSSL::Crypto)
  if(WIN32)
    target_link_libraries(vscphelper_sample_transport PUBLIC ws2_32)
  endif()

  add_executable(stcptest linux/samples/stcptest.c)
  target_link_libraries(stcptest PRIVATE vscphelper_sample_transport)

  add_executable(stcp_tls_client linux/samples/stcp_tls_client.c)
  target_link_libraries(stcp_tls_client PRIVATE vscphelper_sample_transport)

  find_package(Python3 3.8 COMPONENTS Interpreter QUIET)
  if(Python3_Interpreter_FOUND)
    add_custom_target(test_raw_transport_samples
      COMMAND ${Python3_EXECUTABLE} "${PROJECT_SOURCE_DIR}/tests/raw_transport_samples.py"
              $<TARGET_FILE:stcptest> $<TARGET_FILE:stcp_tls_client>
      DEPENDS stcptest stcp_tls_client
      USES_TERMINAL)
  else()
    message(STATUS "Python 3.8 or later not found; test_raw_transport_samples target is unavailable")
  endif()
endif()
