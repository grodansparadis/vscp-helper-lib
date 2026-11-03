///////////////////////////////////////////////////////////////////////////////
// vscphelperlogging.cpp
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (C) 2000-2026 Åke Hedman and contributors, The VSCP Project, 
// <akhe@vscp.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "vscphelperlib.h"
#include "vscphelperlogging.h"

#include <array>
#include <cstdio>
#include <exception>
#include <memory>
#include <mutex>
#include <vector>

#include <spdlog/logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

#if defined(__GNUC__) && !defined(_WIN32)
#define LOGGING_API __attribute__((visibility("default")))
#else
#define LOGGING_API HELPERLIB_API
#endif

namespace {

thread_local std::array<char, 512> loggingError{};

void reportError(const char* message) noexcept
{
    std::snprintf(loggingError.data(), loggingError.size(), "%s", message);
    std::fprintf(stderr, "VSCP logging: %s\n", loggingError.data());
}

struct LoggingState {
    std::mutex mutex;
    std::shared_ptr<spdlog::logger> logger;
    bool defaultStderr = true;
};

LoggingState& loggingState()
{
    static LoggingState state;
    return state;
}

bool validLevel(int level)
{
    return level >= VSCPHELPER_LOG_LEVEL_TRACE && level <= VSCPHELPER_LOG_LEVEL_OFF;
}

} // namespace

extern "C" LOGGING_API int
vscphlp_configureLogging(int consoleLevel,
                         int fileLevel,
                         const char* filePath,
                         size_t maxFileSize,
                         size_t maxFiles)
{
    loggingError[0] = '\0';
    if (!validLevel(consoleLevel) || !validLevel(fileLevel) ||
        (fileLevel != VSCPHELPER_LOG_LEVEL_OFF &&
         (!filePath || !*filePath || maxFileSize == 0 || maxFiles == 0 || maxFiles > 200000))) {
        reportError("Invalid logging level, file path, or rotation limits");
        return VSCP_ERROR_PARAMETER;
    }
    if (consoleLevel == VSCPHELPER_LOG_LEVEL_OFF && fileLevel == VSCPHELPER_LOG_LEVEL_OFF) {
        return vscphlp_disableLogging();
    }

    try {
        auto& state = loggingState();
        std::lock_guard<std::mutex> lock(state.mutex);
        if (state.logger) {
            state.logger->flush();
            if (loggingError[0]) {
                return VSCP_ERROR_ERROR;
            }
        }
        std::vector<spdlog::sink_ptr> sinks;
        if (consoleLevel != VSCPHELPER_LOG_LEVEL_OFF) {
            auto sink = std::make_shared<spdlog::sinks::stderr_sink_mt>();
            sink->set_level(static_cast<spdlog::level::level_enum>(consoleLevel));
            sinks.push_back(sink);
        }
        if (fileLevel != VSCPHELPER_LOG_LEVEL_OFF) {
            auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                filePath, maxFileSize, maxFiles);
            sink->set_level(static_cast<spdlog::level::level_enum>(fileLevel));
            sinks.push_back(sink);
        }
        auto logger = std::make_shared<spdlog::logger>("vscp-helper", sinks.begin(), sinks.end());
        logger->set_level(static_cast<spdlog::level::level_enum>(
            consoleLevel < fileLevel ? consoleLevel : fileLevel));
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        logger->flush_on(spdlog::level::err);
        logger->set_error_handler([](const std::string& message) { reportError(message.c_str()); });
        state.logger = std::move(logger);
        state.defaultStderr = false;
        return VSCP_ERROR_SUCCESS;
    }
    catch (const std::exception& error) {
        reportError(error.what());
        return VSCP_ERROR_ERROR;
    }
}

extern "C" LOGGING_API int
vscphlp_disableLogging(void)
{
    loggingError[0] = '\0';
    try {
        auto& state = loggingState();
        std::lock_guard<std::mutex> lock(state.mutex);
        state.defaultStderr = false;
        if (state.logger) {
            state.logger->flush();
        }
        state.logger.reset();
        return loggingError[0] ? VSCP_ERROR_ERROR : VSCP_ERROR_SUCCESS;
    }
    catch (const std::exception& error) {
        reportError(error.what());
        return VSCP_ERROR_ERROR;
    }
}

extern "C" LOGGING_API int
vscphlp_flushLogging(void)
{
    loggingError[0] = '\0';
    try {
        auto& state = loggingState();
        std::lock_guard<std::mutex> lock(state.mutex);
        if (state.logger) {
            state.logger->flush();
        }
        return loggingError[0] ? VSCP_ERROR_ERROR : VSCP_ERROR_SUCCESS;
    }
    catch (const std::exception& error) {
        reportError(error.what());
        return VSCP_ERROR_ERROR;
    }
}

extern "C" LOGGING_API const char*
vscphlp_getLastLoggingError(void)
{
    return loggingError.data();
}

void vscphlp_logTransportError(const char* format, va_list arguments) noexcept
{
    try {
        auto& state = loggingState();
        std::lock_guard<std::mutex> lock(state.mutex);
        if (!state.logger) {
            if (state.defaultStderr) {
                std::fputs("VSCP TCP: ", stderr);
                std::vfprintf(stderr, format, arguments);
                std::fputc('\n', stderr);
            }
            return;
        }
        if (!state.logger->should_log(spdlog::level::err)) {
            return;
        }
        std::array<char, 2048> message{};
        va_list copy;
        va_copy(copy, arguments);
        int length = std::vsnprintf(message.data(), message.size(), format, copy);
        va_end(copy);
        if (length < 0) {
            reportError("Cannot format transport diagnostic");
            return;
        }
        if (static_cast<size_t>(length) >= message.size()) {
            // Transport diagnostics can contain arbitrarily long paths/hostnames.
            std::vector<char> fullMessage(static_cast<size_t>(length) + 1);
            std::vsnprintf(fullMessage.data(), fullMessage.size(), format, arguments);
            state.logger->error("VSCP TCP: {}", fullMessage.data());
        }
        else {
            state.logger->error("VSCP TCP: {}", message.data());
        }
    }
    catch (const std::exception& error) {
        reportError(error.what());
    }
}

void vscphlp_logHelperError(const char* message) noexcept
{
    try {
        auto& state = loggingState();
        std::lock_guard<std::mutex> lock(state.mutex);
        if (state.logger) {
            state.logger->error("VSCP helper: {}", message);
        }
        else if (state.defaultStderr) {
            std::fputs(message, stderr);
        }
    }
    catch (const std::exception& error) {
        reportError(error.what());
    }
}
