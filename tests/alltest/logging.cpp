#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

#include <gtest/gtest.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/spdlog.h>
#include <vscphelperlib.h>

namespace {

namespace fs = std::filesystem;

int emitTransportError(const std::string& caFile)
{
    long session = vscphlp_newSession();
    if (!session) {
        return VSCP_ERROR_MEMORY;
    }
    int result = vscphlp_setTLSOptions(session, 1, caFile.c_str(), nullptr,
                                      nullptr, nullptr, "not-to-be-logged");
    if (result == VSCP_ERROR_SUCCESS) {
        result = vscphlp_open(session, "stcp://127.0.0.1:1",
                              "private-user", "private-password");
    }
    vscphlp_closeSession(session);
    return result;
}

class Logging : public testing::Test {
protected:
    void SetUp() override
    {
        directory = fs::temp_directory_path() /
                    ("vscp-helper-logging-" + std::to_string(
                        std::chrono::steady_clock::now().time_since_epoch().count()));
        ASSERT_TRUE(fs::create_directory(directory));
        path = (directory / "transport.log").string();
    }

    void TearDown() override
    {
        EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_disableLogging());
        fs::remove_all(directory);
    }

    int configure(int console = VSCPHELPER_LOG_LEVEL_OFF,
                  int file = VSCPHELPER_LOG_LEVEL_ERROR,
                  size_t size = 1024 * 1024,
                  size_t archives = 2)
    {
        return vscphlp_configureLogging(console, file, path.c_str(), size, archives);
    }

    static int emit(const std::string& caFile)
    {
        return emitTransportError(caFile);
    }

    std::string read() const
    {
        std::ifstream stream(path);
        return std::string(std::istreambuf_iterator<char>(stream), {});
    }

    fs::path directory;
    std::string path;
};

TEST_F(Logging, FileOnlyAndHostIsolation)
{
    auto oldDefault = spdlog::default_logger();
    std::ostringstream hostOutput;
    auto hostSink = std::make_shared<spdlog::sinks::ostream_sink_mt>(hostOutput);
    auto hostLogger = std::make_shared<spdlog::logger>("host-default", hostSink);
    hostLogger->set_level(spdlog::level::trace);
    spdlog::set_default_logger(hostLogger);
    auto hostLevel = hostLogger->level();
    int configResult = configure();
    EXPECT_EQ(VSCP_ERROR_SUCCESS, configResult);
    if (configResult != VSCP_ERROR_SUCCESS) {
        spdlog::set_default_logger(std::move(oldDefault));
        return;
    }
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "missing.pem").string()));
    EXPECT_TRUE(testing::internal::GetCapturedStderr().empty());
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_flushLogging());
    std::string output = read();
    EXPECT_NE(std::string::npos, output.find("[error] VSCP TCP: cannot read TLS file:"));
    EXPECT_EQ(std::string::npos, output.find("private-password"));
    EXPECT_EQ(std::string::npos, output.find("private-user"));
    EXPECT_EQ(std::string::npos, output.find("not-to-be-logged"));
    EXPECT_EQ(hostLogger, spdlog::default_logger());
    EXPECT_EQ(hostLevel, hostLogger->level());
    EXPECT_TRUE(hostOutput.str().empty());
    EXPECT_EQ(nullptr, spdlog::get("vscp-helper"));
    spdlog::set_default_logger(std::move(oldDefault));
}

TEST_F(Logging, ConsoleBothFilteringAndDisable)
{
    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure(VSCPHELPER_LOG_LEVEL_ERROR));
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "both.pem").string()));
    EXPECT_NE(std::string::npos, testing::internal::GetCapturedStderr().find("both.pem"));
    EXPECT_NE(std::string::npos, read().find("both.pem"));

    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure(VSCPHELPER_LOG_LEVEL_CRITICAL,
                                           VSCPHELPER_LOG_LEVEL_ERROR));
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "file-filter.pem").string()));
    EXPECT_TRUE(testing::internal::GetCapturedStderr().empty());
    EXPECT_NE(std::string::npos, read().find("file-filter.pem"));

    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure(VSCPHELPER_LOG_LEVEL_ERROR,
                                           VSCPHELPER_LOG_LEVEL_OFF));
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "console.pem").string()));
    EXPECT_NE(std::string::npos, testing::internal::GetCapturedStderr().find("console.pem"));
    EXPECT_EQ(std::string::npos, read().find("console.pem"));

    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_disableLogging());
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "disabled.pem").string()));
    EXPECT_TRUE(testing::internal::GetCapturedStderr().empty());
    EXPECT_EQ(std::string::npos, read().find("disabled.pem"));
}

TEST_F(Logging, InvalidConfigurationRetainsLogger)
{
    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure());
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(-1));
    EXPECT_NE('\0', *vscphlp_getLastLoggingError());
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(VSCPHELPER_LOG_LEVEL_OFF, 7));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(VSCPHELPER_LOG_LEVEL_OFF,
                                             VSCPHELPER_LOG_LEVEL_ERROR, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(VSCPHELPER_LOG_LEVEL_OFF,
                                             VSCPHELPER_LOG_LEVEL_ERROR, 100, 0));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(VSCPHELPER_LOG_LEVEL_OFF,
                                             VSCPHELPER_LOG_LEVEL_ERROR, 100, 200001));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_configureLogging(6, 4, nullptr, 100, 2));
    EXPECT_EQ(VSCP_ERROR_PARAMETER, vscphlp_configureLogging(6, 4, "", 100, 2));
    EXPECT_EQ(VSCP_ERROR_ERROR, vscphlp_configureLogging(
        6, 4, directory.string().c_str(), 100, 2));
    EXPECT_NE('\0', *vscphlp_getLastLoggingError());
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "retained.pem").string()));
    EXPECT_NE(std::string::npos, read().find("retained.pem"));
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_flushLogging());
    EXPECT_EQ('\0', *vscphlp_getLastLoggingError());
}

TEST_F(Logging, RotationIsBoundedAndLongMessagesAreIntact)
{
    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure(VSCPHELPER_LOG_LEVEL_OFF,
                                           VSCPHELPER_LOG_LEVEL_ERROR, 400, 2));
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "missing.pem").string()));
    }
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_flushLogging());
    EXPECT_LE(fs::file_size(path), 400u);
    EXPECT_LE(fs::file_size(directory / "transport.1.log"), 400u);
    EXPECT_LE(fs::file_size(directory / "transport.2.log"), 400u);
    EXPECT_FALSE(fs::exists(directory / "transport.3.log"));

    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure());
    std::string longPath(3000, 'x');
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emit(longPath));
    EXPECT_NE(std::string::npos, read().find(longPath));
}

TEST_F(Logging, ConcurrentConfigurationAndDiagnostics)
{
    long session = vscphlp_newSession();
    ASSERT_NE(0, session);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_setTLSOptions(
        session, 1, (directory / "concurrent.pem").string().c_str(),
        nullptr, nullptr, nullptr, nullptr));
    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure());
    std::atomic<bool> success{true};
    std::thread writer([&] {
        for (int i = 0; i < 30; ++i) {
            if (vscphlp_open(session, "stcp://127.0.0.1:1", "user", "password")
                != VSCP_ERROR_CONNECTION) {
                success = false;
            }
        }
    });
    for (int i = 0; i < 30; ++i) {
        EXPECT_EQ(VSCP_ERROR_SUCCESS, configure());
        EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_flushLogging());
    }
    writer.join();
    vscphlp_closeSession(session);
    EXPECT_TRUE(success);
    EXPECT_NE(std::string::npos, read().find("concurrent.pem"));
}

TEST_F(Logging, DiagnosticsAreThreadLocal)
{
    EXPECT_EQ(VSCP_ERROR_PARAMETER, configure(-1));
    std::string error = vscphlp_getLastLoggingError();
    std::thread other([] {
        EXPECT_STREQ("", vscphlp_getLastLoggingError());
        EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_flushLogging());
    });
    other.join();
    EXPECT_EQ(error, vscphlp_getLastLoggingError());
}

TEST_F(Logging, RuntimeSinkFailuresAreReported)
{
    ASSERT_EQ(VSCP_ERROR_SUCCESS, configure(VSCPHELPER_LOG_LEVEL_OFF,
                                           VSCPHELPER_LOG_LEVEL_ERROR, 200, 1));
    auto archive = directory / "transport.1.log";
    ASSERT_TRUE(fs::create_directory(archive));
    std::ofstream(archive / "blocker").put('x');
    testing::internal::CaptureStderr();
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(VSCP_ERROR_CONNECTION, emit((directory / "missing.pem").string()));
    }
    EXPECT_NE(std::string::npos, testing::internal::GetCapturedStderr().find("VSCP logging:"));
    EXPECT_NE('\0', *vscphlp_getLastLoggingError());
    EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_disableLogging());
}

} // namespace

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    // Check the initial default once, before tests mutate the global configuration.
    auto missing = fs::temp_directory_path() / ("vscp-helper-missing-" + std::to_string(
        std::chrono::steady_clock::now().time_since_epoch().count()) + ".pem");
    testing::internal::CaptureStderr();
    EXPECT_EQ(VSCP_ERROR_CONNECTION, emitTransportError(missing.string()));
    EXPECT_NE(std::string::npos, testing::internal::GetCapturedStderr().find(
        "VSCP TCP: cannot read TLS file:"));
    return RUN_ALL_TESTS();
}
