

```clike
unsigned char vscphlp_getVscpPriority( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
VSCP event.


### Return Value
Returns the event priority (`0` to `7`), not an error code. A null event returns `0`, which
is also a valid priority.

### Description
Extract the event priority from a VSCP event. Priority is a value from 0 to 7, where 0 is the highest priority.

#### C example

```clike
vscpEvent event = {0};
vscphlp_setVscpPriority(&event, 3);
printf("Priority: %u\n", (unsigned)vscphlp_getVscpPriority(&event));
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
vscphelper.setVscpPriority(event, 3)
print(vscphelper.getVscpPriority(event))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getVscpPriorityEx](vscphlp_getvscppriorityex.md)



[filename](./bottom_copyright.md ':include')