# 02 - CMake Build File

This file explains `CMakeLists.txt`.

`CMakeLists.txt` tells CMake how to configure and build the project. It defines
the C++ version, the application executable, the test executable, include
folders, and the test command.

## File Location

```text
CMakeLists.txt
```

## Purpose

The build file answers these questions:

- What is the project called?
- Which programming language is used?
- Which C++ standard is required?
- Which source files belong to the main app?
- Which source files belong to the tests?
- Where should the compiler look for header files?
- How should CTest run the tests?

## Minimum CMake Version

```cmake
cmake_minimum_required(VERSION 3.16)
```

This means the project expects CMake version `3.16` or newer. If someone uses
an older version, CMake may stop during configuration.

## Project Declaration

```cmake
project(AIVideoEditor LANGUAGES CXX)
```

This names the project `AIVideoEditor` and says the project uses C++.

`CXX` is CMake's name for the C++ language.

## C++ Standard Settings

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

These lines require C++17.

- `CMAKE_CXX_STANDARD 17` asks for C++17.
- `CMAKE_CXX_STANDARD_REQUIRED ON` makes C++17 mandatory.
- `CMAKE_CXX_EXTENSIONS OFF` asks the compiler to avoid vendor-specific C++
  extensions where possible.

The project needs C++17 because it uses `std::filesystem` in `TrimEngine.cpp`
and `TrimEngineTests.cpp`.

## Main Application Executable

```cmake
add_executable(AIVideoEditor
    src/main.cpp
    src/TrimEngine.cpp
)
```

This creates the main executable named `AIVideoEditor`.

It is built from:

- `src/main.cpp`
- `src/TrimEngine.cpp`

`src/main.cpp` contains the `main()` function, so it is the starting point of
the real command-line app.

`src/TrimEngine.cpp` contains the trimming logic used by the app.

## Include Directory For The Main App

```cmake
target_include_directories(AIVideoEditor PRIVATE
    include
)
```

This tells the compiler that header files can be found in the `include`
directory.

That is why source files can write:

```cpp
#include "TrimEngine.h"
```

instead of:

```cpp
#include "../include/TrimEngine.h"
```

The keyword `PRIVATE` means this include path is only needed while building
this target.

## Enable Testing

```cmake
enable_testing()
```

This turns on CTest support for the project.

CTest is CMake's test runner. After building, tests can be run with:

```powershell
ctest --test-dir build
```

## Test Executable

```cmake
add_executable(TrimEngineTests
    tests/TrimEngineTests.cpp
    src/TrimEngine.cpp
)
```

This creates a second executable named `TrimEngineTests`.

It is built from:

- `tests/TrimEngineTests.cpp`
- `src/TrimEngine.cpp`

The test executable includes `src/TrimEngine.cpp` because the tests call the
real `TrimEngine` code.

It does not include `src/main.cpp`, because tests need their own `main()`
function. `tests/TrimEngineTests.cpp` provides that test-specific `main()`.

## Include Directory For Tests

```cmake
target_include_directories(TrimEngineTests PRIVATE
    include
)
```

This gives the test executable access to `include/TrimEngine.h`.

Without this line, `tests/TrimEngineTests.cpp` might fail to compile when it
tries to include:

```cpp
#include "TrimEngine.h"
```

## Registering The Test With CTest

```cmake
add_test(NAME TrimEngineTests COMMAND TrimEngineTests)
```

This registers the `TrimEngineTests` executable as a CTest test.

The test name is:

```text
TrimEngineTests
```

The command CTest runs is:

```text
TrimEngineTests
```

## Why There Are Two Executables

The project builds two separate programs:

```text
AIVideoEditor      -> the real command-line app
TrimEngineTests    -> the test program
```

This keeps the real app and the tests separate while allowing both to reuse
`src/TrimEngine.cpp`.
