

```clike
int vscphlp_getISOTimeString( char *buf, 
                                size_t buf_len, 
                                time_t *t )
```

### Parameters

#### buf
Buffer that will receive the ISO time string on success.

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### t
Pointer to a time_t object containing a time value. time_t is an alias for an arithmetic type capable of representing times returned by the time function.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`,
`VSCP_ERROR_PARAMETER`.

### Description
Get ISO time string from time_t.



#### C example

```clike
time_t now = time(NULL);
char text[64];
int result = vscphlp_getISOTimeString(text, sizeof(text), &now);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getISOTimeString failed (error %d)\n", result);
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

result, value = vscphelper.getISOTimeString(int(time.time()))
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getISOTimeString failed (error {})".format(result))
if not value:
    raise RuntimeError("No time string returned")
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
