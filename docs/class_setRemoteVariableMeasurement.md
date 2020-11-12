



```clike
int setRemoteVariableMeasurement( const wxString& name, 
                                    double value,
                                    uint8_t unit = 0,
                                    uint8_t sensoridx = 0,
                                    uint8_t zone = 255,
                                    uint8_t subzone = 255 )
```

### Parameters

#### name
Name of remote variable to set value for.

#### value
Double containing the value for the measurement.

#### unit
The unit for the measurement.

#### sensoridx
The sensor index for the measurement.

#### zone
The zone for the measurement.

#### subzone
The sub zone for the measurement.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Set remote measurement variable value. 



[filename](./bottom_copyright.md ':include')