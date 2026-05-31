# AI Video Editor

A beginner-friendly C++ command-line app that trims a video by calling
FFmpeg. The first version is intentionally small so it is easy to read,
build, run, and change.

The app asks for:

- the input video path
- the output video path
- the start time in seconds
- the end time in seconds

It then creates a new trimmed video without re-encoding, which helps keep the
trim fast and preserves the original video quality.

## What You Will Need

Install these before you build the project:

- A C++ compiler that supports C++17
- CMake 3.16 or newer
- FFmpeg

On Windows, you can use Visual Studio Build Tools, Visual Studio Community, or
another C++ compiler that works with CMake.

Check that FFmpeg is installed by running:

```powershell
ffmpeg -version
```

If PowerShell says the command is not found, install FFmpeg and add it to your
system `PATH`.

## Project Files

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

What each file does:

- `src/main.cpp` shows prompts in the terminal and reads your answers.
- `include/TrimEngine.h` declares the `TrimEngine` class.
- `src/TrimEngine.cpp` checks the inputs and builds the FFmpeg command.
- `tests/TrimEngineTests.cpp` contains small tests for the trimming logic.
- `CMakeLists.txt` tells CMake how to build the app and tests.

## Build The App

Open PowerShell in this project folder, then run:

```powershell
cmake -S . -B build
cmake --build build
```

After the build finishes, the executable should be here:

```text
build\AIVideoEditor.exe
```

## Run The App

From the project folder, run:

```powershell
.\build\AIVideoEditor.exe
```

Example input:

```text
Enter input video path: C:\Videos\original.mp4
Enter output video path: C:\Videos\short-clip.mp4
Enter start time in seconds: 10
Enter end time in seconds: 25
```

This creates a new video clip from second `10` to second `25`.

If your path contains spaces, you can paste it with quotes:

```text
"C:\Users\You\Videos\my video.mp4"
```

## Run The Tests

Build the project first, then run:

```powershell
ctest --test-dir build
```

You can also run the test executable directly:

```powershell
.\build\TrimEngineTests.exe
```

## How The Trim Works

For an input from `10` seconds to `25` seconds, the app generates a command like:

```powershell
ffmpeg -y -ss 10 -i "C:\Videos\original.mp4" -to 15 -c copy "C:\Videos\short-clip.mp4"
```

The important pieces are:

- `ffmpeg` starts FFmpeg.
- `-y` allows FFmpeg to replace the output file if it already exists.
- `-ss 10` starts reading at 10 seconds.
- `-i "C:\Videos\original.mp4"` selects the input video.
- `-to 15` keeps 15 seconds of output.
- `-c copy` trims without re-encoding.
- `"C:\Videos\short-clip.mp4"` is the new output file.

## Common Problems

### FFmpeg is not found

Run:

```powershell
ffmpeg -version
```

If that fails, FFmpeg is either not installed or not available in your `PATH`.

### Input file does not exist

Check that the video path is correct. On Windows, you can drag a file into
PowerShell to paste its full path.

### Output path must include a file name

Use a full file path for the output, not just a folder.

Good:

```text
C:\Videos\clip.mp4
```

Not enough:

```text
C:\Videos
```

### End time must be greater than start time

The app needs an end time that comes after the start time.

Good:

```text
Start: 10
End: 25
```

Not valid:

```text
Start: 25
End: 10
```

## Beginner Notes

If you are new to this project, read the files in this order:

1. `src/main.cpp`
2. `include/TrimEngine.h`
3. `src/TrimEngine.cpp`
4. `tests/TrimEngineTests.cpp`

This helps you follow the app from the user input, to the class declaration, to
the trim logic, and finally to the tests.

## Current Scope

This project currently focuses on a simple Phase 1 workflow:

1. Ask the user for trim settings.
2. Validate the time range.
3. Check that the input file exists.
4. Check that the output path looks like a video file.
5. Run FFmpeg to create the trimmed output.

Future versions could add a graphical interface, previews, multiple clips, or
AI-assisted editing features.
