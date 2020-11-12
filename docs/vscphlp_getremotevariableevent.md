

```clike
int vscphlp_getVariableEvent( long handle, 
                                const char *pName, 
                                vscpEvent *pEvent ) 
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
         for ( int i=0; i<pEvent->sizeData; i++ ) {
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
```

### See Also
[vscphlp_setRemoteVariableEvent](vscphlp_setremotevariableevent.md)



[filename](./bottom_copyright.md ':include')