///////////////////////////////////////////////////////////////////////////////
// vscphelperlogging.h
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

#pragma once

#include <cstdarg>
#include <exception>
#include <memory>
#include <utility>

#include <spdlog/logger.h>

#if defined(__GNUC__) && !defined(_WIN32)
__attribute__((visibility("hidden")))
#endif
void vscphelper_logTransportError(const char* format, va_list arguments) noexcept;

#if defined(__GNUC__) && !defined(_WIN32)
__attribute__((visibility("hidden")))
#endif
std::shared_ptr<spdlog::logger> vscphelper_getLogger() noexcept;

#if defined(__GNUC__) && !defined(_WIN32)
__attribute__((visibility("hidden")))
#endif
void vscphelper_reportLoggingFailure(const char* message) noexcept;

template <typename... Args>
void vscphlp_log(spdlog::level::level_enum level,
                 spdlog::format_string_t<Args...> format,
                 Args&&... args) noexcept
{
    try {
        auto logger = vscphelper_getLogger();
        if (logger && logger->should_log(level)) {
            logger->log(level, format, std::forward<Args>(args)...);
        }
    }
    catch (const std::exception& error) {
        vscphelper_reportLoggingFailure(error.what());
    }
    catch (...) {
        vscphelper_reportLoggingFailure("Unknown exception while logging");
    }
}

#define VSCPHLP_LOG_TRACE(...) vscphlp_log(spdlog::level::trace, __VA_ARGS__)
#define VSCPHLP_LOG_DEBUG(...) vscphlp_log(spdlog::level::debug, __VA_ARGS__)
#define VSCPHLP_LOG_INFO(...) vscphlp_log(spdlog::level::info, __VA_ARGS__)
#define VSCPHLP_LOG_WARN(...) vscphlp_log(spdlog::level::warn, __VA_ARGS__)
#define VSCPHLP_LOG_ERROR(...) vscphlp_log(spdlog::level::err, __VA_ARGS__)
#define VSCPHLP_LOG_CRITICAL(...) vscphlp_log(spdlog::level::critical, __VA_ARGS__)
