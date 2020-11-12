

```clike
void vscphlp_setVscpPriorityEx( vscpEventEx *pEvent, 
                                unsigned char priority )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
None

### Description
Set Event priority. Priority is defined as a value between 0-7 where 0 is the highest priority. 

#### C example

```clike
vscpEventEx ex3;
ex3.head = 0;
ex3.vscp_class = 10;
ex3.vscp_type = 6;
ex3.obid = 0;
ex3->year = 2017;
ex3->month = 1;  // January
ex3->day = 2;
ex3->hour = 13;
ex3->minute = 10;
ex3->second = 43;
ex3.timestamp = 0;
memset( ex3.GUID, 0, 16 );
ex3.sizeData = 3;
ex3.data[ 0 ] = 138;
ex3.data[ 1 ] = 0;
ex3.data[ 2 ] = 30;
 
unsigned char eventPriority;
vscphlp_setVscpPriorityEx( &ex3, VSCP_PRIORITY_LOW );
if ( VSCP_PRIORITY_LOW == ( eventPriority = vscphlp_getVscpPriorityEx( &ex3 ) ) ) {
    printf("Event priority = %d\n", eventPriority );
}
else {
    printf("\aError: Set EventEx priority = %d\n", eventPriority );
}
```


### See Also
[vscphlp_setVscpPriority](vscphlp_setvscppriority.md)



[filename](./bottom_copyright.md ':include')