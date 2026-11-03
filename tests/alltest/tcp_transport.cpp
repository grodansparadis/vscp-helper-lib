#include <cstdlib>
#include <string>

#include <gtest/gtest.h>
#include <vscphelperlib.h>

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
