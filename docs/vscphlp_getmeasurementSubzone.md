

```clike
int vscphlp_getMeasurementSubZone( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Poniter to VSCP measurement event.

### Return Value
Zone is returned as 0-255 where 255 means “all zones”. -1 is returned if the event is not a measurement event or is invalid. Some events does not have a subzone defined and for them zero is always returned. 

### Description
Get subzone for a measurement event. 




[filename](./bottom_copyright.md ':include')