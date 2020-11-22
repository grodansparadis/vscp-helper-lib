


```clike
int readLevel2Register( uint32_t reg,
                        uint16_t page,
                        uint8_t *pval,
                        cguid& ifGUID,
                        cguid *pdestGUID = NULL,
                        bool bLevel2 = false)
```

### Parameters

#### reg
Register to read (32-bit value for true Level II).

#### page
Page to read the register from.

#### pval
Pointer to eight bit value that will get read value from register.

#### ifGUID
GUID for interface this events should be sent on. This is used to read registers of Level I devices.

#### pdestGUID
GUID for remote node.

#### bLevel2
If true this is a true Level II read operation.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Read a level II register. 




[filename](./bottom_copyright.md ':include')