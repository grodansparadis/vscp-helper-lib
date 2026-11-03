#include <cstdlib>
#include <array>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <vscphelperlib.h>
#include <crc.h>

namespace {

class Session {
public:
    Session() : handle(vscphlp_newSession()) {}
    ~Session()
    {
        if (handle) {
            vscphlp_closeSession(handle);
        }
    }

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    const long handle;
};

class ReceivedFrame {
public:
    ReceivedFrame() = default;
    ~ReceivedFrame() { vscphlp_freeBinaryFrame(data); }
    ReceivedFrame(const ReceivedFrame&) = delete;
    ReceivedFrame& operator=(const ReceivedFrame&) = delete;

    unsigned char* data = nullptr;
    size_t size = 0;
};

void openBinarySession(const Session& session, const char* endpointName, const char* scenario = nullptr)
{
    const char* endpoint = std::getenv(endpointName);
    ASSERT_NE(nullptr, endpoint) << endpointName << " is not set";
    ASSERT_NE(0, session.handle);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setResponseTimeout(session.handle, 500));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    if (scenario) {
        std::string command = std::string("SCENARIO ") + scenario + "\r\n";
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCommand(session.handle, command.c_str()));
    }
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCmdBinary(session.handle));
}

void checkConnection(const char* endpointName)
{
    const char* endpoint = std::getenv(endpointName);
    ASSERT_NE(nullptr, endpoint) << endpointName << " is not set";

    Session session;
    ASSERT_NE(0, session.handle);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setResponseTimeout(session.handle, 500));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
}

} // namespace

TEST(TcpTransport, Plain)
{
    checkConnection("VSCP_TEST_PLAIN");
}

TEST(TcpTransport, DefaultTrustPaths)
{
    checkConnection("VSCP_TEST_TLS");
}

TEST(TcpTransport, RejectUntrustedCertificate)
{
    const char* endpoint = std::getenv("VSCP_TEST_UNTRUSTED");
    ASSERT_NE(nullptr, endpoint);

    Session session;
    ASSERT_NE(0, session.handle);
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
}

TEST(TcpTransport, RejectWrongHostname)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    ASSERT_NE(nullptr, endpoint);

    std::string wrongHost(endpoint);
    const auto position = wrongHost.find("localhost");
    ASSERT_NE(std::string::npos, position);
    wrongHost.replace(position, std::string("localhost").size(), "127.0.0.1");

    Session session;
    ASSERT_NE(0, session.handle);
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, wrongHost.c_str(), "admin", "secret"));
    EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
}

TEST(TlsOptions, ModesAndInvalidArguments)
{
    Session session;
    Session other;
    ASSERT_NE(0, session.handle);
    ASSERT_NE(0, other.handle);
    int mode = -1;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(session.handle, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_AUTO_SELECT, mode);
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_enableTLS(0, 1));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_setTLSAutoSelect(0));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_setTLSMode(0, 1));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_getTLSMode(0, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_AUTO_SELECT, mode);
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_setTLSOptions(0, 1, nullptr, nullptr, nullptr, nullptr, nullptr));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_getTLSMode(session.handle, nullptr));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setTLSMode(session.handle, -1));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setTLSMode(session.handle, 3));
    for (int selected : {VSCPHELPER_TLS_MODE_FORCE_TLS, VSCPHELPER_TLS_MODE_FORCE_PLAIN,
                         VSCPHELPER_TLS_MODE_AUTO_SELECT}) {
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSMode(session.handle, selected));
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(session.handle, &mode));
        EXPECT_EQ(selected, mode);
    }
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_enableTLS(session.handle, 1));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setTLSMode(session.handle, 3));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(session.handle, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_FORCE_TLS, mode);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_enableTLS(session.handle, 0));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(session.handle, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_FORCE_PLAIN, mode);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(other.handle, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_AUTO_SELECT, mode);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSAutoSelect(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getTLSMode(session.handle, &mode));
    EXPECT_EQ(VSCPHELPER_TLS_MODE_AUTO_SELECT, mode);
}

TEST(TlsOptions, ExplicitCAFileAndForcedTls)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    const char* ca = std::getenv("VSCP_TEST_CA");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, ca);
    Session session;
    std::string caCopy(ca);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, caCopy.c_str(), nullptr, nullptr, nullptr, nullptr));
    caCopy.assign("no-longer-the-ca-file");
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSAutoSelect(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSMode(session.handle, VSCPHELPER_TLS_MODE_FORCE_TLS));
    std::string tcpEndpoint = "tcp://" + std::string(endpoint).substr(7);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, tcpEndpoint.c_str(), "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint + 7, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
}

TEST(TlsOptions, ExplicitCADirectory)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    const char* directory = std::getenv("VSCP_TEST_CA_DIR");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, directory);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, "", "missing-ca-directory", "", "", ""));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, "", directory, "", "", ""));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
}

TEST(TlsOptions, ExplicitTrustReplacesDefaultsAndIsPerSession)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    const char* wrongCa = std::getenv("VSCP_TEST_WRONG_CA");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, wrongCa);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, wrongCa, nullptr, nullptr, nullptr, nullptr));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    checkConnection("VSCP_TEST_TLS");
}

TEST(TlsOptions, OptionsApplyToNextConnectionAndReset)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    ASSERT_NE(nullptr, endpoint);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, "missing-ca.pem", nullptr, nullptr, nullptr, nullptr));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, nullptr, nullptr, nullptr, nullptr, nullptr));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
}

TEST(TlsOptions, ExplicitVerificationRejectsWrongHostname)
{
    const char* endpoint = std::getenv("VSCP_TEST_TLS");
    const char* ca = std::getenv("VSCP_TEST_CA");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, ca);
    std::string wrongHost(endpoint);
    const auto position = wrongHost.find("localhost");
    ASSERT_NE(std::string::npos, position);
    wrongHost.replace(position, std::string("localhost").size(), "127.0.0.1");
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, ca, nullptr, nullptr, nullptr, nullptr));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, wrongHost.c_str(), "admin", "secret"));
}

TEST(TlsOptions, VerificationOptOutIsExplicitAndPerSession)
{
    const char* endpoint = std::getenv("VSCP_TEST_UNTRUSTED");
    ASSERT_NE(nullptr, endpoint);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 0, nullptr, nullptr, nullptr, nullptr, nullptr));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    Session secureSession;
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(secureSession.handle, endpoint, "admin", "secret"));
}

TEST(TlsOptions, MutualTlsWithEncryptedKeyAndCopiedOptions)
{
    const char* endpoint = std::getenv("VSCP_TEST_MTLS");
    const char* ca = std::getenv("VSCP_TEST_CA");
    const char* cert = std::getenv("VSCP_TEST_CERT");
    const char* key = std::getenv("VSCP_TEST_KEY");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, ca);
    ASSERT_NE(nullptr, cert);
    ASSERT_NE(nullptr, key);
    Session session;
    std::string certCopy(cert), keyCopy(key), password("test-password");
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, ca, nullptr,
                                                      certCopy.c_str(), keyCopy.c_str(), password.c_str()));
    certCopy.assign("missing-client.pem");
    keyCopy.assign("missing-key.pem");
    password.assign("wrong-password");
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
}

TEST(TlsOptions, RejectWrongKeyPassword)
{
    const char* endpoint = std::getenv("VSCP_TEST_MTLS");
    const char* ca = std::getenv("VSCP_TEST_CA");
    const char* cert = std::getenv("VSCP_TEST_CERT");
    const char* key = std::getenv("VSCP_TEST_KEY");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, ca);
    ASSERT_NE(nullptr, cert);
    ASSERT_NE(nullptr, key);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, ca, nullptr, cert, key, "wrong-password"));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
}

TEST(TlsOptions, RejectMissingClientCertificate)
{
    const char* endpoint = std::getenv("VSCP_TEST_MTLS");
    const char* ca = std::getenv("VSCP_TEST_CA");
    ASSERT_NE(nullptr, endpoint);
    ASSERT_NE(nullptr, ca);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, ca, nullptr, nullptr, nullptr, nullptr));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_open(session.handle, endpoint, "admin", "secret"));
}

TEST(TlsOptions, ModeChangesApplyToNextConnectionAndOptionsPersist)
{
    const char* tlsEndpoint = std::getenv("VSCP_TEST_TLS");
    const char* plainEndpoint = std::getenv("VSCP_TEST_PLAIN");
    const char* ca = std::getenv("VSCP_TEST_CA");
    ASSERT_NE(nullptr, tlsEndpoint);
    ASSERT_NE(nullptr, plainEndpoint);
    ASSERT_NE(nullptr, ca);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(session.handle, 1, ca, nullptr, nullptr, nullptr, nullptr));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, tlsEndpoint, "admin", "secret"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_enableTLS(session.handle, 0));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    std::string interface = "stcp://" + std::string(plainEndpoint).substr(6) + ";admin;secret";
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_openInterface(session.handle, interface.c_str(), 0));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSAutoSelect(session.handle));
    interface = std::string(tlsEndpoint) + ";admin;secret";
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_openInterface(session.handle, interface.c_str(), 0));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
}

TEST(BinaryLink, InvalidHandlesArgumentsAndDisconnectedSession)
{
    Session session;
    ASSERT_NE(0, session.handle);
    const unsigned char sent[] = {0xe0, 0, 0, 0, 0};
    int mode = -1;
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_doCmdBinary(0));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_isBinaryMode(0, &mode));
    EXPECT_EQ(-1, mode);
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_isBinaryMode(session.handle, nullptr));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
    EXPECT_EQ(0, mode);
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_sendBinaryFrame(0, sent, sizeof(sent)));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendBinaryFrame(session.handle, nullptr, 1));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendBinaryFrame(session.handle, sent, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendBinaryFrame(session.handle, sent, 65536));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_doCmdBinary(session.handle));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_sendBinaryFrame(session.handle, sent, sizeof(sent)));

    unsigned char marker = 42;
    unsigned char* output = &marker;
    size_t size = 42;
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_receiveBinaryFrame(0, &output, &size, 0));
    EXPECT_EQ(nullptr, output);
    EXPECT_EQ(0u, size);
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_receiveBinaryFrame(session.handle, nullptr, &size, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_receiveBinaryFrame(session.handle, &output, nullptr, 0));
    EXPECT_EQ(VSCP_ERROR_CONNECTION, vscphlp_receiveBinaryFrame(session.handle, &output, &size, 0));
    EXPECT_EQ(nullptr, output);
    EXPECT_EQ(0u, size);
    vscphlp_freeBinaryFrame(nullptr);
}

TEST(BinaryLink, NegotiationModeIsolationAndReconnect)
{
    const char* endpoint = std::getenv("VSCP_TEST_PLAIN");
    ASSERT_NE(nullptr, endpoint);
    Session session;
    Session other;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    const unsigned char sent[] = {0xe0, 0, 0, 0, 0};
    ReceivedFrame received;
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendBinaryFrame(session.handle, sent, sizeof(sent)));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 0));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCmdBinary(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCmdBinary(session.handle));
    int mode = -1;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
    EXPECT_EQ(1, mode);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(other.handle, &mode));
    EXPECT_EQ(0, mode);
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_noop(session.handle));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_doCommand(session.handle, "VERS\r\n"));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_enterReceiveLoop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
    EXPECT_EQ(0, mode);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCommand(session.handle, "binary\r\n"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
    EXPECT_EQ(1, mode);
}

TEST(BinaryLink, RawFrameRoundtripOverTcpAndTls)
{
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        SCOPED_TRACE(endpoint);
        Session session;
        openBinarySession(session, endpoint);
        for (unsigned char type : {0xe0, 0xf0, 0x11, 0x12, 0x13}) {
            std::vector<unsigned char> sent = {type, 0, 1, '\r', '\n', 0, 0xff, 0, 3};
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendBinaryFrame(session.handle, sent.data(), sent.size()));
            ReceivedFrame received;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 1000));
            ASSERT_NE(nullptr, received.data);
            EXPECT_EQ(sent, std::vector<unsigned char>(received.data, received.data + received.size));
        }
        for (size_t size : {size_t(1), size_t(65535)}) {
            std::vector<unsigned char> sent(size, 0xa5);
            sent[0] = 0xe0;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendBinaryFrame(session.handle, sent.data(), sent.size()));
            ReceivedFrame received;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 1000));
            ASSERT_NE(nullptr, received.data);
            EXPECT_EQ(sent, std::vector<unsigned char>(received.data, received.data + received.size));
        }
    }
}

TEST(BinaryLink, CoalescedFramesHaveIndependentOwnership)
{
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        Session session;
        openBinarySession(session, endpoint, "coalesced");
        ReceivedFrame first, second;
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &first.data, &first.size, 500));
        ASSERT_NE(nullptr, first.data);
        ASSERT_EQ(8u, first.size);
        std::vector<unsigned char> saved(first.data, first.data + first.size);
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &second.data, &second.size, 500));
        ASSERT_NE(nullptr, second.data);
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
        EXPECT_NE(first.data, second.data);
        EXPECT_EQ(saved, std::vector<unsigned char>(first.data, first.data + first.size));
        EXPECT_EQ(saved, std::vector<unsigned char>(second.data, second.data + second.size));
    }
}

TEST(BinaryLink, PartialFramesSurviveTimeout)
{
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        for (const char* scenario : {"partial", "partial-body"}) {
            SCOPED_TRACE(scenario);
            Session session;
            openBinarySession(session, endpoint, scenario);
            ReceivedFrame received;
            EXPECT_EQ(VSCP_ERROR_TIMEOUT, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 30));
            EXPECT_EQ(nullptr, received.data);
            EXPECT_EQ(0u, received.size);
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 500));
            ASSERT_NE(nullptr, received.data);
            EXPECT_EQ(8u, received.size);
            EXPECT_EQ(0xe0, received.data[0]);
            ReceivedFrame empty;
            EXPECT_EQ(VSCP_ERROR_TIMEOUT, vscphlp_receiveBinaryFrame(session.handle, &empty.data, &empty.size, 0));
            EXPECT_EQ(nullptr, empty.data);
            EXPECT_EQ(0u, empty.size);
        }
    }
}

TEST(BinaryLink, RejectMalformedAndTruncatedFrames)
{
    for (const char* scenario : {"zero", "truncated"}) {
        Session session;
        openBinarySession(session, "VSCP_TEST_TLS", scenario);
        ReceivedFrame received;
        const int expected = std::string(scenario) == "zero" ? VSCP_ERROR_INVALID_FRAME : VSCP_ERROR_STOPPED;
        EXPECT_EQ(expected, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 500));
        EXPECT_EQ(nullptr, received.data);
        EXPECT_EQ(0u, received.size);
        EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
        int mode = -1;
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
        EXPECT_EQ(0, mode);
    }
}

TEST(BinaryLink, NegotiationErrors)
{
    struct {
        const char* scenario;
        int expected;
        bool remainsConnected;
    } cases[] = {
        {"reject", VSCP_ERROR_ERROR, true},
        {"malformed-response", VSCP_ERROR_INVALID_FRAME, false},
        {"silent", VSCP_ERROR_TIMEOUT, false},
    };
    const char* endpoint = std::getenv("VSCP_TEST_PLAIN");
    ASSERT_NE(nullptr, endpoint);
    for (const auto& test : cases) {
        SCOPED_TRACE(test.scenario);
        Session session;
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
        std::string command = std::string("SCENARIO ") + test.scenario + "\r\n";
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCommand(session.handle, command.c_str()));
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setResponseTimeout(session.handle, 100));
        EXPECT_EQ(test.expected, vscphlp_doCmdBinary(session.handle));
        int mode = -1;
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
        EXPECT_EQ(0, mode);
        EXPECT_EQ(test.remainsConnected, vscphlp_isConnected(session.handle) == VSCP_ERROR_SUCCESS);
        if (test.remainsConnected) {
            EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_noop(session.handle));
        }
    }
}

TEST(BinaryLink, NegotiationRejectsActiveTextReceiveLoop)
{
    const char* endpoint = std::getenv("VSCP_TEST_PLAIN");
    ASSERT_NE(nullptr, endpoint);
    Session session;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_enterReceiveLoop(session.handle));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_doCmdBinary(session.handle));
    int mode = -1;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_isBinaryMode(session.handle, &mode));
    EXPECT_EQ(0, mode);
}

TEST(BinaryLink, ExistingEventApisUseBinaryLink)
{
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        Session session;
        openBinarySession(session, endpoint);
        vscpEventEx sent = {};
        sent.head = VSCP_HEADER16_FRAME_VERSION_UNIX_NS;
        sent.timestamp_ns = 1792051200123456789ULL;
        sent.vscp_class = 10;
        sent.vscp_type = 6;
        sent.GUID[15] = 27;
        sent.sizeData = 4;
        sent.data[0] = 0;
        sent.data[1] = '\r';
        sent.data[2] = '\n';
        sent.data[3] = 0xff;
        for (int i = 0; i < 2; ++i) {
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendEventEx(session.handle, &sent));
            vscpEventEx received = {};
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_blockingReceiveEventEx(session.handle, &received, 1000));
            EXPECT_EQ(sent.head, received.head);
            EXPECT_EQ(sent.timestamp_ns, received.timestamp_ns);
            EXPECT_EQ(sent.vscp_class, received.vscp_class);
            EXPECT_EQ(sent.vscp_type, received.vscp_type);
            EXPECT_EQ(sent.GUID[15], received.GUID[15]);
            ASSERT_EQ(sent.sizeData, received.sizeData);
            EXPECT_EQ(std::vector<unsigned char>(sent.data, sent.data + sent.sizeData),
                      std::vector<unsigned char>(received.data, received.data + received.sizeData));
        }

    }
}

namespace {

struct FrameKeys {
    std::array<unsigned char, 32> aes{}, mac{};
    FrameKeys()
    {
        for (size_t i = 0; i < aes.size(); ++i) {
            aes[i] = static_cast<unsigned char>(i);
            mac[i] = static_cast<unsigned char>(i + 32);
        }
    }
};

std::vector<unsigned char> plainCommand(size_t size = 5)
{
    std::vector<unsigned char> frame(size, 0x42);
    frame[0] = 0xe0;
    frame[1] = 0;
    frame[2] = 7;
    const uint16_t checksum = crcSlow(frame.data() + 1, static_cast<int>(size - 3));
    frame[size - 2] = static_cast<unsigned char>(checksum >> 8);
    frame.back() = static_cast<unsigned char>(checksum);
    return frame;
}

void openSecureSession(const Session& session, const char* endpointName, int algorithm,
                       const char* fault = "")
{
    const char* endpoint = std::getenv(endpointName);
    ASSERT_NE(nullptr, endpoint);
    FrameKeys keys;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setBinarySecurity(session.handle, algorithm, keys.aes.data(),
                                                          8 * (algorithm + 1), keys.mac.data(), keys.mac.size()));
    keys.aes.fill(0);
    keys.mac.fill(0);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_open(session.handle, endpoint, "admin", "secret"));
    std::string command = "SCENARIO secure-" + std::to_string(algorithm);
    if (*fault) {
        command += std::string("-") + fault;
    }
    command += "\r\n";
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCommand(session.handle, command.c_str()));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_doCmdBinary(session.handle));
}

} // namespace

TEST(FrameSecurity, ConfigurationValidationAndIsolation)
{
    FrameKeys keys;
    Session session, other;
    int algorithm = -1;
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_setBinarySecurity(0, 3, keys.aes.data(), 32, keys.mac.data(), 32));
    EXPECT_EQ(VSCP_ERROR_INVALID_HANDLE, vscphlp_getBinarySecurity(0, &algorithm));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_getBinarySecurity(session.handle, nullptr));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getBinarySecurity(session.handle, &algorithm));
    EXPECT_EQ(VSCP_ENCRYPTION_NONE, algorithm);
    for (int selected : {1, 2, 3}) {
        EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, selected, nullptr, 8 * (selected + 1), keys.mac.data(), 32));
        EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, selected, keys.aes.data(), 1, keys.mac.data(), 32));
        EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, selected, keys.aes.data(), 8 * (selected + 1), nullptr, 32));
        EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, selected, keys.aes.data(), 8 * (selected + 1), keys.mac.data(), 31));
        EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, selected, keys.aes.data(), 8 * (selected + 1), keys.aes.data(), 32));
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setBinarySecurity(session.handle, selected, keys.aes.data(), 8 * (selected + 1), keys.mac.data(), 32));
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getBinarySecurity(session.handle, &algorithm));
        EXPECT_EQ(selected, algorithm);
    }
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, -1, nullptr, 0, nullptr, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, 4, nullptr, 0, nullptr, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, 0, keys.aes.data(), 32, nullptr, 0));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getBinarySecurity(session.handle, &algorithm));
    EXPECT_EQ(3, algorithm);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getBinarySecurity(other.handle, &algorithm));
    EXPECT_EQ(0, algorithm);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setBinarySecurity(session.handle, 0, nullptr, 0, nullptr, 0));
}

TEST(FrameSecurity, StandaloneKnownAnswerAndFailureIsolation)
{
    FrameKeys keys;
    std::array<unsigned char, 16> iv{};
    for (size_t i = 0; i < iv.size(); ++i) {
        iv[i] = static_cast<unsigned char>(i);
    }
    const auto plain = plainCommand();
    const std::vector<unsigned char> expected = {
        0xe3,0xb8,0x65,0xbc,0xf5,0x20,0xd8,0x3d,0x27,0x08,0x50,0x2a,0xe7,0x12,0x63,0x8a,0xeb,
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
        0x27,0x0f,0xec,0x51,0xe9,0x79,0x45,0x41,0xf4,0x7a,0xab,0x3d,0xd9,0xf9,0x47,0xce
    };
    std::vector<unsigned char> encrypted(plain.size() + 48, 0xa5);
    size_t length = 99;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_encryptFrameV1(encrypted.data(), encrypted.size(), &length,
               plain.data(), plain.size(), keys.aes.data(), 32, keys.mac.data(), 32, iv.data(), 16, 3));
    encrypted.resize(length);
    EXPECT_EQ(expected, encrypted);
    std::vector<unsigned char> output(plain.size(), 0xa5);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_decryptFrameV1(output.data(), output.size(), &length,
               encrypted.data(), encrypted.size(), keys.aes.data(), 32, keys.mac.data(), 32));
    auto expectedPlain = plain;
    expectedPlain[0] = 0xe3;
    EXPECT_EQ(expectedPlain, output);
    EXPECT_EQ(plain.size(), length);
    for (size_t index : {size_t(0), size_t(1), size_t(20), size_t(48)}) {
        auto tampered = encrypted;
        tampered[index] ^= 0x10;
        output.assign(output.size(), 0xa5);
        EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_decryptFrameV1(output.data(), output.size(), &length,
                  tampered.data(), tampered.size(), keys.aes.data(), 32, keys.mac.data(), 32));
        EXPECT_EQ(0u, length);
        EXPECT_EQ(std::vector<unsigned char>(output.size(), 0xa5), output);
    }
    output.assign(output.size(), 0xa5);
    EXPECT_EQ(VSCP_ERROR_BUFFER_TO_SMALL, vscphlp_decryptFrameV1(output.data(), plain.size() - 1, &length,
              encrypted.data(), encrypted.size(), keys.aes.data(), 32, keys.mac.data(), 32));
    EXPECT_EQ(0u, length);
    EXPECT_EQ(std::vector<unsigned char>(output.size(), 0xa5), output);
    auto inPlace = encrypted;
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_decryptFrameV1(inPlace.data(), inPlace.size(), &length,
               inPlace.data(), inPlace.size(), keys.aes.data(), 32, keys.mac.data(), 32));
    EXPECT_EQ(expectedPlain, std::vector<unsigned char>(inPlace.begin(), inPlace.begin() + length));
}

TEST(FrameSecurity, StandaloneAlgorithmsAndRandomIvs)
{
    FrameKeys keys;
    for (int algorithm : {1, 2, 3}) {
        for (size_t size : {size_t(5), size_t(16), size_t(17), size_t(550)}) {
            const auto plain = plainCommand(size);
            std::vector<unsigned char> first(size + 48), second(size + 48), output(size);
            size_t length = 0, decoded = 0;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_encryptFrameV1(first.data(), first.size(), &length,
                       plain.data(), plain.size(), keys.aes.data(), 8 * (algorithm + 1), keys.mac.data(), 32,
                       nullptr, 0, algorithm));
            first.resize(length);
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_encryptFrameV1(second.data(), second.size(), &length,
                       plain.data(), plain.size(), keys.aes.data(), 8 * (algorithm + 1), keys.mac.data(), 32,
                       nullptr, 0, algorithm));
            second.resize(length);
            EXPECT_NE(first, second);
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_decryptFrameV1(output.data(), output.size(), &decoded,
                       first.data(), first.size(), keys.aes.data(), 8 * (algorithm + 1), keys.mac.data(), 32));
            auto expected = plain;
            expected[0] |= static_cast<unsigned char>(algorithm);
            EXPECT_EQ(expected, output);
            EXPECT_EQ(plain.size(), decoded);
        }
    }
}

TEST(FrameSecurity, AutomaticEncryptedRoundtripOverTcpAndTls)
{
    FrameKeys keys;
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        for (int algorithm : {1, 2, 3}) {
            Session session;
            openSecureSession(session, endpoint, algorithm);
            EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_setBinarySecurity(session.handle, 0, nullptr, 0, nullptr, 0));
            for (size_t size : {size_t(5), size_t(17), size_t(4048)}) {
                const auto sent = plainCommand(size);
                ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendBinaryFrame(session.handle, sent.data(), sent.size()));
                ReceivedFrame received;
                ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 1000));
                ASSERT_NE(nullptr, received.data);
                EXPECT_EQ(sent, std::vector<unsigned char>(received.data, received.data + received.size));
            }
            auto oversized = plainCommand(4049);
            EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_sendBinaryFrame(session.handle, oversized.data(), oversized.size()));
            auto corrupted = plainCommand();
            corrupted.back() ^= 1;
            EXPECT_EQ(VSCP_ERROR_INVALID_FRAME, vscphlp_sendBinaryFrame(session.handle, corrupted.data(), corrupted.size()));
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_close(session.handle));
            int configured = -1;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_getBinarySecurity(session.handle, &configured));
            EXPECT_EQ(algorithm, configured);
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setBinarySecurity(session.handle, 0, nullptr, 0, nullptr, 0));
        }
    }
}

TEST(FrameSecurity, RejectsTamperingAndDowngradeWithoutPlaintext)
{
    for (const char* fault : {"prefix", "version", "length", "type", "algorithm", "unencrypted",
                              "ciphertext", "iv", "tag", "padding", "crc", "legacy"}) {
        SCOPED_TRACE(fault);
        Session session;
        openSecureSession(session, "VSCP_TEST_TLS", 3, fault);
        ReceivedFrame received;
        EXPECT_EQ(VSCP_ERROR_INVALID_FRAME, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 1000));
        EXPECT_EQ(nullptr, received.data);
        EXPECT_EQ(0u, received.size);
        EXPECT_NE(VSCP_ERROR_SUCCESS, vscphlp_isConnected(session.handle));
    }
}

TEST(FrameSecurity, AuthenticatedPartialAndCoalescedFrames)
{
    for (const char* fault : {"partial", "partial-body", "coalesced"}) {
        Session session;
        openSecureSession(session, "VSCP_TEST_TLS", 3, fault);
        ReceivedFrame received;
        if (std::string(fault) != "coalesced") {
            EXPECT_EQ(VSCP_ERROR_TIMEOUT, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 30));
            EXPECT_EQ(nullptr, received.data);
            EXPECT_EQ(0u, received.size);
        }
        ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &received.data, &received.size, 1000));
        ASSERT_NE(nullptr, received.data);
        EXPECT_EQ(plainCommand(), std::vector<unsigned char>(received.data, received.data + received.size));
        if (std::string(fault) == "coalesced") {
            ReceivedFrame second;
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_receiveBinaryFrame(session.handle, &second.data, &second.size, 1000));
            ASSERT_NE(nullptr, second.data);
            EXPECT_EQ(plainCommand(), std::vector<unsigned char>(second.data, second.data + second.size));
        }
    }
}

TEST(FrameSecurity, ExistingEventApisAuthenticateAndEncrypt)
{
    for (const char* endpoint : {"VSCP_TEST_PLAIN", "VSCP_TEST_TLS"}) {
        Session session;
        openSecureSession(session, endpoint, 3);
        vscpEventEx sent = {};
        sent.head = VSCP_HEADER16_FRAME_VERSION_UNIX_NS;
        sent.vscp_class = 10;
        sent.vscp_type = 6;
        sent.sizeData = 3;
        sent.data[0] = 0;
        sent.data[1] = '\r';
        sent.data[2] = 0xff;
        for (int i = 0; i < 2; ++i) {
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_sendEventEx(session.handle, &sent));
            vscpEventEx received = {};
            ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_blockingReceiveEventEx(session.handle, &received, 1000));
            EXPECT_EQ(sent.vscp_class, received.vscp_class);
            EXPECT_EQ(sent.vscp_type, received.vscp_type);
            ASSERT_EQ(sent.sizeData, received.sizeData);
            EXPECT_EQ(std::vector<unsigned char>(sent.data, sent.data + sent.sizeData),
                      std::vector<unsigned char>(received.data, received.data + received.sizeData));
        }
    }
}
