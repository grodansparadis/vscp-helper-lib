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

## UDP and multicast clients

Build the helper-library datagram examples from the repository root:

```sh
cmake -S . -B build -DBUILD_DATAGRAM_SAMPLES=ON
cmake --build build --target datagram_udp datagram_multicast datagram_hmac
```

`build/datagram_udp` sends to the VSCP UDP broadcast endpoint by default;
`build/datagram_multicast` joins the VSCP multicast group. Both examples wait
for an event from a peer, so they time out if no compatible peer is active.
`build/datagram_hmac [udp|multicast] [udp://host:port]` sends and receives
AES-256 + HMAC-SHA-256 authenticated datagrams. Set `VSCP_DATAGRAM_AES_KEY`
and `VSCP_DATAGRAM_HMAC_KEY` to independent keys from `openssl rand -hex 32`.
In UDP mode it defaults to `udp://127.0.0.1:9598` and receives its own event.
For multicast, use a peer configured with the same group and keys; local
loopback behavior varies by interface and operating system.
See [the datagram client guide](../../docs/datagram_clients.md) for
configuration details and network requirements.

`build/stcp_tls_client [host:port] [ca.pem] [client-cert.pem [client-key.pem]]`
connects to a TLS server and prints its first response. It defaults to
`localhost:4433` and verifies the server certificate and hostname using the
OpenSSL default CA file (or `SSL_CERT_FILE`). Specify a CA file for a
self-signed server. For client authentication, provide a certificate and key,
or a single PEM containing both.
