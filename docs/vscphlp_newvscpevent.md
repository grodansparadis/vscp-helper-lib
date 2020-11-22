

```clike
bool vscphlp_newVSCPevent( vscpEvent **ppEvent )
```

### Parameters

#### pEvent
Pointer to pointer to a VSCP event.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure.

### Description
Creates a new VSCP event. Initializes the data pointer.

#### C example

```clike
vscpEvent *pEvent;
vscphlp_newVSCPevent( &pEvent );
```


### See Also
[vscphlp_deleteVSCPevent](vscphlp_deletevscpevent.md)  
[vscphlp_deleteVSCPevent_v2](vscphlp_deletescpevent_v2.md)



[filename](./bottom_copyright.md ':include')