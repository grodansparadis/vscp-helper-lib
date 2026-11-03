

```clike
int doCmdStatistics(VSCPStatistics *pStatistics)
```

### Parameters

#### pStatistics
Pointer to a VSCPStatistics structure that will receive the remote VSCP server statistics.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get the VSCP statistics structure from the VSCP remote server. 

> **Known limitation:** The pinned implementation can copy the first `STAT`
> response value into multiple counters. See
> [vscphlp_getStatistics](vscphlp_getstatistics.md) for details.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')