

```clike
unsigned short vscphlp_calc_crc_Event ( vscpEvent *pEvent,
                                short bSet )
```

### Parameters

#### pEvent
VSCP event.

#### bSet
If true (nonzero), write the CRC to the event structure's crc member.

### Return Value
VSCP CRC. 

### Description
Calculate VSCP CRC and optionally set it.

#### C example

```clike
vscpEvent event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
unsigned short crc = vscphlp_calc_crc_Event(&event, 0);
printf("CRC: 0x%04X\n", crc);
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 10
event.vscptype = 6
crc = vscphelper.calc_crc_Event(event, 0)
print("CRC: 0x{:04X}".format(crc))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_calc_crc_Event](vscphlp_calc_crc_event.md)



[filename](./bottom_copyright.md ':include')