


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
Pointer to an array that will receive the values read from the registers.

#### ifGUID
GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.

#### pdestGUID
GUID of the remote node.

#### bLevel2
If true, this is a true Level II read operation.

### Return Value
`CANAL_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`CANAL_ERROR_PARAMETER` if a required pointer is null or `count` exceeds 128,
and `CANAL_ERROR_TIMEOUT` if the expected replies do not arrive. Send/receive
errors are not propagated directly and can result in a timeout.

### Description
Read one or more level II registers. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `interface_guid` and `device_guid` for the target device.

```cpp
uint8_t values[4] = {};
int result = client.readLevel2Registers(0x10, 0, 4, values, interface_guid, &device_guid);
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "readLevel2Registers failed (error " << result << ")\n";
} else {
    std::cout << "First value: " << static_cast<unsigned>(values[0]) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')