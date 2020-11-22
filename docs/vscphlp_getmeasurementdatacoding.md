

```clike
unsigned char vscphlp_getMeasurementDataCoding( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Event that the data coding is fetched from.


### Return Value
Data coding byte.

### Description
Get the [measurement data coding byte](https://grodansparadis.gitbooks.io/the-vscp-specification/vscp_data_coding.html) from an event. The measurement data coding byte specifies how the data in the event should be interpreted. 

#### C example

```clike
pEvent = new vscpEvent;
pEvent->head = 0;
pEvent->vscp_class = 10;
pEvent->vscp_type = 6;
pEvent->obid = 0;
pEvent->timestamp = 0;
memset( pEvent->GUID, 0, 16 );
pEvent->sizeData = 3;
pEvent->pdata = new unsigned char[3];
pEvent->pdata[ 0 ] = 138;
pEvent->pdata[ 1 ] = 0;
pEvent->pdata[ 2 ] = 30;
 
unsigned char dataCoding = vscphlp_getMeasurementDataCoding( pEvent );
if ( dataCoding = 138 ) {
    printf("Data Coding = %d\n", dataCoding );
}
else {
    printf("Error: Data Coding = %d\n", dataCoding );
}
```



[filename](./bottom_copyright.md ':include')