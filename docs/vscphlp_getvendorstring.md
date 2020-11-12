

```clike
int vscphlp_getVendorString( long handle, 
                                char *pVendor, 
                                size_t len )
```

```python
(rv,strversion) pyvscphlp_getVendorString( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pVendor (c/c++)
Pointer to a string that will receive vendor information.

#### len (c/c++)
Size of supplied buffer.


### Return Value

#### c/c++
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

#### Python
A tuple that consist of the return value (see c/c++ version) and the vendorstirng is returned. 

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

```python
print "Get vendor string"
(rv,strvendor) = pyvscphlp_getVendorString( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getVendorString  Error code=%d' % rv )
print "Vendor string = %s" % strvendor
```

### See Also
[xxx](xxx.md)



[filename](./bottom_copyright.md ':include')
