#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace cppforge {

class Arguments {
public:
    Arguments(int argc, char* argv[]);

    bool has(const std::string& key) const;
    std::string get(const std::string& key,
                    const std::string& fallback = "") const;

    const std::vector<std::string>& positional() const;
    const std::unordered_map<std::string, std::string>& options() const;

private:
    std::unordered_map<std::string, std::string> options_;
    std::vector<std::string> positional_;
};

}