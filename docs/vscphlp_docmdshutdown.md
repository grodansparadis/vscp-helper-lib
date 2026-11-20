

```clike
int vscphlp_shutDownServer( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_ERROR`.

### Description
Shut down the daemon. This is a privileged command on the server side.

#### C availability

The older name `vscphlp_serverShutDown` is still exported as an alias for
older code; use `vscphlp_shutDownServer`.

```clike
int rv = vscphlp_shutDownServer(handle);
if (VSCP_ERROR_SUCCESS != rv) {
    fprintf(stderr, "shutDownServer failed (error %d)\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)),
this privileged command shuts down the server:

```python
import vscp
import vscphelper

result = vscphelper.serverShutDown(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("serverShutDown failed (error {})".format(result))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')
