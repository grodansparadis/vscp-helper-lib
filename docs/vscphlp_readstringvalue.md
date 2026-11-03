

```clike
long vscphlp_readStringValue( const char * pStrValue )
```

### Parameters

#### pStrValue
Pointer to string representation of value.

### Return Value
The converted number as a signed long.

### Description
Convert a string to an integer. The string can represent a decimal value (10, 00001) or a hexadecimal value (0xff).

#### C example

```clike
long readValue = vscphlp_readStringValue("0x22");
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

value = vscphelper.readStringValue("0x22")
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')