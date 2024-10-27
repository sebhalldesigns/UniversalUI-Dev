cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UniversalUI-Dev)

find_package(SDL2 REQUIRED)

# Add an executable
add_executable(UniversalUI-Dev main.cpp)

target_include_directories(UniversalUI-Dev PUBLIC ${SDL2_INCLUDE_DIR})

# Link the library
target_link_libraries(UniversalUI-Dev PUBLIC ${SDL2_LIBRARIES})

# Ensure the correct entry point for Windows applications
set_target_properties(UniversalUI-Dev PROPERTIES LINK_FLAGS "-Wl,-subsystem,console")