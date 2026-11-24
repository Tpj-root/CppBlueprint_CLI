#pragma once

#include "cppforge/cli/Arguments.h"
#include "cppforge/config/Config.h"

namespace cppforge {

class App {
public:
    App(const Arguments& args);

    int run();

private:
    void printHelp() const;
    void commandInfo() const;
    void commandConfig() const;
    void commandHello() const;
    void commandSystemInfo() const;

    const Arguments& args_;
    Config config_;
    std::string configPath_;
    std::string appName_;
    std::string appVersion_;
};

} // namespace cppforge
