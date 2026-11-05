#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <string>

#include <gtest/gtest.h>
#include "vscphelperlib.h"

namespace {

uint16_t
findUdpPort()
{
#ifdef _WIN32
    const SOCKET socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketHandle == INVALID_SOCKET) {
        return 0;
    }
#else
    const int socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketHandle < 0) {
        return 0;
    }
#endif

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = 0;
#ifdef _WIN32
    int addressLength = sizeof(address);
    const int bindResult = bind(socketHandle,
                                reinterpret_cast<const sockaddr *>(&address),
                                sizeof(address));
    const int nameResult = bindResult == 0 ?
                             getsockname(socketHandle,
                                         reinterpret_cast<sockaddr *>(&address),
                                         &addressLength) : SOCKET_ERROR;
    closesocket(socketHandle);
    return nameResult == 0 ? ntohs(address.sin_port) : 0;
#else
    socklen_t addressLength = sizeof(address);
    const int bindResult = bind(socketHandle,
                                reinterpret_cast<const sockaddr *>(&address),
                                sizeof(address));
    const int nameResult = bindResult == 0 ?
                             getsockname(socketHandle,
                                         reinterpret_cast<sockaddr *>(&address),
                                         &addressLength) : -1;
    close(socketHandle);
    return nameResult == 0 ? ntohs(address.sin_port) : 0;
#endif
}

} // namespace

TEST(DatagramClient, UdpConfigurationAndValidation)
{
    const long handle = vscphlp_newUdpClient();
    ASSERT_NE(0, handle);

    int connected = -1;
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isDatagramClientConnected(handle, &connected));
    EXPECT_EQ(0, connected);
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_isDatagramClientConnected(handle, nullptr));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_configureDatagramClient(handle, nullptr));
    EXPECT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(handle, "{\"ip\":\"udp://127.0.0.1:9598\"}"));
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(handle, "{\"ip\":\"invalid endpoint\"}"));
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(handle, "{invalid json"));

    vscpEventEx event{};
    vscpEventFilter filter{};
    uint16_t count = 0;
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendDatagramEventEx(handle, nullptr));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_receiveDatagramEventEx(handle, nullptr, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_receiveDatagramEventEx(handle, &event, -1));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setDatagramClientFilter(handle, &filter));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getDatagramClientCount(handle, &count));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_clearDatagramClientQueue(handle));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_connectDatagramClient(handle));
}

TEST(DatagramClient, MulticastConfigurationAndValidation)
{
    const long handle = vscphlp_newMulticastClient();
    ASSERT_NE(0, handle);

    EXPECT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(
                handle, "{\"ip\":\"udp://224.0.23.158:9598\",\"ttl\":1}"));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_disconnectDatagramClient(0));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_closeDatagramClient(handle));
}

TEST(DatagramClient, UdpLoopbackSendAndReceive)
{
    const long handle = vscphlp_newUdpClient();
    ASSERT_NE(0, handle);
    const uint16_t port = findUdpPort();
    ASSERT_NE(0, port);

    const std::string config =
      "{\"ip\":\"udp://127.0.0.1:" + std::to_string(port) + "\"}";
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_configureDatagramClient(handle, config.c_str()));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_connectDatagramClient(handle));

    vscpEventEx outgoing{};
    outgoing.vscp_class = 10;
    outgoing.vscp_type = 6;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendDatagramEventEx(handle, &outgoing));

    vscpEventEx incoming{};
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveDatagramEventEx(handle, &incoming, 2000));
    EXPECT_EQ(outgoing.vscp_class, incoming.vscp_class);
    EXPECT_EQ(outgoing.vscp_type, incoming.vscp_type);
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));
}
