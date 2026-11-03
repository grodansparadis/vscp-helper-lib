

```clike
int vscphlp_replaceBackslash( char *pStr )
```

### Parameters

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

#### pStr
Pointer to a writable null-terminated string to convert in place.


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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')



