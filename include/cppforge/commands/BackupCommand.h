#pragma once
namespace cppforge {
struct AppContext;
class BackupCommand {
public:
    static int execute(const AppContext& ctx);
};
}