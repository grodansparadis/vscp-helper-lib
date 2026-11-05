

```clike
unsigned char vscphlp_getVscpPriorityEx( const vscpEventEx *pEvent )
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
vscpEventEx event = {0};
vscphlp_setVscpPriorityEx(&event, 5);
printf("Priority: %u\n", (unsigned)vscphlp_getVscpPriorityEx(&event));
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
vscphelper.setVscpPriorityEx(event, 5)
print(vscphelper.getVscpPriorityEx(event))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_getVscpPriority](vscphlp_getvscppriority.md)



[filename](./bottom_copyright.md ':include')