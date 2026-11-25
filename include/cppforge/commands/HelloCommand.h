#pragma once
namespace cppforge {
struct AppContext;
class HelloCommand {
public:
    static int execute(const AppContext& ctx);
};
}