

```clike
int vscphlp_convertLevel1MeasuremenToLevel2String( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to VSCP event.

### Return Value
VSCP_ERROR_SUCCESS is returned if the measurement event is converted correctly, VSCP_ERROR_ERROR is returned if not. 

### Description
Convert Level I measurement to a Level II string measurement event [CLASS2.MEASUREMENT_STRING). 

### See Also
[vscphlp_convertLevel1MeasuremenToLevel2Double](vscphlp_convertlevel1measurementolevel2double.md)



[filename](./bottom_copyright.md ':include')

