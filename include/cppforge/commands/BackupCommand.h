#pragma once

#include <string>

namespace cppforge {

class BackupCommand {
public:
    static std::string name();
    static std::string description();

    static int execute();
};

}