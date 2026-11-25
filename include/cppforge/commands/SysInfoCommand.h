#pragma once
namespace cppforge {
struct AppContext;
class SysInfoCommand {
public:
    static int execute(const AppContext& ctx);
};
}