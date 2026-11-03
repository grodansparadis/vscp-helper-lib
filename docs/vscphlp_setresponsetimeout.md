

```clike
int vscphlp_setResponseTimeout( long handle, 
                        unsigned long timeout )
```


### Parameters

#### handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](vscphlp_newsession.md).

#### timeout 
Timeout in milliseconds. It can also be set before a session is opened.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
Set the timeout used when waiting for replies to commands sent to the server. It can be changed at any time during a communication session. The default is 2000 milliseconds; values below 100 milliseconds are treated as 1000 milliseconds.

#### C example

With a session handle named `handle`, set the timeout to three seconds:

```clike
int result = vscphlp_setResponseTimeout(handle, 3000);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "setResponseTimeout failed (error %d)\n", result);
}
```


#### Python example

With a session handle named `handle`, set the timeout to three seconds:

```python
import vscp
import vscphelper

result = vscphelper.setResponseTimeout(handle, 3000)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setResponseTimeout failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See also
[vscphlp_setAfterCommandSleep](vscphlp_setaftercommandsleep.md)



[filename](./bottom_copyright.md ':include')