# VSCP Helper library API - Variable handling 

The library supports most operations for handling variables on the VSCP daemon. This section describes the API. Variables and their use are discussed [here](https://docs.vscp.org/vscpd/latest/#/decision_matrix).

**Note:** From version 2, names use **vscphlp_xxxxRemoteVariable** instead of **vscphlp_xxxxVariable**.

## vscphlp_createRemoteVariable

`<code="c">`
int vscphlp_createRemoteVariable( long handle, 
                                    const char *pName,
                                    const char* pType,
                                    const char* pValue,
                                    int bPersistent ) 
`</code>`

Create a variable of a specific type. The write methods below also create a variable if it does not exist, but this method additionally lets you set its persistence.

#### handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#### pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pType

Pointer to the variable type, either as a symbolic name such as "string" or "long", or as a numeric code such as "1" or "6". Numeric codes are also supplied as strings. The variable types are described [here](https://docs.vscp.org/vscpd/13.1/#/./remote_variables?id=variable_types).

####  pValue

Pointer to string that contains the value of the string variable. 

#### bPersistent

If nonzero, the variable is persistent: it is saved to disk and remains available until it is deleted.

#### Example

`<code="c">`

// Create a variable
char strBuf[32];
if ( VSCP_ERROR_SUCCESS == 
       (rv = vscphlp_createRemoteVariable( handle1, 
                                      "test_of_create_variable",
                                      "string",
                                      "Carpe Diem",
                                      1 ) ) )  {
    printf( "Command success: vscphlp_createRemoteVariable on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_createRemoteVariable on channel 1  Error code=%d\n", rv);
}

if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableString( handle1, 
                                             "test_of_create_variable", 
                                             strBuf, 
                                             sizeof( strBuf )-1 ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableString on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableString on channel 1  Error code=%d\n", rv);
}
`</code>`


## vscphlp_deleteRemoteVariable

`<code="c">`
int vscphlp_deleteRemoteVariable( long handle, const char *pName ) 
`</code>`

Delete a remote variable.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### Example

`<code="C">`
// Delete a variable
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_deleteRemoteVariable( handle1, 
                                       "test_of_create_variable" ) ) )  {
    printf( "Command success: vscphlp_deleteRemoteVariable on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_deleteRemoteVariable on channel 1  Error code=%d\n", rv);
}
`</code>`


## vscphlp_saveRemoteVariablesToDisk

`<code="c">`
int vscphlp_saveRemoteVariablesToDisk( long handle ) 
`</code>`

Saves variables marked as persistent to disk.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#### Example

`<code="C">`
// Save variables marked as persistent
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_saveRemoteVariablesToDisk( handle1 ) ) )  {
    printf( "Command success: vscphlp_saveRemoteVariablesToDisk on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_saveRemoteVariablesToDisk on channel 1  Error code=%d\n", rv);
}
`</code>`

## vscphlp_getRemoteVariableString

`<code="c">`
int vscphlp_getRemoteVariableString( const char *pName, char *pValue, size_t len ) 
`</code>`

get value of string variable.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to string that gets the value of the string variable. 

#### len

Size of supplied buffer that will receive the value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a string variable
char strBuf[32];

if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableString( handle1, "test_string_variable", strBuf, sizeof( strBuf )-1 ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableString on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableString on channel 1  Error code=%d\n", rv);
}
`</code>`

## vscphlp_getRemoteVariableValue

This function calls **vscphlp_getRemoteVariableValue**


## vscphlp_setRemoteVariableString

`<code="c">`
int vscphlp_setRemoteVariableString( long handle, const char *pName, char *pValue ) 
`</code>`

Write a value to a string variable. If the variable does not exist it will be created.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to string that contains the value to be written to the string. 

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to a string variable
if ( VSCP_ERROR_SUCCESS == 
        (rv = vscphlp_setRemoteVariableString( handle1, 
                            "test_sting_variable", 
                            "this is the value of the string variable" )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableString on channel 1\n" );
}
else {
    printf("Command error: vscphlp_setRemoteVariableString on channel 1  Error code=%d\n", rv);
}
`</code>`

## vscphlp_setRemoteVariableValue

This function calls **vscphlp_setRemoteVariableString**


## vscphlp_getRemoteVariableBool

`<code="c">`
int vscphlp_getRemoteVariableBool( long handle, const char *pName, bool *bValue ) 
`</code>`

Get the value of the boolean variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  bValue

Pointer to a boolean variable that will receive the remote variable's value.


#### Example

`<code="c">`
// Read a value from a boolean variable
int valBool;
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableBool( handle1, "test_bool_variable", &valBool ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableBool on channel 1\n" );
    printf(" Value = %s\n", valBool ? "true" : "false" );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableBool on channel 1  Error code=%d\n", rv);
}
`</code>`



####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

## vscphlp_setRemoteVariableBool

`<code="c">`
int vscphlp_setRemoteVariableBool( long handle, const char *pName, bool bValue ) 
`</code>`

Get the value of the boolean variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  bValue

Pointer to a boolean variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value (false) to a boolean variable
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableBool( handle1, "test_bool_variable", 0 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableBool on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableBool on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableInt

`<code="c">`
int vscphlp_getRemoteVariableInt( long handle, const char *pName, int *value ) 
`</code>`
Get the value of the integer variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to an integer variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a int variable
int intValue;
if ( VSCP_ERROR_SUCCESS == 
            (rv = vscphlp_getRemoteVariableInt( handle1, "test_integer_variable", &intValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableInt on channel 1\n" );
    printf(" Value = %d\n", intValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableInt on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableInt

`<code="c">`
int vscphlp_setRemoteVariableInt( long handle, const char *pName, int value ) 
`</code>`
Get the value of the integer variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to an integer variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an int variable
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_setRemoteVariableInt( handle1, "test_integer_variable", 777666 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableInt on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableInt on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableLong

`<code="c">`
int vscphlp_getRemoteVariableLong( long handle, const char *pName, long *value ) 
`</code>`
Get the value of the long variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to a long variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a long variable
long longValue;
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_getRemoteVariableLong( handle1, "test_long_variable", &longValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableLong on channel 1\n" );
    printf(" Value = %lu\n", longValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableLong on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableLong

`<code="c">`
int vscphlp_setRemoteVariableLong( long handle, const char *pName, long value ) 
`</code>`
Get the value of the long variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to a long variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an long variable
if ( VSCP_ERROR_SUCCESS == 
    ( rv = vscphlp_setRemoteVariableLong( handle1, "test_long_variable", 123456780 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableLong on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableLong on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableDouble

`<code="c">`
int vscphlp_getRemoteVariableDouble( long handle, const char *pName, double *value ) 
`</code>`
Get the value of the double variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to a double variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a float variable
double floatValue;
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableDouble( handle1, "test_float_variable", &floatValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableDouble on channel 1\n" );
    printf(" Value = %f\n", floatValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableDouble on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableDouble

`<code="c">`
int vscphlp_setRemoteVariableDouble( long handle, const char *pName, double value ) 
`</code>`
Get the value of the double variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Pointer to a double variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an float variable
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableDouble( handle1, "test_float_variable", 1.2345001 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableDouble on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableDouble on channel 1  Error code=%d\n", rv);
}
`</code>`


## vscphlp_getRemoteVariableMeasurement

`<code="c">`
int vscphlp_getRemoteVariableMeasurement( long handle, 
                                          const char *pName, 
                                          double *pvalue,
                                          int *punit,
                                          int *psensoridx,
                                          int *pzone,
                                          int *psubzone ) 
`</code>`
Get variable value, unit, sensor index, zone, subzone from a named measurement variable. 

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pvalue

A double that receives the value of the measurement.

#### punit

Pointer to an integer that will receive the unit for a measurement. The value is from 0 to 3 for Level I or from 0 to 255 for Level II.

#### psensoridx

Pointer to an integer that will receive the sensor index for a measurement. The value is from 0 to 7 for Level I or from 0 to 255 for Level II.

#### pzone

Pointer to an integer that will receive the zone for a measurement. The value is from 0 to 255, where 255 means ALL zones. Use 255 for events without a defined measurement zone.

#### psubzone

Pointer to an integer that will receive the subzone for a measurement. The value is from 0 to 255, where 255 means ALL subzones. Use 255 for events without a defined measurement subzone.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a measurement variable 
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_getRemoteVariableMeasurement( handle1, "test_measurement_variable", strBuf, sizeof(strBuf)-1  ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableMeasurement on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableMeasurement on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableMeasurement

`<code="c">`
int vscphlp_setRemoteVariableMeasurement( long handle, 
                                        const char *pName, 
                                        double value,
                                        int unit,
                                        int sensoridx,
                                        int zone, 
                                        int subzone ) 
`</code>`
Set variable value, unit sensor index, zone and subzone for a measurement variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  value

Double containing the value of a measurement.

#### unit

Integer containing the unit for a measurement. It should be a value from 0 to 3 for Level I or from 0 to 255 for Level II.

#### sensoridx

Integer containing the sensor index for a measurement. It should be a value from 0 to 7 for Level I or from 0 to 255 for Level II.

#### zone

Integer containing the zone for a measurement. It should be a value from 0 to 255, where 255 means ALL zones. Use 255 if no zone is specified, as with most Level I measurement events.

#### subzone

Integer containing the subzone for a measurement. It should be a value from 0 to 255, where 255 means ALL subzones. Use 255 if no subzone is specified, as with most Level I measurement events.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an measurement variable
if ( VSCP_ERROR_SUCCESS == 
       ( rv = vscphlp_setRemoteVariableMeasurement( handle1, "test_measurement_variable", "138,0,23" )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableMeasurement on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableMeasurement on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableEvent

`<code="c">`
int vscphlp_getVariableEvent( long handle, const char *pName, vscpEvent *pEvent ) 
`</code>`
Get the value of the event variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pEvent

Pointer to an event variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
pEvent = new vscpEvent;

// Read a value from a event variable 
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableEvent( handle1, "test_event_variable", pEvent  ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableEvent on channel 1\n" );
    printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        pEvent->vscp_class,
                        pEvent->vscp_type,
                        pEvent->sizeData );
    if ( pEvent->sizeData && ( NULL != pEvent->pdata ) ) {
         printf("Data = ");
         for ( int i=0; i`<pEvent->`sizeData; i++ ) {
             printf("%d ", pEvent->pdata[i] );
         }
         printf("\n");
    }
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableEvent on channel 1  Error code=%d\n", rv);
}

// Free the event
vscphlp_deleteVSCPevent( pEvent );
`</code>`



## vscphlp_setRemoteVariableEvent

`<code="c">`
int vscphlp_setRemoteVariableEvent( long handle, const char *pName, vscpEvent *pEvent ) 
`</code>`
Get the value of the event variable

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pEvent

Pointer to an event variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

#### Example

`<code="c">`
// Write a value to an event variable
pEvent = new vscpEvent;
pEvent->head = 0;
pEvent->vscp_class = 10;
pEvent->vscp_type = 6;
pEvent->obid = 0;
pEvent->timestamp = 0;
memset( pEvent->GUID, 0, 16 );
pEvent->sizeData = 4;
pEvent->pdata = new unsigned char[4];
pEvent->pdata[ 0 ] = 10;
pEvent->pdata[ 1 ] = 20;
pEvent->pdata[ 2 ] = 30;
pEvent->pdata[ 3 ] = 40;
    
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableEvent( handle1, "test_event_variable", pEvent )  ) ) {
    printf( "Command success: vscphlp_setVariableEvent on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableEvent on channel 1  Error code=%d\n", rv);
}

// Free the event
vscphlp_deleteVSCPevent( pEvent );
`</code>`



## vscphlp_getRemoteVariableEventEx

`<code="c">`
int vscphlp_getRemoteVariableEventEx( long handle, const char *pName, vscpEventEx *pEvent ) 
`</code>`
Get the value of the event variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pEvent

Pointer to an event variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a event variable 
vscpEventEx ex1;
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_getRemoteVariableEventEx( handle1, "test_eventex_variable", &ex1  ) ) ) {
    printf( "Command success: vscphlp_getVariableEventEx on channel 1\n" );
    printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        ex1.vscp_class,
                        ex1.vscp_type,
                        ex1.sizeData );
    if ( ex1.sizeData ) {
        printf("Data = ");
        for ( int i=0; i<ex1.sizeData; i++ ) {
            printf("%d ", ex1.data[i] );
        }
        printf("\n");
    }
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableEvent on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableEventEx

`<code="c">`
int vscphlp_setRemoteVariableEventEx( long handle, const char *pName, vscpEventEx *pEvent ) 
`</code>`
Get the value of the event variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pEvent

Pointer to an event variable that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an event variable
vscpEventEx ex1;
ex1.head = 0;
ex1.vscp_class = 50;
ex1.vscp_type = 22;
ex1.obid = 0;
ex1.timestamp = 0;
memset( ex1.GUID, 0, 16 );
ex1.sizeData = 4;
ex1.data[ 0 ] = 40;
ex1.data[ 1 ] = 30;
ex1.data[ 2 ] = 20;
ex1.data[ 3 ] = 10;
    
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableEventEx( handle1, "test_eventex_variable", &ex1 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableEventEx on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableEventEx on channel 1  Error code=%d\n", rv);
}

// Read a value from a event variable 
if ( VSCP_ERROR_SUCCESS == 
     ( rv = vscphlp_getRemoteVariableEventEx( handle1, "test_eventex_variable", &ex1  ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableEventEx on channel 1\n" );
    printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        ex1.vscp_class,
                        ex1.vscp_type,
                        ex1.sizeData );
    if ( ex1.sizeData ) {
         printf("Data = ");
         for ( int i=0; i<ex1.sizeData; i++ ) {
              printf("%d ", ex1.data[i] );
         }
         printf("\n");
    }
}
else {
     printf("\aCommand error: vscphlp_getRemoteVariableEvent on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableGUIDString

`<code="c">`
int vscphlp_getRemoteVariableGUIDString( long handle, 
                                            const char *pName, 
                                            const char *pGUID, size_t len ) 
`</code>`

Get the value of the GUID variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pGUID

Pointer to the GUID string.

#### len

Size of buffer for GUID.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a GUID variable - string type
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_getRemoteVariableGUIDString( handle1, "test_guidstr_variable", strGUID, sizeof(strGUID)-1 )  ) )  {
    printf( "Command success: vscphlp_getRemoteVariableGUIDString on channel 1\n" );
    printf(" Value = %s\n", strGUID );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableGUIDString on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableGUIDString

`<code="c">`
int vscphlp_getRemoteVariableGUID( long handle, const char *pName, const char * pGUID ) 
`</code>`

Set the value for GUID variable.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pGUID

Pointer to a string that contains the GUID on the string form 
"FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF"

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an GUID variable - string type
char strGUID[64];
strcpy( strGUID, "FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD" );

if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableGUIDString( handle1, "test_guidstr_variable", strGUID ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableGUIDString on channel 1\n" );
}
else {
     printf("\aCommand error: vscphlp_setRemoteVariableGUIDString on channel 1  Error code=%d\n", rv);
}
`</code>`


## vscphlp_getRemoteVariableGUIDArray

`<code="c">`
int vscphlp_getRemoteVariableGUIDArray( long handle, const char *pName, const char * pGUID ) 
`</code>`

Get the value of the GUID variable. Array type.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pGUID

Pointer to an array forming a 16-byte GUID.  

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Read a value from a GUID variable - array type
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_getRemoteVariableGUIDArray( handle1, "test_guidarray_variable", GUID  ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableGUIDArray on channel 1\n" );
    printf(" Value = " );
    for ( int i=0; i<16; i++ ) {
        printf("%d ", GUID[i] );    
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableGUIDArray on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableGUIDArray

`<code="c">`
int vscphlp_getRemoteVariableGUIDArray( long handle, const char *pName, const char * pGUID ) 
`</code>`

Get the value of the GUID variable. This is a variant where the GUID is stored in an array.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pGUID

Pointer to an array forming a 16-byte GUID. 

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value to an GUID variable - array type
unsigned char GUID[16];
memset( GUID, 0, 16 );
for ( int i=0;i<16; i++ ) {
    GUID[i] = i;
}

if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_setRemoteVariableGUIDArray( handle1, "test_guidarray_variable", GUID ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableGUIDArray on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableGUIDArray on channel 1  Error code=%d\n", rv);
}
`</code>`

## vscphlp_getRemoteVariableVSCPdata

`<code="c">`
int vscphlp_getRemoteVariableVSCPdata( long handle, const char *pName, uint16_t *psizeData, uint8_t *pData ) 
`</code>`

Get the value of the VSCP data variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  psizeData

Pointer to variable that will hold the size of the data array 

####  pData

Pointer to a VSCP data array variable (unsigned char [8]) that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
unsigned short size;
memset( dataArray, 0, sizeof( dataArray ) );
   
// Read a value from a data variable 
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableVSCPData( handle1, "test_dataarray_variable", dataArray, &size  ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableVSCPData on channel 1\n" );
    printf(" Value = " );
    for ( int i=0; i<size; i++ ) {
        printf("%d ", dataArray[i] );    
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableVSCPData on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableVSCPdata

`<code="c">`
int vscphlp_setRemoteVariableVSCPdata( long handle, 
                                  const char *pName, 
                                  uint16_t sizeData, 
                                  uint8_t *pData ) 
`</code>`

Get the value of the VSCP data variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  sizeData

Pointer to variable that will hold the size of the data array 

####  pData

Pointer to a VSCP data array variable (unsigned char [8]) that will receive the remote variable's value.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
unsigned char dataArray[10];
memset( dataArray, 0, sizeof(dataArray) );
for ( int i=0; i<sizeof(dataArray); i++ ) {
    dataArray[ i ] = i;    
}

if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableVSCPData( handle1, "test_dataarray_variable", dataArray, sizeof( dataArray ) ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableVSCPData on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableVSCPData on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableVSCPclass

`<code="c">`
int vscphlp_getRemoteVariableVSCPclass( long handle, 
                                    const char *pName, 
                                    uint16_t *vscp_class ) 
`</code>`
Get the value of the class variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  vscp_class

Pointer to an int that will receive the value of the class variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
unsigned short vscpclass;

// Read a value from aVSCP class type
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableVSCPClass( handle1, "test_vscp_class_variable", &vscpclass ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableVSCPClass on channel 1\n" );
    printf(" Value = %d\n", vscpclass );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableVSCPClass on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableVSCPclass

`<code="c">`
int vscphlp_setRemoteVariableVSCPclass( long handle, 
                                     const char *pName, 
                                     unsigned short vscp_class ) 
`</code>`

Get the value of the class variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  vscp_class

Pointer to an int that will receive the value of the class variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
// Write a value for VSCP class type
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableVSCPClass( handle1, "test_vscp_class_variable", 10 ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableVSCPClass on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableVSCPClass on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_getRemoteVariableVSCPtype

`<code="c">`
int vscphlp_getRemoteVariableVSCPtype( long handle, 
                                   const char *pName, 
                                   unsigned short *vscp_type ) 
`</code>`

Get the value of the type variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  vscp_type

Pointer to an int that will receive the value of the type variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


#### Example

`<code="c">`
unsigned short vscptype;

// Read a value from aVSCP type type
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableVSCPType( handle1, "test_vscp_type_variable", &vscptype ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableVSCPType on channel 1\n" );
    printf(" Value = %d\n", vscptype );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableVSCPType on channel 1  Error code=%d\n", rv);
}
`</code>`



## vscphlp_setRemoteVariableVSCPtype

`<code="c">`
int vscphlp_setRemoteVariableVSCPtype( long handle, 
                                    const char *pName, 
                                    unsigned short vscp_type ) 
`</code>`

Get the value of the type variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  vscp_type

Pointer to an int that will receive the value of the type variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
// Write a value for VSCP type type
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_setRemoteVariableVSCPType( handle1, "test_vscp_type_variable", 22 ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableVSCPType on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableVSCPType on channel 1  Error code=%d\n", rv);
}
`</code>`

## vscphlp_getRemoteVariableVSCPTimestamp

`<code="c">`
int vscphlp_getRemoteVariableVSCPTimestamp( long handle, 
                                                const char *pName, 
                                                unsigned long *vscp_timestamp ) 
`</code>`

Get the value of the VSCP timestamp variable

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### vscp_timestamp

Pointer to a string that will receive the value of the VSCP timestamp variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableVSCPTimestamp

`<code="c">`
vscphlp_setRemoteVariableVSCPTimestamp( long handle, 
                                            const char *pName, 
                                            unsigned long vscp_timestamp ) 
`</code>`

Set the variable's value from a VSCP timestamp.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  vscp_timestamp

Pointer to unsigned long that holds the VSCP timestamp to set variable to. 

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableDateTime

`<code="c">`
vscphlp_getRemoteVariableDateTime( long handle, 
                                    const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
`</code>`

Get the value of the datetime variable. The returned value is in ISO format "YYYY-MM-DDTHH:MM:SS"

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the value of the datetime variable.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_setRemoteVariableDateTime

`<code="c">`
int vscphlp_setRemoteVariableDateTime( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set the variable's value from a datetime in ISO format "YYYY-MM-DDTHH:MM:SS".

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableDate

`<code="c">`
vscphlp_getRemoteVariableDate( long handle, 
                                 const char *pName, 
                                 char *pValue, 
                                 size_t len ) 
`</code>`

Get the value of the date variable. The returned value is in ISO format "YYYY-MM-DD"

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableDate

`<code="c">`
int vscphlp_setRemoteVariableDate( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set the variable's value from a date in ISO format "YYYY-MM-DD".

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableTime

`<code="c">`
vscphlp_getRemoteVariableTime( long handle, 
                                 const char *pName, 
                                 char *pValue, 
                                 size_t len ) 
`</code>`

Get the value of the time variable. The returned value is in ISO format "HH:MM:SS"

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableTime

`<code="c">`
int vscphlp_setRemoteVariableTime( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value from time in ISO format "HH:MM:SS"

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableBlob

`<code="c">`
vscphlp_getRemoteVariableBlob( long handle, 
                                 const char *pName, 
                                 char *pValue, 
                                 size_t len ) 
`</code>`

Get the value of the blob variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableBlob

`<code="c">`
int vscphlp_setRemoteVariableBlob( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a blob variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableMIME

`<code="c">`
vscphlp_getRemoteVariableMIME( long handle, 
                                 const char *pName, 
                                 char *pValue, 
                                 size_t len ) 
`</code>`

Get the value of the MIME variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableMIME

`<code="c">`
int vscphlp_setRemoteVariableMIME( long handle, 
                                     const char *pName, 
                                     char *pValue ) 
`</code>`

Set variable value for a MIME variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableHTML

`<code="c">`
vscphlp_getRemoteVariableHTML( long handle, 
                                 const char *pName, 
                                 char *pValue, 
                                 size_t len ) 
`</code>`

Get the value of the HTML variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableHTML

`<code="c">`
int vscphlp_setRemoteVariableHTML( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a HTML variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableJavaScript

`<code="c">`
vscphlp_getRemoteVariableJavaScript( long handle, 
                                    const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
`</code>`

Get the value of the JavaScript variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableJavaScript

`<code="c">`
int vscphlp_setRemoteVariableJavaScript( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a JavaScript variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableLUA

`<code="c">`
vscphlp_getRemoteVariableLUA( long handle, 
                                const char *pName, 
                                char *pValue, 
                                size_t len ) 
`</code>`

Get the value of the LUA script variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableLUA

`<code="c">`
int vscphlp_setRemoteVariableLUA( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a LUA script variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableLUARES

`<code="c">`
vscphlp_getRemoteVariableLUARES( long handle, 
                                    const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
`</code>`

Get the value of the LUARES variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableLUARES

`<code="c">`
int vscphlp_setRemoteVariableLUARES( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a LUARES variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableUX1

`<code="c">`
vscphlp_getRemoteVariableUX1( long handle, 
                                const char *pName, 
                                char *pValue, 
                                size_t len ) 
`</code>`

Get the value of the UX1 (User interface version 1) variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableUX1

`<code="c">`
int vscphlp_setRemoteVariableUX1( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a UX1 (User interface version 1) variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableDMROW

`<code="c">`
vscphlp_getRemoteVariableDMROW( long handle, 
                                  const char *pName, 
                                  char *pValue, 
                                  size_t len ) 
`</code>`

Get the value of a DM row variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableDMROW

`<code="c">`
int vscphlp_setRemoteVariableDMROW( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a DM row variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableDriver

`<code="c">`
vscphlp_getRemoteVariableDriver( long handle, 
                                   const char *pName, 
                                   char *pValue, 
                                   size_t len ) 
`</code>`

Get the value of a driver variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableDriver

`<code="c">`
int vscphlp_setRemoteVariableDriver( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a driver variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`

## vscphlp_getRemoteVariableUser

`<code="c">`
vscphlp_getRemoteVariableUser( long handle, 
                                    const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
`</code>`

Get the value of a user variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableUser

`<code="c">`
int vscphlp_setRemoteVariableUser( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a user variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`


## vscphlp_getRemoteVariableFilter

`<code="c">`
vscphlp_getRemoteVariableFilter( long handle, 
                                    const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
`</code>`

Get the value of a filter variable. The returned value is Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

#### pValue

Pointer to a string buffer that will receive the remote variable's value.

#### len

Size of the string buffer.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`

`</code>`

## vscphlp_setRemoteVariableFilter

`<code="c">`
int vscphlp_setRemoteVariableFilter( long handle, 
                                        const char *pName, 
                                        char *pValue ) 
`</code>`

Set variable value for a filter variable. The value is always expected to be Base64-encoded.

####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

####  pName

Pointer to a string containing the variable name. The name should begin with a letter from a to z and is not case-sensitive.

####  pValue

Pointer to a string containing the value to assign to the variable.

####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.



#### Example

`<code="c">`
`</code>`



\\ 
----
Copyright (c) 2000-2019 [Åke Hedman](mailto/akhe@grodansparadis.com), [Paradise of the Frog / the VSCP Project](https://www.grodansparadis.com)
