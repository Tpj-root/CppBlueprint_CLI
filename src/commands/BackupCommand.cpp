#include "cppforge/commands/BackupCommand.h"
#include <iostream>

namespace cppforge {

int BackupCommand::execute(const AppContext&)
{
    std::cout << "Backup started...\n";
    return 0;
}

}