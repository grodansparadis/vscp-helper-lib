

```clike
int vscphlp_serverShutDown( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Shut down the daemon. This is a privileged command on the server side.

#### C availability

The current public header declares `vscphlp_serverShutDown`, but the current
implementation exports `vscphlp_shutDownServer` instead. A call using the
header declaration cannot link against that implementation, so no C example
is provided until the names are aligned. The Python wrapper handles either
exported name.

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)),
this privileged command shuts down the server:

```python
import vscp
import vscphelper

result = vscphelper.serverShutDown(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("serverShutDown failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
