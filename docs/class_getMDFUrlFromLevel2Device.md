

```clike
int getMDFUrlFromLevel2Device( cguid& ifGUID,
                                cguid& destGUID,
                                wxString &strurl,
                                bool bLevel2 = false )
```

### Parameters

#### ifGUID
GUID for interface this events should be sent on. This is used to read registers of Level I devices.

#### pdestGUID
GUID for remote node.

#### strURL
Reference to string that will get the MDF url of the device if call is successful..

#### bLevel2
If true this is a true Level II read operation.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get MDf file from device registers.



[filename](./bottom_copyright.md ':include')