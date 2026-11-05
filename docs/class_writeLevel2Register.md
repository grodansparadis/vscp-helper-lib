

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
Pointer to the byte to write to the register. The implementation compares it
with the reply but does not replace it with the returned value.

#### ifGUID
GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.

#### pdestGUID
GUID of the remote node.

#### bLevel2
If true, this is a true Level II write operation.

### Return Value
`CANAL_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`CANAL_ERROR_PARAMETER` for a null value pointer, `CANAL_ERROR_REGISTER` if
the checked reply value differs, and `CANAL_ERROR_TIMEOUT` if no matching
reply arrives.

The destination GUID must also be valid; it is dereferenced without a null
check. Send/receive errors are not propagated directly and can result in a
timeout.

### Description
Write a level 2 register.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `interface_guid` and `device_guid` for the target device. This changes a device register; verify the address and value first.

```cpp
uint8_t value = 42;
int result = client.writeLevel2Register(0x10, 0, &value, interface_guid, &device_guid);
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "writeLevel2Register failed (error " << result << ")\n";
} else {
    std::cout << "Read-back value: " << static_cast<unsigned>(value) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')