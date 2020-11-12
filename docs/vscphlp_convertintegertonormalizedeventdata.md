

```clike
int vscphlp_convertIntegerToNormalizedEventData( unsigned char *pdata,
                                unsigned short *psize,
                                unsigned long long val64,
                                unsigned char unit,
                                unsigned char sensoridx )
```

### Parameters

#### pdata
Pointer to data buffer that will get the result. The buffer should be large enough to hold the normalized data. That is bigger than eight bytes.

#### psize
The size of the written data will be returned here.

#### value
Floating point value to write as a 64-bit float.

#### unit
A unit value 0-3

#### sensoridx
A sensor index value 0-7


### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Write an integer value as measurement event data in normalized integer form.

#### C example

```clike
Example will be added. TODO
```



[filename](./bottom_copyright.md ':include')