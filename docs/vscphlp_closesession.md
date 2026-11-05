

```clike
void vscphlp_closeSession( long handle )
```

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).


### Return Value
No value or error code is returned. An invalid handle is not reported to the caller.

### Description
Close an open session. Call this after you have finished using the TCP/IP session.

<!-- tabs:start -->

#### C example

With `handle` referring to an open connection, close the connection and then
release the session:

```clike
int result = vscphlp_close(handle);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "close failed (error %d)\n", result);
}
vscphlp_closeSession(handle);
```

#### Python example

With `handle` referring to an open connection:

```python
import vscp
import vscphelper

try:
    result = vscphelper.close(handle)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("close failed (error {})".format(result))
finally:
    vscphelper.closeSession(handle)
```

The current Python wrapper unloads the shared library in `closeSession`; call
it only after all wrapper work is complete. See [bindings](bindings.md#python).

<!-- tabs:end -->

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_newSession](vscphlp_newsession.md)



[filename](./bottom_copyright.md ':include')