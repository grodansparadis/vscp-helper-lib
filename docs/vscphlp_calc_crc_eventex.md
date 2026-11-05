

```clike
unsigned short vscphlp_calc_crc_EventEx( vscpEventEx *pEvent,
                                         short bSet )
```

### Parameters

#### pEvent
VSCP extended event.

#### bSet
If true (nonzero), write the CRC to the event structure's crc member.

### Return Value
Returns the CRC, not an error code. A null event or allocation failure returns `0`, which
can also be a valid CRC.

### Description
Calculate VSCP CRC and optionally set it. 

#### C availability

The implementation takes a `vscpEventEx *`, but the current public header
declares this parameter as `vscpEvent *`. Do not call it using the incorrect
declaration; a C example requires the header to be corrected.

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
event.vscpclass = 10
event.vscptype = 6
crc = vscphelper.calc_crc_EventEx(event, 0)
print("CRC: 0x{:04X}".format(crc))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_calc_crc_Event](vscphlp_calc_crc_event.md)



[filename](./bottom_copyright.md ':include')