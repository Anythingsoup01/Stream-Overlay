cmake_minimum_required(VERSION 4.2.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(overlay-wks LANGUAGES CXX)
set(SRCS
    "src/main.cpp"
)
add_executable(overlay ${SRCS})
set_property(TARGET overlay PROPERTY CXX_STANDARD 20)

target_include_directories(overlay PRIVATE
    "include"
    "pch"
)

