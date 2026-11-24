#include "cppforge/system/SystemInfo.h"

namespace cppforge {

std::string SystemInfo::operatingSystem()
{
#ifdef __linux__
    return "Linux";
#elif defined(_WIN32)
    return "Windows";
#elif defined(__APPLE__)
    return "macOS";
#else
    return "Unknown";
#endif
}

int SystemInfo::cppVersion()
{
    return __cplusplus;
}

}
