

```clike
int vscphlp_convertLevel1MeasurementToLevel2Double( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert Level I measurement to a Level II float measurement event [CLASS2.MEASUREMENT_FLOAT](https://grodansparadis.gitbooks.io/the-vscp-specification/class2.measurement_float.html). 

> The misspelled `vscphlp_convertLevel1MeasuremenToLevel2Double` is still exported as an alias for older code; use `vscphlp_convertLevel1MeasurementToLevel2Double`.


#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_convertLevel1MeasurementToLevel2DoubleEx](vscphlp_convertlevel1measurementolevel2doubleex.md)
[vscphlp_convertLevel1MeasurementToLevel2String](vscphlp_convertlevel1measurementolevel2string.md)
[vscphlp_convertLevel1MeasurementToLevel2StringEx](vscphlp_convertlevel1measurementolevel2stringex.md)



[filename](./bottom_copyright.md ':include')
