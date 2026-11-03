

```clike
int vscphlp_getVersion( long handle,
                        unsigned char *pMajorVer,
                        unsigned char *pMinorVer,
                        unsigned char *pSubMinorVer )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### MajorVer
VSCP server major version.

#### MinorVer
VSCP server minor version.

#### SubMinorVer
VSCP server sub minor version.

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Get the version of the remote VSCP server. To get the helper library's own
four-part version, use [vscphlp_getVersionString](vscphlp_getversionstring.md)
instead.

#### C example

```clike
// Get server version
unsigned char v1,v2,v3;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle2, &v1, &v2, &v3 ) ) ) {
    printf( "Command success: vscphlp_getVersion on channel 2\n" );
    printf( "Version for VSCP daemon on channel 2 is %d.%d.%d\n", v1,v2,v3 );
}
else {
    printf("\aCommand error: vscphlp_getVersion on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result, major, minor, subminor = vscphelper.getVersion(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getVersion failed (error {})".format(result))
print("Server version: {}.{}.{}".format(major.value, minor.value, subminor.value))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')