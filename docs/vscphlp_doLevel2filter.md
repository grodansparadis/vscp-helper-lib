

```clike
int vscphlp_doLevel2Filter( const vscpEvent *pEvent, 
                            const vscpEventFilter *pFilter )
```

### Parameters

#### pEvent
Pointer to event that should be filtered.

#### pFilter
Filter/mask to use for the filtering.

### Return Value
Return true (non-zero) if the event is accepted by the filter. 

### Description
Check VSCP filter condition. 

#### C example

```clike
if ( vscphlp_doLevel2Filter( pEvent, &filter ) ) {
    printf( "Event pass:  vscphlp_doLevel2Filter\n");
}
else {
   printf( "Event does NOT pass:  vscphlp_doLevel2Filter\n");
}
```



[filename](./bottom_copyright.md ':include')
