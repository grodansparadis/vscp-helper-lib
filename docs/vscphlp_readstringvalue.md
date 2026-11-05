

```clike
unsigned long vscphlp_readStringValue( const char * pStrValue )
```

### Parameters

#### pStrValue
Pointer to string representation of value.

### Return Value
The parsed number is returned as `unsigned long`, not as an error code. Invalid or
out-of-range text produces `0`, which is also a valid value. Negative numbers are converted
to unsigned. The input pointer must be non-null.

### Description
Convert a string to an integer. The string can represent a decimal value (10, 00001) or a hexadecimal value (0xff).

#### C example

```clike
unsigned long readValue = vscphlp_readStringValue("0x22");
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

The official [Node.js binding](bindings.md#nodejs) does not currently expose
this function. A Node.js FFI example is available in
[Using with JavaScript](using.md#using-with-javascript).

[filename](./bottom_copyright.md ':include')