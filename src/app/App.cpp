#include "cppforge/app/App.h"
#include "cppforge/app/AppContext.h"
#include "cppforge/log/Logger.h"

#include "cppforge/commands/InfoCommand.h"
#include "cppforge/commands/ConfigCommand.h"
#include "cppforge/commands/HelloCommand.h"
#include "cppforge/commands/SysInfoCommand.h"
#include "cppforge/commands/BackupCommand.h"
#include "cppforge/commands/DateCommand.h"
#include <iostream>

namespace cppforge {

App::App(const Arguments& args)
    : args_(args),
      configPath_(args.get("--config", "config.ini")),
      appName_("CppForge"),
      appVersion_("1.0.0")
{
    if (!config_.load(configPath_))
        Logger::warning("Config file not found: " + configPath_);

    appName_    = config_.get("app", "name",    appName_);
    appVersion_ = config_.get("app", "version", appVersion_);

    Logger::setVerbose(args_.has("--verbose") ||
                       config_.getBool("general", "verbose", false));

    registerCommands();
}

// ---------------------------------------------------------------------------
// Add a command = add one block here. Help updates automatically.
// ---------------------------------------------------------------------------
void App::registerCommands()
{
    registry_.add({
        "info", "-i", "--info",
        "Show application information",
        "info",
        "InfoCommand::execute",
        [](const AppContext& ctx) { return InfoCommand::execute(ctx); }
    });

    registry_.add({
        "config", "-C", "--show-config",
        "Display loaded configuration",
        "config",
        "ConfigCommand::execute",
        [](const AppContext& ctx) { return ConfigCommand::execute(ctx); }
    });

    registry_.add({
        "hello", "-g", "--greet",
        "Print a greeting (use --name NAME)",
        "hello --name Developer",
        "HelloCommand::execute",
        [](const AppContext& ctx) { return HelloCommand::execute(ctx); }
    });

    registry_.add({
        "sysinfo", "-s", "--sysinfo",
        "Show system information",
        "sysinfo",
        "SysInfoCommand::execute",
        [](const AppContext& ctx) { return SysInfoCommand::execute(ctx); }
    });

    registry_.add({
        "backup", "-b", "--backup",
        "Create a backup",
        "backup",
        "BackupCommand::execute",
        [](const AppContext& ctx) { return BackupCommand::execute(ctx); }
    });

	registry_.add({
	    "date", "-d", "--date",
	    "Show current date and time",
	    "date",
	    "DateCommand::execute",
	    [](const AppContext& ctx) { return DateCommand::execute(ctx); }
	});

    
}

int App::run()
{
    // 1. Global help / version
    if (args_.has("--help") || args_.has("-h")) {
        registry_.printHelp(appName_, appVersion_);
        return 0;
    }
    if (args_.has("--version") || args_.has("-v")) {
        std::cout << appName_ << ' ' << appVersion_ << '\n';
        return 0;
    }

    AppContext ctx{args_, config_, configPath_, appName_, appVersion_};

    // 2. Positional command (canonical form)
    const auto& positional = args_.positional();
    if (!positional.empty()) {
        if (registry_.matches(positional.front()))
            return registry_.execute(positional.front(), ctx);

        std::cerr << "Unknown command: " << positional.front() << '\n'
                  << "Use --help to see available commands.\n";
        return 1;
    }

    // 3. Option-triggered command (e.g. `cppforge -s` or `cppforge --sysinfo`)
    for (const auto& [key, _] : args_.options()) {
        if (registry_.matches(key))
            return registry_.execute(key, ctx);
    }

    // 4. Nothing to do → help
    registry_.printHelp(appName_, appVersion_);
    return 0;
}

} // namespace cppforge