

```clike
int vscphlp_getDateStringFromEventEx( char *buf, 
                                size_t buf_len, 
                                vscpEventEx *pEventEx )
```

### Parameters

#### buf
Buffer that will get datestring from event ex.

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### pEventEx
Event to get datestring from.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Extract an ISO date string from the datetime block of an event.

#### C example


### See Also
[vscphlp_getDateStringFromEvent](vscphlp_getdatestringfromevent.md)



[filename](./bottom_copyright.md ':include')