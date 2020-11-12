


```clike
int vscphlp_tableGetAverage( const unsigned char *pName, 
                        const char *pFrom, 
                        const char *pTo,
                        double *pAverage )
```

### Parameters

#### tblName
Name of an existing table.

#### from
Date/time from which resulting data should be fetched. Set to “0000-01-01T00:00:00” for beginning of time.

#### to
Date/time to which resulting data should be fetched. Set to “9999-12-31T23:59:59” for end of time.

#### pAverage
Pointer to a double that will get the average of all values in the interval on success.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get the average of all values for an interval in a named table. 



[filename](./bottom_copyright.md ':include')