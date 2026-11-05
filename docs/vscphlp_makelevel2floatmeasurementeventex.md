

```clike
int vscphlp_makeLevel2FloatMeasurementEventEx( vscpEventEx *pEventEx, 
                                                uint16_t type,
                                                double value,
                                                uint8_t unit,
                                                uint8_t sensoridx,
                                                uint8_t zone,
                                                uint8_t subzone )
```

### Parameters

#### pEventEx
Pointer to the event ex to which data should be written.

#### type
The VSCP type for the event. Must be one of the types in [CLASS1.MEASUREMENT](https://grodansparadis.gitbooks.io/the-vscp-specification/class1.measurement.html)

#### value
Double precision floating point measurement value.

#### unit
Unit (0-255) for the measurement.

#### sensoridx
Sensor index (0-255) for the measurement.

#### zone
Zone (0-255) for the measurement.

#### subzone
Sub zone (0-255) for the measurement.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Construct a Level II floating point measurement event from supplied data. **Note** that the GUID must be set externally. 

> **Known limitation:** The current implementation copies the `double` in
> host byte order, but Level II floating-point measurement data is specified
> most-significant byte first. On little-endian systems the resulting wire
> bytes do not represent the requested value. The C and Python APIs share this
> implementation.

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_makeLevel2StringMeasurementEvent](vscphlp_makelevel2stringmeasurementevent.md)
[vscphlp_makeLevel2StringMeasurementEventEx](vscphlp_makelevel2stringmeasurementeventex.md)
[vscphlp_makeLevel2FloatMeasurementEvent](vscphlp_makelevel2floatmeasurementevent.md)


[filename](./bottom_copyright.md ':include')