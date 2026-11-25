#include "cppforge/commands/SysInfoCommand.h"
#include "cppforge/system/SystemInfo.h"
#include <iostream>

namespace cppforge {

int SysInfoCommand::execute(const AppContext&)
{
    std::cout << "OS          : " << SystemInfo::operatingSystem() << '\n'
              << "C++ Version : " << SystemInfo::cppVersion()      << '\n';
    return 0;
}

}