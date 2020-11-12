

```clike
vscphlp_getRemoteVariableBlob( long handle, 
                            const char *pName, 
                            char *pValue, 
                            size_t len ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pValue
Pointer to string buffer that will get the value of the date variable.

#### len
Size of string buffer.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

### Description
Get variable value from blob variable. The returned value is BASE64 encoded. 

#### C example

```clike
TODO
```

#### Python example

```python
TODO
```

### See Also
[vscphlp_setRemoteVariableBlob](vscphlp_setremotevariableblob.md)



[filename](./bottom_copyright.md ':include')