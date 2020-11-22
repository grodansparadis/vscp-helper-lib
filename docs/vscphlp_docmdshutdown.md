

```clike
int vscphlp_doCmdShutDown( long handle )
```

```python
int vscphlp_doCmdShutDown( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Shut down the daemon. Needless to say this is a privileged command on the server side. 

#### C example

```clike
// Shut down the server
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_doCmdShutDown( handle2 ) ) ) {
    printf( "Command success: vscphlp_doCmdShutDownon channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_doCmdShutDownon channel 2  Error code=%d\n", rv);
}


```

#### Python example

```python
print "Shut down server"
rv = pyvscphlp_serverShutDown( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_serverShutDown  Error code=%d' % rv )
```



[filename](./bottom_copyright.md ':include')
