

```clike
int vscphlp_convertLevel1MeasuremenToLevel2Double( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to VSCP event.

### Return Value
VSCP_ERROR_SUCCESS is returned if the event is a measurement, VSCP_ERROR_ERROR is returned if the event is not a measurement. 

### Description
Convert Level I measurement to a Level II float measurement event [CLASS2.MEASUREMENT_FLOAT](https://grodansparadis.gitbooks.io/the-vscp-specification/class2.measurement_float.html). 


### See Also
[vscphlp_convertLevel1MeasuremenToLevel2DoubleEx](vscphlp_convertlevel1measurementolevel2doubleex.md)
[vscphlp_convertLevel1MeasuremenToLevel2String](vscphlp_convertlevel1measurementolevel2string.md)
[vscphlp_convertLevel1MeasuremenToLevel2StringEx](vscphlp_convertlevel1measurementolevel2stringex.md)



[filename](./bottom_copyright.md ':include')
