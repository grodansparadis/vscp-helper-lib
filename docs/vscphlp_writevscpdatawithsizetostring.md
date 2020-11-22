

```clike
int vscphlp_writeVscpDataWithSizeToString( const unsigned char *pdata,
                                              const unsigned short. 
                                              char *pstr, 
                                              size_t len,
                                              int bUseHtmlBreak,
                                              int bBreak )
```

### Parameters

#### pData
Pointer to VSCP data array.

#### size
Number of bytes in data array.

#### pstr
Pointer to string buffer that will receive string.

#### len
Size of string receive buffer.

#### bUseHtmlBreak
Set to true (non zero) to use “\<br\>” instead of “\n” as linebreak in string.
bBreak

Set to true (non zero) to add the break character.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Write VSCP data in readable form to a possibly multi line string from a data array with size.


[filename](./bottom_copyright.md ':include')