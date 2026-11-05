#include <stdio.h>

#include "vscphelperlib.h"

int
main(void)
{
    const char *config = "{\"ip\":\"udp://224.0.23.158:9598\",\"ttl\":1}";
    const long client = vscphlp_newMulticastClient();
    if (!client) {
        fprintf(stderr, "Could not create multicast client\n");
        return 1;
    }

    int result = vscphlp_configureDatagramClient(client, config);
    if (result == VSCP_ERROR_SUCCESS) {
        result = vscphlp_connectDatagramClient(client);
    }
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Could not configure or connect multicast client: %d\n", result);
        vscphlp_closeDatagramClient(client);
        return 1;
    }

    vscpEventEx outgoing = {0};
    outgoing.vscp_class = 10;
    outgoing.vscp_type = 6;
    result = vscphlp_sendDatagramEventEx(client, &outgoing);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Multicast send failed: %d\n", result);
        vscphlp_closeDatagramClient(client);
        return 1;
    }

    vscpEventEx incoming = {0};
    result = vscphlp_receiveDatagramEventEx(client, &incoming, 5000);
    if (result == VSCP_ERROR_SUCCESS) {
        printf("Received multicast event: class=%u type=%u\n",
               incoming.vscp_class, incoming.vscp_type);
    }
    else {
        fprintf(stderr, "Multicast receive failed or timed out: %d\n", result);
    }

    vscphlp_closeDatagramClient(client);
    return result == VSCP_ERROR_SUCCESS ? 0 : 1;
}
