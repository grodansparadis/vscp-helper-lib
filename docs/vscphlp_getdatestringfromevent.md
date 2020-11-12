

```clike
int vscphlp_getDateStringFromEvent( char *buf, 
                            size_t buf_len, 
                            vscpEvent *pEvent )
```

### Parameters

#### buf
Buffer that will get datestring from event

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### pEvent
Event to get datestring from.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Extract an ISO date string from the datetime block of an event.

#### C example

### See Also
[vscphlp_getDateStringFromEventEx](vscphlp_getdatestringfromeventex.md)



[filename](./bottom_copyright.md ':include')