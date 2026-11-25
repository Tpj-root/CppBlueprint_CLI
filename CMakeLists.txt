cmake_minimum_required(VERSION 3.16)
project(CppBlueprint VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(CppBlueprint_core
    src/cli/Arguments.cpp
    src/config/Config.cpp
    src/log/Logger.cpp
    src/system/SystemInfo.cpp
    src/app/App.cpp
    src/app/CommandRegistry.cpp
    src/commands/InfoCommand.cpp
    src/commands/ConfigCommand.cpp
    src/commands/HelloCommand.cpp
    src/commands/SysInfoCommand.cpp
    src/commands/BackupCommand.cpp
    src/commands/DateCommand.cpp

    include/cppforge/cli/Arguments.h
    include/cppforge/config/Config.h
    include/cppforge/log/Logger.h
    include/cppforge/system/SystemInfo.h
    include/cppforge/app/App.h
    include/cppforge/app/AppContext.h
    include/cppforge/app/CommandRegistry.h
    include/cppforge/commands/Command.h
    include/cppforge/commands/InfoCommand.h
    include/cppforge/commands/ConfigCommand.h
    include/cppforge/commands/HelloCommand.h
    include/cppforge/commands/SysInfoCommand.h
    include/cppforge/commands/BackupCommand.h
    include/cppforge/commands/DateCommand.h

)

target_include_directories(CppBlueprint_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(CppBlueprint src/main.cpp)
target_link_libraries(CppBlueprint PRIVATE CppBlueprint_core)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
    ${CMAKE_CURRENT_BINARY_DIR}/config.ini
    COPYONLY
)

set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
    PROPERTIES HEADER_FILE_ONLY TRUE
)

target_sources(CppBlueprint PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(CppBlueprint_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(CppBlueprint      PRIVATE -Wall -Wextra -Wpedantic)
endif()