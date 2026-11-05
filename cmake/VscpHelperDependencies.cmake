# VscpHelperDependencies.cmake
#
# Downloads the third-party source code needed to build vscp-helper-lib
# (same method as used in vscp-tcpip-daemon).
#
# After inclusion the following variables are available
#
#   vscp_SOURCE_DIR           - VSCP main project sources
#   spdlog_SOURCE_DIR         - spdlog (used header only)
#   nlohmann_json_SOURCE_DIR  - nlohmann JSON (header only)
#
# Only sources are fetched. No targets from the dependencies are added
# to the build. To use a local checkout instead of downloading set
# for example -DFETCHCONTENT_SOURCE_DIR_VSCP=/path/to/vscp
#
# Copyright (C) 2000-2026 Åke Hedman, the VSCP Project
# SPDX-License-Identifier: MIT

include(FetchContent)

set(VSCP_FETCH_CONTENT_OPTIONS)
if(NOT CMAKE_VERSION VERSION_LESS "3.18")
  list(APPEND VSCP_FETCH_CONTENT_OPTIONS SOURCE_SUBDIR "__vscp_sources_only__")
endif()

set(VSCP_FETCH_URL_OPTIONS)
if(NOT CMAKE_VERSION VERSION_LESS "3.24")
  list(APPEND VSCP_FETCH_URL_OPTIONS DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
endif()

FetchContent_Declare(
  vscp
  # Only a handful of VSCP source files are compiled into the library, so a
  # pinned source tarball is used instead of cloning the repository with all
  # its history and submodules.
  # Get URL_HASH with
  # curl -sL https://codeload.github.com/grodansparadis/vscp/tar.gz/<commit> | sha256sum
  URL https://codeload.github.com/grodansparadis/vscp/tar.gz/f76ac50a67213749819a2014ff99f1a46bf3ea04
  URL_HASH SHA256=5b19b9bf1f827b28821fbb794cdc7ea593acf1a5fcd7a1b30874e2b81190bc3a
  ${VSCP_FETCH_URL_OPTIONS}
  ${VSCP_FETCH_CONTENT_OPTIONS}
)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.17.0
  GIT_SHALLOW TRUE
  ${VSCP_FETCH_CONTENT_OPTIONS}
)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
  GIT_SHALLOW TRUE
  ${VSCP_FETCH_CONTENT_OPTIONS}
)

# Make the sources available without adding the dependencies own
# library/install targets to this build.
if(CMAKE_VERSION VERSION_LESS "3.18")
  foreach(_vscp_dep vscp spdlog nlohmann_json)
    FetchContent_GetProperties(${_vscp_dep})
    if(NOT ${_vscp_dep}_POPULATED)
      FetchContent_Populate(${_vscp_dep})
    endif()
  endforeach()
else()
  FetchContent_MakeAvailable(vscp spdlog nlohmann_json)
endif()

message(STATUS "vscp sources: ${vscp_SOURCE_DIR}")
message(STATUS "spdlog sources: ${spdlog_SOURCE_DIR}")
message(STATUS "nlohmann_json sources: ${nlohmann_json_SOURCE_DIR}")
