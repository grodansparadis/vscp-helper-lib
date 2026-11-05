

```clike
int vscphlp_getDLLVersion( long handle,
                          unsigned long *pdllversion )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pdllversion (c/c++)
Pointer to an unsigned long that will receive the driver version.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`.
The version pointer must be valid; it is not checked for null.

#### Python

Returns a tuple containing the return value and dllversion. See the C/C++ return values above for rv.

### Description
Fetch the DLL version from the VSCP server. This is the interface version.

#### C example

```clike
// Get DLL version
unsigned long dllversion;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDLLVersion( handle2, &dllversion ) ) ) {
    printf( "Command success: vscphlp_getDLLVersion on channel 2\n" );
    printf( "DLL version is %08lX\n", dllversion );
}
else {
    printf("\aCommand error: vscphlp_getDLLVersion on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result, version = vscphelper.getDLLVersion(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getDLLVersion failed (error {})".format(result))
print("DLL version: {}".format(version.value))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')