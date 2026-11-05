

```clike
int vscphlp_noop( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`.

### Description
Use this command to test the connection. It sends a command over the interface and checks the result.

#### C example

```clike
// NOOP on handle1
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle1 ) ) ) {
    printf( "Command success: vscphlp_noop on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_noop on channel 1  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result = vscphelper.noop(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("noop failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')