# Internal test files

Non of the files in this folder is of interest to end users.
Yes! that is true.

Use demands that libvscphelper is installed

http://www.adp-gmbh.ch/cpp/gcc/create_lib.html
http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html

nm -Ca ../libvscphelper15.so  - list method sin lib

cc example1.c -o example1 -L.. -lvscphelper

## Raw TCP and TLS samples

Build the migrated transport samples from the repository root:

```sh
cmake -S . -B build -DBUILD_RAW_TRANSPORT_SAMPLES=ON
cmake --build build --target stcptest stcp_tls_client
```

Run their loopback regression tests with
`cmake --build build --target test_raw_transport_samples`. The tests require
Python 3.8 or later and the `openssl` command.

The samples use OpenSSL's socket and TLS BIOs. They do not use the helper
library's TCP client. Socket and TLS operations have a five-second timeout;
system DNS resolution may take longer.

`build/stcptest [host:port] [user] [password]` connects twice, authenticates,
and times one and then 101 NOOP commands. It defaults to `127.0.0.1:9598`.
For helper-library API examples, see `bigtest` and the tests in `tests/alltest`.

`build/stcp_tls_client [host:port] [ca.pem] [client-cert.pem [client-key.pem]]`
connects to a TLS server and prints its first response. It defaults to
`localhost:4433` and verifies the server certificate and hostname using the
OpenSSL default CA file (or `SSL_CERT_FILE`). Specify a CA file for a
self-signed server. For client authentication, provide a certificate and key,
or a single PEM containing both.
