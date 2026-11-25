#pragma once

#include <functional>
#include <string>

namespace cppforge {

struct AppContext;

// A single self-describing CLI command.
struct Command {
    std::string name;          // "info"
    std::string shortOption;   // "-i"
    std::string longOption;    // "--info"
    std::string description;   // "Show application information"
    std::string example;       // "info"
    std::string handler;       // "InfoCommand::execute"
    std::function<int(const AppContext&)> function;
};

} // namespace cppforge