

```clike
int writeLevel2Register(uint32_t reg,
                        uint16_t page,
                        uint8_t *pval,
                        cguid& ifGUID,
                        cguid *pdestGUID = NULL,
                        bool bLevel2 = false )
```

### Parameters

#### reg
Register to write to (32-bit value for true Level II).

#### page
Page at which the register is located.

#### pval
Pointer to byte that should be written into the register. At exit this byte contains the written value returned from the node where it got written.

#### ifGUID
GUID for interface this events should be sent on. This is used to read registers of Level I devices.

#### pdestGUID
GUID for remote node.

#### bLevel2
If true this is a true Level II read operation.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Write a level 2 register.



[filename](./bottom_copyright.md ':include')