# CppBlueprint_CLI

A small, expandable C++17 CLI application template using OOP, CMake, command-line arguments, INI configuration, and a simple logger.

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/CppBlueprint_CLI --help
./build/CppBlueprint_CLI --version
./build/CppBlueprint_CLI info
./build/CppBlueprint_CLI config
./build/CppBlueprint_CLI hello --name When
./build/CppBlueprint_CLI --config ./config.ini hello --name When
```

## CLI options

- `--help`, `-h`: show help
- `--version`, `-v`: show version
- `--config PATH`: select config file
- `--verbose`: enable verbose logging
- Commands: `info`, `config`, `hello`

## Project structure

- `include/`: public headers
- `src/`: implementation files
- `src/app/`: application orchestration and command handlers
- `src/cli/`: command-line argument parser
- `src/config/`: INI config loader
- `src/log/`: logging utility

Add new modules by creating a header/source pair and adding the `.cpp` file to `CppBlueprint_CLI_core` in CMake.





## **1. Create the files**

```
CppForge/
├── include/
│   └── cppforge/
│       └── commands/
│           └── BackupCommand.h
│
└── src/
    └── commands/
        └── BackupCommand.cpp
```

## **2. BackupCommand.h**

```
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
```

## **3. BackupCommand.cpp**

Your implementation is already correct:

```
#include "cppforge/commands/BackupCommand.h"
#include <iostream>

namespace cppforge {

std::string BackupCommand::name()
{
    return "backup";
}

std::string BackupCommand::description()
{
    return "Create a backup";
}

int BackupCommand::execute()
{
    std::cout << "Backup started...\n";
    return 0;
}

}
```

## **4. Register files in CMakeLists.txt**

Add these two files inside `cppforge_core`:

```
add_library(cppforge_core
    src/cli/Arguments.cpp
    src/config/Config.cpp
    src/log/Logger.cpp
    src/app/App.cpp

    # Backup command
    src/commands/BackupCommand.cpp
    include/cppforge/commands/BackupCommand.h
)
```

## **5. Connect it to App.cpp**

Add the header:

```
#include "cppforge/commands/BackupCommand.h"
```

Inside your existing `App::run()`, add this condition:

```
else if (command == cppforge::BackupCommand::name()) {
    return cppforge::BackupCommand::execute();
}
```

For example:

```
if (command == "info") {
    commandInfo();

} else if (command == "config") {
    commandConfig();

} else if (command == "hello") {
    commandHello();

} else if (command == "sysinfo") {
    commandSystemInfo();

} else if (command == cppforge::BackupCommand::name()) {
    return cppforge::BackupCommand::execute();

} else {
    Logger::error("Unknown command: " + command);
    return 1;
}
```

## **6. Add it to printHelp()**

Inside `App::printHelp()`:

```
std::cout
    << "Commands:\n"
    << "  info       Show application information\n"
    << "  config     Display configuration\n"
    << "  hello      Print a greeting\n"
    << "  sysinfo    Show system information\n"
    << "  backup     " << cppforge::BackupCommand::description() << "\n";
```

## **7. Build and test**

```
cmake -S . -B build
cmake --build build -j$(nproc)
```

Run:

```
./build/cppforge backup
```

Expected output

```
Backup started...
```

## **8. Understand the OOP design**

| Function        | Responsibility           |
| --------------- | ------------------------ |
| `name()`        | Returns command name     |
| `description()` | Returns help description |
| `execute()`     | Executes the command     |

Notice that these are `static` functions. You don't need to create an object:

```
cppforge::BackupCommand::execute();
```


## **9. How to add a new command from now on**

Suppose you want a `clean` command.

## **Only 3 steps**

**1. Create files**

```
include/cppforge/commands/CleanCommand.h
src/commands/CleanCommand.cpp
```

**2. Add the new library to CMake**

```
src/commands/CleanCommand.cpp
include/cppforge/commands/CleanCommand.h
```

**3. Register it in&#x20;**`App.cpp`

```
registry_.add(
    "clean",
    "Clean temporary files",
    []() {
        return CleanCommand::execute();
    }
);