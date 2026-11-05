


```clike
void setRegisterOperationTiming( uint8_t retries, 
                                uint32_t resendto, 
                                uint32_t errorto)
```

### Parameters

#### retries
Number of allowed resend retries before giving up a register read.

#### resendto
Resend timeout in milliseconds.

#### erroto
Error timeout in milliseconds before giving up a read register operation.


### Return Value
Returns no value or error code.

### Description
Set register read/write timings.




#### C++ example

With a `VscpRemoteTcpIf client`, use three retries, a one-second resend timeout, and a five-second error timeout:

```cpp
client.setRegisterOperationTiming(3, 1000, 5000);
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')