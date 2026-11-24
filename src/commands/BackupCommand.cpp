#include "cppforge/commands/BackupCommand.h"
#include <iostream>

namespace cppforge {

std::string BackupCommand::name()
{
    return "backup";
}

std::string BackupCommand::description()
{
    return "Create a backup";
}

int BackupCommand::execute()
{
    std::cout << "Backup started...\n";
    return 0;
}

}