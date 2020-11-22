

```clike
int vscphlp_getISOTimeString( char *buf, 
                                size_t buf_len, 
                                time_t *t )
```

### Parameters

#### buf
Buffer that will get ISO time string after a successful call.

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### t
Pointer to an object of type time_t that contains a time value. time_t is an alias of a fundamental arithmetic type capable of representing times as returned by function time.


### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Get ISO time string from time_t.



[filename](./bottom_copyright.md ':include')
