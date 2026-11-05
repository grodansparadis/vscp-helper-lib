# UDP and multicast clients

The helper library exposes the pinned VSCP `vscp-client-udp` and
`vscp-client-multicast` implementations through a separate datagram-client
handle API. These handles are independent of TCP sessions created by
`vscphlp_newSession`; use only the datagram-client functions below with them.

UDP sends to a configured destination and listens on that port. Multicast
sends to a multicast group and joins that group to receive events. Both
clients exchange VSCP event datagrams and support the normal VSCP event
filters. Datagram transport is connectionless: delivery, ordering, and
retransmission are not guaranteed, and there is no server acknowledgement.

## UDP example

The UDP client defaults to the VSCP broadcast address and port. The
[UDP sample](../linux/samples/datagram_udp.c) shows configuration, sending,
and waiting for an event from a peer:

```c
long client = vscphlp_newUdpClient();
if (!client) {
    /* Handle allocation failure. */
}

int result = vscphlp_configureDatagramClient(
    client, "{\"ip\":\"udp://255.255.255.255:9598\"}");
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_connectDatagramClient(client);
}
if (result != VSCP_ERROR_SUCCESS) {
    vscphlp_closeDatagramClient(client);
    /* Handle the configuration or socket error. */
}

vscpEventEx outgoing = {0};
outgoing.vscp_class = 10;
outgoing.vscp_type = 6;
result = vscphlp_sendDatagramEventEx(client, &outgoing);

vscpEventEx incoming = {0};
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_receiveDatagramEventEx(client, &incoming, 5000);
}
vscphlp_closeDatagramClient(client);
```

The sample needs a compatible peer to send an event back; UDP does not echo
the transmitted event. The `ip` endpoint sets both the UDP destination and
local receive port.
Choose an address and port reachable by the intended peer. An optional
`interface` value selects a network interface by name or index.

## Multicast example

Multicast requires a multicast group address. Set `ttl` to limit the number
of router hops; it defaults to `1`. The
[multicast sample](../linux/samples/datagram_multicast.c) uses the VSCP
multicast group:

```c
long client = vscphlp_newMulticastClient();
if (!client) {
    /* Handle allocation failure. */
}

int result = vscphlp_configureDatagramClient(
    client, "{\"ip\":\"udp://224.0.23.158:9598\",\"ttl\":1}");
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_connectDatagramClient(client);
}
if (result != VSCP_ERROR_SUCCESS) {
    vscphlp_closeDatagramClient(client);
    /* Handle the configuration or socket error. */
}

vscpEventEx outgoing = {0};
outgoing.vscp_class = 10;
outgoing.vscp_type = 6;
result = vscphlp_sendDatagramEventEx(client, &outgoing);

vscpEventEx incoming = {0};
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_receiveDatagramEventEx(client, &incoming, 5000);
}
vscphlp_closeDatagramClient(client);
```

Use the same multicast group and port on peers that should exchange events.
Set `interface` when the host has multiple network interfaces or when the
IPv6 group requires an interface scope. The client requests multicast
loopback be disabled, but behavior depends on the interface and OS; an event
sent through Linux loopback can still be received locally. Use another peer
for a reliable multicast demonstration.

## Configuration and receive operations

The JSON configuration accepts `ip` (`udp://host:port` or a bare
`host:port`), `port`, and `interface`. Multicast additionally accepts `ttl`
(0–255). Both clients accept optional `encryption`, `key`, `hmac-key`, and
event filter properties (`priority-filter`, `priority-mask`, `class-filter`,
`class-mask`, `type-filter`, `type-mask`, `guid-filter`, and `guid-mask`).
Configure before connecting. Without `hmac-key`, the `encryption` option is
legacy AES encryption with **no integrity protection**; use HMAC
authentication as described below whenever datagrams are encrypted.

## Authenticated UDP and multicast (HMAC)

Both clients support opt-in AES-CBC with HMAC-SHA-256 (encrypt-then-MAC, the
same version-1 records used by [authenticated TCP binary
mode](frame_security.md)). Set `encryption` to `1`, `2`, or `3` for AES-128,
AES-192, or AES-256, supply `key` as 32, 48, or 64 hexadecimal digits, and set
`hmac-key` to an **independent** 32-byte key encoded as exactly 64
hexadecimal digits:

```json
{
  "ip": "udp://192.168.1.255:9598",
  "encryption": 3,
  "key": "<64 hex digits from openssl rand -hex 32>",
  "hmac-key": "<another 64 hex digits from openssl rand -hex 32>"
}
```

Multicast uses the same security options together with its group, `ttl`, and
optional `interface`. Generate each key separately with a cryptographically
secure generator (`openssl rand -hex 32`; use `-hex 16` or `-hex 24` for the
AES-128 or AES-192 key; the HMAC key is always 32 bytes) and provision
identical values on every peer through a secure channel. There is no key
exchange.

A nonempty `hmac-key` enables authentication for **both sending and
receiving**:

* Each datagram is
  `[0x55][version/length:2][type/encryption:1][ciphertext][IV:16][HMAC:16]`.
  The big-endian prefix holds version `1` in its three high bits and the
  13-bit inner length. A fresh random IV is used for every datagram, and the
  tag is the leftmost 128 bits of HMAC-SHA-256 over the prefix, type byte,
  ciphertext, and IV.
* Receivers require version 1 and the configured AES algorithm, and verify the
  tag in constant time **before** decryption, then check padding, event length,
  and CRC. Plaintext, legacy-encrypted, forged, or tampered datagrams are
  discarded before filtering or queueing; a receive call times out if no valid
  datagram arrives. The library may log a diagnostic, and there is no fallback
  to legacy framing.
* Configuration is transactional. `vscphlp_configureDatagramClient` returns
  `VSCP_ERROR_PARAMETER` and keeps the previous settings for a malformed
  `hmac-key`, `hmac-key` with `encryption` `0`, an AES key that has not been
  explicitly configured (the legacy default key is never used), or an HMAC key
  whose prefix reuses the AES key. Omitted options keep their values; set
  `"hmac-key": ""` to explicitly disable authentication.
* Disconnect before changing security settings, and drain the queue or call
  `vscphlp_clearDatagramClientQueue` first; configuration is rejected while
  events received under a different security policy are still queued.

Authenticated and legacy peers cannot exchange datagrams until configured
alike. HMAC authenticates the sender's key possession but does **not** prevent
replay of captured datagrams; add sequence numbers or timestamps at the
application level if replay matters. Keep configuration strings containing
keys out of logs and clear them after use.

### C example

The [authenticated datagram sample](../linux/samples/datagram_hmac.c) reads
both keys from the environment instead of hard-coding them:

```c
/* aesHex and hmacHex hold independent 64-digit hex keys from secure storage. */
char config[256];
snprintf(config, sizeof(config),
         "{\"ip\":\"udp://127.0.0.1:9598\",\"encryption\":3,"
         "\"key\":\"%s\",\"hmac-key\":\"%s\"}", aesHex, hmacHex);

long client = vscphlp_newUdpClient();   /* or vscphlp_newMulticastClient() */
int result = client ? vscphlp_configureDatagramClient(client, config)
                    : VSCP_ERROR_MEMORY;
memset(config, 0, sizeof(config));
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_connectDatagramClient(client);
}
/* Send and receive exactly as with unauthenticated clients. */
```

Run it with:

```sh
export VSCP_DATAGRAM_AES_KEY=$(openssl rand -hex 32)
export VSCP_DATAGRAM_HMAC_KEY=$(openssl rand -hex 32)
build/datagram_hmac udp                       # loopback, receives its own event
build/datagram_hmac udp udp://192.168.1.255:9598
build/datagram_hmac multicast                 # needs a peer with the same keys
```

With the default `udp://127.0.0.1:9598`, the UDP sample receives its own
authenticated event, which verifies the configuration on one host. For
multicast, use another peer with the same group and keys; depending on the
interface and OS, the client may also receive its own event.

### Python example

The updated Python wrapper accepts a configuration dictionary or JSON
string. This loopback example reads independently provisioned AES-256 and
HMAC keys as hexadecimal strings from the environment:

```python
import os
import sys

import vscp
import vscphelper


def check(status):
    if status != 0:
        raise RuntimeError("VSCP datagram error {}".format(status))


client = vscphelper.newUdpClient()
if not client:
    raise RuntimeError("Could not create UDP client")
try:
    check(vscphelper.configureDatagramClient(client, {
        "ip": "udp://127.0.0.1:9598", "encryption": 3,
        "key": os.environ["VSCP_DATAGRAM_AES_KEY"],
        "hmac-key": os.environ["VSCP_DATAGRAM_HMAC_KEY"],
    }))
    check(vscphelper.connectDatagramClient(client))
    event = vscp.vscpEventEx()
    event.vscpclass, event.vscptype = 10, 6
    check(vscphelper.sendDatagramEventEx(client, event))
    received = vscp.vscpEventEx()
    check(vscphelper.receiveDatagramEventEx(client, received, 3000))
    print(received.vscpclass, received.vscptype)
finally:
    status = vscphelper.closeDatagramClient(client)
    if status != 0:
        print("Close failed (error {})".format(status), file=sys.stderr)
```

Use `newMulticastClient()` with a multicast `ip`, `ttl`, and optional
`interface` for multicast; another configured peer is normally required.
See the runnable
[Python example](https://github.com/grodansparadis/pyvscphelper/blob/main/examples/authenticated_udp.py)
in the wrapper source.

### JavaScript example

The Node.js wrapper uses the same configuration. It returns a status code or
`[status, value]` and throws for invalid JavaScript argument types:

```javascript
const { loadHelper, ENCRYPTION } = require('node-vscp-helper');
const api = loadHelper();
const aesKey = process.env.VSCP_DATAGRAM_AES_KEY;
const hmacKey = process.env.VSCP_DATAGRAM_HMAC_KEY;
if (!/^[0-9a-f]{64}$/i.test(aesKey || '') ||
    !/^[0-9a-f]{64}$/i.test(hmacKey || '')) {
    throw new Error('Provide independent AES-256 and HMAC keys as 64 hex digits');
}
function check(status) {
    if (status !== 0) throw new Error(`VSCP datagram error ${status}`);
}
const client = api.newUdpClient();
if (!client) throw new Error('Could not create UDP client');
try {
    check(api.configureDatagramClient(client, {
        ip: 'udp://127.0.0.1:9598', encryption: ENCRYPTION.AES256,
        key: aesKey, 'hmac-key': hmacKey
    }));
    check(api.connectDatagramClient(client));
    check(api.sendDatagramEventEx(client, { vscpClass: 10, vscpType: 6 }));
    const [status, event] = api.receiveDatagramEventEx(client, 3000);
    check(status);
    console.log(event.vscpClass, event.vscpType);
} finally {
    const status = api.closeDatagramClient(client);
    if (status !== 0) console.error(`Close failed: ${status}`);
}
```

For multicast, use `newMulticastClient()` and configure the group, TTL, and
interface. The synchronous receive blocks the event loop; use a worker when
needed. See the runnable
[Node.js example](https://github.com/grodansparadis/node-vscp-helper/blob/master/examples/authenticated-udp.js)
in the wrapper source.

`vscphlp_receiveDatagramEventEx` waits up to the supplied timeout in
milliseconds. A timeout returns `VSCP_ERROR_TIMEOUT`; `vscphlp_sendDatagramEventEx`
and receive operations report the underlying VSCP error code. Configure a
filter with `vscphlp_setDatagramClientFilter`; inspect or clear queued events
with `vscphlp_getDatagramClientCount` and `vscphlp_clearDatagramClientQueue`.
Always close the client with `vscphlp_closeDatagramClient`.

| API | Possible results |
|---|---|
| `vscphlp_newUdpClient`, `vscphlp_newMulticastClient` | Nonzero handle on success; `0` on allocation failure or handle exhaustion |
| `vscphlp_configureDatagramClient` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_MEMORY` |
| `vscphlp_connectDatagramClient` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` (invalid authentication settings), or a transport/socket error |
| `vscphlp_disconnectDatagramClient`, `vscphlp_closeDatagramClient` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, or a transport/socket error |
| `vscphlp_isDatagramClientConnected` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_sendDatagramEventEx`, `vscphlp_receiveDatagramEventEx` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER`, or a transport/event error; receive may return `VSCP_ERROR_TIMEOUT` |
| `vscphlp_setDatagramClientFilter`, `vscphlp_getDatagramClientCount` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_clearDatagramClientQueue` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE` |

Build the optional samples with:

```sh
cmake -S . -B build -DBUILD_DATAGRAM_SAMPLES=ON
cmake --build build --target datagram_udp datagram_multicast datagram_hmac
```

[filename](./bottom_copyright.md ':include')
