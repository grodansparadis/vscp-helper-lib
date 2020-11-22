

```clike
int vscphlp_receiveEvent( long handle, 
                          vscpEvent *pEvent )
```

```python
int pyvscphlp_receiveEvent( handle, event )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
Pointer to vscpEvent structure that will receive the event if the call is successful. The structure vscpEvent is define in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) and is defined as

```clike
typedef struct  {	
  uint16_t crc;           // crc checksum - currently only used for UDP and RF
  uint8_t  *pdata;        // Pointer to data. Max 487 (512- 25) bytes
  // Following two are for daemon internal use
  uint32_t obid;          // Used by driver for channel info etc.
 
  // Time block - Always UTC time
  uint16_t year; 
  uint8_t month;                  // 1-12
  uint8_t day;	                  // 1-31
  uint8_t hour;                   // 0-23
  uint8_t minute;                 // 0-59
  uint8_t second;                 // 0-59 
 
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
Receive one VSCP event from the remote VSCP server if there is one available in the server queue. Data for the event is dynamically allocated and must be deleted by the application. 

For Python use of [pyvscphlp_receiveEventEx](pyvscphlp_receiveeventex.md) may be simpler as there id no dynamically allocated data to take care off. 

#### C example

```clike
// Read event
vscpEvent *pEvent = new vscpEvent;
pEvent->pdata = NULL;   // A must for a successful delete
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEvent( handle2, pEvent ) ) ) {
    printf( "Command success: vscphlp_receiveEvent on handle2\n" );
    printf( "VSCP class=%d VSCP type=%d sizeData=%d\n", 
                    pEvent->vscp_class,
                    pEvent->vscp_type,
                    pEvent->sizeData );
    printf("Data = ");
    for ( int i=0; i<pEvent->sizeData; i++ ) {
        printf("%d ", pEvent->pdata[i] );
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_receiveEvent on channel 2  Error code=%d\n", rv);
}
 
// Do something with the received event
 
//delete pEvent->pdata;
//delete pEvent;
vscphlp_deleteVSCPevent( pEvent );  // This helper is the same as the above two commented lines
```

#### Python example

```python

```

### See Also
[vscphlp_receiveEventEx](vscphlp_receiveeventex.md)



[filename](./bottom_copyright.md ':include')