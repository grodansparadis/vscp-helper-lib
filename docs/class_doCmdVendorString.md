

```clike
const char *doCmdVendorString(void)
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
A pointer to a null terminated string containing vendor information is returned. On failure a NULL pointer is returned. 

### Description
Get the vendor (maker of DL/DLL) string. This is intended for CANAL. 



[filename](./bottom_copyright.md ':include')