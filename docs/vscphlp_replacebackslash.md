

```clike
int vscphlp_replaceBackslash( char *pStr )
```

### Parameters

#### pStr
Pointer to a writable null-terminated string to convert in place.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Replace all backslashes (“\”) in a string with forward slashes (“/”). 




#### C example

```clike
char path[] = "a\\b\\c";
int result = vscphlp_replaceBackslash(path);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "replaceBackslash failed (error %d)\n", result);
} else {
    printf("%s\n", path);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

result, path = vscphelper.replaceBackslash(r"a\b\c")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("replaceBackslash failed (error {})".format(result))
print(path)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')


