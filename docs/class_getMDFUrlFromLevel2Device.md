

```clike
bool getMDFUrlFromLevel2Device( cguid& ifGUID,
                                cguid& destGUID,
                                std::string &strurl,
                                bool bLevel2 = false )
```

### Parameters

#### ifGUID
GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.

#### destGUID
GUID of the remote node.

#### strURL
Reference to a string that will receive the device's MDF URL on success.

#### bLevel2
If true, this is a true Level II read operation.

### Return Value
Returns true on success and false on failure.

### Description
Get the MDF file from the device registers.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `interface_guid` and `device_guid` for the target device:

```cpp
std::string url;
if (!client.getMDFUrlFromLevel2Device(interface_guid, device_guid, url)) {
    std::cerr << "Could not read the MDF URL\n";
} else {
    std::cout << url << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')