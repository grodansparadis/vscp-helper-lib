

```clike
int vscphlp_doCommand( long handle, 
                        const char *cmd )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### cmd
This is the command that should be sent to the server. It should be terminated with “\r\n”.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`, `VSCP_ERROR_INVALID_FRAME`.

For ordinary text commands, a rejected response, reply timeout, or write
failure is reported as `VSCP_ERROR_ERROR`. The explicit timeout, stopped,
and invalid-frame codes can result from `BINARY` negotiation.

### Description
Send a command over the communication link. The command should end with “\r\n”. The server's response is checked for +OK.

`BINARY\r\n` is special: it negotiates [binary link mode](binary_link.md).
Use `vscphlp_doCmdBinary` for the same operation with explicit negotiation
errors. Other text commands are rejected with `VSCP_ERROR_PARAMETER` after
the session has switched to binary mode.

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_doCommand( handle1, "NOOP\r\n" ) ) {
    printf("Command sent successfully!\n");   
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

result = vscphelper.doCommand(handle, "NOOP\r\n")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("doCommand failed (error {})".format(result))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_checkReply](vscphlp_checkreply.md)  
[vscphlp_clearLocalInputQueue](vscphlp_clearlocalinputqueue.md)



[filename](./bottom_copyright.md ':include')