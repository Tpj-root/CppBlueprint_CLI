#pragma once
namespace cppforge {
struct AppContext;
class InfoCommand {
public:
    static int execute(const AppContext& ctx);
};
}