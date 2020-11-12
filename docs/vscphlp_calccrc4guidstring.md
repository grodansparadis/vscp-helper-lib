

```clike
unsigned char vscphlp_calcCRC4GUIDString( unsigned char *strguid)
```

### Parameters

#### strguid
String containing GUID on standard string form.


### Return Value
8-bit CRC for GUID. 

### Description
Calculate 8-bit crc for a GUID string. 

#### C example

```clike
// Calculate GUID for GUID string
char strguid[64];
strcpy( strguid, "FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD" );
crc8 = vscphlp_calcCRC4GUIDString( strguid);
printf("CRC = %02X\n", crc8 )
```



[filename](./bottom_copyright.md ':include')