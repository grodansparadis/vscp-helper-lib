

```clike
unsigned long 
vscphlp_getCANALidFromEventEx( const vscpEventEx *pEvent )
```
### Parameters

#### pEvent
VSCP event.

### Return Value
Returns the constructed CANAL identifier, not an error code. The event pointer must be
valid.

### Description
Get CANAL id (CAN id) from VSCP event. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
vscphlp_setVscpPriorityEx(&event, 3);
unsigned long canal_id = vscphlp_getCANALidFromEventEx(&event);
printf("0x%08lX\n", canal_id);
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
event.vscpclass = 10
event.vscptype = 6
vscphelper.setVscpPriorityEx(event, 3)
canal_id = vscphelper.getCANALidFromEventEx(event)
print("0x{:08X}".format(canal_id))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getCANALidFromVSCPevent](vscphlp_getcanalidfromvscpevent.md)



[filename](./bottom_copyright.md ':include')