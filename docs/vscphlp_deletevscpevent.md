

```clike
void vscphlp_deleteVSCPevent( vscpEvent *pEvent )
```

### Parameters

#### pEvent
VSCP event.


### Return Value
Returns no value or error code.

### Description
Releases an event's helper-allocated data buffer and sets its data pointer to
null. It does **not** release the event structure or reset `sizeData`. To
release an event allocated by [vscphlp_newVSCPevent](vscphlp_newvscpevent.md),
use [vscphlp_deleteVSCPevent_v2](vscphlp_deletevscpevent_v2.md).

#### C example

```clike
/* event was allocated by vscphlp_newVSCPevent. */
vscphlp_deleteVSCPevent(event);
event->sizeData = 0;
vscphlp_deleteVSCPevent_v2(&event);
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

result, event = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event:
    raise RuntimeError("Could not allocate an event (error {})".format(result))
try:
    event.contents.vscpclass = 10
    print(event.contents.vscpclass)
    vscphelper.deleteVSCPevent(event)
    event.contents.sizedata = 0
finally:
    vscphelper.deleteVSCPevent_v2(event)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_newVSCPevent](vscphlp_newvscpevent.md)  
[vscphlp_deleteVSCPevent_v2](vscphlp_deletevscpevent_v2.md)



[filename](./bottom_copyright.md ':include')