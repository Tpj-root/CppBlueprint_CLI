#include "cppforge/app/App.h"
#include "cppforge/log/Logger.h"
#include "cppforge/system/SystemInfo.h"

#include <iostream>

namespace cppforge {

App::App(const Arguments& args)
    : args_(args),
      configPath_(args.get("--config", "config.ini")),
      appName_("CppForge"),
      appVersion_("1.0.0")
{
    // Read config file, if present. Defaults remain active if not found.
    if (!config_.load(configPath_))
        Logger::warning("Config file not found: " + configPath_ + " (using built-in defaults)");

    appName_ = config_.get("app", "name", appName_);
    appVersion_ = config_.get("app", "version", appVersion_);

    // CLI flags override config file values.
    const bool verbose = args_.has("--verbose") || config_.getBool("general", "verbose", false);
    Logger::setVerbose(verbose);
}

int App::run()
{
    if (args_.has("--help") || args_.has("-h")) {
        printHelp();
        return 0;
    }

    if (args_.has("--version") || args_.has("-v")) {
        std::cout << appName_ << " " << appVersion_ << '\n';
        return 0;
    }

    if (args_.has("--sysinfo") || args_.has("-s")) {
        commandSystemInfo();;
        return 0;
    }

    if (args_.has("--OS") || args_.has("-os")) {
        std::cout << "OS          : "
                  << cppforge::SystemInfo::operatingSystem()
                  << '\n';
        return 0;
    }

    if (args_.has("--Cpp_version") || args_.has("-c")) {
        std::cout << "C++ Version : "
                  << cppforge::SystemInfo::cppVersion()
                  << '\n';
        return 0;
    }


    const auto& positional = args_.positional();
    if (positional.empty()) {
        printHelp();
        return 0;
    }

    const std::string command = positional.front();

    if (command == "info") {
        commandInfo();
    } else if (command == "config") {
        commandConfig();
    } else if (command == "hello") {
        commandHello();
    }
      else if (command == "sysinfo") {
        commandSystemInfo();

    } else {
        Logger::error("Unknown command: " + command);
        std::cout << "Use --help to see available commands.\n";
        return 1;
    }

    return 0;
}

void App::printHelp() const
{
    std::cout
        << appName_ << " - expandable C++ CLI template\n\n"
        << "Usage:\n"
        << "  cppforge [options] <command>\n\n"
        << "Options:\n"
        << "  -h, --help          Show this help\n"
        << "  -v, --version       Show version\n"
        << "  -s, --sysinfo       Show sysinfo\n"
        << "  -os, --OS           Show OS version\n"
        << "  -c, ---Cpp_version  Show CPP version\n"
        << "      --config PATH   Use a config file\n"
        << "      --verbose       Enable debug logging\n\n"
        << "Commands:\n"
        << "  info                Show app information\n"
        << "  config              Display loaded settings\n"
        << "  hello [--name NAME]  Print a greeting\n\n"
        << "Examples:\n"
        << "  cppforge info\n"
        << "  cppforge hello --name Developer\n"
        << "  cppforge --config ./config.ini config\n"
        << "  cppforge sysinfo\n"
        ;
}



void App::commandInfo() const
{
    std::cout << "Application : " << appName_ << '\n'
              << "Version     : " << appVersion_ << '\n'
              << "Config file : " << configPath_ << '\n';
}

void App::commandConfig() const
{
    std::cout << "Config file: " << configPath_ << '\n'
              << "[app]\n"
              << "name = " << config_.get("app", "name", appName_) << '\n'
              << "version = " << config_.get("app", "version", appVersion_) << '\n'
              << "[general]\n"
              << "verbose = " << (config_.getBool("general", "verbose", false) ? "true" : "false") << '\n'
              << "user = " << config_.get("general", "user", "developer") << '\n'
              << "[logging]\n"
              << "level = " << config_.get("logging", "level", "info") << '\n';
}

void App::commandHello() const
{
    const auto& positional = args_.positional();
    (void)positional;

    const std::string name = args_.get("--name", config_.get("general", "user", "Developer"));
    Logger::info("Hello, " + name + "!");
    Logger::debug("Debug output is enabled.");
}


void App::commandSystemInfo() const
{
    std::cout << "OS          : "
              << cppforge::SystemInfo::operatingSystem()
              << '\n';

    std::cout << "C++ Version : "
              << cppforge::SystemInfo::cppVersion()
              << '\n';
}

// void App::commandSystemInfo() const
// {
//     std::cout << "--sysinfo\n";

//     std::cout << "  --OS          : "
//               << cppforge::SystemInfo::operatingSystem()
//               << '\n';

//     std::cout << "  --Cpp_version : "
//               << cppforge::SystemInfo::cppVersion()
//               << '\n';
// }





} // namespace cppforge
