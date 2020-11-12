

```clike
int vscphlp_getRemoteVariableVSCPdata( long handle, 
                                const char *pName, 
                                uint16_t *psizeData, 
                                uint8_t *pData ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### psizeData
Pointer to variable that will hold the size of the data array

#### pData
Pointer to VSCP data array variable (unsigned char [8] ) that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from VSCP data variable.

#### C example

```clike
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
```

### See Also
[vscphlp_setRemoteVariableVSCPdata](vscphlp_setremotevariablevscpdata.md)



[filename](./bottom_copyright.md ':include')