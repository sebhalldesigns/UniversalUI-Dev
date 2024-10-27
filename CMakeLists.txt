cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UniversalUI-Dev)

if(WIN32)
    message(STATUS "Configuring for WIN32")

    find_package(SDL2 REQUIRED)

    # Add an executable
    add_executable(UniversalUI-Dev main.cpp)

    target_include_directories(UniversalUI-Dev PUBLIC ${SDL2_INCLUDE_DIR})

    # Link the library
    target_link_libraries(UniversalUI-Dev PUBLIC ${SDL2_LIBRARIES})

    # Ensure the correct entry point for Windows applications
    set_target_properties(UniversalUI-Dev PROPERTIES LINK_FLAGS "-Wl,-subsystem,console")

elseif(EMSCRIPTEN)
    message(STATUS "Configuring for WASM")
    add_executable(UniversalUI-Dev main.cpp)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -s \"FETCH=1\" -s \"USE_WEBGL2=1\" -s \"USE_SDL=2\" -s \"MIN_WEBGL_VERSION=2\"")

    add_custom_command(TARGET UniversalUI-Dev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/resources/index.html
            ${CMAKE_CURRENT_BINARY_DIR}/index.html)

endif()
