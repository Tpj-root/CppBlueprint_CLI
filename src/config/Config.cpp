#include "cppforge/config/Config.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>

namespace cppforge {
namespace {

std::string trim(std::string text)
{
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return {};

    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

std::string toLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

} // namespace

bool Config::load(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
        return false;

    std::string section;
    std::string line;

    while (std::getline(file, line)) {
        line = trim(line);

        // Ignore blank lines and comment lines.
        if (line.empty() || line[0] == '#' || line[0] == ';')
            continue;

        // Section heading, such as [app]
        if (line.front() == '[' && line.back() == ']') {
            section = trim(line.substr(1, line.size() - 2));
            continue;
        }

        // key=value line
        const auto equal = line.find('=');
        if (equal == std::string::npos)
            continue;

        const std::string key = trim(line.substr(0, equal));
        const std::string value = trim(line.substr(equal + 1));

        if (!key.empty())
            values_[section + "." + key] = value;
    }

    return true;
}

std::string Config::get(const std::string& section,
                        const std::string& key,
                        const std::string& fallback) const
{
    const auto it = values_.find(section + "." + key);
    return it == values_.end() ? fallback : it->second;
}

bool Config::getBool(const std::string& section,
                    const std::string& key,
                    bool fallback) const
{
    const auto value = toLower(get(section, key, fallback ? "true" : "false"));
    if (value == "true" || value == "1" || value == "yes" || value == "on")
        return true;
    if (value == "false" || value == "0" || value == "no" || value == "off")
        return false;
    return fallback;
}

void Config::set(const std::string& section,
                 const std::string& key,
                 const std::string& value)
{
    values_[section + "." + key] = value;
}

} // namespace cppforge
