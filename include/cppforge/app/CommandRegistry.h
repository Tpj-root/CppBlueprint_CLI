#pragma once

#include <functional>
#include <string>
#include <vector>

namespace cppforge {

class CommandRegistry {
public:

    // Type of a command function
    using CommandFunction = std::function<int()>;

    // Store one command
    void add(const std::string& name,
             const std::string& description,
             CommandFunction function);

    // Execute command by name
    int execute(const std::string& name) const;

    // Check if command exists
    bool exists(const std::string& name) const;

    // Print all registered commands
    void printHelp() const;

private:

    struct Command {
        std::string name;
        std::string description;
        CommandFunction function;
    };

    std::vector<Command> commands_;
};

}