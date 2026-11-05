

```clike
void vscphlp_setVscpPriority( vscpEvent *pEvent, 
                                unsigned char priority )
```

### Parameters

#### pEvent
Event whose priority will be changed.

#### priority
Priority from 0 to 7.

### Return Value
Returns no value or error code.

### Description
Set the event priority. Priority is a value from 0 to 7, where 0 is the highest priority.

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
[vscphlp_setVscpPriorityEx](vscphlp_setvscppriorityex.md)



[filename](./bottom_copyright.md ':include')