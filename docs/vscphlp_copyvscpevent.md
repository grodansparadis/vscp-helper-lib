

```clike
int vscphlp_copyVSCPEvent( vscpEvent *pEventTo, 
                              const vscpEvent *pEventFrom )
```

### Parameters

#### pEventTo
VSCP event that will get the result.

#### pEventFrom
VSCP event that should be copied


### Return Value
VSCP_ERROR_SUCCESS on success.

### Description
Copy VSCP event to other event. 

#### C example
mmmm

```clike
vscpEvent *pEventFrom = new vscpEvent;
vscpEvent *pEventTo = new vscpEvent;
pEventFrom->head = 0;
pEventFrom->vscp_class = 10;
pEventFrom->vscp_type = 6;
pEventFrom->obid = 0;
pEventFrom->timestamp = 0;
memset( pEventFrom->GUID, 0, 16 );
pEventFrom->sizeData = 2;
pEventFrom->pdata = new unsigned char[2];
pEventFrom->pdata[ 0 ] = 0xAA;
pEventFrom->pdata[ 1 ] = 0x55;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_copyVSCPEvent( pEventTo, pEventFrom ) ) {
    printf( "OK vscphlp_copyVSCPEvent %02X %02X \n", pEventTo->pdata[0], pEventTo->pdata[1] );
}
else {
    printf( "\aError: vscphlp_copyVSCPEvent\n");
}
 
// Free the events
vscphlp_deleteVSCPevent( pEventFrom );
vscphlp_deleteVSCPevent( pEventTo );
```



[filename](./bottom_copyright.md ':include')