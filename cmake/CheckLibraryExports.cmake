if(NOT DEFINED LIBRARY)
  message(FATAL_ERROR "LIBRARY is required")
endif()

find_program(NM_EXECUTABLE nm)
if(NOT NM_EXECUTABLE)
  message(FATAL_ERROR "nm is required to inspect library exports")
endif()
execute_process(
  COMMAND "${NM_EXECUTABLE}" -D --defined-only "${LIBRARY}"
  RESULT_VARIABLE nm_result
  OUTPUT_VARIABLE nm_output
  ERROR_VARIABLE nm_error)
if(NOT nm_result EQUAL 0)
  message(FATAL_ERROR "Cannot inspect library exports: ${nm_error}")
endif()

string(REPLACE "\n" ";" nm_lines "${nm_output}")
set(export_count 0)
foreach(line IN LISTS nm_lines)
  if(line STREQUAL "")
    continue()
  endif()
  if(NOT line MATCHES "^[0-9A-Fa-f]+ [A-Za-z] vscphlp_[A-Za-z0-9_]+$")
    message(FATAL_ERROR "Unexpected exported symbol: ${line}")
  endif()
  math(EXPR export_count "${export_count} + 1")
endforeach()

if(export_count EQUAL 0)
  message(FATAL_ERROR "No vscphlp_* API symbols were exported")
endif()
message(STATUS "Verified ${export_count} exported vscphlp_* API symbols")
