#include "cppforge/log/Logger.h"

#include <iostream>

namespace cppforge {

bool Logger::verbose_ = false;

void Logger::setVerbose(bool enabled)
{
    verbose_ = enabled;
}

void Logger::log(LogLevel level, const std::string& message)
{
    if (level == LogLevel::Debug && !verbose_)
        return;

    const char* label = "INFO";
    std::ostream* output = &std::cout;

    switch (level) {
    case LogLevel::Debug:   label = "DEBUG"; break;
    case LogLevel::Info:    label = "INFO"; break;
    case LogLevel::Warning: label = "WARN"; break;
    case LogLevel::Error:
        label = "ERROR";
        output = &std::cerr;
        break;
    }

    *output << '[' << label << "] " << message << '\n';
}

void Logger::debug(const std::string& message)   { log(LogLevel::Debug, message); }
void Logger::info(const std::string& message)    { log(LogLevel::Info, message); }
void Logger::warning(const std::string& message)  { log(LogLevel::Warning, message); }
void Logger::error(const std::string& message)   { log(LogLevel::Error, message); }

} // namespace cppforge
