

```clike
int vscphlp_convertEventToXML( vscpEvent *pEvent, 
                                char *pBuffer, 
                                size_t len )
```

### Parameters

#### pEvent
Pointer to event.

#### pBuffer
Buffer that will receive string result ==

#### len
Size of string buffer.

### Return Value
VSCP_ERROR_SUCCESS is returned on success, VSCP_ERROR_BUFFER_TO_SMALL is returned if the size of the supplied buffer is to small. 

### Description
Write VSCP event on XML format to string. Format is specified in [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h). 


### See Also
[vscphlp_convertEventExToXML](vscphlp_converteventextoxml.md)



[filename](./bottom_copyright.md ':include')
