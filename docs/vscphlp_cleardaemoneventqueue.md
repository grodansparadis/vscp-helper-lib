
```clike
int vscphlp_clearDaemonEventQueue( long handle )
```

```python
int pyvscphlp_clearDaemonEventQueue( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
VSCP_ERROR_SUCCESS if the VSCP daemon cleared the queue and VSCP_ERROR_ERROR. if not or no response is received before the timeout expires. VSCP_ERROR_CONNECTION is returned if the communication channel is not open. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
Clear the receiving side (to us) event queue on the VSCP daemon. 

#### C example

```clike
// Clear event queue on VSCP daemon on handle1
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_clearDaemonEventQueue( handle1 ) ) ) {
    printf( "Command success: vscphlp_clearDaemonEventQueueon channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_clearDaemonEventQueueon channel 1  Error code=%d\n", rv);
}
```

#### Python example
```python
print "Empty VSCP server queue"
rv = pyvscphlp_clearDaemonEventQueue(h1)
if VSCP_ERROR_SUCCESS == rv:
    print "Server queue now is empty"
else:
    print "Failed to clear server queue", rv
```




[filename](./bottom_copyright.md ':include')