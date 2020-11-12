

```clike
int vscphlp_getVSCPMeasurementAsDouble( const vscpEvent *pEvent, 
                                        double *pvalue)
```

### Parameters

#### pEvent
The event that contain the measurement data.

#### pvalue
A pointer to a double that will get the measurement result.


### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
This method returns a double representing the measurement data. It recognize all data coding forms and give sensible output back. 

#### C example

```clike
pEventMeasurement->pdata[0] = VSCP_DATACODING_INTEGER;
pEventMeasurement->pdata[1] = 0xFF;
pEventMeasurement->pdata[2] = 0xFF;
pEventMeasurement->pdata[3] = 0xFF;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsDouble( pEventMeasurement, &value ) ) {
    printf("OK - vscphlp_getVSCPMeasurementAsDouble value = %lf\n", value );
}
else {
    printf("Error - vscphlp_getVSCPMeasurementAsDouble value = %slf \n", value );
}
```



[filename](./bottom_copyright.md ':include')