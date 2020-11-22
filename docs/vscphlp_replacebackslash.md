

```clike
int vscphlp_replaceBackslash( const char *pStr )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

#### pStr
Pointer to null terminated string to convert.


### Description
Replace all backslashes (“\”) in a string with forward slashes (“/”). 




[filename](./bottom_copyright.md ':include')



