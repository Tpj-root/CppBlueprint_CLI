#include "cppforge/cli/Arguments.h"

namespace cppforge {

Arguments::Arguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        const std::string token = argv[i];

        // --key=value form
        if (token.rfind("--", 0) == 0) {
            const auto equal = token.find('=');
            if (equal != std::string::npos) {
                const std::string key = token.substr(0, equal);
                const std::string value = token.substr(equal + 1);
                options_[key] = value;
            }
            // --key value form, unless next token is another option
            else if (i + 1 < argc && std::string(argv[i + 1]).rfind("-", 0) != 0) {
                options_[token] = argv[++i];
            }
            // Standalone flag
            else {
                options_[token] = "true";
            }
        }
        // Short flags: -h, -v (kept as flags)
        else if (token.size() == 2 && token[0] == '-') {
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

} // namespace cppforge
