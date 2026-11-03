

```clike
int vscphlp_getTimeString( char *buf, 
                            size_t buf_len, 
                            time_t *t )
```

### Parameters

#### buf
Buffer that will receive the time string on success.

#### buf_len
Length of the buffer.

#### t
Pointer to a time_t object containing a time value. time_t is an alias for an arithmetic type capable of representing times returned by the time function.


### Return Value
Returns VSCP_ERROR_SUCCESS on success.

### Description
Get GMT time https://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.3.

Example result: Sun, “06 Nov 1994 08:49:37 GMT” 

#### C example

```clike
time_t now = time(NULL);
char text[64];
int result = vscphlp_getTimeString(text, sizeof(text), &now);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getTimeString failed (error %d)\n", result);
} else {
    printf("%s\n", text);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import time

import vscp
import vscphelper

result, value = vscphelper.getTimeString(int(time.time()))
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getTimeString failed (error {})".format(result))
if not value:
    raise RuntimeError("No time string returned")
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')