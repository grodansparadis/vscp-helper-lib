

```clike
int vscphlp_sendEvent( long handle, 
                        const vscpEvent *pEvent )
```

```python
int pyvscphlp_sendEvent( handle, event )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
The level I or level II event to send. The structure vscpEvent is defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) as 

```clike
  typedef struct  {	
  uint16_t crc;           // crc checksum - currently only used for UDP and RF
  uint8_t  *pdata;        // Pointer to data. Max 487 (512- 25) bytes
  // Following two are for daemon internal use
  uint32_t obid;          // Used by driver for channel info etc.
  // Time block - Always UTC time
  uint16_t year; 
  uint8_t month;          // 1-12
  uint8_t day;	          // 1-31
  uint8_t hour;           // 0-23
  uint8_t minute;         // 0-59
  uint8_t second;         // 0-59
  uint32_t timestamp;     // Relative time stamp for package in microseconds
  // CRC should be calculated from
  // here to end + datablock
  uint16_t head;          // Bit 16   GUID is IP v.6 address.
                          // bit 765  priority, Priority 0-7 where 0 is highest.
                          // bit 4 = hard coded, true for a hard coded device.
                          // bit 3 = Don't calculate CRC, false for CRC usage.
                          // bit 2 = Reserved.
                          // bit 1 = Reserved.
                          // bit 0 = Reserved.
  uint16_t vscp_class;    // VSCP class
  uint16_t vscp_type;     // VSCP type
  uint8_t  GUID[ 16 ];    // Node globally unique id LSB(0) -> MSB(15
  uint16_t sizeData;      // Number of valid data bytes		
} vscpEvent;
```

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Send a VSCP event. If the event is successfully sent or not it's the calling programs responsibility to deallocate the event. It's easy to forget to free the data part of an event created on the stack.

Note that there is no need to calculate a crc for the data it is only used as placeholder for more insecure transfer mechanisms. Also head, obid, the UTC timeblock and timestamp can be set to zero in most cases. The timeblock and timestamp will be set by the server interface when the event is received.

[pyvscphlp_sendEventEx](vscphlp_sendeventex.md) may a better alternative to use with Python as that version does not have dynamically allocated event data but one should be aware that it is more wasteful with memory. 

#### C example

```clike
// Send event on channel 1
vscpEvent e;
e.timestamp = 0                    // Let interface set timestamp
e.year = e.month = e.day = 0;      // Let interface set date
e.hour = e.minute = e.second = 0;  // Let interface set time
e.vscp_class = 10;  // CLASS1.MEASUREMENT
e.vscp_type = 6;    // Temperature
e.head = 0;
e.sizeData = 3;
e.pdata = new unsigned char[3];
e.pdata[0] = 138;  // Six degrees Celsius from sensor 2
e.pdata[1] = 0;
e.pdata[2] = 6;
memset(e.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID
 
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
    printf( "Command success: vscphlp_sendEvent on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_sendEvent on channel 1  Error code=%d\n", rv);
}
 
// The event must be deallocated
//delete pEvent->pdata;
//delete pEvent;
vscphlp_deleteVSCPevent( pEvent );  // This helper is the same as the above two commented lines 
```

#### Python example

```python
e = vscpEvent()
e.timestamp = 0
e.vscpclass = 20
e.vscptype = 9
e.sizedata = 3
p = (c_ubyte*3)()
p[0] = 11
p[1] = 22
p[2] = 33
e.pdata = cast(p, POINTER(c_ubyte))
 
print "------------------------------------------------------------------------"
print "command: sendEvent"
rv = pyvscphlp_sendEvent(h1,e)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: sendEvent  Error code=%d' % rv )
e.pdata = None 
```

### See Also
[vscphlp_sendEventEx](vscphlp_sendeventex.md)



[filename](./bottom_copyright.md ':include')