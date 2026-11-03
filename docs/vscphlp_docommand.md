

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
Returns VSCP_ERROR_SUCCESS if the VSCP daemon responds with +OK after receiving the command, or VSCP_ERROR_ERROR if it responds with -OK or no response arrives before the timeout expires. Returns VSCP_ERROR_CONNECTION if the communication channel is not open and VSCP_ERROR_INVALID_HANDLE if the handle is invalid.

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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_checkReply](vscphlp_checkreply.md)  
[vscphlp_clearLocalInputQueue](vscphlp_clearlocalinputqueue.md)



[filename](./bottom_copyright.md ':include')