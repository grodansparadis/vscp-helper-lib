# vscphlp_isSingleChannelReceiveLoopEnabled

```c
int vscphlp_isSingleChannelReceiveLoopEnabled(long handle, int *pEnabled);
```

On success, writes `1` to `*pEnabled` if the session is configured to use
single-channel text receive-loop mode, or `0` otherwise. This reports the
configured option; it does not indicate whether the connection is open or the
receive loop is active.

`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible errors are
`VSCP_ERROR_INVALID_HANDLE` and `VSCP_ERROR_PARAMETER` (`pEnabled` is null).

See [single-channel TCP/IP mode](vscphlp_setsinglechannelreceiveloop.md) for
configuration requirements and a send/receive example.

[filename](./bottom_copyright.md ':include')
