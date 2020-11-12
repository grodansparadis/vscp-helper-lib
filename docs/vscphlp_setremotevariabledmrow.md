

```clike
int vscphlp_setRemoteVariableDMROW( long handle, 
                                    const char *pName, 
                                    char *pValue ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pValue
Pointer to string that contains the value the variable should be set to.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop.

### Description
Set variable value for a DM row variable. The value is always expected to be BASE64 encoded. 

#### C example

```clike
TODO
```

#### Python example

```python
TODO
```

### See Also
[vscphlp_getRemoteVariableDMROW](vscphlp_getremotevariabledmrow.md)



[filename](./bottom_copyright.md ':include')