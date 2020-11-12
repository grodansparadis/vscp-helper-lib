

```clike
int vscphlp_setRemoteVariableMeasurement( long handle, 
                                        const char *pName, 
                                        double value,
                                        int unit,
                                        int sensoridx,
                                        int zone, 
                                        int subzone )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### value
Double that contain the value of a measurement.

#### unit
Integer that contain the unit for a measurement. This should be a value between 0-3 for Level I and 0-255 for Level II.

##### sensoridx
Integer that contain the sensor index for a measurement. This should be a value between 0-7 for Level I and 0-255 for Level II.

#### zone
Integer that contain the zone for a measurement. This should be a value between 0-255 where 255 means ALL zones. Use 255 if no zone is specified as is the case for most Level I measurement events.

#### subzone
Integer that contain the sub zone for a measurement. This should be a value between 0-255 where 255 means ALL sub zones. Use 255 if no sub zone is specified as is the case for most Level I measurement events.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Set variable value, unit sensor index, zone and sub zone for a measurement variable.

#### C example

```clike
// Write a value to an measurement variable
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_setRemoteVariableMeasurement( handle1, "test_measurement_variable", "138,0,23" )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableMeasurement on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableMeasurement on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_getRemoteVariableMeasurement](vscphlp_getremotevariablemeasurement.md)



[filename](./bottom_copyright.md ':include')