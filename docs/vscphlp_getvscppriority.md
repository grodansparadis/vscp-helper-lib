

```clike
unsigned char vscphlp_getVscpPriority( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
VSCP event.


### Return Value
Priority. 

### Description
Extract the event priority from a VSCP event. Priority is defined as a value between 0-7 where 0 is the highest priority. 

#### C example

```clike
pEvent = new vscpEvent;
pEvent->head = 0;
pEvent->vscp_class = 10;
pEvent->vscp_type = 6;
pEvent->obid = 0;
pEvent->year = 2017;
pEvent->month = 1;  // January
pEvent->day = 2;
pEvent->hour = 13;
pEvent->minute = 10;
pEvent->second = 43;
pEvent->timestamp = 0;
memset( pEvent->GUID, 0, 16 );
pEvent->sizeData = 3;
pEvent->pdata = new unsigned char[3];
pEvent->pdata[ 0 ] = 138;
pEvent->pdata[ 1 ] = 0;
pEvent->pdata[ 2 ] = 30;
 
unsigned char eventPriority;
if ( 0 == ( eventPriority = vscphlp_getVscpPriority( pEvent ) ) ) {
    printf("Event priority = %d\n", eventPriority );
}
else {
    printf("\aError: Event priority = %d\n", eventPriority );
}
 
// Free the event
vscphlp_deleteVSCPevent( pEvent );
```

### See Also
[vscphlp_getVscpPriorityEx](vscphlp_getvscppriorityex.md)



[filename](./bottom_copyright.md ':include')