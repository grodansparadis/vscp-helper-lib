

```clike
int vscphlp_blockingReceiveEvent( long handle, 
                                    vscpEvent *Event, 
                                    unsigned long timeout )
```

```python
int vscphlp_blockingReceiveEvent( handle, event, timeout )
```

### Parameters
#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
Pointer to event that will get event data after a sucessful call. See [vscphlp_receiveEvent](vscphlp_receiveevent.md) for a description.

#### timeout
This is the max time to block. Zero means wait forever.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while NOT in a receive loop (see vscphlp_enterReceiveLoop. 

### Description
Blocking receive of one VSCP event from the remote VSCP server. Data for the event is dynamically allocated and must be deleted by the application.

For Python use of [pyvscphlp_receiveEventEx](pyvscphlp_receiveeventex.md) may be simpler as there id no dynamically allocated data to take care off. 

#### C example

```clike
// Enter receiveloop
pEvent = new vscpEvent;
pEvent->pdata = NULL;   // A must for a successful delete
if ( VSCP_ERROR_SUCCESS == vscphlp_blockingReceiveEvent( handle2, pEvent ) ) {
    printf( "Command success: vscphlp_blockingReceiveEvent on channel 2\n" );
    printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        pEvent->vscp_class,
                        pEvent->vscp_type,
                        pEvent->sizeData );
    if ( pEvent->sizeData && ( NULL != pEvent->pdata ) ) {
        printf("Data = ");
        for ( int i=0; i<ex2.sizeData; i++ ) {
            printf("%d ", ex2.data[i] );
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
        e = vscpEvent()
        rv = pyvscphlp_blockingReceiveEvent(h1,e, 1000 )
 
        if VSCP_ERROR_SUCCESS == rv: 
            e.dump()
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
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')