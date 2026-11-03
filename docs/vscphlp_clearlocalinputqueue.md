

```clike
int vscphlp_clearLocalInputQueue( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns VSCP_ERROR_SUCCESS if the VSCP daemon clears the queue, or VSCP_ERROR_ERROR if it does not or no response arrives before the timeout expires. Returns VSCP_ERROR_INVALID_HANDLE if the handle is invalid.

### Description
Clear the local communication input queue. This is the same operation performed when **bClear** is set for [vscphlp_checkReply](vscphlp_checkreply.md).

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_clearLocalInputQueue( handle1 ) ) {
    printf("Our local input queue cleared.\n");   
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result = vscphelper.clearLocalInputQueue(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("clearLocalInputQueue failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_checkReply](vscphlp_checkreply.md)
[vscphlp_doCommand](vscphlp_docommand.md)



[filename](./bottom_copyright.md ':include')