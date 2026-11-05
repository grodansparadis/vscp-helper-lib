

```clike
int vscphlp_openInterface( long handle,
                            const char *interface, 
                            unsigned long flags )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### interface
The endpoint and credentials, separated by semicolons:

    stcp://host:port;username;password

The `stcp://` prefix selects TLS. Use `tcp://host:port;username;password` or
`host:port;username;password` for plain, unencrypted TCP. The server must
listen for the selected transport on that port.

These prefixes apply in the default auto-select mode.
[Per-session TLS settings](vscphlp_tls.md) apply to this function too:
`vscphlp_setTLSOptions` forces TLS and supplies trust/client credentials;
an explicit forced mode overrides the endpoint prefix.

The interface string contains credentials; keep it private and do not log it.
There is no escaping for semicolons in the username or password. If either
contains a semicolon, use [vscphlp_open](vscphlp_open.md) with separate
arguments instead.

See [TLS connections](tls.md) for server verification, CA setup, and examples.

#### flags
Currently unused; pass `0`.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_USER`, `VSCP_ERROR_PASSWORD`.
See [vscphlp_open](vscphlp_open.md#return-value) for the corresponding causes.

### Description
Opens a session to the TCP/IP interface of a VSCP server.
Connections start in text mode; negotiate [binary mode](binary_link.md)
after login to exchange binary frames over the same TCP or TLS link.

#### C example

With an initialized `handle` and an `interface_string` constructed using
credentials supplied by the application:

```c
int result = vscphlp_openInterface(handle, interface_string, 0);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "VSCP connection failed (error %d)\n", result);
}
```

#### Python example

With an initialized `handle` and an `interface_string` constructed using
credentials supplied by the application:

```python
import vscp
import vscphelper

result = vscphelper.openInterface(handle, interface_string, 0)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("VSCP connection failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_open](vscphlp_open.md)  
[vscphlp_close](vscphlp_close.md)



[filename](./bottom_copyright.md ':include')