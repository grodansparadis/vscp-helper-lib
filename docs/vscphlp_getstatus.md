

```clike
int vscphlp_getStatus( long handle,
                       VSCPStatus *pstatus )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pstatus (c/c++)
Pointer to [VSCPStatus](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) structure that will be filled with data after a successful call.

#### status (Python)
[VSCPStatus](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) structure that will hold status information after a successful call.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_GENERIC`.
The status pointer must be valid; it is not checked for null. The output
may be modified even when an error is returned; use it only on success.

### Description
Fetch the status structure from the VSCP server. 

#### C example

```clike
VSCPStatus status;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatus( handle2, &status ) ) ) {
    printf( "Command success: vscphlp_getStatus on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_getStatus on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

status = vscp.VSCPStatus()

result = vscphelper.getStatus(handle, status)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getStatus failed (error {})".format(result))
print("Last error: {}".format(status.lasterrorcode))
print("Last error subcode: {}".format(status.lasterrorsubcode))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')