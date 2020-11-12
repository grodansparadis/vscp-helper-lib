

```clike
int vscphlp_getMeasurementZone( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to VSCP measurement event.

### Return Value
Zone is returned as 0-255 where 255 means “all zones”. 1 is returned if the event is not a measurement event or is invalid. 

### Description
Get zone for a measurement event. Some events does not have a zone defined and for them zero is always returned. 



[filename](./bottom_copyright.md ':include')