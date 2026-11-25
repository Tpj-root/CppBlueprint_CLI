#include "cppforge/commands/InfoCommand.h"
#include "cppforge/app/AppContext.h"
#include <iostream>

namespace cppforge {

int InfoCommand::execute(const AppContext& ctx)
{
    std::cout << "Application : " << ctx.appName    << '\n'
              << "Version     : " << ctx.appVersion << '\n'
              << "Config file : " << ctx.configPath << '\n';
    return 0;
}

}