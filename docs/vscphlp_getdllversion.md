

```clike
const char * vscphlp_getDLLVersion( long handle, 
                            unsigned long *pdllversion )
```

```python
(rv,dllversion) = pyvscphlp_getDLLVersion( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pdllversion (c/c++)
Pointer to an unsigned long that will get driver version.

### Return Value

#### c/c++

Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

#### Python

Returned a tuple consisting of return value and dllversion. See above c/c++ version for rv return values.


### Description
Fetch the dll version from the VSCP server. This is the version of the interface. 

#### C example

```clike
// Get DLL version
unsigned long dllversion;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDLLVersion( handle2, &dllversion ) ) ) {
    printf( "Command success: vscphlp_getDLLVersion on channel 2\n" );
    printf( "DL(L) version is %08X\n", dllversion );
}
else {
    printf("\aCommand error: vscphlp_getDLLVersion on channel 2  Error code=%d\n", rv);
}
```

#### Python example

```python
print "Get DLL version"
(rv,dllversion) = pyvscphlp_getDLLVersion( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getStatus  Error code=%d' % rv )
print "DLL version = %d" % dllversion
```



[filename](./bottom_copyright.md ':include')