# Apply transport and logging extensions only to build-local source copies.
find_package(Git REQUIRED)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_LIST_DIR}/patches/vscp-authenticated-binary.patch"
  "${CMAKE_CURRENT_LIST_DIR}/patches/vscp-helper-logging.patch"
  "${CMAKE_CURRENT_LIST_DIR}/libvscphelper.map")

set(VSCP_HELPER_CLIENT_DIR "${CMAKE_CURRENT_BINARY_DIR}/vscp-client")
set(_vscp_client_work "${VSCP_HELPER_CLIENT_DIR}/patch-work")
file(MAKE_DIRECTORY "${_vscp_client_work}")
foreach(_file vscpremotetcpif.h vscpremotetcpif.cpp vscphelper.cpp)
  configure_file("${vscp_SOURCE_DIR}/src/vscp/common/${_file}"
                 "${_vscp_client_work}/${_file}" COPYONLY)
endforeach()
foreach(_patch vscp-authenticated-binary.patch vscp-helper-logging.patch)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" apply --no-index --whitespace=error-all
            "${CMAKE_CURRENT_LIST_DIR}/patches/${_patch}"
    WORKING_DIRECTORY "${_vscp_client_work}"
    RESULT_VARIABLE _vscp_patch_result
    ERROR_VARIABLE _vscp_patch_error)
  if(NOT "${_vscp_patch_result}" STREQUAL "0")
    message(FATAL_ERROR "Cannot apply the pinned VSCP patch ${_patch}: ${_vscp_patch_error}")
  endif()
endforeach()
foreach(_file vscpremotetcpif.h vscpremotetcpif.cpp vscphelper.cpp)
  configure_file("${_vscp_client_work}/${_file}"
                 "${VSCP_HELPER_CLIENT_DIR}/${_file}" COPYONLY)
endforeach()
