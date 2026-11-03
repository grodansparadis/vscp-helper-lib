

```clike
int vscphlp_saveRemoteVariablesToDisk( long handle ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Historically, this function saved persistent variables to disk.

> **Availability:** The current helper library does not declare or export
> this function, and the official Python wrapper does not expose it. The
> signature above is historical; no working C/C++ or Python example is
> available for the current build.



#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')