

```clike
unsigned char vscphlp_getVscpPriorityEx( const vscpEventEx *pEvent )
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
if ( 0 == ( eventPriority = vscphlp_getVscpPriorityEx( &ex3 ) ) ) {
    printf("EventEx priority = %d\n", eventPriority );
}
else {
    printf("\aError: EventEx priority = %d\n", eventPriority );
}
```

#### Python example
mmm

```python
xxx
```

### See Also
[vscphlp_getVscpPriority](vscphlp_getvscppriority.md.md)



[filename](./bottom_copyright.md ':include')