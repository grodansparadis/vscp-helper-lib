find_package(GTest CONFIG REQUIRED)

add_executable(unittest unittest.cpp)
target_link_libraries(unittest PRIVATE libvscphelper GTest::gtest)

add_executable(unittest_tcp_transport tcp_transport.cpp)
target_sources(unittest_tcp_transport PRIVATE ${vscp_SOURCE_DIR}/src/common/crc.c)
target_link_libraries(unittest_tcp_transport PRIVATE libvscphelper GTest::gtest_main)

add_executable(unittest_datagram_clients datagram_clients.cpp)
target_link_libraries(unittest_datagram_clients PRIVATE libvscphelper GTest::gtest_main)
if(WIN32)
  target_link_libraries(unittest_datagram_clients PRIVATE ws2_32)
endif()
add_custom_target(test_datagram_clients
  COMMAND $<TARGET_FILE:unittest_datagram_clients>
  DEPENDS unittest_datagram_clients
  USES_TERMINAL)

add_executable(unittest_logging logging.cpp)
target_link_libraries(unittest_logging PRIVATE libvscphelper GTest::gtest Threads::Threads)
add_custom_target(test_logging
  COMMAND $<TARGET_FILE:unittest_logging>
  DEPENDS unittest_logging
  USES_TERMINAL)

set(VSCP_TEST_HOST_SPDLOG_INCLUDE_DIR "" CACHE PATH
    "Optional alternate spdlog include directory for host compatibility testing")
if(VSCP_TEST_HOST_SPDLOG_INCLUDE_DIR)
  if(NOT EXISTS "${VSCP_TEST_HOST_SPDLOG_INCLUDE_DIR}/spdlog/version.h")
    message(FATAL_ERROR "VSCP_TEST_HOST_SPDLOG_INCLUDE_DIR must contain spdlog headers")
  endif()
  add_executable(unittest_logging_host_compat logging.cpp)
  target_include_directories(unittest_logging_host_compat BEFORE PRIVATE
    "${VSCP_TEST_HOST_SPDLOG_INCLUDE_DIR}")
  target_link_libraries(unittest_logging_host_compat PRIVATE libvscphelper GTest::gtest Threads::Threads)
  add_custom_target(test_logging_host_compat
    COMMAND $<TARGET_FILE:unittest_logging_host_compat>
    DEPENDS unittest_logging_host_compat
    USES_TERMINAL)
endif()

add_executable(logging_c_host logging_c_host.c)
target_link_libraries(logging_c_host PRIVATE libvscphelper)
set_target_properties(logging_c_host PROPERTIES LINKER_LANGUAGE CXX)
add_custom_target(test_logging_c_host
  COMMAND $<TARGET_FILE:logging_c_host>
  DEPENDS logging_c_host
  USES_TERMINAL)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_custom_target(test_library_exports
    COMMAND "${CMAKE_COMMAND}"
            "-DLIBRARY=$<TARGET_FILE:libvscphelper>"
            -P "${PROJECT_SOURCE_DIR}/cmake/CheckLibraryExports.cmake"
    DEPENDS libvscphelper
    USES_TERMINAL)
endif()

add_custom_target(test_dependency_fetch
  COMMAND "${CMAKE_COMMAND}"
          -S "${PROJECT_SOURCE_DIR}/tests/dependency_fetch"
          -B "${CMAKE_CURRENT_BINARY_DIR}/dependency-fetch"
          "-DVSCP_HELPER_SOURCE_DIR=${PROJECT_SOURCE_DIR}"
          "-DFETCHCONTENT_SOURCE_DIR_VSCP=${vscp_SOURCE_DIR}"
          "-DFETCHCONTENT_SOURCE_DIR_SPDLOG=${spdlog_SOURCE_DIR}"
          "-DFETCHCONTENT_SOURCE_DIR_NLOHMANN_JSON=${nlohmann_json_SOURCE_DIR}"
          "-DFETCHCONTENT_SOURCE_DIR_VSCP_MONGOOSE=${CMAKE_CURRENT_BINARY_DIR}/unavailable-mongoose"
          -DFETCHCONTENT_FULLY_DISCONNECTED=ON
  VERBATIM)

find_package(Python3 3.7 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
  add_custom_target(test_tcp_transport
    COMMAND ${Python3_EXECUTABLE}
            "${CMAKE_CURRENT_SOURCE_DIR}/run_transport_tests.py"
            "${vscp_SOURCE_DIR}/tests/tcpiptls/run_transport_tests.py"
            $<TARGET_FILE:unittest_tcp_transport>
    DEPENDS unittest_tcp_transport
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    USES_TERMINAL)
else()
  message(STATUS "Python 3.7 or later not found; test_tcp_transport target is unavailable")
endif()
