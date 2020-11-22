

```clike
void vscphlp_copyVSCPFilter( vscpEventFilter *pToFilter, 
                    const vscpEventFilter *pFromFilter )
```

### Parameters

#### pToFilter
Pointer to VSCP filter structure that will receive data.

### pFromFilter
Pointer to VSCP filter structure that data will be copied from.


### Return Value
None

### Description
Copy VSCP filter from one to another. 

#### C example

```clike
vscphlp_clearVSCPFilter( pFilter )
```



[filename](./bottom_copyright.md ':include')