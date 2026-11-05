# vscphlp_getVersionString

```c
const char *vscphlp_getVersionString(void);
```

Returns the loaded helper library's full version in
`major.minor.revision.patch` format. This is the library version, not the
remote server version returned by [vscphlp_getVersion](vscphlp_getversion.md).
No session or server connection is required.

The return value is a non-null, null-terminated, read-only string owned by the
library. Do not modify or free it. It remains valid until the library is
unloaded and can be read concurrently by multiple threads. It does not return an error code.

## C example

```c
#include <stdio.h>
#include <vscphelperlib.h>

int main(void)
{
    printf("Helper library version: %s\n", vscphlp_getVersionString());
    return 0;
}
```

## C++ example

```cpp
#include <iostream>
#include <vscphelperlib.h>

int main()
{
    std::cout << "Helper library version: " << vscphlp_getVersionString() << '\n';
}
```

## Python example

The current Python wrapper does not yet expose this function directly. Use
`ctypes` and set `VSCPHELPER_LIB` to the full path of the shared library:

```python
import ctypes
import os

library = ctypes.CDLL(os.environ["VSCPHELPER_LIB"])
get_version = library.vscphlp_getVersionString
get_version.argtypes = []
get_version.restype = ctypes.c_char_p
print("Helper library version: {}".format(get_version().decode("ascii")))
```

## JavaScript availability

The [Node.js binding](bindings.md#nodejs) exposes this function through
`api.raw.vscphlp_getVersionString()`. An example is available in
[Using with JavaScript](using.md#using-with-javascript).

[filename](./bottom_copyright.md ':include')
