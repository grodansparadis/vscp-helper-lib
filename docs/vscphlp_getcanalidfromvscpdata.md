

```clike
unsigned long 
vscphlp_getCANALidFromData( unsigned char priority,
                                unsigned short vscp_class, 
                                unsigned short vscp_type )
```

### Parameters

#### priority
VSCP event priority (0-7).

#### vscp_class
VSCP Class.

#### vscp_type
VSCP type.

### Return Value
CANAL (CAN) id. 

### Description
Construct a CANAL id (CAN id ) from a VSCP event. 

#### C example

With the helper-library headers and standard C headers included:

```clike
unsigned long canal_id = vscphlp_getCANALidFromData(3, 10, 6);
printf("0x%08lX\n", canal_id);
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

canal_id = vscphelper.getCANALidFromData(3, 10, 6)
print("0x{:08X}".format(canal_id))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')