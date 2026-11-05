

```clike
unsigned short 
vscphlp_getVSCPclassFromCANALid( unsigned long id )
```

### Parameters

#### id
Extended 29-bit CANAL id to get head from.

### Return Value
Returns the extracted VSCP class, not an error code.

### Description
Get the VSCP class from a CANAL message id. 

#### C example

```clike
unsigned long canalid = 0x0c0a0601;
unsigned short can_vscpclass = vscphlp_getVSCPclassFromCANALid( canalid );
if ( 10 == can_vscpclass ) {
    printf("VSCP Class = %d\n", can_vscpclass );
}
else {
    printf("\aError: vscphlp_getVSCPclassFromCANAALid = %d\n", can_vscpclass );
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

canal_id = vscphelper.getCANALidFromData(7, 10, 6)
print(vscphelper.getVSCPclassFromCANALid(canal_id))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')