


```clike
long vscphlp_newSession( void );
```

### Parameters
none

### Return Value
A positive session handle is returned on success. `0` indicates that the allocation returned
null; on Windows, `VSCP_ERROR_ERROR` (`-1`) is returned if Winsock initialization fails.
Check for a positive handle, not merely a nonzero value. Allocation may also throw rather
than returning an error code.

### Description

Opens a new communication session. This is the first method that should be called before TCP/IP communication can be established. 

<!-- tabs:start -->

#### ** C example **

Initialize the library using C.

```clike
handle1 = vscphlp_newSession();
if (handle1 > 0) {
    printf( "Handle for channel 1 OK %ld\n", handle1 );
}
else {
    printf("\aError: Failed to get handle for channel 1\n");
}
```

#### Python example

Create a session before connecting and release it when finished:

```python
import vscphelper

handle = vscphelper.newSession()
if handle <= 0:
    raise RuntimeError("Could not create a VSCP session")

try:
    print("Created session {}".format(handle))
finally:
    vscphelper.closeSession(handle)
```

<!-- tabs:end -->

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See also
[vscphlp_closeSession](vscphlp_closesession.md)



[filename](./bottom_copyright.md ':include')