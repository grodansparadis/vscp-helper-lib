# Return values and error handling

The return convention depends on the function. Check its reference page before
interpreting the result:

* Most status-returning C functions and C++ methods use `VSCP_ERROR_SUCCESS`
  (`0`) for success and a nonzero error code for failure. Check `result !=
  VSCP_ERROR_SUCCESS`, not `result < 0`: most VSCP errors are positive.
* Some `int` functions return a value or a boolean instead of a status.
  For example, `VscpRemoteTcpIf::doCmdDataAvailable` returns a count or `-1`,
  while `vscphlp_isGUIDEmpty` returns `1` or `0`. Conversely,
  `vscphlp_isConnected` returns a status, not a boolean.
* `vscphlp_newSession` returns a positive handle, not a status. Check for a
  positive result: `0` and, on Windows, `-1` can indicate failure.
* `void` functions do not report an error code. Pointer, timestamp, CRC, and
  other value-returning functions must not be interpreted as status codes.

The method pages list the codes returned by this library and the pinned
`VscpRemoteTcpIf` implementation. A server's nonzero binary event-confirmation
status can also be returned by binary event receive operations. Code values
and aliases are defined in the pinned
[VSCP header](https://github.com/grodansparadis/vscp/blob/f76ac50a67213749819a2014ff99f1a46bf3ea04/src/vscp/common/vscp.h)
and [CANAL header](https://github.com/grodansparadis/vscp/blob/f76ac50a67213749819a2014ff99f1a46bf3ea04/src/vscp/common/canal.h).

## Common codes

The meaning of a code depends on the operation. For example, `PARAMETER` may
mean an invalid argument or a command that is not allowed in the current mode.
The following table covers codes referenced by the method documentation; it is
not a list of codes returned by every function.

| Code | Value | General meaning |
| --- | ---: | --- |
| `VSCP_ERROR_SUCCESS` | 0 | The operation succeeded. |
| `VSCP_ERROR_ERROR` | -1 | General failure, rejected operation, or negative predicate result. |
| `VSCP_ERROR_GENERIC` | 12 | Generic operation or response failure. |
| `VSCP_ERROR_RCV_EMPTY` | 19 | The receive queue is empty. |
| `VSCP_ERROR_TIMEOUT` | 32 | The operation timed out. |
| `VSCP_ERROR_NOT_OPEN` | 33 | The connection or interface is not open. |
| `VSCP_ERROR_PARAMETER` | 34 | An argument or operation is invalid for the current state. |
| `VSCP_ERROR_MEMORY` | 35 | Memory-related failure; some APIs also use this for a null event. |
| `VSCP_ERROR_USER` | 38 | The username login command failed. |
| `VSCP_ERROR_PASSWORD` | 39 | The password login command failed. |
| `VSCP_ERROR_CONNECTION` | 40 | The connection is unavailable or could not be established. |
| `VSCP_ERROR_INVALID_HANDLE` | 41 | The session handle is invalid. |
| `VSCP_ERROR_OPERATION_FAILED` | 42 | The requested operation failed. |
| `VSCP_ERROR_BUFFER_TO_SMALL` | 43 | The supplied output buffer is too small. The spelling is part of the API. |
| `VSCP_ERROR_STOPPED` | 47 | An operation stopped or the transport ended. |
| `VSCP_ERROR_INVALID_POINTER` | 48 | A required pointer is null or invalid. |
| `VSCP_ERROR_INVALID_SYNTAX` | 58 | Input syntax is invalid. |
| `VSCP_ERROR_INVALID_FRAME` | 63 | A frame, authentication tag, or protocol response is invalid. |
| `VSCP_ERROR_SIZE` | 64 | The requested size exceeds a supported limit. |
| `VSCP_ERROR_READ` | 66 | Reading or decoding an input failed; `VSCP_ERROR_READ_ERROR` is an alias. |
| `VSCP_ERROR_INVALID_FORMAT` | 69 | Data could not be converted to the required format. |

Some C++ register methods use `CANAL_ERROR_SUCCESS` (`0`),
`CANAL_ERROR_REGISTER` (`20`, a register reply value mismatch),
`CANAL_ERROR_TIMEOUT` (`32`), and `CANAL_ERROR_PARAMETER` (`34`). These are
CANAL names for the corresponding numeric values; do not assume every VSCP
and CANAL constant with the same spelling has the same value.

Error codes are not a substitute for validating inputs. Some legacy wrappers
dereference pointers without checking them, truncate output, or report only
a generic failure. Exceptions or invalid memory accesses are not guaranteed
to be converted into an error code. Consult the method's parameters and
documented limitations, and provide valid pointers and sufficiently sized
buffers.

[filename](./bottom_copyright.md ':include')
