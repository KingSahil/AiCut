# 01 - Reading Order

This folder explains the project one file at a time. The files are numbered in
the recommended reading order so a beginner can follow the program from the
project setup to the application flow, then to the trim engine and tests.

## Recommended Order

1. `01-reading-order.md`
   - Start here to understand how the documentation is organized.

2. `02-cmake-build-file.md`
   - Explains `CMakeLists.txt`, which defines how the application and test
     executable are built.

3. `03-main-entry-point.md`
   - Explains `src/main.cpp`, where the command-line program starts and reads
     user input.

4. `04-trim-engine-header.md`
   - Explains `include/TrimEngine.h`, which declares the public interface and
     private helper functions for the trim engine.

5. `05-trim-engine-implementation.md`
   - Explains `src/TrimEngine.cpp`, where validation, FFmpeg command creation,
     and command execution happen.

6. `06-trim-engine-tests.md`
   - Explains `tests/TrimEngineTests.cpp`, which checks important failure cases.

7. `07-project-readme.md`
   - Explains `README.md`, the user-facing project guide.

## Project Shape

```text
AIVideoEditor/
|-- CMakeLists.txt
|-- README.md
|-- include/
|   `-- TrimEngine.h
|-- src/
|   |-- main.cpp
|   `-- TrimEngine.cpp
|-- tests/
|   `-- TrimEngineTests.cpp
`-- docs/
    `-- code-walkthrough/
```

## High-Level Program Flow

The current app is a small command-line video trimmer.

```text
User runs app
    |
    v
src/main.cpp asks for paths and times
    |
    v
TrimEngine::trim validates input
    |
    v
TrimEngine builds an FFmpeg command
    |
    v
std::system runs FFmpeg
    |
    v
App exits with 0 on success, 1 on failure
```

## Main Ideas To Watch For

- `src/main.cpp` is responsible for user interaction.
- `TrimEngine` is responsible for trim validation and FFmpeg command execution.
- `CMakeLists.txt` builds both the real app and the test app.
- The test file focuses on validation behavior, not real video processing.
- FFmpeg does the actual video trimming work; this C++ program prepares and
  launches the FFmpeg command.
