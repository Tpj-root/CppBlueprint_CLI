#pragma once

#include <string>

namespace cppforge {

class Arguments;
class Config;

struct AppContext {
    const Arguments& args;
    const Config&    config;
    const std::string& configPath;
    const std::string& appName;
    const std::string& appVersion;
};

} // namespace cppforge