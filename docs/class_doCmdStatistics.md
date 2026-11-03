

```clike
int doCmdStatistics(canalStatistics *pStatistics)
```

### Parameters

#### pStatistics
Pointer to a canalStatistics structure that will receive the remote VSCP server statistics.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get the CANAL statistics structure from the VSCP remote server. 

> **Known limitation:** In the pinned implementation, this overload calls
> itself recursively and can overflow the stack. Do not call it until the
> implementation is corrected.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
