#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace cppforge {

class Arguments {
public:
    // Parse argv into options, flags, and positional values.
    Arguments(int argc, char* argv[]);

    bool has(const std::string& key) const;
    std::string get(const std::string& key,
                   const std::string& fallback = "") const;

    const std::vector<std::string>& positional() const;

private:
    std::unordered_map<std::string, std::string> options_;
    std::vector<std::string> positional_;
};

} // namespace cppforge
