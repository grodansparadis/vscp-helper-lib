

```clike
int vscphlp_setRemoteVariableEvent( long handle, 
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
Set variable value from event variable 

#### C example

```clike
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
```


### See Also
[vscphlp_getRemoteVariableEvent](vscphlp_getremotevariableevent.md)



[filename](./bottom_copyright.md ':include')
