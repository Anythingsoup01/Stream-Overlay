cmake_minimum_required(VERSION 4.2.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(overlay-wks LANGUAGES C CXX)
set(SRCS
    "src/imgui/imgui_layer.cpp"
    "src/imgui/imgui_build.cpp"
    "src/window/serializer.cpp"
    "src/window/window.cpp"
    "src/main.cpp"
)
add_executable(overlay ${SRCS})
set_property(TARGET overlay PROPERTY CXX_STANDARD 20)

target_precompile_headers(overlay PUBLIC pch/sopch.h)
target_include_directories(overlay PRIVATE
    "include"
    "pch"
    "dep/GLFW/include"
    "dep/ImGui"
    "dep/glad/include"
    "dep/yaml/include"
)

target_link_libraries(overlay
    GL
    Glad
    glfw
    ImGui
    yaml-cpp
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
target_compile_definitions(overlay
PUBLIC
    SO_DEBUG
)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)
if(CMAKE_BUILD_TYPE STREQUAL Release)
target_compile_definitions(overlay
PUBLIC
    SO_RELEASE
)
endif(CMAKE_BUILD_TYPE STREQUAL Release)
add_subdirectory(dep/glad)
add_subdirectory(dep/GLFW)
add_subdirectory(dep/ImGui)
add_subdirectory(dep/yaml)
