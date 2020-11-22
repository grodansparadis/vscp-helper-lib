

```clike
long vscphlp_readStringValue( const char * pStrValue )
```

### Parameters

#### pStrValue
Pointer to string representation of value.

### Return Value
The converted number as a signed long.. 

### Description
Convert a string to an integer value. The string can be expressed as a decimal (10, 00001 ) or a hexadecimal value(0xff).

#### C example

```clike
long readValue = vscphlp_readStringValue("0x22");
```



[filename](./bottom_copyright.md ':include')