


```clike
void setAfterCommandSleep(uint16_t to)
```

### Parameters

#### to
Sleep value in milliseconds. This value is currently ignored.

### Return Value
Returns no value or error code. This compatibility setter is a no-op.

### Description
This method is retained for backward compatibility. It currently has no effect on the delay after a command.



#### C++ example

With a `VscpRemoteTcpIf client`, this retained compatibility method has no effect:

```cpp
client.setAfterCommandSleep(0);
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')