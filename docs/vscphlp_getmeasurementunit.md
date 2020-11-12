

```clike
int vscphlp_getMeasurementUnit( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to VSCP measurement event.

### Return Value
Unit is returned as 0-3 for a Level I event and as 0-255 for a level II event. 

### Description
Get unit for a measurement event. Some events does not have a unit defined and for then zero is always returned as it is understood that the default unit should be used. 



[filename](./bottom_copyright.md ':include')