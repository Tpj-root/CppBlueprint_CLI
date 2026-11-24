#pragma once

#include <string>

namespace cppforge {

class SystemInfo {
public:
    static std::string operatingSystem();
    static int cppVersion();
};

}