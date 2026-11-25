// include/cppforge/commands/DateCommand.h
#pragma once
namespace cppforge {
struct AppContext;
class DateCommand {
public:
    static int execute(const AppContext& ctx);
};
}