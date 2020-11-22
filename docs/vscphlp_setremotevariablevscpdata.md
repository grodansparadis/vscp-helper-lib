

```clike
int vscphlp_setRemoteVariableVSCPdata( long handle, 
                                  const char *pName, 
                                  uint16_t sizeData, 
                                  uint8_t *pData )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### sizeData
Pointer to variable that will hold the size of the data array

#### pData
Pointer to VSCP data array variable (unsigned char [8] ) that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from VSCP data variable.

#### C example

```clike
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
```

### See Also
[vscphlp_getRemoteVariableVSCPdata](vscphlp_getremotevariablevscpdata.md)



[filename](./bottom_copyright.md ':include')
