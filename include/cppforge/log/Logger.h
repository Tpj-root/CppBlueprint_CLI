#pragma once

#include <string>

namespace cppforge {

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static void setVerbose(bool enabled);
    static void log(LogLevel level, const std::string& message);

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

private:
    static bool verbose_;
};

} // namespace cppforge
