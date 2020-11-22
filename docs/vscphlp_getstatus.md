

```clike
const char * vscphlp_getStatus( long handle, 
                                VSCPStatus *pstatus )
```

```python
const char * pyvscphlp_getStatus( handle, status)
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pstatus (c/c++)
Pointer to [VSCPStatus](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) structure that will be filled with data after a successful call.

#### status (Python)
[VSCPStatus](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) structure that will hold status information after a successful call.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

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

```python
print "Get status"
status = VSCPStatus()
rv = pyvscphlp_getStatus( h1, status )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )
print "Channel status = %d" % status.channel_status 
print "Channel status = %d" % status.lasterrorcode 
print "Channel status = %d" % status.lasterrorsubcode 
```



[filename](./bottom_copyright.md ':include')