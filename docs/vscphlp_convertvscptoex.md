

```clike
int vscphlp_convertVSCPtoEx( vscpEventEx *pEventEx, 
                              const vscpEvent *pEvent )
```

### Parameters

#### pEventEx
VSCP event ex to convert to

#### pEvent
VSCP event to convert to.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert VSCP standard event form to ex form. 

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {1, 2, 3};
vscpEvent event = {0};
event.vscp_class = 30; event.vscp_type = 5;
event.sizeData = sizeof(data); event.pdata = data;
vscpEventEx extended = {0};
int result = vscphlp_convertVSCPtoEx(&extended, &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertVSCPtoEx failed (error %d)\n", result);
} else {
    printf("class=%u type=%u data=%u,%u,%u\n",
           extended.vscp_class, extended.vscp_type,
           extended.data[0], extended.data[1], extended.data[2]);
}
```


#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 30
event.vscptype = 5
extended = vscp.vscpEventEx()
result = vscphelper.convertVSCPtoEx(extended, event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertVSCPtoEx failed (error {})".format(result))
print(extended.vscpclass, extended.vscptype)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_convertVSCPfromEx](vscphlp_convertvscpfromex.md)



[filename](./bottom_copyright.md ':include')