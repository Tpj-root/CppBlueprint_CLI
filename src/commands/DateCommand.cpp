// src/commands/DateCommand.cpp
#include "cppforge/commands/DateCommand.h"
#include <ctime>
#include <iostream>
namespace cppforge {
int DateCommand::execute(const AppContext&) {
    std::time_t t = std::time(nullptr);
    std::cout << std::ctime(&t);
    return 0;
}
}