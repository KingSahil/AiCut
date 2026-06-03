# 03 - Main Entry Point

This file explains `src/main.cpp`.

`src/main.cpp` is where the command-line application starts. It asks the user
for input, cleans up quoted paths, creates a `TrimEngine`, and returns an exit
code based on whether trimming worked.

## File Location

```text
src/main.cpp
```

## Included Headers

```cpp
#include "TrimEngine.h"

#include <iostream>
#include <string>
```

`TrimEngine.h` gives this file access to the `TrimEngine` class.

`<iostream>` provides `std::cout`, `std::cin`, and `std::getline`.

`<string>` provides `std::string`.

## removeSurroundingQuotes

```cpp
std::string removeSurroundingQuotes(const std::string& text)
```

This helper removes one pair of double quotes if the whole string is wrapped in
quotes.

This is useful on Windows because users often paste paths like:

```text
"C:\Users\You\Videos\my video.mp4"
```

The function turns that into:

```text
C:\Users\You\Videos\my video.mp4
```

### Short Strings Are Returned As-Is

```cpp
if (text.length() < 2)
{
    return text;
}
```

If the string has fewer than two characters, it cannot contain both an opening
quote and a closing quote, so the function returns it unchanged.

### Quote Detection

```cpp
bool startsWithQuote = text.front() == '"';
bool endsWithQuote = text.back() == '"';
```

These lines check the first and last characters.

### Removing The Quotes

```cpp
if (startsWithQuote && endsWithQuote)
{
    return text.substr(1, text.length() - 2);
}
```

If both ends have quotes, the function returns the middle part of the string.

For example:

```text
"video.mp4"
```

becomes:

```text
video.mp4
```

If the string is not wrapped in quotes, it is returned unchanged.

## main

```cpp
int main()
```

This is the starting point of the app.

## Variables

```cpp
std::string inputPath;
std::string outputPath;
double startSeconds = 0.0;
double endSeconds = 0.0;
```

The app stores four user-provided values:

- `inputPath`: the video to trim.
- `outputPath`: where the trimmed video should be saved.
- `startSeconds`: where the trim should begin.
- `endSeconds`: where the trim should end.

The time values are `double`, so the user can enter decimal values such as
`2.5`.

## Title Message

```cpp
std::cout << "Lossless AI Video Editor - Phase 1\n\n";
```

This prints the program name and adds a blank line after it.

## Reading Paths

```cpp
std::cout << "Enter input video path: ";
std::getline(std::cin, inputPath);
inputPath = removeSurroundingQuotes(inputPath);
```

The program uses `std::getline` for paths so paths with spaces can be read
correctly.

After reading the path, it calls `removeSurroundingQuotes`.

The same pattern is used for the output path:

```cpp
std::cout << "Enter output video path: ";
std::getline(std::cin, outputPath);
outputPath = removeSurroundingQuotes(outputPath);
```

## Reading Times

```cpp
std::cout << "Enter start time in seconds: ";
std::cin >> startSeconds;

std::cout << "Enter end time in seconds: ";
std::cin >> endSeconds;
```

The program uses `std::cin >>` to read numeric values.

Example:

```text
Enter start time in seconds: 10
Enter end time in seconds: 25
```

## Creating The Trim Engine

```cpp
TrimEngine engine;
```

This creates an object that knows how to validate trim settings, build an
FFmpeg command, and run it.

## Calling trim

```cpp
bool success = engine.trim(
    inputPath,
    outputPath,
    startSeconds,
    endSeconds
);
```

This sends the user's values to `TrimEngine::trim`.

`trim` returns:

- `true` if the trim command succeeds.
- `false` if validation fails or FFmpeg fails.

## Exit Code

```cpp
if (success)
{
    return 0;
}

return 1;
```

Command-line programs use exit codes to report success or failure.

- `0` usually means success.
- Non-zero values usually mean failure.

So if trimming works, the app exits with `0`. Otherwise, it exits with `1`.

## Responsibility Of This File

`src/main.cpp` should stay focused on the command-line experience:

- showing prompts
- reading user input
- cleaning pasted paths
- calling the trim engine
- returning the final process status

It does not build FFmpeg commands directly. That job belongs to
`src/TrimEngine.cpp`.
