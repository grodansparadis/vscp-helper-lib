

```clike
int vscphlp_setRemoteVariableEventEx( long handle, 
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
Set variable value from event variable.

#### C example

```clike
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
```

### See Also
[vscphlp_getRemoteVariableEventEx](vscphlp_getremotevariableeventex.md)



[filename](./bottom_copyright.md ':include')