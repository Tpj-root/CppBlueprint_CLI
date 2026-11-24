cmake_minimum_required(VERSION 3.16)
project(CppBlueprint VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(CppBlueprint_core
    # Source files
    src/cli/Arguments.cpp
    src/config/Config.cpp
    src/log/Logger.cpp
    src/app/App.cpp
    src/system/SystemInfo.cpp
    src/main.cpp

    # Header files (display in Qt Creator)
    include/cppforge/cli/Arguments.h
    include/cppforge/config/Config.h
    include/cppforge/log/Logger.h
    include/cppforge/app/App.h
    include/cppforge/system/SystemInfo.h

)



target_include_directories(CppBlueprint_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(CppBlueprint
    src/main.cpp
)

target_link_libraries(CppBlueprint PRIVATE CppBlueprint_core)

# --------------------------------------------------
# config.ini
# --------------------------------------------------

# Copy config.ini into the build directory
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
    ${CMAKE_CURRENT_BINARY_DIR}/config.ini
    COPYONLY
)

# Display config.ini in Qt Creator's project tree
set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
    PROPERTIES HEADER_FILE_ONLY TRUE
)

target_sources(CppBlueprint PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
)

# Compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(CppBlueprint_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(CppBlueprint PRIVATE -Wall -Wextra -Wpedantic)
endif()
