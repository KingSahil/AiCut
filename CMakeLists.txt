cmake_minimum_required(VERSION 3.16)

project(AIVideoEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(AIVideoEditor
    src/main.cpp
    src/TrimEngine.cpp
)

target_include_directories(AIVideoEditor PRIVATE
    include
)

enable_testing()

add_executable(TrimEngineTests
    tests/TrimEngineTests.cpp
    src/TrimEngine.cpp
)

target_include_directories(TrimEngineTests PRIVATE
    include
)

add_test(NAME TrimEngineTests COMMAND TrimEngineTests)
