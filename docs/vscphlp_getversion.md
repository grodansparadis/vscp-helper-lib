

```clike
unsigned long vscphlp_getVersion( long handle, 
                                    unsigned char *pMajorVer,
                                    unsigned char *pMinorVer,
                                    unsigned char *pSubMinorVer )
```

```python
unsigned long pyvscphlp_getVersion( handle, 
                                      MajorVer,
                                      MinorVer,
                                      SubMinorVer )
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
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

### Description
Get the version of the remote VSCP server. 

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

```python
print "command: Get sever version"
(rv,v1,v2,v3) = pyvscphlp_getVersion(h1)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''pyvscphlp_getVersion''  Error code=%d' % rv )
print "Server version = %d.%d.%d" % (v1.value,v2.value,v3.value)
```




[filename](./bottom_copyright.md ':include')