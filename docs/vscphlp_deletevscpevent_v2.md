

```clike
void vscphlp_deleteVSCPevent_v2( vscpEvent **ppEvent )
```

### Parameters

#### ppEvent
Address of a pointer to a helper-allocated VSCP event. The pointer is set to
null after the event is released.


### Return Value
Returns no value or error code.

### Description
Release the event's helper-allocated data and the event structure itself. Do
not use this function on a stack-allocated event or a Python-owned structure.

#### C example

```clike
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
finally:
    vscphelper.deleteVSCPevent_v2(event)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_newVSCPevent](vscphlp_newvscpevent.md)  
[vscphlp_deleteVSCPevent](vscphlp_deletevscpevent.md)



[filename](./bottom_copyright.md ':include')