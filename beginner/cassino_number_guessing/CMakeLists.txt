cmake_minimum_required(VERSION 3.22.1)
project(CassinoNumberGuessing)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
    src/main.cc
)
