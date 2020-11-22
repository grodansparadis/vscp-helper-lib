

```clike
int vscphlp_enterReceiveLoop( long handle )
```

```python
int pyvscphlp_enterReceiveLoop( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Enter the receive loop. After this command only vscphlp_quitReceiveLoop and vscphlp_Close and the blocking receive methods [vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md) / [vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md) is available. The intent of the command is for threaded communication where one thread is sending events and one is receiving events and can use blocking calls to do so. 

#### C example
```clike
// Enter receiveloop
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_enterReceiveLoop( handle2 ) ) ) {
    printf( "Command success: vscphlp_enterReceiveLoop on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_enterReceiveLoop on channel 2  Error code=%d\n", rv);
}
```

#### Python example

```python
print "Enter receive loop. Will lock channel on just receiving events"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
    print "Now blocking receive - will take forever if no events is received"
 
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        ex = vscpEventEx()
        rv = pyvscphlp_blockingReceiveEventEx(h1,ex, 1000 )
 
        if VSCP_ERROR_SUCCESS == rv: 
            ex.dump()
        else:
            if VSCP_ERROR_TIMEOUT != rv:
                print "Blocking receive failed with error code = %d" % rv 
                break;
            print "Waiting for event in blocking mode rv=%d" % rv
 
    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    
 
else:    
    print "Failed to enter receive loop!"
```

### See Also
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)  
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)  
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')