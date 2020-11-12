

```clike
int vscphlp_getRemoteVariableEventEx( long handle, 
                                const char *pName,
                                vscpEventEx *pEvent ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pEvent
Pointer to event variable that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from event variable.

#### C example

```clike
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
```

### See Also
[vscphlp_setRemoteVariableEventEx](vscphlp_setremotevariableeventex.md)



[filename](./bottom_copyright.md ':include')