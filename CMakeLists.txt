cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UniversalUIApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(./UniversalUI)

add_executable(UniversalUIApp src/main.cpp)

target_include_directories(UniversalUIApp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/UniversalUI/lib
)

target_link_libraries(UniversalUIApp PRIVATE UniversalUI)

if(EMSCRIPTEN)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -s \"FETCH=1\" -s \"USE_WEBGL2=1\" -s \"USE_SDL=2\" -s \"MIN_WEBGL_VERSION=2\"")


    add_custom_command(TARGET UniversalUIApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/resources/index.html
            ${CMAKE_BINARY_DIR}/index.html)
endif()