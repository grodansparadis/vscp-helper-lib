


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
Pointer to an eight-bit value that will receive the value read from the register.

#### ifGUID
GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.

#### pdestGUID
GUID of the remote node.

#### bLevel2
If true, this is a true Level II read operation.

### Return Value
`CANAL_ERROR_SUCCESS` (`0`) is returned on a reply and `CANAL_ERROR_TIMEOUT` when waiting
times out. In the pinned implementation, a null output or destination GUID also returns `0`
(`false`), indistinguishable from success; callers must validate both pointers before
calling. Send/receive errors are not propagated directly and can result in a
timeout.

### Description
Read a level II register. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `interface_guid` and `device_guid` for the target device.

```cpp
uint8_t value = 0;
int result = client.readLevel2Register(0x10, 0, &value, interface_guid, &device_guid);
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "readLevel2Register failed (error " << result << ")\n";
} else {
    std::cout << "Value: " << static_cast<unsigned>(value) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')