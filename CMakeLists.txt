cmake_minimum_required(VERSION 3.0)
project(ConsoleGraphLib)

set(CMAKE_BINARY_DIR ./build)

aux_source_directory(./source SOURCE)
add_library(ConsoleGraph STATIC ${SOURCE})
target_include_directories(ConsoleGraph PUBLIC ./include)
