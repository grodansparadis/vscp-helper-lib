

```clike
int doCmdFilter(const wxString& filter, const wxString& mask)
```

### Parameters

#### filter
Filter to set on string form (“priority,class,type,guid”).

#### mask
Mask to set on string form (“priority,class,type,guid”).

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Set the receive filter on the remote VSCP server. By setting the filter on can select which events one want to receive. It is possible to open several channels ans have a filter on each for complex setups. 



[filename](./bottom_copyright.md ':include')
