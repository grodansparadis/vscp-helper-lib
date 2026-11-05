

```clike
int vscphlp_getVendorString( long handle, 
                                char *pVendor, 
                                size_t len )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pVendor (c/c++)
Pointer to a string that will receive vendor information.

#### len (c/c++)
Size of the supplied buffer.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`.

Truncation is not reported; the output may lack a terminating null byte if the buffer is too
small.

#### Python
Returns a tuple containing the return value (see the C/C++ version) and the vendor string.

### Description
Fetch the vendor string from the driver. 

#### C example

```clike
// Get vendor string
char buf[120];
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVendorString( handle2, buf, sizeof(buf) ) ) ) {
    printf( "Command success: vscphlp_getVendorString on channel 2\n" );
    printf( "Vendorstring = \"%s\"\n", buf );
}
else {
    printf("\aCommand error: vscphlp_getVendorString on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result, vendor = vscphelper.getVendorString(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getVendorString failed (error {})".format(result))
print("Vendor: {}".format(vendor))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getDriverInfo](vscphlp_getdriverinfo.md)



[filename](./bottom_copyright.md ':include')
