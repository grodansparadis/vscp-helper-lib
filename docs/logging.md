# Library logging

The C API configures a private, synchronous spdlog logger for the underlying
TCP/TLS transport and helper diagnostics. No spdlog pointers, C++ objects, or
callbacks cross the C ABI. The application does not need to link spdlog.
The library never changes spdlog's default logger, registry, global levels,
thread pool, or shutdown state.

Before configuration, existing diagnostics still go to stderr in their
original format. Configuration is library-wide, not per session, and applies
immediately to both existing and future sessions.

## Console, file, or both

```c
#include <stdio.h>
#include <vscphelperlib.h>

/* stderr at WARN and above; append to a rotating file at DEBUG and above.
 * Rotate around 5 MiB, keeping three archives plus the active file.
 */
int result = vscphlp_configureLogging(
    VSCPHELPER_LOG_LEVEL_WARN,
    VSCPHELPER_LOG_LEVEL_DEBUG,
    "/path/owned/by/application/vscp.log",
    5u * 1024u * 1024u,
    3);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "%s\n", vscphlp_getLastLoggingError());
}
```

Use an application-controlled path appropriate to your platform. Configure
before opening sessions when early connection/TLS diagnostics are needed.

For console only:

```c
int result = vscphlp_configureLogging(
    VSCPHELPER_LOG_LEVEL_ERROR, VSCPHELPER_LOG_LEVEL_OFF, NULL, 0, 0);
```

For file only:

```c
int result = vscphlp_configureLogging(
    VSCPHELPER_LOG_LEVEL_OFF, VSCPHELPER_LOG_LEVEL_ERROR, "vscp.log",
    5u * 1024u * 1024u, 3);
```

All calls return a VSCP error code; check each result. Thresholds are:

| Constant | Value |
| --- | --- |
| `VSCPHELPER_LOG_LEVEL_TRACE` | 0 |
| `VSCPHELPER_LOG_LEVEL_DEBUG` | 1 |
| `VSCPHELPER_LOG_LEVEL_INFO` | 2 |
| `VSCPHELPER_LOG_LEVEL_WARN` | 3 |
| `VSCPHELPER_LOG_LEVEL_ERROR` | 4 |
| `VSCPHELPER_LOG_LEVEL_CRITICAL` | 5 |
| `VSCPHELPER_LOG_LEVEL_OFF` | 6 |

Each sink has its own threshold; OFF disables that sink. Current underlying
diagnostics are ERROR messages. Selecting DEBUG/TRACE does not add packet,
command, credential, or payload dumps.

## Rotation, flushing, and disabling

File logging appends rather than truncates. `maxFileSize` must be positive
and `maxFiles` must be 1 through 200000 when the file sink is enabled.
These arguments and `filePath` are ignored when the file sink is OFF.
Rotation creates names such as `vscp.1.log`, `vscp.2.log`, etc.
The byte threshold is a rotation trigger, not a strict cap: a single message
larger than the threshold is preserved in full. Parent directories may be
created by spdlog.

`vscphlp_flushLogging()` flushes configured sinks and returns a VSCP error
code. ERROR messages also flush automatically. Flushing is not an `fsync`
durability guarantee.

`vscphlp_disableLogging()` disables both sinks and releases the file sink.
It is also valid before any configuration. Re-enable with another
`vscphlp_configureLogging` call; closing a session does not disable logging.

Configuration, emission, flushing, and disabling are serialized. A successful
disable returns after earlier emissions finish; logging creates no background
threads. Slow disk/console writes can therefore delay library calls.
Do not unload the library while sessions or library calls are still active.

## Errors and safety

Invalid arguments return `VSCP_ERROR_PARAMETER`. File-open, allocation, and
other logging failures return `VSCP_ERROR_ERROR`. Failed configuration leaves
the previous logger active, although attempts to open a new file may create
files/directories. Logging failures are always reported to stderr, including
when console logging is disabled, rather than silently discarded.

`vscphlp_getLastLoggingError()` returns a thread-local, library-owned diagnostic
(up to 511 bytes). Do not free it. It remains valid until the same thread's
next configure/disable/flush call or logging failure. Successful configuration,
disabling, or flushing clears it. A runtime sink failure is reported on the
emitting thread; it does not change a transport operation's return code or
terminate the application.

Use trusted paths and restrictive directory permissions; file permissions
follow the process/platform defaults. Do not share the same rotating path
between processes or unrelated loggers. Rotation is not a cross-process lock.
Hostnames and certificate paths can appear in diagnostics. Credentials, key
material, and event payloads are not logged.

This logger routes diagnostics in the sources compiled into this library.
It does not intercept arbitrary stdout/stderr output from externally loaded
CANAL drivers, OpenSSL, or the application. Python/Node wrappers do not yet
expose these functions directly; C-compatible foreign-function calls can use
them on the same loaded helper library.
