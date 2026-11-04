# Apply transport and logging extensions only to build-local source copies.
find_package(Git REQUIRED)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_LIST_DIR}/patches/vscp-authenticated-binary.patch"
  "${CMAKE_CURRENT_LIST_DIR}/patches/vscp-helper-logging.patch"
  "${CMAKE_CURRENT_LIST_DIR}/patches/vscp-private-logging.patch"
  "${CMAKE_CURRENT_LIST_DIR}/libvscphelper.map")

set(VSCP_HELPER_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/vscp-client")
set(_vscp_client_work "${VSCP_HELPER_CLIENT_DIR}/patch-work")
file(MAKE_DIRECTORY "${_vscp_client_work}")
foreach(_file vscpremotetcpif.h vscpremotetcpif.cpp vscphelper.cpp)
  configure_file("${vscp_SOURCE_DIR}/src/vscp/common/${_file}"
                 "${_vscp_client_work}/${_file}" COPYONLY)
  # Git applies the LF patches to a normalized build-local copy.
  file(READ "${_vscp_client_work}/${_file}" _vscp_client_source)
  string(REPLACE "\r\n" "\n" _vscp_normalized_source "${_vscp_client_source}")
  file(WRITE "${_vscp_client_work}/${_file}" "${_vscp_normalized_source}")
endforeach()

function(_vscp_apply_client_patch _patch)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" apply --no-index --whitespace=error-all
            "${CMAKE_CURRENT_LIST_DIR}/patches/${_patch}"
    WORKING_DIRECTORY "${_vscp_client_work}"
    RESULT_VARIABLE _vscp_patch_result
    ERROR_VARIABLE _vscp_patch_error)
  if(NOT "${_vscp_patch_result}" STREQUAL "0")
    message(FATAL_ERROR "Cannot apply the pinned VSCP patch ${_patch}: ${_vscp_patch_error}")
  endif()
endfunction()

_vscp_apply_client_patch(vscp-authenticated-binary.patch)

set(_vscp_logging_source "${vscp_SOURCE_DIR}/src/vscp/common/vscphelperlogging.cpp")
set(_vscp_logging_header "${vscp_SOURCE_DIR}/src/vscp/common/vscphelperlogging.h")
if(EXISTS "${_vscp_logging_source}" AND EXISTS "${_vscp_logging_header}")
  set(VSCP_HELPER_LOGGING_DIR "${vscp_SOURCE_DIR}/src/vscp/common")
  set(VSCP_HELPER_LOGGING_SOURCES "${_vscp_logging_source}")
  # Use one canonical header: vscphelper.h also includes it with quotes.
  file(REMOVE "${_vscp_client_work}/vscphelperlogging.h"
              "${VSCP_HELPER_CLIENT_DIR}/vscphelperlogging.h")
  if(EXISTS "${VSCP_HELPER_LOGGING_DIR}/vscphelperlogging-forward.cpp")
    foreach(_file vscphelperlogging.cpp vscphelperlogging-forward.cpp vscphelperlogging-internal.h)
      configure_file("${VSCP_HELPER_LOGGING_DIR}/${_file}"
                     "${_vscp_client_work}/${_file}" COPYONLY)
      file(READ "${_vscp_client_work}/${_file}" _vscp_client_source)
      string(REPLACE "\r\n" "\n" _vscp_normalized_source "${_vscp_client_source}")
      file(WRITE "${_vscp_client_work}/${_file}" "${_vscp_normalized_source}")
    endforeach()
    _vscp_apply_client_patch(vscp-private-logging.patch)
    foreach(_file vscphelperlogging.cpp vscphelperlogging-forward.cpp vscphelperlogging-internal.h)
      configure_file("${_vscp_client_work}/${_file}"
                     "${VSCP_HELPER_CLIENT_DIR}/${_file}" COPYONLY)
    endforeach()
    set(VSCP_HELPER_LOGGING_SOURCES
        "${VSCP_HELPER_CLIENT_DIR}/vscphelperlogging.cpp"
        "${VSCP_HELPER_CLIENT_DIR}/vscphelperlogging-forward.cpp")
  endif()
  foreach(_file vscpremotetcpif.cpp vscphelper.cpp)
    file(READ "${_vscp_client_work}/${_file}" _vscp_client_source)
    string(FIND "${_vscp_client_source}" "VSCP_ENABLE_HELPER_LOGGING" _vscp_logging_position)
    if(_vscp_logging_position EQUAL -1)
      message(FATAL_ERROR "VSCP provides the logger but ${_file} does not integrate it")
    endif()
  endforeach()
  message(STATUS "VSCP helper logging: upstream sources")
elseif(NOT EXISTS "${_vscp_logging_source}" AND NOT EXISTS "${_vscp_logging_header}")
  set(VSCP_HELPER_LOGGING_DIR "${VSCP_HELPER_CLIENT_DIR}")
  set(VSCP_HELPER_LOGGING_SOURCES "${VSCP_HELPER_LOGGING_DIR}/vscphelperlogging.cpp")
  file(REMOVE "${_vscp_client_work}/vscphelperlogging.cpp"
              "${_vscp_client_work}/vscphelperlogging.h")
  _vscp_apply_client_patch(vscp-helper-logging.patch)
  foreach(_file vscphelperlogging.cpp vscphelperlogging.h)
    configure_file("${_vscp_client_work}/${_file}"
                   "${VSCP_HELPER_LOGGING_DIR}/${_file}" COPYONLY)
  endforeach()
  message(STATUS "VSCP helper logging: pinned-source compatibility patch")
else()
  message(FATAL_ERROR "VSCP must provide both vscphelperlogging.cpp and vscphelperlogging.h")
endif()

foreach(_file vscpremotetcpif.h vscpremotetcpif.cpp vscphelper.cpp)
  configure_file("${_vscp_client_work}/${_file}"
                 "${VSCP_HELPER_CLIENT_DIR}/${_file}" COPYONLY)
endforeach()
