#include "cppforge/app/CommandRegistry.h"

#include <iostream>

namespace cppforge {

// Add a new command to the registry
void CommandRegistry::add(const std::string& name,
                         const std::string& description,
                         CommandFunction function)
{
    commands_.push_back({
        name,
        description,
        function
    });
}

// Execute a command by its name
int CommandRegistry::execute(const std::string& name) const
{
    for (const auto& command : commands_) {
        if (command.name == name) {
            return command.function();
        }
    }

    std::cerr << "Unknown command: " << name << '\n';
    return 1;
}

// Check whether the command exists
bool CommandRegistry::exists(const std::string& name) const
{
    for (const auto& command : commands_) {
        if (command.name == name) {
            return true;
        }
    }

    return false;
}

// Automatically print all registered commands
void CommandRegistry::printHelp() const
{
    std::cout << "Commands:\n";

    for (const auto& command : commands_) {
        std::cout << "  "
                  << command.name;

        // Align descriptions
        if (command.name.length() < 12) {
            std::cout << std::string(12 - command.name.length(), ' ');
        } else {
            std::cout << " ";
        }

        std::cout << command.description << '\n';
    }
}

}