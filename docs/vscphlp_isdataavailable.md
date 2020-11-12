

```clike
int vscphlp_isDataAvailable( long handle, 
                                unsigned int *pCount )
```

```python
int pyvscphlp_isDataAvailable( handle, count )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### pCount (c/c++)
Pointer to variable that gets the number of events waiting in the queue on a successful call.

### count (Python)
Variable that gets the number of events waiting in the queue on a successful call.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Check the number of events (if any) that are available in the remote input queue. 

#### C example

```clike
// Check queue for events
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
     printf( "Command success: vscphlp_isDataAvailable on handle2\n" );
    printf( "count = %d\n", count );
        if ( 3 == count ) printf("Which is correct.\n");
}
else {
    printf("\aCommand error: vscphlp_isDataAvailable on channel 2  Error code=%d\n", rv);
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



[filename](./bottom_copyright.md ':include')