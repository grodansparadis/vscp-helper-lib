# Changes since v15.2.242

**Status:** Unreleased changes compared with
[v15.2.242](https://github.com/grodansparadis/vscp-helper-lib/releases/tag/v15.2.242),
published September 23, 2026. This summary covers the repository through
commit [`e32aeb0`](https://github.com/grodansparadis/vscp-helper-lib/commit/e32aeb03b401d8cc4346727eb07f7de8053bb483)
on November 3, 2026. Changes made after that commit are not included.
See the [full comparison](https://github.com/grodansparadis/vscp-helper-lib/compare/v15.2.242...e32aeb03b401d8cc4346727eb07f7de8053bb483).

## TLS configuration

* Added per-session C APIs: `vscphlp_enableTLS`,
  `vscphlp_setTLSAutoSelect`, `vscphlp_setTLSMode`, `vscphlp_getTLSMode`, and
  `vscphlp_setTLSOptions`.
* Applications can configure peer verification, CA files or directories,
  client certificates, private keys, and key passwords without relying only
  on environment variables. Settings are copied per session and apply to the
  next connection; they persist across reconnects.
* TLS usage, server certificate and hostname verification, mutual TLS,
  transport selection, and troubleshooting are described in the
  [TLS guide](docs/tls.md) and [API reference](docs/vscphlp_tls.md).

## Binary VSCP link frames

* Added `vscphlp_doCmdBinary` and `vscphlp_isBinaryMode` to negotiate and
  inspect binary mode after connecting and authenticating.
* Added `vscphlp_sendBinaryFrame`, `vscphlp_receiveBinaryFrame`, and
  `vscphlp_freeBinaryFrame` for raw frame I/O over TCP or TLS. Received frame
  buffers are allocated by the library and must be released with
  `vscphlp_freeBinaryFrame`.
* Existing event send and receive APIs can operate in binary mode. Event
  receives process confirmations, validate CRCs, and acknowledge received
  events. A binary event send does not wait for server confirmation.
* Receive timeouts preserve partial frame input. Binary negotiation and
  malformed or interrupted streams have explicit error handling.

See [binary link frames](docs/binary_link.md) and
[sending and receiving events](docs/events.md) for usage and ownership.

## Authenticated frame encryption

* Added `vscphlp_setBinarySecurity` and `vscphlp_getBinarySecurity` for
  automatic per-session version-1 framing. It supports AES-128/192/256-CBC
  with HMAC-SHA-256, using a 128-bit authentication tag.
* Added standalone `vscphlp_encryptFrameV1` and `vscphlp_decryptFrameV1`
  helpers for applications that manage version-1 frames themselves.
* Authentication is checked before decryption. Invalid or downgraded records
  are rejected without returning plaintext.

Legacy, unauthenticated binary framing remains the default. Authenticated
mode requires matching independently provisioned keys and a compatible
version-1 peer. It does not provide key exchange or replay protection. Frame
security starts after binary negotiation, so use TLS to protect the initial
login as well. See [frame security](docs/frame_security.md) for limits and
examples.

## Versioning and compatibility

* The library version now has four components:
  `major.minor.revision.patch`. The revision is set manually from 0 to 255;
  the patch is derived from the Git first-parent commit count and can exceed
  255. Version synchronization and package metadata were updated accordingly.
* Added `vscphlp_getVersionString()` to obtain the full library version
  without opening a session. The returned string is owned by the library.
  The existing `vscphlp_getVersion` continues to query the server.
* Consumers that parse version strings or package metadata should accept the
  additional component. Windows numeric version resources limit the patch to
  65,535; macOS retains a three-component Mach-O compatibility version while
  package metadata keeps the full version.

## Build, samples, and tests

* CMake now requires version 3.14 or newer and a C++17 compiler.
* Git submodules were removed. CMake fetches pinned VSCP, spdlog, and
  nlohmann-json sources, with local source overrides available for offline
  builds. Git is required to apply the authenticated-framing patch to a
  build-local VSCP client copy; fetched sources are not modified.
* Updated the GUID parser integration for the pinned VSCP dependency and
  reorganized the test build.
* Updated raw TCP/TLS samples and added loopback tests, plus tests for TLS
  settings ([#4](https://github.com/grodansparadis/vscp-helper-lib/issues/4)),
  binary framing, authenticated encryption, dependency fetching, and version
  metadata. See [tests/README.md](tests/README.md) for commands.

## Documentation and bindings

* Proofread and expanded the documentation, including TLS, event handling,
  binary frames, frame security, versioning, and C/C++ and Python examples.
* The Python wrapper does not yet expose the new TLS, binary-frame, or frame
  security functions directly; the guides show how to call the C API with
  `ctypes`. The current Node.js binding does not expose these helper APIs.
  See [language bindings](docs/bindings.md).
* The project remains under the MIT license; the copyright notice was updated.

## Upgrade notes

* Connections start in text mode. Binary mode must be negotiated after login;
  close and reopen the connection to return to text mode.
* Raw frame reads and event receives consume the same incoming stream. Do not
  alternate them without a dispatch strategy.
* With automatic frame security enabled, pass plaintext events or plaintext
  inner frames to the normal APIs. Do not pre-encrypt them with the standalone
  helpers before sending.
* The Python `ctypes` examples must use sessions created by the same loaded C
  library rather than mixing them with wrapper-owned sessions.

## Additional unreleased work (after the comparison above)

* Added UDP and multicast datagram clients using the pinned
  `vscp-client-udp` and `vscp-client-multicast` implementations. The C API now
  supports creating/configuring clients, connecting, sending and receiving
  events, filtering, and queue inspection. Added optional UDP and multicast
  samples; see [UDP and multicast clients](docs/datagram_clients.md).
* Exposed `vscphlp_setSingleChannelReceiveLoop` and
  `vscphlp_isSingleChannelReceiveLoopEnabled` to enable and query the
  single-channel text receive loop from the C API. A dedicated reader
  demultiplexes events and command responses on one TCP/TLS connection,
  allowing event sends while another thread waits for events. The server must
  support commands during `RCVLOOP`; only `SEND`, `NOOP`, `CLRA`, and
  `QUITLOOP` are supported, and command replies must be distinguishable from
  bare `+OK` receive-loop keepalives. See
  [single-channel TCP/IP receive loop](docs/single_channel.md) for examples
  and limitations.
* Added library-wide `vscphlp_configureLogging`, `vscphlp_disableLogging`,
  `vscphlp_flushLogging`, and `vscphlp_getLastLoggingError` C APIs.
* Underlying TCP/TLS and helper diagnostics can use stderr, rotating files,
  or both with independent severity thresholds. The private, thread-safe
  spdlog logger does not change the application's logger. Existing stderr
  diagnostics remain the default; failed configuration retains the previous
  logger. See [logging](docs/logging.md) for examples and safety limits.
