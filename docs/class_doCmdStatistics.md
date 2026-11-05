

```clike
int doCmdStatistics(canalStatistics *pStatistics)
```

### Parameters

#### pStatistics
Pointer to a canalStatistics structure that will receive the remote VSCP server statistics.

### Return Value
`VSCP_ERROR_PARAMETER` is returned if the pointer is null. With a non-null pointer, this
overload calls itself recursively and can overflow the stack instead of returning a status;
do not rely on a success or failure code.

### Description
Get the CANAL statistics structure from the VSCP remote server. 

> **Known limitation:** In the pinned implementation, this overload calls
> itself recursively and can overflow the stack. Do not call it until the
> implementation is corrected.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
