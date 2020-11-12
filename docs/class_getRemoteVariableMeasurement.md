

```clike
int getRemoteVariableMeasurement( const wxString& name, 
                                    double *pvalue,
                                    uint8_t *punit,
                                    uint8_t *psensoridx,
                                    uint8_t *pzone,
                                    uint8_t *psubzone )
```

### Parameters

#### name
Name of remote variable to set value for.

#### pvalue
Pointer to a double that will get the value of the measurement.

##### punit
Pointer to uint8_t that will get the unit of the measurement.

#### psensoridx
Pointer to uint8_t that will get the sensor index of the measurement.

#### pzone
Pointer to a uint8_t that will get the zone of the measurement.

#### psubzone
Pointer to a unit8_t that will get the sub zone of the measurement.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value for measurement variable. 




[filename](./bottom_copyright.md ':include')
