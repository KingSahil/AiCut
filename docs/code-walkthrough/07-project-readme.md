# 07 - Project README

This file explains `README.md`.

The README is the user-facing guide for the project. It tells someone what the
app does, what tools they need, how to build it, how to run it, how to run the
tests, and how the FFmpeg command works.

## File Location

```text
README.md
```

## Purpose

The README is not part of the compiled application. It is documentation for
humans.

It is especially useful for someone who has just opened the project and wants
to know:

- what the app is
- what must be installed
- how the files are organized
- how to build the app
- how to run the app
- how to run the tests
- what common errors mean

## Project Summary

The README describes the project as:

```text
A beginner-friendly C++ command-line app that trims a video by calling FFmpeg.
```

That is the central idea of the codebase.

The C++ app does not directly decode, edit, or encode video frames. Instead, it
collects user settings and uses FFmpeg to do the media work.

## Required Tools

The README lists three requirements:

- a C++17 compiler
- CMake 3.16 or newer
- FFmpeg

These match the project code and build file.

`CMakeLists.txt` requires C++17 and CMake 3.16. `TrimEngine.cpp` requires
FFmpeg to be available as a command-line program.

## Project Files Section

The README shows the project tree:

```text
AIVideoEditor/
|-- CMakeLists.txt
|-- README.md
|-- include/
|   `-- TrimEngine.h
|-- src/
|   |-- main.cpp
|   `-- TrimEngine.cpp
`-- tests/
    `-- TrimEngineTests.cpp
```

This is a quick map of the codebase.

The README also gives a short explanation for each important file. The files in
this `docs/code-walkthrough` folder expand those short explanations into more
detailed notes.

## Build Instructions

The README recommends:

```powershell
cmake -S . -B build
cmake --build build
```

The first command configures the project and creates the `build` directory.

The second command compiles the project.

After the build, the main executable should be:

```text
build\AIVideoEditor.exe
```

## Run Instructions

The README says to run:

```powershell
.\build\AIVideoEditor.exe
```

This launches the command-line app from `src/main.cpp`.

The app asks for:

- input video path
- output video path
- start time in seconds
- end time in seconds

Then it calls `TrimEngine::trim`.

## Test Instructions

The README gives two ways to run tests:

```powershell
ctest --test-dir build
```

or:

```powershell
.\build\TrimEngineTests.exe
```

The first uses CTest.

The second runs the test executable directly.

Both ultimately run the code in `tests/TrimEngineTests.cpp`.

## FFmpeg Explanation

The README explains the generated command:

```powershell
ffmpeg -y -ss 10 -i "C:\Videos\original.mp4" -to 15 -c copy "C:\Videos\short-clip.mp4"
```

This matches the command built in `TrimEngine::buildCommand`.

The most important option is:

```text
-c copy
```

That tells FFmpeg to copy the existing streams instead of re-encoding them.

This makes trimming fast and preserves original quality, though stream-copy
trims can depend on keyframe placement.

## Common Problems Section

The README explains likely user errors:

- FFmpeg is not found.
- The input file does not exist.
- The output path does not include a file name.
- The end time is not greater than the start time.

These match the validation and runtime behavior in `TrimEngine.cpp`.

## Beginner Notes Section

The README suggests this reading order:

1. `src/main.cpp`
2. `include/TrimEngine.h`
3. `src/TrimEngine.cpp`
4. `tests/TrimEngineTests.cpp`

The docs in this folder use a similar order, with `CMakeLists.txt` added near
the beginning because it explains how all the files are connected during the
build.

## Current Scope Section

The README says the current version focuses on a Phase 1 workflow:

1. Ask the user for trim settings.
2. Validate the time range.
3. Check that the input file exists.
4. Check that the output path looks like a video file.
5. Run FFmpeg to create the trimmed output.

That is a good summary of the current app architecture.

## How This README Relates To The Code Walkthrough

Use `README.md` when you want to build, run, or understand the app at a high
level.

Use this numbered walkthrough folder when you want a deeper explanation of each
individual file.
