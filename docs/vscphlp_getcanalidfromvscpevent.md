

```clike
unsigned long 
vscphlp_getCANALidFromEvent( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
VSCP event.


### Return Value
CANAL (CAN) id. 

### Description
Get CANAL id (CAN id) from VSCP event. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
vscphlp_setVscpPriority(&event, 3);
unsigned long canal_id = vscphlp_getCANALidFromEvent(&event);
printf("0x%08lX\n", canal_id);
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 10
event.vscptype = 6
vscphelper.setVscpPriority(event, 3)
canal_id = vscphelper.getCANALidFromEvent(event)
print("0x{:08X}".format(canal_id))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getCANALidFromEventEx](vscphlp_getcanalidfromvscpeventex.md)



[filename](./bottom_copyright.md ':include')