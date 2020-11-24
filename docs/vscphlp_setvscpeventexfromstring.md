> Deprecated: Use [vscphlp_convertStringToEventEx](vscphlp_convertstringtoeventex.md)

```clike
int vscphlp_setVscpEventExFromString( vscpEventEx *pEvent, 
                                        const char *pstr )
```

### Parameters

#### pEvent
The VSCP event ex which will be written to.

#### pstr
Pointer to string buffer that contain an event in string form

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....



### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set VSCP event ex from a string. 

#### C example

```clike
vscpEventEx ex6;
if ( VSCP_ERROR_SUCCESS == vscphlp_setVscpEventExFromString( &ex6,  
      "0,10,6,0,20170102T19:32:48,0,FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD,0x8A,0x00,0x1E" ) ) 
    printf( "OK vscphlp_setVscpEventExFromString class=%d Type=%d\n", 
                   ex6.vscp_class, ex6.vscp_type );
}
else {
    printf( "\aError: vscphlp_setVscpEventExFromString\n");
}
```

### See Also
[vscphlp_setVscpEventFromString](vscphlp_setvscpeventfromstring.md)



[filename](./bottom_copyright.md ':include')