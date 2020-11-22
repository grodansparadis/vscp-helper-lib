


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
None

### Description
Set register read/write timings.




[filename](./bottom_copyright.md ':include')