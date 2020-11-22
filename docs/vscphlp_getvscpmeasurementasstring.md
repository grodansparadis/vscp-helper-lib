

```clike
int vscphlp_getVSCPMeasurementAsString( const vscpEvent *pEvent, 
                                        char *pResult, 
                                        size_t len )
```

### Parameters

#### pEvent
The event the measurement string should be collected from.

#### pResult
The resulting measurement in string form.

#### len
Size for the buffer in which the resulting string is written.

### Return Value
VSCP_ERROR_SUCCESS is return on success. 

### Description
This method returns a string representing the measurement data. It recognize all data coding forms and give sensible output back. 

#### C example

```clike
vscpEvent *pEventMeasurement = new vscpEvent;
pEventMeasurement->head = 0;
pEventMeasurement->vscp_class = 10;
pEventMeasurement->vscp_type = 6;
pEventMeasurement->obid = 0;
pEventMeasurement->timestamp = 0;
memset( pEventMeasurement->GUID, 0, 16 );
pEventMeasurement->sizeData = 4;
pEventMeasurement->pdata = new unsigned char[ pEventMeasurement->sizeData ];
pEventMeasurement->pdata[0] = 0x89;
pEventMeasurement->pdata[1] = 0x02;
pEventMeasurement->pdata[2] = 0x00;
pEventMeasurement->pdata[3] = 0xF1;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement, 
                                                              stringbuf, 
                                                              sizeof( stringbuf ) ) ) {
    printf("OK - vscphlp_getVSCPMeasurementAsString value = %s \n", stringbuf );
}
else {
    printf("Error - vscphlp_getVSCPMeasurementAsString value = %s \n", stringbuf );
}
 
pEventMeasurement->pdata[0] = 0x89;
pEventMeasurement->pdata[1] = 0x02;
pEventMeasurement->pdata[2] = 0xFF;
pEventMeasurement->pdata[3] = 0xF1;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement, 
                                                              stringbuf, 
                                                              sizeof( stringbuf ) ) ) {
    printf("OK - vscphlp_getVSCPMeasurementAsString value = %s \n", stringbuf );
}
else {
    printf("Error - vscphlp_getVSCPMeasurementAsString value = %s \n", stringbuf );
}
 
// Free the event
vscphlp_deleteVSCPevent( pEventMeasurement );
```



[filename](./bottom_copyright.md ':include')