
```clike
int vscphlp_checkReply( long handle, int bclear )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### bclear
If TRUE (nonzero), clear the input buffer before waiting for +OK or -OK in the incoming data.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_ERROR`.

### Description
Check reply data for “+OK”/“-OK” on server. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_checkReply( handle1, TRUE ) ) {
    printf("+OK was received from VSCP daemon.\n");   
}


```

#### Python example

With an open session `handle` and a reply pending:

```python
import vscp
import vscphelper

result = vscphelper.checkReply(handle, False)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("checkReply failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_doCommand](vscphlp_docommand.md)



[filename](./bottom_copyright.md ':include')