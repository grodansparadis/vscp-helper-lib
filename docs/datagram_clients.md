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
IPv6 group requires an interface scope. The client disables multicast loopback
for locally transmitted packets, so use another peer to observe the sample's
send.

## Configuration and receive operations

The JSON configuration accepts `ip` (`udp://host:port` or a bare
`host:port`), `port`, and `interface`. Multicast additionally accepts `ttl`
(0–255). Both clients accept optional `encryption`, `key`, and event filter
properties (`priority-filter`, `priority-mask`, `class-filter`, `class-mask`,
`type-filter`, `type-mask`, `guid-filter`, and `guid-mask`). Configure before
connecting. The VSCP datagram encryption option is legacy encryption, not an
authenticated transport; do not treat it as a substitute for a secure network.

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
| `vscphlp_connectDatagramClient`, `vscphlp_disconnectDatagramClient`, `vscphlp_closeDatagramClient` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, or a transport/socket error |
| `vscphlp_isDatagramClientConnected` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_sendDatagramEventEx`, `vscphlp_receiveDatagramEventEx` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER`, or a transport/event error; receive may return `VSCP_ERROR_TIMEOUT` |
| `vscphlp_setDatagramClientFilter`, `vscphlp_getDatagramClientCount` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_clearDatagramClientQueue` | `VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_HANDLE` |

Build the optional samples with:

```sh
cmake -S . -B build -DBUILD_DATAGRAM_SAMPLES=ON
cmake --build build --target datagram_udp datagram_multicast
```

[filename](./bottom_copyright.md ':include')
