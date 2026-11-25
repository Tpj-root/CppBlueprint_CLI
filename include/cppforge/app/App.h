#pragma once

#include "cppforge/app/CommandRegistry.h"
#include "cppforge/cli/Arguments.h"
#include "cppforge/config/Config.h"

#include <string>

namespace cppforge {

class App {
public:
    explicit App(const Arguments& args);
    int run();

private:
    void registerCommands();

    const Arguments& args_;

    Config          config_;
    CommandRegistry registry_;

    std::string configPath_;
    std::string appName_;
    std::string appVersion_;
};

} // namespace cppforge