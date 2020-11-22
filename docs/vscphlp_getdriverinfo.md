

```clike
const char * vscphlp_getDriverInfo( long handle, 
                                    char *pInfo, 
                                    size_t len )
```

```python
(rv,strdriverinfo) = vscphlp_getDriverInfo( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pInfo /c/c++)
A pointer to string with XML formatted information about the driver in use. This information (if available) can be used to help a user to configure the driver among other things.

#### len (c/c++)
Size of supplied buffer.

### Return Value

#### c/c++
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

#### Python
A touple consisting of the the return vale and the driver info string is returned. For return codes see c/c++ return value.


### Description
Get driver information. A buffer with size enough to hold the XML data must be supplied. For Python 32000 byte is used. 

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

```python
print "Get driver info string"
(rv,strdriverinfo) = pyvscphlp_getDriverInfo( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getDriverInfo  Error code=%d' % rv )
print "Driver info string = %s" % strdriverinfo
```



[filename](./bottom_copyright.md ':include')



