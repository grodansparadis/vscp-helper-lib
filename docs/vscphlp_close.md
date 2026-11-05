

```clike
int vscphlp_close( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`.

### Description
Close the interface. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle1 ) ) {
    printf("Closed successfully.\n");
 }
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)): This closes the connection; the session must still be closed.

```python
import vscp
import vscphelper

result = vscphelper.close(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("close failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_open](vscphlp_open.md)  
[vscphlp_openInterface](vscphlp_openinterface.md)  



[filename](./bottom_copyright.md ':include')