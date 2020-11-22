

```clike
int vscphlp_makeFloatMeasurementEvent( vscpEvent *pEvent, 
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx )
```

### Parameters

#### pEvent
Pointer to a VSCP event that will get the result as it's data.

#### value
Floating point value to write as a 32-bit float.

#### unit
A unit value 0-3

#### sensorid
A sensor index value 0-7

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Make a floating point (32-bit) coded level I event from floating point data.

#### C example

```clike
Example will be added. TODO
```



[filename](./bottom_copyright.md ':include')