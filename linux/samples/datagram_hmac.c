/*
 * Authenticated (AES-256-CBC + HMAC-SHA-256) UDP or multicast datagrams.
 *
 * Usage: datagram_hmac [udp|multicast] [udp://host:port]
 *
 * Keys are read from VSCP_DATAGRAM_AES_KEY and VSCP_DATAGRAM_HMAC_KEY as
 * 64 hexadecimal digits each. Generate them with `openssl rand -hex 32` (run
 * twice for two independent keys) and provision the same values on every peer.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vscphelperlib.h"

static const char *
hexKey(const char *name)
{
    const char *value = getenv(name);
    size_t i;
    if (!value || strlen(value) != 64) {
        return NULL;
    }
    for (i = 0; i < 64; ++i) {
        if (!isxdigit((unsigned char)value[i])) {
            return NULL;
        }
    }
    return value;
}

static void
clearConfig(char *config, size_t length)
{
    volatile char *bytes = config;
    while (length--) {
        *bytes++ = 0;
    }
}

static int
closeClient(long client)
{
    const int result = vscphlp_closeDatagramClient(client);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Could not close datagram client: %d\n", result);
    }
    return result;
}

int
main(int argc, char *argv[])
{
    const char *mode = argc > 1 ? argv[1] : "udp";
    const int multicast = strcmp(mode, "multicast") == 0;
    const char *endpoint;
    const char *aesKey = hexKey("VSCP_DATAGRAM_AES_KEY");
    const char *hmacKey = hexKey("VSCP_DATAGRAM_HMAC_KEY");
    const char *p;
    char config[512];
    long client;
    int result;
    vscpEventEx outgoing;
    vscpEventEx incoming;

    if (!multicast && strcmp(mode, "udp") != 0) {
        fprintf(stderr, "Usage: %s [udp|multicast] [udp://host:port]\n", argv[0]);
        return 2;
    }
    if (!aesKey || !hmacKey) {
        fprintf(stderr, "Set VSCP_DATAGRAM_AES_KEY and VSCP_DATAGRAM_HMAC_KEY to "
                        "independent 64-digit hex keys (openssl rand -hex 32)\n");
        return 2;
    }
    endpoint = argc > 2 ? argv[2] :
               multicast ? "udp://224.0.23.158:9598" : "udp://127.0.0.1:9598";
    for (p = endpoint; *p; ++p) {
        if ((unsigned char)*p < 0x20 || *p == '"' || *p == '\\') {
            fprintf(stderr, "Endpoint contains an invalid character\n");
            return 2;
        }
    }

    /* encryption 3 selects AES-256; a nonempty hmac-key enables authentication. */
    result = snprintf(config, sizeof(config),
                      "{\"ip\":\"%s\",%s\"encryption\":3,\"key\":\"%s\",\"hmac-key\":\"%s\"}",
                      endpoint, multicast ? "\"ttl\":1," : "", aesKey, hmacKey);
    if (result < 0 || (size_t)result >= sizeof(config)) {
        clearConfig(config, sizeof(config));
        fprintf(stderr, "Could not format the datagram configuration\n");
        return 2;
    }

    client = multicast ? vscphlp_newMulticastClient() : vscphlp_newUdpClient();
    if (!client) {
        clearConfig(config, sizeof(config));
        fprintf(stderr, "Could not create %s client\n", mode);
        return 1;
    }

    result = vscphlp_configureDatagramClient(client, config);
    clearConfig(config, sizeof(config));
    if (result == VSCP_ERROR_SUCCESS) {
        result = vscphlp_connectDatagramClient(client);
    }
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Could not configure or connect %s client: %d\n", mode, result);
        closeClient(client);
        return 1;
    }

    memset(&outgoing, 0, sizeof(outgoing));
    outgoing.vscp_class = 10;
    outgoing.vscp_type = 6;
    result = vscphlp_sendDatagramEventEx(client, &outgoing);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Authenticated %s send failed: %d\n", mode, result);
        closeClient(client);
        return 1;
    }

    /* Only datagrams with a valid HMAC for the configured keys are delivered. */
    memset(&incoming, 0, sizeof(incoming));
    result = vscphlp_receiveDatagramEventEx(client, &incoming, 5000);
    if (result == VSCP_ERROR_SUCCESS) {
        printf("Received authenticated %s event: class=%u type=%u\n",
               mode, incoming.vscp_class, incoming.vscp_type);
    }
    else {
        fprintf(stderr, "Authenticated %s receive failed or timed out: %d\n", mode, result);
    }

    if (closeClient(client) != VSCP_ERROR_SUCCESS) {
        return 1;
    }
    return result == VSCP_ERROR_SUCCESS ? 0 : 1;
}
