

```clike
int doCmdFilter(const vscpEventFilter *pFilter)
```

### Parameters

#### pFilter
Pointer to VSCP filter structure to set.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Set the receive filter on the remote VSCP server. By setting the filter on can select which events one want to receive. It is possible to open several channels ans have a filter on each for complex setups. 



[filename](./bottom_copyright.md ':include')