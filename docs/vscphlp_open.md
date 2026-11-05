

```c
int vscphlp_open(long handle,
                 const char *host,
                 const char *username,
                 const char *password);
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### host

The server endpoint, including a port:

* `stcp://host:port` uses TLS.
* `tcp://host:port` or `host:port` uses plain, unencrypted TCP.

The server must be listening for the selected transport on that port. For TLS,
use a hostname matching the server certificate. IPv6 literals must be enclosed
in brackets, for example `[::1]:9598`.

These prefixes apply in the default auto-select mode. The per-session
[TLS configuration functions](vscphlp_tls.md) override transport selection:
`vscphlp_setTLSOptions` or `vscphlp_enableTLS(handle, 1)` forces TLS;
`vscphlp_enableTLS(handle, 0)` forces plain TCP. Configure trust and client
certificates with `vscphlp_setTLSOptions` before opening.

The legacy `ssl://` prefix and `:CERT:CA_CERT` suffixes are not supported.
See [TLS connections](tls.md) for trust configuration, limitations, and a
complete example.

#### username
Username to use as credentials for login to the remote VSCP daemon.

#### password
Password to use as credentials for login to the remote VSCP daemon.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible errors are
`VSCP_ERROR_INVALID_HANDLE` for an invalid session, `VSCP_ERROR_PARAMETER`
for an invalid endpoint, `VSCP_ERROR_CONNECTION` for a connection or TLS
failure, `VSCP_ERROR_TIMEOUT` for a timeout, and `VSCP_ERROR_USER` or
`VSCP_ERROR_PASSWORD` for login-command failures.

### Description
Connects and logs in to the TCP/IP interface of a VSCP server. The call waits
for connection and login to complete, so applications should avoid calling it
on a thread that must remain responsive.

Connections start in text mode. To read/write binary frames over the same
TCP or TLS link, negotiate [binary mode](binary_link.md) after login.

#### C example (TLS)

With an initialized `handle` and credentials supplied by the application:

```c
int result = vscphlp_open(handle, "stcp://server.example.com:9598",
                          username, password);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "VSCP connection failed (error %d)\n", result);
}
```

Port 9598 is an example; use the port configured for TLS on your server.
The [TLS guide](tls.md) includes a complete C program.

#### Python example (TLS)

With an initialized `handle` and credentials supplied by the application:

```python
import vscp
import vscphelper

result = vscphelper.open(handle, "stcp://server.example.com:9598",
                         username, password)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("VSCP connection failed (error {})".format(result))
```

See the [TLS guide](tls.md) for a complete program and per-session CA
configuration through `ctypes`; the Python wrapper does not yet expose the
new TLS setters.

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_openInterface](vscphlp_openinterface.md)  
[vscphlp_close](vscphlp_close.md)



[filename](./bottom_copyright.md ':include')