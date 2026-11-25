#pragma once

#include "cppforge/cli/Arguments.h"
#include "cppforge/config/Config.h"
#include "cppforge/app/CommandRegistry.h"

#include <string>

namespace cppforge {

class App {
public:
    App(const Arguments& args);

    int run();

private:
    // Register all CLI commands
    void registerCommands();

    // Application functions
    void printHelp() const;
    void commandInfo() const;
    void commandConfig() const;
    void commandHello() const;
    void commandSystemInfo() const;

    // Members
    const Arguments& args_;

    Config config_;
    CommandRegistry registry_;

    std::string configPath_;
    std::string appName_;
    std::string appVersion_;
};

} // namespace cppforge