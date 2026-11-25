#pragma once

#include "cppforge/commands/Command.h"

#include <string>
#include <vector>

namespace cppforge {

struct AppContext;

class CommandRegistry {
public:
    void add(Command cmd);

    // True if `token` matches name, short, or long option.
    bool matches(const std::string& token) const;

    // Execute by any of the three identifiers.
    int execute(const std::string& token, const AppContext& ctx) const;

    // Auto-generated from the registered commands.
    void printHelp(const std::string& appName,
                   const std::string& appVersion) const;

private:
    std::vector<Command> commands_;
};

} // namespace cppforge