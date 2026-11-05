# vscphlp_setSingleChannelReceiveLoop

```c
int vscphlp_setSingleChannelReceiveLoop(long handle, int enable);
```

Enables or disables the single-channel **text** receive-loop mode for a
session. Set it before calling
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md). The setting defaults
to disabled. It can be selected before connecting or after connecting but
before entering the receive loop.

The mode uses one TCP/TLS connection for both asynchronous event reception and
commands that are supported inside the receive loop. Without this option,
commands other than leaving the loop are not available concurrently with
blocking event receives.

`enable` is false when zero and true for any nonzero value.
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible errors are
`VSCP_ERROR_INVALID_HANDLE` and `VSCP_ERROR_PARAMETER`; the latter is returned
if the receive loop or its reader is already active. The mode cannot be
changed until the receive loop has been exited.

## Supported commands and server requirements

While the single-channel receive loop is active, only `SEND`, `NOOP`, `CLRA`,
and `QUITLOOP` commands are supported. Other text commands return
`VSCP_ERROR_PARAMETER`. The server must support commands during `RCVLOOP` and
return an unambiguous command response. A bare `+OK` line is treated as a
receive-loop keepalive, not as the command's response; a server should return
a response such as `+OK - Success`. If a command response times out, the
connection may be closed to prevent a later reply from being mistaken for it.

This is a text-mode receive-loop option, not binary mode. It is opt-in and
does not change the default behavior.

## C++ example using the C API

With `session` already connected and `outgoing` initialized, receive on one
thread while sending on another. The library's reader thread continues
demultiplexing events and command replies on the same connection.

```cpp
#include <thread>
#include <vscphelperlib.h>

int sendWhileReceiving(long session,
                       const vscpEventEx& outgoing,
                       vscpEventEx& incoming)
{
    int result = vscphlp_setSingleChannelReceiveLoop(session, 1);
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }
    result = vscphlp_enterReceiveLoop(session);
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }

    int receiveResult = VSCP_ERROR_ERROR;
    std::thread receiver([&]() {
        receiveResult = vscphlp_blockingReceiveEventEx(session, &incoming, 2000);
    });
    const int sendResult = vscphlp_sendEventEx(session, &outgoing);
    receiver.join();

    const int quitResult = vscphlp_quitReceiveLoop(session);
    if (sendResult != VSCP_ERROR_SUCCESS) {
        return sendResult;
    }
    if (receiveResult != VSCP_ERROR_SUCCESS) {
        return receiveResult;
    }
    return quitResult;
}
```

The received event is not necessarily an echo of `outgoing`; a server may
deliver another event first. Serialize other operations on the session while
using this mode, except for the send/receive concurrency shown above.

## Query the setting

```c
int enabled = 0;
int result = vscphlp_isSingleChannelReceiveLoopEnabled(session, &enabled);
if (result == VSCP_ERROR_SUCCESS) {
    /* enabled is 1 when configured, otherwise 0. */
}
```

The query reports the configured option, not whether the session is currently
connected or in its receive loop. It returns `VSCP_ERROR_INVALID_HANDLE` for
an invalid session or `VSCP_ERROR_PARAMETER` if `pEnabled` is null.

The official Python and Node.js bindings do not expose these new functions.
Python can call them through `ctypes`; Node.js applications can use a native
FFI such as Koffi. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
