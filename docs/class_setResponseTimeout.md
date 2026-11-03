



```clike
void setResponseTimeout(uint32_t to)
```

### Parameters

#### to
Timeout value in milliseconds.


### Return Value
Nothing

### Description
Set the response timeout in milliseconds. The default is 2000 milliseconds; values below 100 milliseconds are treated as 1000 milliseconds.




#### C++ example

With a `VscpRemoteTcpIf client`, set the response timeout to three seconds:

```cpp
client.setResponseTimeout(3000);
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')