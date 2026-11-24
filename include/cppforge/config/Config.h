#pragma once

#include <string>
#include <unordered_map>

namespace cppforge {

class Config {
public:
    // Load key/value entries from an INI file. Missing file leaves defaults.
    bool load(const std::string& path);

    std::string get(const std::string& section,
                   const std::string& key,
                   const std::string& fallback = "") const;

    bool getBool(const std::string& section,
                const std::string& key,
                bool fallback = false) const;

    void set(const std::string& section,
             const std::string& key,
             const std::string& value);

private:
    // Keys are stored as "section.key".
    std::unordered_map<std::string, std::string> values_;
};

} // namespace cppforge
