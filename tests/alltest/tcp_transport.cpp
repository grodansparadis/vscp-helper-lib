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
