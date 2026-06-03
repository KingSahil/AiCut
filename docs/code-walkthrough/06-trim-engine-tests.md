# 06 - Trim Engine Tests

This file explains `tests/TrimEngineTests.cpp`.

The tests are small and direct. They create a `TrimEngine`, call `trim` with
different invalid inputs, and check that the function rejects them.

## File Location

```text
tests/TrimEngineTests.cpp
```

## Included Headers

```cpp
#include "TrimEngine.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
```

`TrimEngine.h` lets the tests create and use a `TrimEngine`.

The standard headers are used for:

- `<filesystem>`: creating and removing temporary files/directories.
- `<fstream>`: writing temporary files.
- `<iostream>`: printing failure messages.
- `<sstream>`: capturing output from `std::cout`.

## Test Program main

```cpp
int main()
{
    TrimEngine engine;
    ...
}
```

This test file is a complete executable with its own `main()`.

It does not use a testing framework. Instead, each test is written manually:

- call the code
- check the result
- print an error and return `1` if something is wrong
- return `0` if all checks pass

## Test 1: Missing Input File

```cpp
bool missingFileResult = engine.trim(
    "this-file-should-not-exist.mp4",
    "output.mp4",
    1.0,
    2.0
);
```

This calls `trim` with an input path that should not exist.

The expected result is `false`.

```cpp
if (missingFileResult)
{
    std::cout << "Test failed: trim should reject a missing input file.\n";
    return 1;
}
```

If `trim` returns `true`, the test fails because the trim engine should not
accept a missing input file.

## Temporary Input File

```cpp
const std::string temporaryInputPath = "temporary-test-input.mp4";

std::ofstream temporaryFile(temporaryInputPath);
temporaryFile << "This is only a test file.\n";
temporaryFile.close();
```

The tests create a temporary file so validation can pass the "input exists"
check.

This is not a real video. That is okay for tests that stop before FFmpeg runs.

## Test 2: Invalid Time Range

```cpp
bool invalidTimeResult = engine.trim(
    temporaryInputPath,
    "output.mp4",
    5.0,
    2.0
);
```

This calls `trim` with:

```text
start = 5
end = 2
```

That is invalid because the end time is before the start time.

The expected result is `false`.

After this test, the temporary input file is removed:

```cpp
std::filesystem::remove(temporaryInputPath);
```

## Test 3: Output Path Is A Folder

```cpp
std::filesystem::create_directory("temporary-output-folder");
```

This creates a real folder.

Then the test creates another temporary input file:

```cpp
std::ofstream secondTemporaryFile(temporaryInputPath);
secondTemporaryFile << "This is only a test file.\n";
secondTemporaryFile.close();
```

The test then calls:

```cpp
bool directoryOutputResult = engine.trim(
    temporaryInputPath,
    "temporary-output-folder",
    1.0,
    2.0
);
```

This passes a folder path as the output path.

The expected result is `false`.

## Capturing std::cout

```cpp
std::ostringstream capturedOutput;
std::streambuf* originalOutput = std::cout.rdbuf(capturedOutput.rdbuf());
```

This redirects `std::cout` into a string stream.

The test does this so it can inspect the message printed by `trim`.

After calling `trim`, the original output stream is restored:

```cpp
std::cout.rdbuf(originalOutput);
```

Restoring `std::cout` is important. Otherwise later output would keep going
into `capturedOutput` instead of the terminal.

## Cleanup

```cpp
std::filesystem::remove(temporaryInputPath);
std::filesystem::remove("temporary-output-folder");
```

The test removes temporary files and folders after use.

This keeps the project directory clean after the test runs.

## Checking The Folder Output Result

```cpp
if (directoryOutputResult)
{
    std::cout << "Test failed: trim should reject a folder as the output path.\n";
    return 1;
}
```

If `trim` accepts the folder path, the test fails.

## Checking The Error Message

```cpp
if (capturedOutput.str().find("output path must include a file name") == std::string::npos)
{
    std::cout << "Test failed: trim should explain that output needs a file name.\n";
    return 1;
}
```

This verifies that the user receives a helpful explanation.

`std::string::npos` means "not found."

So this condition means:

```text
If the expected message was not found, fail the test.
```

## Success Message

```cpp
std::cout << "All TrimEngine tests passed.\n";
return 0;
```

If every check passes, the test program prints a success message and exits with
`0`.

## What These Tests Cover

The tests currently cover:

- missing input file rejection
- invalid time range rejection
- output folder rejection
- helpful output-path error message

## What These Tests Do Not Cover Yet

The tests do not currently verify:

- successful trimming of a real video
- exact FFmpeg command generation
- behavior when FFmpeg is missing
- behavior when FFmpeg returns a non-zero exit code
- paths containing embedded double quotes
- negative start or end times

That is fine for a small first version, but these would be useful areas to test
as the project grows.
