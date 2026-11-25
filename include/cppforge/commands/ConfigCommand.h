#pragma once
namespace cppforge {
struct AppContext;
class ConfigCommand {
public:
    static int execute(const AppContext& ctx);
};
}