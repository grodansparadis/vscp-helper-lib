

```clike
int vscphlp_setFilter( long handle, 
                        const vscpEventFilter *pFilter )
```

```python
int pyvscphlp_setFilter( handle, filter )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pFilter (c/c++)
Pointer to a VSCP filter structure that should be applied to the sending stream on the server. The VSCP filter structure is defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) and has the following format 

```clike
typedef struct  {
  uint8_t filter_priority;        // Priority 
  uint8_t mask_priority;
 
  uint16_t filter_class;          // VSCP class
  uint16_t mask_class;
 
  uint16_t filter_type;           // VSCP type
  uint16_t mask_type;
 
  uint8_t filter_GUID[ 16 ];      // Node address MSB -> LSB, LSB is node nickname id
  uint8_t mask_GUID[ 16 ];        //		when interfacing the VSCP daemon.
 
} vscpEventFilter;
```

#### filter (Python)

VSCP filter structure that should be applied to the sending stream on the server. 

```python
# Receiving event filter
class vscpEventFilter(Structure):
    _fields_ = [("filter_priority", c_ubyte),
                ("mask_priority", c_ubyte),
                ("filter_class", c_ubyte),
                ("mask_class", c_ubyte),
                ("filter_type", c_ubyte),
                ("mask_type", c_ubyte),
                ("filter_guid", c_ubyte * 16),
                ("mask_guid", c_ubyte * 16) ]
 
    def __init__(self):
        self.filter_priority = 0
        self.mask_priority = 0
        self.filter_class = 0
        self.mask_class = 0
        self.filter_type = 0
        self.mask_type = 0
        for i in (0,15):
            self.filter_guid[i] = 0
        for i in (0,15):
            self.mask_guid[i] = 0
```

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Set VSCP filter/mask.

#### C example
Set filter.

```clike
// Set VSCP filter
vscpEventFilter filter;
filter.filter_class = 22;   // We are interested in events with VSCP class=22 only
filter.mask_class = 0xffff;
filter.mask_type = 0;               // Any type
filter.mask_priority = 0;           // Any priority
memset( filter.mask_GUID, 0, 16 );  // Any GUID
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
    printf( "Command success: vscphlp_setFilter on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_setFilter on channel 2  Error code=%d\n", rv);
}
```

#### C example
Clear filter

```clike
// Clear the filter
memset( &filter, 0, sizeof( vscpEventFilter ) );
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
    printf( "Command success: vscphlp_setFilter on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_setFilter on channel 2  Error code=%d\n", rv);
}
```

#### Python example
set filter

```python


# Set filter
filter = vscpEventFilter()
filter.mask_class = 0xFFFF                      # All bits should be checked
filter.filter_class = VSCP_CLASS1_MEASUREMENT   # Only CLASS1.MEASUREMENT received
rv = pyvscphlp_setFilter( h1, filter )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )
 
print "Enter receive loop. Will lock channel for 60 seconds or unit CLASS1.MEASUREMENT event received"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
 
    cnt = 0   
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        ex = vscpEventEx()
        rv = pyvscphlp_blockingReceiveEventEx(h1,ex, 1000 )
 
        if VSCP_ERROR_SUCCESS == rv: 
            ex.dump()
        else: 
            print "Waiting for CLASS1.MEASUREMENT event in blocking mode rv=%d" % rv
 
        cnt += 1
        if ( cnt > 60 ):
            print "Not received within 60 seconds. We quit!"
            break
 
    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    
 
else:    
    print "Failed to enter receive loop!"


```

#### Python example
Clear filter

```python
# Clear filter
print "Clear filter"
filter = vscpEventFilter()
filter.clear()
rv = pyvscphlp_setFilter( h1, filter )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )
```





[filename](./bottom_copyright.md ':include')