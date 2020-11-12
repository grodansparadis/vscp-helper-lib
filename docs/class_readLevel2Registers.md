


```clike
int readLevel2Registers( uint32_t reg,
                        uint16_t page,
                        uint8_t count,
                        uint8_t *pval,
                        cguid& ifGUID,
                        cguid *pdestGUID = NULL,
                        bool bLevel2 = false )
```

### Parameters

#### reg
First register to read (32-bit value for true Level II).

#### page
Page to read the register(s) from.

#### count
Number of registers to read.

#### pval
Pointer to array that will get read value(s) from register(s).

#### ifGUID
GUID for interface this events should be sent on. This is used to read registers of Level I devices.

#### pdestGUID
GUID for remote node.

#### bLevel2
If true this is a true Level II read operation.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Read one or more level II registers. 



[filename](./bottom_copyright.md ':include')