

```clike
int vscphlp_quitReceiveLoop( long handle )
```

```python
int vscphlp_quitReceiveLoop( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Quit the receive loop. 

#### C example

```clike
// Quit receiveloop
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_quitReceiveLoop( handle2 ) ) ) {
    printf( "Command success: vscphlp_quitReceiveLoop on channel 2\n" );
}
else {
    printf("Command error: vscphlp_quitReceiveLoop on channel 2  Error code=%d\n", rv);
}
```

#### Python example
mmm

```python
if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"
```

### See Also
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)  
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)  
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')