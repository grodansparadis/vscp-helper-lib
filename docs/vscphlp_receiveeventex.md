

```clike
int vscphlp_receiveEventEx( long handle, 
                            vscpEventEx *pEventEx )
```

```python
int pyvscphlp_receiveEventEx( handle, eventex )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).e

#### pEventEx
Pointer to VSCP ex data structure that will receive the event.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Receive a VSCP event. The difference to vscphlp_receiveEvent is that the vscphlp_vscpEventEx structure have the data in the structure and vscpEvent that have a pointer to the data in the structure. 

#### C example

```clike
// Read event  -  Use vscpEventEx
vscpEventEx ex2;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEventEx( handle2, &ex2 ) ) ) {
    printf( "Command success: vscphlp_receiveEventEx on handle2\n" );
    printf( "VSCP class=%d VSCP type=%d sizeData=%d\n", 
                    ex2.vscp_class,
                    ex2.vscp_type,
                    ex2.sizeData );
    printf("Data = ");
    for ( int i=0; i<ex2.sizeData; i++ ) {
        printf("%d ", ex2.data[i] );
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_receiveEventEx on channel 2  Error code=%d\n", rv);
}
```

#### Python example

```python
print "Waiting for incoming data..."
 
cntAvailable = ctypes.c_uint(0)
while cntAvailable.value==0:
    print 'Still waiting...'
    time.sleep(1)
    pyvscphlp_isDataAvailable(h1,cntAvailable)
 
print '%d event(s) is available' % cntAvailable.value
 
for i in range(0,cntAvailable.value):
    ex = vscpEventEx()
    if VSCP_ERROR_SUCCESS == pyvscphlp_receiveEventEx(h1,ex):
        ex.dump()
```

### See Also
[vscphlp_receiveEvent](vscphlp_receiveevent.md)



[filename](./bottom_copyright.md ':include')