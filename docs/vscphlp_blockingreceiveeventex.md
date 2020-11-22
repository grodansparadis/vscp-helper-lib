
```clike
int vscphlp_blockingReceiveEventEx( long handle, 
                                vscpEventEx *Eventex, 
                                unsigned long timeout )
```

```python
int pyvscphlp_blockingReceiveEventEx( handle, eventex, timeout )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent (c/c++)
Pointer to event that will get event data after a sucessfull call. See vscphlp_receiveEvent for a description.

#### pEvent (Python)
Event that will get event data after a sucessfull call. See vscphlp_receiveEvent for a description.
timeout

This is the max time to block. Zero means wait forever.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Blocking receive one VSCP event from the remote VSCP server if there is one available in the server queue. 

#### C example

```clike
vscpEventEx ex;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_blockingReceiveEventEx( handle2, &ex ) ) {
    printf( "Command success: vscphlp_blockingReceiveEventEx on channel 2\n" );
    printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        ex.vscp_class,
                        ex.vscp_type,
                        ex.sizeData );
    if ( ex.sizeData ) {
        printf("Data = ");
        for ( int i=0; i<ex.sizeData; i++ ) {
            printf("%d ", ex.data[i] );
        }
        printf("\n");
    }
}
vscphlp_deleteVSCPevent( pEvent );
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
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)   
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)   
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)



[filename](./bottom_copyright.md ':include')