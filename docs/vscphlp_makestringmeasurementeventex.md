

```clike
int vscphlp_makeStringMeasurementEvent( vscpEventEx *pEventEx, 
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx )
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex event that will get the result as it's data.

#### value
Floating point value to write as a 32-bit float.

#### unit
A unit value 0-3

#### sensorid
A sensor index value 0-7

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Make a string coded level I event from floating point data.

#### C example

```clike
Example will be added. TODO
```



[filename](./bottom_copyright.md ':include')