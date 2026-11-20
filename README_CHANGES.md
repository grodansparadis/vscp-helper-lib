# Changes in vscp-helper-lib

Every change that goes into a release is listed here, newest release first.
Add each change under **Unreleased** when it is made. When a release is
tagged, rename **Unreleased** to the version and date, and start a new
**Unreleased** section above it.

## Unreleased

- Measurement unit conversion for all measurement classes: `vscphlp_convertMeasurementUnit()`, `vscphlp_getMeasurementUnitInfo()`, `vscphlp_convertMeasurement()` and `vscphlp_convertMeasurementEx()` use the unit table compiled into the library. The alternative `vscphlp_loadUnitExpressions()`/`vscphlp_loadUnitExpressionsFromString()` and `vscphlp_convertMeasurementUnitExpr()` evaluate the conversion expressions of `vscp-units.json` at runtime; `vscphlp_evalUnitExpression()` evaluates one expression. Tests in `tests/alltest/units.cpp` (`test_units` target)
- Floating point measurement values are read and written MSB first, as the specification says (from vscp: `vscphlp_convertFloatToFloatEventData()`/`vscphlp_makeFloatMeasurementEvent()` wrote them in host byte order, and MEASUREMENT32/64 values were read in host byte order)
- Build against vscp master 50a5337c3 (measurement unit conversion)
- Build against the latest vscp master (d75d4f5c6)
### TLS configuration

- Added per-session C APIs: `vscphlp_enableTLS`,
  `vscphlp_setTLSAutoSelect`, `vscphlp_setTLSMode`, `vscphlp_getTLSMode`, and
  `vscphlp_setTLSOptions`.
- Applications can configure peer verification, CA files or directories,
  client certificates, private keys, and key passwords without relying only
  on environment variables. Settings are copied per session and apply to the
  next connection; they persist across reconnects.
- TLS usage, server certificate and hostname verification, mutual TLS,
  transport selection, and troubleshooting are described in the
  [TLS guide](docs/tls.md) and [API reference](docs/vscphlp_tls.md).

### Binary VSCP link frames

- Added `vscphlp_doCmdBinary` and `vscphlp_isBinaryMode` to negotiate and
  inspect binary mode after connecting and authenticating.
- Added `vscphlp_sendBinaryFrame`, `vscphlp_receiveBinaryFrame`, and
  `vscphlp_freeBinaryFrame` for raw frame I/O over TCP or TLS. Received frame
  buffers are allocated by the library and must be released with
  `vscphlp_freeBinaryFrame`.
- Existing event send and receive APIs can operate in binary mode. Event
  receives process confirmations, validate CRCs, and acknowledge received
  events. A binary event send does not wait for server confirmation.
- Receive timeouts preserve partial frame input. Binary negotiation and
  malformed or interrupted streams have explicit error handling.

See [binary link frames](docs/binary_link.md) and
[sending and receiving events](docs/events.md) for usage and ownership.

### Authenticated frame encryption

- Added `vscphlp_setBinarySecurity` and `vscphlp_getBinarySecurity` for
  automatic per-session version-1 framing. It supports AES-128/192/256-CBC
  with HMAC-SHA-256, using a 128-bit authentication tag.
- Added standalone `vscphlp_encryptFrameV1` and `vscphlp_decryptFrameV1`
  helpers for applications that manage version-1 frames themselves.
- Authentication is checked before decryption. Invalid or downgraded records
  are rejected without returning plaintext.
- Updated the VSCP pin to
  [`fc71470`](https://github.com/grodansparadis/vscp/commit/fc71470a6277657a74e6fbd72dab87a43c42b1e3)
  and adopted its native authenticated TCP binary mode. TCP now uses a
  two-byte length prefix instead of the previous three-byte version-1 prefix;
  authenticated TCP peers must use the upstream format. UDP and multicast
  framing is unchanged. The C API remains unchanged.

Legacy, unauthenticated binary framing remains the default. Authenticated
mode requires matching independently provisioned keys and a compatible
version-1 peer. It does not provide key exchange or replay protection. Frame
security starts after binary negotiation, so use TLS to protect the initial
login as well. See [frame security](docs/frame_security.md) for limits and
examples.

### Versioning and compatibility

- Updated the base library version to 16.0.0, retaining the automatic
  Git-derived fourth component.
- The library version now has four components:
  `major.minor.revision.patch`. The revision is set manually from 0 to 255;
  the patch is derived from the Git first-parent commit count and can exceed
  255. Version synchronization and package metadata were updated accordingly.
- Added `vscphlp_getVersionString()` to obtain the full library version
  without opening a session. The returned string is owned by the library.
  The existing `vscphlp_getVersion` continues to query the server.
- Consumers that parse version strings or package metadata should accept the
  additional component. Windows numeric version resources limit the patch to
  65,535; macOS retains a three-component Mach-O compatibility version while
  package metadata keeps the full version.

### Build, samples, and tests

- Removed the unused legacy `test/simple` example; active test suites remain
  in `tests/`.
- Removed the obsolete package-build script, incomplete Python extension
  skeleton, unused Windows session-manager sources and static resource file,
  and legacy `tests/oldtest` program. Removed tracked Python bytecode and
  added ignore rules for generated Python caches.
- Consolidated the historical changelog into this file.
- CMake now requires version 3.14 or newer and a C++17 compiler.
- Git submodules were removed. CMake fetches pinned VSCP, spdlog, and
  nlohmann-json sources, with local source overrides available for offline
  builds. Git is required to apply compatibility patches to a build-local
  VSCP client copy; fetched sources are not modified.
- Updated the GUID parser integration for the pinned VSCP dependency and
  reorganized the test build.
- Updated raw TCP/TLS samples and added loopback tests, plus tests for TLS
  settings ([#4](https://github.com/grodansparadis/vscp-helper-lib/issues/4)),
  binary framing, authenticated encryption, dependency fetching, and version
  metadata. See [tests/README.md](tests/README.md) for commands.

### Documentation and bindings

- Proofread and expanded the documentation, including TLS, event handling,
  binary frames, frame security, versioning, and C/C++ and Python examples.
- Updated the separate Python wrapper with binary negotiation and frame I/O,
  AES/HMAC session and standalone frame helpers, and UDP/multicast client
  operations. TCP and datagram event-ex operations translate both the older
  and current `pyvscp` layouts. Other event helpers still require a matching
  `pyvscp` ABI. `closeSession` no longer unloads the shared library or
  invalidates other sessions. TLS configuration setters still require `ctypes`.
- Added a Node.js wrapper with synchronous session, event, AES/HMAC, binary,
  UDP, and multicast helpers. It includes lazy C API bindings and retains
  the existing `hello()` addon function. Raw calls require native buffer and
  ownership handling. Some functions declared in the C header are not
  exported by the current library; attempting to bind one reports an error.
- Added Python and Node.js authenticated transport examples and integration
  tests. These wrapper changes are in separate repositories and require
  corresponding releases; installing an older published package will not
  provide the new APIs. See [language bindings](docs/bindings.md),
  [frame security](docs/frame_security.md), and
  [UDP/multicast clients](docs/datagram_clients.md).
- The project remains under the MIT license; the copyright notice was updated.

### UDP and multicast clients

- Added UDP and multicast datagram clients using the pinned
  `vscp-client-udp` and `vscp-client-multicast` implementations. The C API now
  supports creating/configuring clients, connecting, sending and receiving
  events, filtering, and queue inspection. Added optional UDP and multicast
  samples; see [UDP and multicast clients](docs/datagram_clients.md).
- Added opt-in HMAC authentication for UDP and multicast clients by updating
  the pinned VSCP sources to
  [`f76ac50`](https://github.com/grodansparadis/vscp/commit/f76ac50a67213749819a2014ff99f1a46bf3ea04).
  A nonempty `hmac-key` JSON option, together with AES `encryption` and an
  explicit `key`, sends and requires version-1 AES-CBC + HMAC-SHA-256
  datagrams. Plaintext, legacy-encrypted, forged, and tampered datagrams are
  discarded before delivery. Legacy datagram framing remains the default. HMAC
  does not provide replay protection. Added the `datagram_hmac` sample; see
  [authenticated UDP and multicast](docs/datagram_clients.md#authenticated-udp-and-multicast-hmac).

### Single-channel receive loop

- Exposed `vscphlp_setSingleChannelReceiveLoop` and
  `vscphlp_isSingleChannelReceiveLoopEnabled` to enable and query the
  single-channel text receive loop from the C API. A dedicated reader
  demultiplexes events and command responses on one TCP/TLS connection,
  allowing event sends while another thread waits for events. The server must
  support commands during `RCVLOOP`; only `SEND`, `NOOP`, `CLRA`, and
  `QUITLOOP` are supported, and command replies must be distinguishable from
  bare `+OK` receive-loop keepalives. See
  [single-channel TCP/IP receive loop](docs/single_channel.md) for examples
  and limitations.

### Logging

- Added library-wide `vscphlp_configureLogging`, `vscphlp_disableLogging`,
  `vscphlp_flushLogging`, and `vscphlp_getLastLoggingError` C APIs.
- Underlying TCP/TLS and helper diagnostics can use stderr, rotating files,
  or both with independent severity thresholds. The private, thread-safe
  spdlog logger does not change the application's logger. Existing stderr
  diagnostics remain the default; failed configuration retains the previous
  logger. See [logging](docs/logging.md) for examples and safety limits.

### Upgrade notes

- Connections start in text mode. Binary mode must be negotiated after login;
  close and reopen the connection to return to text mode.
- Raw frame reads and event receives consume the same incoming stream. Do not
  alternate them without a dispatch strategy.
- With automatic frame security enabled, pass plaintext events or plaintext
  inner frames to the normal APIs. Do not pre-encrypt them with the standalone
  helpers before sending.
- The Python `ctypes` examples must use sessions created by the same loaded C
  library rather than mixing them with wrapper-owned sessions.

### Commit history

The original release summary compared
[v15.2.242](https://github.com/grodansparadis/vscp-helper-lib/releases/tag/v15.2.242)
(September 23, 2026) through
[`e32aeb0`](https://github.com/grodansparadis/vscp-helper-lib/commit/e32aeb03b401d8cc4346727eb07f7de8053bb483)
(November 3, 2026); see the
[comparison](https://github.com/grodansparadis/vscp-helper-lib/compare/v15.2.242...e32aeb03b401d8cc4346727eb07f7de8053bb483).
The sections above also include subsequent unreleased work.

- Pin VSCP to fc71470 and use its native authenticated TCP binary mode
- Add scripts/download-artifacts.sh to download and verify the newest CI build artifacts
- Python wrapper and node.js wrapper (e5dd40f)
- Fix Windows datagram IP Helper linkage (c9fea0d)
- Initial plan (e5c322c)
- Update version (7a7cdb2)
- Align Windows patch with pinned VSCP sources (34667d1)
- Fix Windows VSCP getopt include build (148b2a1)
- Initial plan (01b79cc)
- Added missing files (e531e3b)
- Initial plan (478ff05)
- Added UDP and multicast support (8dc7667)
- Using latest vscp code (997208c)
- Added log test files (845b852)
- Implemented the safer private-logger approach (79d1093)
- Added docs for logging and missing files (ad847cc)
- Added spdlog support Fixes #3 (223f452)
- Keep authenticated transport patch LF on Windows checkouts (8e5f2bd)
- Initial plan (7f8d709)
- Docs for binary mode added (e32aeb0)
- Binary mode added (ee79779)
- Fixes #4 (231dd95)
- Added vscphlp_getVersionString (f9aad14)
- Added vscphlp_getVersionString (6d06bb1)
- Added version level (e1f362b)
- Docs proof reading (0d731c0)
- Version updated (f62ab5d)
- Fixed broken tests (a0d6e5c)
- Submodules removed (now downloaded) (c52c6ce)

## v15.2.242 - 2026-09-23

- Updated submodules (c2da296)
- Test (34174c4)
- Cleaning up (3df3ece)
- Test CI run on older code (932b483)
- Added small logo (37c422c)

## Historical changes

Imported from the legacy changelog, retaining its original date codes.

- 260820 AKHE Adopted CalVer versioning: 26-08-6.
- 211015 AKHE Fixed bug in session handler.
- 211015 AKHE Fixed bug in doCmdReceiveEx which cause VSCP_ERROR_PARAMETER to be returned also on OK received event.
- 211014 AKHE doCmdDataAvailable did not handle error return correctly.
- 211011 AKHE Windows port now adopts to new setup.
- 210701 AKHE Protected stod conversions in helper lib that could throw exceptions for invalid strings
- 210630 AKHE Fixed bug in vscp_hexStr2ByteArray
- 210629 AKHE Path for install of man-pages was wrong. Fixed
- 210628 AKHE Version 15.0.0
