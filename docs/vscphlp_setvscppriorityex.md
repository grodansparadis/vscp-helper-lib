

```clike
void vscphlp_setVscpPriorityEx( vscpEventEx *pEvent, 
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
[vscphlp_setVscpPriority](vscphlp_setvscppriority.md)



[filename](./bottom_copyright.md ':include')