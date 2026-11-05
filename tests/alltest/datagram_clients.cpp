#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#include <array>
#include <cstring>
#include <string>
#include <vector>

#include <crc.h>
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

// Public test keys only; never use them in production.
const char *const kAesKeyHex = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
const char *const kHmacKeyHex = "202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f";

struct DatagramKeys {
    std::array<unsigned char, 32> aes{}, mac{};
    DatagramKeys()
    {
        for (size_t i = 0; i < aes.size(); ++i) {
            aes[i] = static_cast<unsigned char>(i);
            mac[i] = static_cast<unsigned char>(i + 32);
        }
    }
};

std::string
authenticatedUdpConfig(uint16_t port)
{
    return "{\"ip\":\"udp://127.0.0.1:" + std::to_string(port) +
           "\",\"encryption\":3,\"key\":\"" + kAesKeyHex +
           "\",\"hmac-key\":\"" + kHmacKeyHex + "\"}";
}

std::vector<unsigned char>
plainEventFrame(uint16_t vscpClass, uint16_t vscpType)
{
    const size_t headerLength = 35;
    std::vector<unsigned char> frame(1 + headerLength + 2, 0);
    frame[14] = static_cast<unsigned char>(vscpClass >> 8);
    frame[15] = static_cast<unsigned char>(vscpClass);
    frame[16] = static_cast<unsigned char>(vscpType >> 8);
    frame[17] = static_cast<unsigned char>(vscpType);
    const uint16_t checksum = crcSlow(frame.data() + 1, static_cast<int>(frame.size() - 3));
    frame[frame.size() - 2] = static_cast<unsigned char>(checksum >> 8);
    frame.back() = static_cast<unsigned char>(checksum);
    return frame;
}

// Wire format: [0x55][version 1 / 13-bit length, big-endian][inner v1 frame].
std::vector<unsigned char>
authenticatedDatagram(const std::vector<unsigned char> &plain, const DatagramKeys &keys)
{
    std::vector<unsigned char> inner(plain.size() + 48);
    size_t length = 0;
    if (vscphlp_encryptFrameV1(inner.data(), inner.size(), &length, plain.data(), plain.size(),
                               keys.aes.data(), keys.aes.size(), keys.mac.data(), keys.mac.size(),
                               nullptr, 0, VSCP_ENCRYPTION_AES256) != VSCP_ERROR_SUCCESS) {
        return {};
    }
    inner.resize(length);
    const uint16_t prefix = static_cast<uint16_t>((1u << 13) | length);
    std::vector<unsigned char> wire = {0x55, static_cast<unsigned char>(prefix >> 8),
                                       static_cast<unsigned char>(prefix)};
    wire.insert(wire.end(), inner.begin(), inner.end());
    return wire;
}

bool
sendRawDatagram(uint16_t port, const std::vector<unsigned char> &payload)
{
#ifdef _WIN32
    const SOCKET socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketHandle == INVALID_SOCKET) {
        return false;
    }
#else
    const int socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketHandle < 0) {
        return false;
    }
#endif
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(port);
    const int sent = static_cast<int>(sendto(socketHandle, reinterpret_cast<const char *>(payload.data()),
                                             static_cast<int>(payload.size()), 0,
                                             reinterpret_cast<const sockaddr *>(&address), sizeof(address)));
#ifdef _WIN32
    closesocket(socketHandle);
#else
    close(socketHandle);
#endif
    return sent == static_cast<int>(payload.size());
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

TEST(DatagramClient, AuthenticationConfigurationValidation)
{
    const long handle = vscphlp_newUdpClient();
    ASSERT_NE(0, handle);
    const std::string aes = std::string("\"key\":\"") + kAesKeyHex + "\"";
    const std::string mac = std::string("\"hmac-key\":\"") + kHmacKeyHex + "\"";

    // HMAC requires an AES algorithm and an explicitly configured AES key.
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(handle, ("{\"encryption\":0," + mac + "}").c_str()));
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(handle, ("{\"encryption\":3," + mac + "}").c_str()));
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(
                handle, ("{\"encryption\":3," + aes + ",\"hmac-key\":\"2021\"}").c_str()));
    EXPECT_EQ(VSCP_ERROR_PARAMETER,
              vscphlp_configureDatagramClient(
                handle, ("{\"encryption\":3," + aes + ",\"hmac-key\":\"" + kAesKeyHex + "\"}").c_str()));
    EXPECT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(handle, ("{\"encryption\":3," + aes + "," + mac + "}").c_str()));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_configureDatagramClient(handle, "{\"hmac-key\":\"\"}"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));

    const long multicast = vscphlp_newMulticastClient();
    ASSERT_NE(0, multicast);
    EXPECT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(
                multicast, ("{\"ip\":\"udp://224.0.23.158:9598\",\"ttl\":1,\"encryption\":3," +
                            aes + "," + mac + "}").c_str()));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(multicast));
}

TEST(DatagramClient, UdpAuthenticatedLoopbackSendAndReceive)
{
    const long handle = vscphlp_newUdpClient();
    ASSERT_NE(0, handle);
    const uint16_t port = findUdpPort();
    ASSERT_NE(0, port);

    ASSERT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(handle, authenticatedUdpConfig(port).c_str()));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_connectDatagramClient(handle));

    vscpEventEx outgoing{};
    outgoing.vscp_class = 20;
    outgoing.vscp_type = 3;
    outgoing.sizeData = 3;
    outgoing.data[0] = 1;
    outgoing.data[1] = 2;
    outgoing.data[2] = 3;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendDatagramEventEx(handle, &outgoing));

    vscpEventEx incoming{};
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveDatagramEventEx(handle, &incoming, 2000));
    EXPECT_EQ(outgoing.vscp_class, incoming.vscp_class);
    EXPECT_EQ(outgoing.vscp_type, incoming.vscp_type);
    ASSERT_EQ(outgoing.sizeData, incoming.sizeData);
    EXPECT_EQ(0, std::memcmp(outgoing.data, incoming.data, outgoing.sizeData));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));
}

TEST(DatagramClient, UdpAuthenticatedRejectsForgedAndLegacyDatagrams)
{
    const long handle = vscphlp_newUdpClient();
    ASSERT_NE(0, handle);
    const uint16_t port = findUdpPort();
    ASSERT_NE(0, port);
    ASSERT_EQ(VSCP_ERROR_SUCCESS,
              vscphlp_configureDatagramClient(handle, authenticatedUdpConfig(port).c_str()));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_connectDatagramClient(handle));

    const DatagramKeys keys;
    DatagramKeys wrongKeys;
    wrongKeys.mac[0] ^= 0x01;
    const auto plain = plainEventFrame(10, 6);
    auto tampered = authenticatedDatagram(plain, keys);
    ASSERT_FALSE(tampered.empty());
    tampered.back() ^= 0x01;
    const auto forged = authenticatedDatagram(plain, wrongKeys);
    ASSERT_FALSE(forged.empty());

    vscpEventEx incoming{};
    for (const auto &payload : {plain, tampered, forged}) {
        ASSERT_TRUE(sendRawDatagram(port, payload));
        EXPECT_EQ(VSCP_ERROR_TIMEOUT, vscphlp_receiveDatagramEventEx(handle, &incoming, 300));
    }

    // A correctly authenticated datagram from an independent peer is accepted.
    ASSERT_TRUE(sendRawDatagram(port, authenticatedDatagram(plainEventFrame(10, 7), keys)));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveDatagramEventEx(handle, &incoming, 2000));
    EXPECT_EQ(10, incoming.vscp_class);
    EXPECT_EQ(7, incoming.vscp_type);
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_closeDatagramClient(handle));
}
