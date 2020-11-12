

```clike
long tttt(void)
```

```python
xxxx
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pvalue
A double that get the value of the measurement.

#### punit
Pointer to an integer that will get the unit for a measurement. For Level I this is a value between 0-3 and for Level II a value between 0-255.

#### psensoridx
Pointer to an integer that will get the sensor index for a measurement. For Level I this is a value between 0-7 and for Level II a value between 0-255.

#### pzone
Pointer to an integer that will get the zone for a measurement. This is a value between 0-255 where 255 is ALL zones. Some events does not have a zone defined for measurements and in this case the value 255 should be used.

#### psubzone
Pointer to an integer that will get the sub zone for a measurement. This is a value between 0-255 where 255 is ALL sub zones. Some events does not have a sub zone defined for measurements and in this case the value 255 should be used.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

### Description
Get variable value, unit, sensor index, zone, subzone from a named measurement variable. 

#### C example

```clike
// Read a value from a measurement variable 
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_getRemoteVariableMeasurement( handle1, "test_measurement_variable", strBuf, sizeof(strBuf)-1  ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableMeasurement on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableMeasurement on channel 1  Error code=%d\n", rv);
}
```


### See Also
[vscphlp_setRemoteVariableMeasurement](vscphlp_setremotevariablemeasurement.md)



[filename](./bottom_copyright.md ':include')