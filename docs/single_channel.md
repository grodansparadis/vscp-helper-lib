# Single-channel TCP/IP receive loop

In the default text receive loop, the connection is dedicated to receiving
events, so other commands cannot be sent concurrently with blocking receives.
Opt-in single-channel mode starts an internal reader that separates incoming
events from command replies on the same TCP/TLS connection. This lets one
thread block waiting for events while another sends events on the same
session.

The server must allow commands while `RCVLOOP` is active. The feature is
specific to the **text** receive loop; binary mode is a separate option. It
does not alter the default behavior.

## Enable and enter the receive loop

Configure the session after creating it and before
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md). The session may
already be connected, but the setting cannot be changed once the receive loop
or its reader is active.

```c
long session = vscphlp_newSession();
if (session <= 0) {
    /* Handle session creation failure. */
}

int result = vscphlp_setSingleChannelReceiveLoop(session, 1);
if (result != VSCP_ERROR_SUCCESS) {
    /* Handle configuration failure. */
    vscphlp_closeSession(session);
}
```

Open the session with [vscphlp_open](vscphlp_open.md) or
[vscphlp_openInterface](vscphlp_openinterface.md), then call
`vscphlp_enterReceiveLoop`. Configure TLS as described in the
[TLS guide](tls.md) before opening a TLS connection. Check each return code;
see [return values and error handling](error_handling.md).

## Commands supported during the loop

Only `SEND`, `NOOP`, `CLRA`, and `QUITLOOP` are supported while the
single-channel receive loop is active. Other text commands fail with
`VSCP_ERROR_PARAMETER`. A server's bare `+OK` is treated as a receive-loop
keepalive, not a command response. Servers must return a distinct response,
such as `+OK - Success`, for commands issued during the loop. If a response
times out, the connection can be closed to avoid confusing a late reply with
a later command.

## Send while receiving

After connecting and entering the loop, a worker can block on
`vscphlp_blockingReceiveEventEx` while another thread sends with
`vscphlp_sendEventEx`. The internal reader services the one socket and queues
events for the blocking receive call.

```cpp
#include <thread>
#include <vscphelperlib.h>

// session is connected, single-channel mode is enabled, and RCVLOOP is active.
vscpEventEx outgoing = {};
outgoing.vscp_class = 10;
outgoing.vscp_type = 6;
outgoing.sizeData = 2;
outgoing.data[0] = 4;
outgoing.data[1] = 5;

vscpEventEx incoming = {};
int receiveResult = VSCP_ERROR_ERROR;
std::thread receiver([&]() {
    receiveResult = vscphlp_blockingReceiveEventEx(session, &incoming, 2000);
});
int sendResult = vscphlp_sendEventEx(session, &outgoing);
receiver.join();

if (sendResult != VSCP_ERROR_SUCCESS ||
    receiveResult != VSCP_ERROR_SUCCESS) {
    // Handle either error before continuing.
}
```

The received event may not be the event just sent. Call
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md) to leave the loop, then
close the connection/session when finished. Do not concurrently make other
calls on the same session beyond the send/receive pattern shown above.

See [vscphlp_setSingleChannelReceiveLoop](vscphlp_setsinglechannelreceiveloop.md)
and [vscphlp_isSingleChannelReceiveLoopEnabled](vscphlp_issinglechannelreceiveloopenabled.md)
for API details.

[filename](./bottom_copyright.md ':include')
