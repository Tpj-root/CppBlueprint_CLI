#include "cppforge/cli/Arguments.h"

namespace cppforge {
namespace {
bool isOption(const char* s)
{
    return s && s[0] == '-';
}
}

Arguments::Arguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        const std::string token = argv[i];

        // Long option
        if (token.rfind("--", 0) == 0) {
            const auto equal = token.find('=');
            if (equal != std::string::npos) {
                options_[token.substr(0, equal)] = token.substr(equal + 1);
            } else if (i + 1 < argc && !isOption(argv[i + 1])) {
                options_[token] = argv[++i];
            } else {
                options_[token] = "true";
            }
        }
        // Short option: -i, -sL, -C ...
        else if (!token.empty() && token[0] == '-' && token.size() > 1) {
            options_[token] = "true";
        }
        else {
            positional_.push_back(token);
        }
    }
}

bool Arguments::has(const std::string& key) const
{
    return options_.find(key) != options_.end();
}

std::string Arguments::get(const std::string& key,
                           const std::string& fallback) const
{
    const auto it = options_.find(key);
    return it == options_.end() ? fallback : it->second;
}

const std::vector<std::string>& Arguments::positional() const
{
    return positional_;
}

const std::unordered_map<std::string, std::string>& Arguments::options() const
{
    return options_;
}

} // namespace cppforge