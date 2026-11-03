find_package(GTest CONFIG REQUIRED)

add_executable(unittest unittest.cpp)
target_link_libraries(unittest PRIVATE libvscphelper GTest::gtest)

add_executable(unittest_tcp_transport tcp_transport.cpp)
target_link_libraries(unittest_tcp_transport PRIVATE libvscphelper GTest::gtest_main)

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
            "${vscp_SOURCE_DIR}/tests/tcpiptls/run_transport_tests.py"
            $<TARGET_FILE:unittest_tcp_transport>
    DEPENDS unittest_tcp_transport
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    USES_TERMINAL)
else()
  message(STATUS "Python 3.7 or later not found; test_tcp_transport target is unavailable")
endif()
