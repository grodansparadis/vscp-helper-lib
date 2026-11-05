

```clike
int vscphlp_setAfterCommandSleep( long handle, 
                unsigned short millisecondSleep )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newSession](vscphlp_newsession.md).

#### millisecondSleep
Sleep time in milliseconds. This value is currently ignored.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`.

### Description
This function is retained for backward compatibility. It currently has no effect on the delay after a command.

#### C example

```clike
int result = vscphlp_setAfterCommandSleep(handle, 0);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "setAfterCommandSleep failed (error %d)\n", result);
}
```

#### Python example

With a session handle named `handle`, this retained compatibility call succeeds but does not change the command delay:

```python
import vscp
import vscphelper

result = vscphelper.setAfterCommandSleep(handle, 0)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setAfterCommandSleep failed (error {})".format(result))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_setResponseTimeout](vscphlp_setresponsetimeout.md)



[filename](./bottom_copyright.md ':include')
