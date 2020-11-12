

```clike
bool checkReturnValue(bool bClear = false)
```

### Parameters

#### bClear
If set to true the input queue array will be cleared before the call.

### Return Value
True is returned if a positive response (+OK) s received from the remote VSCP server, false otherwise which can be the result of a negative reply or a timeout. 

### Description
Check the response from the remote VSCP server and look for an error or a correctly carried out command. 



[filename](./bottom_copyright.md ':include')