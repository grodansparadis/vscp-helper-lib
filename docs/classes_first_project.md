# First project

This example connects to a VSCP daemon, executes the
[NOOP command](https://grodansparadis.gitbooks.io/the-vscp-daemon/tcp_ip_protocol_description.html#noop),
and disconnects.

With a checkout of the VSCP project in `external/vscp`, use its `vscp_core`
CMake target. It provides the remote TCP class and its OpenSSL transport
dependency.

```cmake
cmake_minimum_required(VERSION 3.16)
project(noop LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/vscp)
add_executable(noop noop.cpp)
target_link_libraries(noop PRIVATE vscp_core)
```

See the [VSCP library reference](https://github.com/grodansparadis/vscp/blob/master/docs/library_reference.md)
for details.

Save the following as `noop.cpp`:

```cpp
#include <cstdio>
#include <vscpremotetcpif.h>

int main(int argc, char* argv[])
{
    const char* host = argc > 1 ? argv[1] : "127.0.0.1:9598";
    const char* user = argc > 2 ? argv[2] : "admin";
    const char* password = argc > 3 ? argv[3] : "secret";

    VscpRemoteTcpIf client;
    if (VSCP_ERROR_SUCCESS != client.doCmdOpen(host, user, password)) {
        std::fprintf(stderr, "Failed to connect to the VSCP daemon\n");
        return 1;
    }

    if (VSCP_ERROR_SUCCESS != client.doCmdNOOP()) {
        std::fprintf(stderr, "NOOP failed\n");
        client.doCmdClose();
        return 1;
    }

    if (VSCP_ERROR_SUCCESS != client.doCmdClose()) {
        std::fprintf(stderr, "Failed to close the connection\n");
        return 1;
    }

    return 0;
}
```

Run it with `./noop host:port user password`, or use `./noop` for the default
connection parameters.

[filename](./bottom_copyright.md ':include')
