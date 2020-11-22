

```clike
int vscphlp_makeLevel2FloatMeasurementEvent( vscpEvent *pEvent, 
                                                uint16_t type,
                                                double value,
                                                uint8_t unit,
                                                uint8_t sensoridx,
                                                uint8_t zone,
                                                uint8_t subzone )
```

### Parameters

#### pEvent
Pointer to event that data should be written to.

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
VSCP_ERROR_SUCCESS is returned if the measurement event is constructed correctly, VSCP_ERROR_ERROR is returned if not. 

### Description
Construct a Level II floating point measurement event from supplied data. **Note** that the GUID must be set externally. 

### See Also
[vscphlp_makeLevel2StringMeasurementEvent](vscphlp_makelevel2stringmeasurementevent.md)
[vscphlp_makeLevel2StringMeasurementEventEx](vscphlp_makelevel2stringmeasurementeventex.md)
[vscphlp_makeLevel2FloatMeasurementEventEx](vscphlp_makelevel2floatmeasurementeventex.md)



[filename](./bottom_copyright.md ':include')