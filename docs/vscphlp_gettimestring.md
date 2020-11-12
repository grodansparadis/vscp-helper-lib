

```clike
int vscphlp_getTimeString( char *buf, 
                            size_t buf_len, 
                            time_t *t )
```

### Parameters

#### buf
Buffer that will get timestring after a successful call.

#### buf_len
Length of the buffer.

#### t
Pointer to an object of type time_t that contains a time value. time_t is an alias of a fundamental arithmetic type capable of representing times as returned by function time.


### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Get GMT time https://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.3.

Example result: Sun, “06 Nov 1994 08:49:37 GMT” 

#### C example
mmmm




[filename](./bottom_copyright.md ':include')