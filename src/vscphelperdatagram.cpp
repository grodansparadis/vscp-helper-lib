#include "vscphelperlib.h"

#include "vscp-client-base.h"
#include "vscp-client-multicast.h"
#include "vscp-client-udp.h"

#include <climits>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <utility>

namespace {

std::mutex g_datagramClientsMutex;
std::map<long, std::shared_ptr<CVscpClient>> g_datagramClients;
long g_nextDatagramHandle = 0x40000000L;

std::shared_ptr<CVscpClient>
getDatagramClient(long handle)
{
    std::lock_guard<std::mutex> lock(g_datagramClientsMutex);
    const auto it = g_datagramClients.find(handle);
    return it == g_datagramClients.end() ? nullptr : it->second;
}

template<typename Client>
long
createDatagramClient()
{
    try {
        std::shared_ptr<CVscpClient> client = std::make_shared<Client>();
        std::lock_guard<std::mutex> lock(g_datagramClientsMutex);
        if (g_nextDatagramHandle == LONG_MAX) {
            return 0;
        }

        const long handle = g_nextDatagramHandle++;
        if (!g_datagramClients.emplace(handle, std::move(client)).second) {
            return 0;
        }
        return handle;
    }
    catch (const std::bad_alloc &) {
        return 0;
    }
}

} // namespace

extern "C" HELPERLIB_API long
vscphlp_newUdpClient(void)
{
    return createDatagramClient<vscpClientUdp>();
}

extern "C" HELPERLIB_API long
vscphlp_newMulticastClient(void)
{
    return createDatagramClient<vscpClientMulticast>();
}

extern "C" HELPERLIB_API int
vscphlp_configureDatagramClient(long handle, const char *jsonConfig)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!jsonConfig) {
        return VSCP_ERROR_PARAMETER;
    }
    try {
        return client->initFromJson(jsonConfig) ? VSCP_ERROR_SUCCESS : VSCP_ERROR_PARAMETER;
    }
    catch (const std::bad_alloc &) {
        return VSCP_ERROR_MEMORY;
    }
}

extern "C" HELPERLIB_API int
vscphlp_connectDatagramClient(long handle)
{
    const auto client = getDatagramClient(handle);
    return client ? client->connect() : VSCP_ERROR_INVALID_HANDLE;
}

extern "C" HELPERLIB_API int
vscphlp_disconnectDatagramClient(long handle)
{
    const auto client = getDatagramClient(handle);
    return client ? client->disconnect() : VSCP_ERROR_INVALID_HANDLE;
}

extern "C" HELPERLIB_API int
vscphlp_closeDatagramClient(long handle)
{
    std::shared_ptr<CVscpClient> client;
    {
        std::lock_guard<std::mutex> lock(g_datagramClientsMutex);
        const auto it = g_datagramClients.find(handle);
        if (it == g_datagramClients.end()) {
            return VSCP_ERROR_INVALID_HANDLE;
        }
        client = std::move(it->second);
        g_datagramClients.erase(it);
    }
    return client->disconnect();
}

extern "C" HELPERLIB_API int
vscphlp_isDatagramClientConnected(long handle, int *pConnected)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!pConnected) {
        return VSCP_ERROR_PARAMETER;
    }
    *pConnected = client->isConnected() ? 1 : 0;
    return VSCP_ERROR_SUCCESS;
}

extern "C" HELPERLIB_API int
vscphlp_sendDatagramEventEx(long handle, const vscpEventEx *pEvent)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!pEvent) {
        return VSCP_ERROR_PARAMETER;
    }
    vscpEventEx event = *pEvent;
    return client->send(event);
}

extern "C" HELPERLIB_API int
vscphlp_receiveDatagramEventEx(long handle, vscpEventEx *pEvent, long timeoutMs)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!pEvent || timeoutMs < 0) {
        return VSCP_ERROR_PARAMETER;
    }
    return client->receiveBlocking(*pEvent, timeoutMs);
}

extern "C" HELPERLIB_API int
vscphlp_setDatagramClientFilter(long handle, const vscpEventFilter *pFilter)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!pFilter) {
        return VSCP_ERROR_PARAMETER;
    }
    vscpEventFilter filter = *pFilter;
    return client->setfilter(filter);
}

extern "C" HELPERLIB_API int
vscphlp_getDatagramClientCount(long handle, uint16_t *pCount)
{
    const auto client = getDatagramClient(handle);
    if (!client) {
        return VSCP_ERROR_INVALID_HANDLE;
    }
    if (!pCount) {
        return VSCP_ERROR_PARAMETER;
    }
    return client->getcount(pCount);
}

extern "C" HELPERLIB_API int
vscphlp_clearDatagramClientQueue(long handle)
{
    const auto client = getDatagramClient(handle);
    return client ? client->clear() : VSCP_ERROR_INVALID_HANDLE;
}
