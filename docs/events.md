# Sending and receiving VSCP events

Use the event APIs when your application wants VSCP events rather than raw
protocol frames. For ordinary event handling, `vscpEventEx` is convenient:
its data is stored in the structure, so the caller does not need to manage a
separate data allocation.

## Choose a link mode

After creating a session and connecting with
[vscphlp_open](vscphlp_open.md) or
[vscphlp_openInterface](vscphlp_openinterface.md), choose how to receive:

* **Text mode:** call [vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)
  before using a blocking receive API. By default, commands are restricted
  while the receive loop is active; opt in to
  [single-channel mode](single_channel.md) to send events while receiving on
  the same TCP/TLS connection. Leave the loop with
  [vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md).
* **Binary mode:** negotiate with `vscphlp_doCmdBinary` after login. A text
  receive loop is not used; the event receive APIs handle binary event frames,
  confirmations, CRC validation, and acknowledgements. See
  [binary link frames](binary_link.md) for mode behavior and raw-frame access.

Serialize operations on a session. Event methods consume event frames from the
connection; do not interleave them with raw frame reads unless your application
dispatches the shared incoming stream deliberately.

## Send an event

`vscphlp_sendEventEx` sends an event and returns after writing it. In binary
mode it does not wait for a server confirmation. The event API processes
asynchronous confirmations while receiving; a successful send call alone does
not mean that a remote application acted on the event.

```c
#include <stdio.h>
#include <vscphelperlib.h>

int sendExampleEvent(long session)
{
    vscpEventEx event = {0};
    event.vscp_class = 10;
    event.vscp_type = 6;
    event.sizeData = 3;
    event.data[0] = 138;
    event.data[1] = 0;
    event.data[2] = 6;

    int result = vscphlp_sendEventEx(session, &event);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "sendEventEx failed (error %d)\n", result);
    }
    return result;
}
```

The caller retains ownership of `event`. See
[vscphlp_sendEventEx](vscphlp_sendeventex.md) for the Python example and the
pointer-based `vscphlp_sendEvent` alternative.

## Receive an event

Use `vscphlp_blockingReceiveEventEx` to wait for the next event, with a timeout
in milliseconds. In binary mode, no receive loop is required. In text mode,
enter the receive loop first. A timeout is not a connection failure; handle it
according to the application's polling or retry policy.

```c
#include <stdio.h>
#include <vscphelperlib.h>

int receiveExampleEvent(long session)
{
    vscpEventEx event = {0};
    int result = vscphlp_blockingReceiveEventEx(session, &event, 1000);
    if (result == VSCP_ERROR_TIMEOUT) {
        puts("No event arrived within one second");
        return result;
    }
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Event receive failed (error %d)\n", result);
        return result;
    }

    printf("Received class=%u type=%u with %u data bytes\n",
           event.vscp_class, event.vscp_type, event.sizeData);
    return VSCP_ERROR_SUCCESS;
}
```

This receives an event from the server, not necessarily a reply to the event
your application just sent. A `vscpEventEx` stores its data inline; use the
`vscpEvent` variants when you need dynamically sized event data and release
that data according to their ownership rules. See
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md) and
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md).

## Enable authenticated binary transport

Binary framing is unencrypted by default. To enable automatic authenticated
encryption, configure per-session keys **after connecting but before binary
negotiation**. Both peers must be provisioned with the same algorithm and
matching independent AES and HMAC keys. Use a secure key-management mechanism;
do not embed production keys in source code.

```c
int result = vscphlp_setBinarySecurity(
    session, VSCP_ENCRYPTION_AES256, aesKey, 32, hmacKey, 32);
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_doCmdBinary(session);
}
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "Could not enable authenticated binary mode (error %d)\n",
            result);
}
```

Once configured, `vscphlp_sendEventEx`, event receives, confirmations, and raw
binary I/O use authenticated encryption automatically. Continue to provide
ordinary plaintext events; do not encrypt them yourself. The Python wrapper
does not yet expose the binary-security setter, so Python applications needing
this option must use `ctypes` and a session created by that same shared
library. See [HMAC and frame encryption](frame_security.md) for key lengths,
transport constraints, security considerations, and C/C++/Python examples.

## Raw frames and language bindings

Use [the binary frame APIs](binary_link.md) for command/reply frames,
custom packet dispatch, or direct access to protocol bytes. Raw frame reads
and event receives consume the same stream, so choose one receive strategy or
implement a dispatcher rather than alternating calls blindly.

The official Python wrapper exposes the event methods shown in the individual
API references. The official Node.js binding does not currently expose the
connection or event helper APIs; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
