#include "cppforge/commands/ConfigCommand.h"
#include "cppforge/app/AppContext.h"
#include "cppforge/config/Config.h"
#include <iostream>

namespace cppforge {

int ConfigCommand::execute(const AppContext& ctx)
{
    std::cout << "Config file: " << ctx.configPath << '\n'
              << "[app]\n"
              << "name = "    << ctx.config.get("app", "name", ctx.appName)    << '\n'
              << "version = " << ctx.config.get("app", "version", ctx.appVersion) << '\n'
              << "[general]\n"
              << "verbose = " << (ctx.config.getBool("general", "verbose", false) ? "true" : "false") << '\n'
              << "user = "    << ctx.config.get("general", "user", "developer") << '\n'
              << "[logging]\n"
              << "level = "   << ctx.config.get("logging", "level", "info") << '\n';
    return 0;
}

}