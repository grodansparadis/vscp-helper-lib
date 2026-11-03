

```clike
int vscphlp_isConnected( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
VSCP_ERROR_SUCCESS if the session is active and VSCP_ERROR_ERROR if it is inactive. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
Check if the session is active or not. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_isConnected( handle1 ) ) {
    // Do your stuff here 
}
```

#### Python example

With a session handle named `handle`:

```python
import vscp
import vscphelper

result = vscphelper.isConnected(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("isConnected failed (error {})".format(result))
print("The session is connected")
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
