#include "cppforge/app/CommandRegistry.h"
#include "cppforge/app/AppContext.h"

#include <iomanip>
#include <iostream>

namespace cppforge {

void CommandRegistry::add(Command cmd)
{
    commands_.push_back(std::move(cmd));
}

bool CommandRegistry::matches(const std::string& token) const
{
    for (const auto& c : commands_) {
        if (c.name == token ||
            c.shortOption == token ||
            c.longOption == token) {
            return true;
        }
    }
    return false;
}

int CommandRegistry::execute(const std::string& token,
                             const AppContext& ctx) const
{
    for (const auto& c : commands_) {
        if (c.name == token ||
            c.shortOption == token ||
            c.longOption == token) {
            return c.function(ctx);
        }
    }
    std::cerr << "Unknown command: " << token << '\n';
    return 1;
}

void CommandRegistry::printHelp(const std::string& appName,
                                const std::string& appVersion) const
{
    std::cout << appName << ' ' << appVersion << " - CLI Application\n\n"
              << "Usage:\n"
              << "  cppforge [options] <command> [command-args]\n\n"
              << "Global options:\n"
              << "  -h, --help        Show this help\n"
              << "  -v, --version     Show version\n"
              << "      --config      Config file path (default: config.ini)\n"
              << "      --verbose     Enable debug logging\n\n"
              << "Commands:\n";

    for (const auto& c : commands_) {
        const std::string opts = c.shortOption + ", " + c.longOption;

        std::cout << "  " << std::left << std::setw(12) << c.name
                  << std::setw(24) << ("[" + opts + "]")
                  << c.description << '\n';
        std::cout << "              Handler: " << c.handler << '\n';
        std::cout << "              Example: cppforge " << c.example << "\n\n";
    }
}

} // namespace cppforge