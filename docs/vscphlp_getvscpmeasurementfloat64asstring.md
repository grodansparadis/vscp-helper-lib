

```clike
int vscphlp_getVSCPMeasurementFloat64AsString(const vscpEvent *pEvent, 
                                    char *pStrResult, 
                                    size_t len )
```

### Parameters

#### pEvent
The event that contain the measurement data.

#### pStrResult
Buffer that will get the string result as a null terminated string.

#### len
The size of the buffer.

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
This method displays data stored in 32-bit floating point form ([IEEE 754](https://en.wikipedia.org/wiki/IEEE_floating_point)) as a string 

#### C example

```clike
vscpEvent *pEventfloat = new vscpEvent;
pEventfloat->head = 0;
pEventfloat->vscp_class = 10;
pEventfloat->vscp_type = 6;
pEventfloat->obid = 0;
pEventfloat->timestamp = 0;
memset( pEventfloat->GUID, 0, 16 );
pEventfloat->sizeData = 8;
pEventfloat->pdata = new unsigned char[ pEventfloat->sizeData ];
pEventfloat->pdata[0] = 234;
pEventfloat->pdata[1] = 46;
pEventfloat->pdata[2] = 68;
pEventfloat->pdata[3] = 84;
pEventfloat->pdata[4] = 251;
pEventfloat->pdata[5] = 33;
pEventfloat->pdata[6] = 9;
pEventfloat->pdata[7] = 64;
 
if ( VSCP_ERROR_SUCCESS == 
       vscphlp_getVSCPMeasurementFloat64AsString( pEventfloat, 
                                                    stringbuf,
                                                    sizeof( stringbuf ) ) ) {
    printf("OK - vscphlp_getVSCPMeasurementFloat64AsString value = %s \n", stringbuf );
}
else {
    printf("Error - vscphlp_getVSCPMeasurementFloat64AsString value = %s \n", stringbuf );
}
 
// Free the event
vscphlp_deleteVSCPevent( pEventfloat );
```



[filename](./bottom_copyright.md ':include')