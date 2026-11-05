# Binary frames over the VSCP link protocol

The helper library supports binary VSCP-GBP frames on authenticated VSCP link
connections over **TCP and TLS**. Binary mode is negotiated with the server;
it is not a different endpoint prefix or a replacement for TLS.

Legacy framing is the default. To enable automatic AES-CBC encryption and
HMAC authentication, configure [binary frame security](frame_security.md)
before negotiation. That opt-in policy uses version-1 framing and requires
a compatible peer; it is retained across reconnects.

1. Create a session and configure any [TLS options](vscphlp_tls.md).
2. Connect and authenticate with [vscphlp_open](vscphlp_open.md) or
   [vscphlp_openInterface](vscphlp_openinterface.md).
3. Call `vscphlp_doCmdBinary` and check its result.
4. Send and receive binary frames on that same session.
5. Free received frames before unloading the library, then close the session.

The server must support the `BINARY` link command. A new connection starts in
text mode. Close and reopen to return to text mode; reconnecting does not
automatically reenter binary mode. Serialize calls using the same session.

## vscphlp_doCmdBinary

```c
int vscphlp_doCmdBinary(long handle);
```

Sends `BINARY\r\n` and switches only after a positive response. Calling it
again on an already binary connection succeeds without renegotiation.
It cannot be called while a text receive loop is active.

Negotiation uses the session's response timeout, configured with
[vscphlp_setResponseTimeout](vscphlp_setresponsetimeout.md).
A server rejection returns `VSCP_ERROR_ERROR` and leaves the session in text
mode. A timeout or malformed response closes the connection because the
server's mode is uncertain; there is no automatic plain-text retry.

`vscphlp_doCommand(handle, "BINARY\r\n")` also performs this transition, but
the dedicated function is recommended. After switching, ordinary text
commands such as `NOOP`, `VERS`, and `RCVLOOP` are not available.

## vscphlp_isBinaryMode

```c
int vscphlp_isBinaryMode(long handle, int *pBinaryMode);
```

On success, writes `1` for a connected binary session or `0` otherwise.
Passing `NULL` for `pBinaryMode` returns `VSCP_ERROR_PARAMETER`. Invalid
arguments leave the output unchanged.

## vscphlp_sendBinaryFrame

```c
int vscphlp_sendBinaryFrame(long handle,
                           const unsigned char *frame,
                           size_t frameSize);
```

Sends one complete frame. `frame` is caller-owned and must remain valid until
the call returns. In legacy mode its size must be from **1 through 65,535 bytes**.

The bytes include the packet type, payload, CRC, and any encryption IV required
by the frame format. Do **not** supply a TCP length prefix: the transport adds
the two-byte big-endian length. This raw API does not calculate or validate
the CRC, encrypt/decrypt frames, or interpret commands and replies in legacy mode.

With [automatic frame security](frame_security.md), instead supply a plaintext
frame of 5 through 4,048 bytes, including valid CRC and a clear encryption
nibble. The transport adds version-1 framing, encryption, random IV, and HMAC.
Do not pre-encrypt these frames.

Success means the transport accepted the write, not that the server accepted
the command or event. Receive and process any protocol confirmations yourself.
A failed write may have sent a partial packet; close and reconnect instead
of blindly resending on the same connection.

## vscphlp_receiveBinaryFrame

```c
int vscphlp_receiveBinaryFrame(long handle,
                              unsigned char **frame,
                              size_t *frameSize,
                              uint32_t timeout);
```

Receives one whole frame, strips the TCP length prefix, and allocates an
exact-sized result. On success, `*frame` points to `*frameSize` bytes owned by
the library. Release them with `vscphlp_freeBinaryFrame`, **not** the caller's
`free` or `delete[]`. Each result is independent of later receives and remains
valid after the session closes, until freed or the library is unloaded.

Both output pointers must be non-`NULL`. With valid output pointers, errors
set `*frame` to `NULL` and `*frameSize` to `0`. Free any previous result before
reusing its pointer variable; this function does not free an existing pointer.

`timeout` is a millisecond timeout for this call; `0` polls without waiting.
Timeouts preserve an incomplete prefix or payload so a later receive can
continue the same frame. Multiple frames arriving in one packet are returned
by separate calls. The returned bytes are opaque: encrypted frames, command
replies, and confirmations are not converted into events or acknowledged.

That describes legacy mode. With automatic frame security, the transport
validates the version-1 prefix and HMAC, decrypts, and validates padding/CRC
before returning plaintext. The plaintext encryption nibble is cleared.
Authentication or framing failure closes the connection and returns no frame.

## vscphlp_freeBinaryFrame

```c
void vscphlp_freeBinaryFrame(unsigned char *frame);
```

Releases a frame returned by `vscphlp_receiveBinaryFrame`. Passing `NULL` is
safe. Free each result exactly once, using the same loaded library.

## Return values

Except for the release function, these functions return `VSCP_ERROR_SUCCESS`
on success. Possible errors for each function are:

| Function | Error codes |
| --- | --- |
| `vscphlp_doCmdBinary` | `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_INVALID_FRAME` |
| `vscphlp_isBinaryMode` | `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_sendBinaryFrame` | `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`, `VSCP_ERROR_MEMORY` |
| `vscphlp_receiveBinaryFrame` | `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_STOPPED`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_MEMORY` |
| `vscphlp_freeBinaryFrame` | None: this function returns `void`. |

A receive timeout retains partial input. An invalid frame or authentication
failure closes the connection. A receive allocation failure also closes the
connection to avoid continuing after a potentially consumed, undeliverable
frame. See [error handling](error_handling.md) for code values and meanings.

## C example

With an already open session and a prepared protocol frame, this function
switches to binary mode, sends the frame, and reads the next frame. That frame
is **not necessarily the reply**: asynchronous events and confirmations may
also arrive, so a real application must dispatch frames by their packet type.

```c
#include <stdio.h>
#include <vscphelperlib.h>

int exchangeBinaryFrame(long session, const unsigned char *request, size_t requestSize)
{
    int result = vscphlp_doCmdBinary(session);
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }
    result = vscphlp_sendBinaryFrame(session, request, requestSize);
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }

    unsigned char *response = NULL;
    size_t responseSize = 0;
    result = vscphlp_receiveBinaryFrame(session, &response, &responseSize, 1000);
    if (result == VSCP_ERROR_SUCCESS) {
        printf("Received %zu bytes, packet type 0x%02x\n",
               responseSize, (unsigned int)response[0]);
    }
    vscphlp_freeBinaryFrame(response);
    return result;
}
```

The caller checks the returned error and closes the session when finished.
The [TLS guide](tls.md#c-example) shows session creation and authentication.

## C++ example

Use a custom `unique_ptr` deleter to release a received frame even if copying
it into a C++ container throws:

```cpp
#include <memory>
#include <vector>
#include <vscphelperlib.h>

int readBinaryFrame(long session, std::vector<unsigned char>& output)
{
    unsigned char* raw = nullptr;
    size_t size = 0;
    int result = vscphlp_receiveBinaryFrame(session, &raw, &size, 1000);
    std::unique_ptr<unsigned char, decltype(&vscphlp_freeBinaryFrame)>
        frame(raw, &vscphlp_freeBinaryFrame);
    if (result == VSCP_ERROR_SUCCESS) {
        output.assign(frame.get(), frame.get() + size);
    }
    return result;
}
```

This helper expects an open, negotiated binary session. To send from a
`std::vector<unsigned char> request`, pass `request.data()` and
`request.size()` to `vscphlp_sendBinaryFrame` and check its result.

## Python example

The updated Python wrapper exposes these operations directly. This example
expects an open session created by `vscphelper.newSession()`:

```python
import vscphelper


def check_result(result):
    if result != 0:  # VSCP_ERROR_SUCCESS
        raise RuntimeError("VSCP binary operation failed (error {})".format(result))


def exchange_binary_frame(session, request):
    check_result(vscphelper.doCmdBinary(session))
    check_result(vscphelper.sendBinaryFrame(session, request))
    result, response = vscphelper.receiveBinaryFrame(session, 1000)
    check_result(result)
    return response
```

Call `exchange_binary_frame(session, request_bytes)` with a complete prepared
frame, including CRC and any IV, but no TCP length prefix. The returned Python
`bytes` object owns a copy; the library's allocation has already been freed.
As with the C example, the next frame may be an asynchronous event rather than
a reply.

## Existing event APIs

After negotiation, `vscphlp_sendEvent`/`vscphlp_sendEventEx` send binary event
frames without waiting for confirmation. Frames are unencrypted in legacy
mode, or encrypted/authenticated according to the configured security policy.
The receive and
blocking-receive event APIs read asynchronous events without `RCVLOOP`,
process event confirmations, validate event CRCs, and acknowledge received
events. Nonblocking-named event receives use the session response timeout in
binary mode; blocking receives use their explicit timeout.

Use the raw frame API for arbitrary command/reply frames or manually encrypted
legacy frames. In automatic authenticated mode, raw I/O accepts/returns
plaintext and performs encryption/authentication itself.
Do not interleave raw and high-level event receives without a dispatch plan:
both consume the same ordered stream, and event receives reject unsupported
frame types rather than preserving them for a later raw receive.

## JavaScript availability

The updated [Node.js binding](bindings.md#nodejs) exposes `doCmdBinary`,
`sendBinaryFrame`, and `receiveBinaryFrame`. Received buffers are copied and
the native allocation is freed by the convenience method. See the
[authenticated binary example](frame_security.md#javascript-example).

[filename](./bottom_copyright.md ':include')
