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
