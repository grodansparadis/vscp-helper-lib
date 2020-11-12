

```clike
int vscphlp_getMeasurementSenzorIndex( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to VSCP measurement event.

### Return Value
Sensor index is returned as 0-7 for a Level I event and as 0-255 for a level II event. 1 is returned if the event is not a measurement event or is invalid. 

### Description
Get the sensor index for a measurement event. Some events does not have a sensor index defined and for them zero is always returned. 




[filename](./bottom_copyright.md ':include')