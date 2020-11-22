
```clike
int vscphlp_sendEventEx( long handle, 
                            const vscpEventEx *pEvent )
```

```python
int pyvscphlp_sendEventEx( handle, eventex )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent

The level I or level II event to send. The structure *vscpEventEx* is defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) as 

```clike
  typedef struct {	
  uint16_t crc;                   // crc checksum
 
  // Following two are for daemon internal use
  uint32_t obid;                  // Used by driver for channel info etc.
 
  // Time block - Always UTC time
  uint16_t year; 
  uint8_t month;                  // 1-12
  uint8_t day;	                  // 1-31
  uint8_t hour;                   // 0-23
  uint8_t minute;                 // 0-59
  uint8_t second;                 // 0-59  
 
  uint32_t timestamp;             // Relative time stamp for package in microseconds.
 
  // CRC should be calculated from
  // here to end + datablock
  uint8_t head;                   // bit 7,6,5 prioriy => Priority 0-7 where 0 is highest.
                                  // bit 4 = hardcoded, true for a hardcoded device.
                                  // bit 3 = Dont calculate CRC, Set to zero to use CRC.
                                  // bit 2 = Set means this is CAN message.
                                  // bit 1 = If bit 2 is set; Extended CAN message if set
                                  // bit 0 = If bit 2 is set: Remote frame if set
  uint16_t vscp_class;            // VSCP class
  uint16_t vscp_type;             // VSCP type
  uint8_t  GUID[ 16 ];            // Node globally unique id MSB(15) -> LSB(0)
  uint16_t sizeData;              // Number of valid data bytes		
 
  uint8_t  data[VSCP_MAX_DATA];   // Pointer to data. Max 487 (512- 25) bytes
 
} vscpEventEx;
```

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Send a VSCP event. If the event is not successfully sent it's the calling programs responsibility to deallocate the event.

Note that there is no need to calculate a crc for the data it is only used as placeholder for more insecure transfer mechanisms. Also head, obid, the UTC timeblock and timestamp can be set to zero in most cases. The timeblock and timestamp will be set by the server interface when the event is received. 

#### C example

```clike
vscpEventEx ex;
e.timestamp = 0                    // Let interface set timestamp
e.year = e.month = e.day = 0;      // Let interface set date
e.hour = e.minute = e.second = 0;  // Let interface set time    
ex.vscp_class = 10; // CLASS1.MEASUREMENT
ex.vscp_type = 6;   // Temperature
ex.head = 0;
ex.sizeData = 3;
ex.data[0] = 138;   // 6 degrees Celsius from sensor 2
ex.data[1] = 0;
ex.data[2] = 6;
memset(ex.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID
 
// Send event again
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &ex ) ) ) {
    printf( "Command success: vscphlp_sendEventEx on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_sendEventEx on channel 1  Error code=%d\n", rv);
}
```

#### Python example

```python
ex = vscpEventEx()
ex.timestamp = 0
ex.vscpclass = 10
ex.vscptype = 99
ex.sizedata = 3
ex.data[0] = 1
ex.data[1] = 2
ex.data[2] = 3
print "command: sendEventEx"
rv = pyvscphlp_sendEventEx(h1,ex)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: sendEventEx  Error code=%d' % rv )
```

### See Also
[pyvscphlp_sendEventEx](pyvscphlp_sendevent.md)



[filename](./bottom_copyright.md ':include')