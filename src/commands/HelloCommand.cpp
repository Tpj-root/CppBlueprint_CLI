#include "cppforge/commands/HelloCommand.h"
#include "cppforge/app/AppContext.h"
#include "cppforge/cli/Arguments.h"
#include "cppforge/config/Config.h"
#include "cppforge/log/Logger.h"

namespace cppforge {

int HelloCommand::execute(const AppContext& ctx)
{
    const std::string fallback = ctx.config.get("general", "user", "Developer");
    const std::string name = ctx.args.get("--name", fallback);

    Logger::info("Hello, " + name + "!");
    Logger::debug("Debug output is enabled.");
    return 0;
}

}