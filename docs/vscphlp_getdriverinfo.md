

```clike
int vscphlp_getDriverInfo( long handle,
                           char *pInfo,
                           size_t len )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pInfo (C/C++)
Pointer to a string containing XML-formatted information about the driver in use. If available, this information can help users configure the driver.

#### len (c/c++)
Size of the supplied buffer.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`.

Truncation is not reported; the output may lack a terminating null byte if the buffer is too
small.

#### Python
Returns a tuple containing the return value and the driver information string. See the C/C++ return values for the return codes.

### Description
Get driver information. Supply a buffer large enough to hold the XML data. For Python, 32000 bytes are used.

#### C example

```clike
// Get driver info
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDriverInfo( handle2, buf, sizeof(buf) ) ) ) {
    printf( "Command success: vscphlp_getDriverInfo on channel 2\n" );
    printf( "Driver info = \"%s\"\n", buf );
}
else {
    printf("\aCommand error: vscphlp_getDriverInfo on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result, driver_info = vscphelper.getDriverInfo(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getDriverInfo failed (error {})".format(result))
print("Driver information: {}".format(driver_info))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')

