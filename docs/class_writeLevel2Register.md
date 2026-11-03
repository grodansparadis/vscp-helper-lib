

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
Pointer to the byte to write to the register. On return, it contains the written value returned by the node.

#### ifGUID
GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.

#### pdestGUID
GUID of the remote node.

#### bLevel2
If true, this is a true Level II write operation.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Write a level 2 register.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `interface_guid` and `device_guid` for the target device. This changes a device register; verify the address and value first.

```cpp
uint8_t value = 42;
int result = client.writeLevel2Register(0x10, 0, &value, interface_guid, &device_guid);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "writeLevel2Register failed (error " << result << ")\n";
} else {
    std::cout << "Read-back value: " << static_cast<unsigned>(value) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')