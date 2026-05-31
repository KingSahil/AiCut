#include "TrimEngine.h"

#include <filesystem>
#include <fstream>
#include <iostream>

int main()
{
    TrimEngine engine;

    bool missingFileResult = engine.trim(
        "this-file-should-not-exist.mp4",
        "output.mp4",
        1.0,
        2.0
    );

    if (missingFileResult)
    {
        std::cout << "Test failed: trim should reject a missing input file.\n";
        return 1;
    }

    const std::string temporaryInputPath = "temporary-test-input.mp4";

    std::ofstream temporaryFile(temporaryInputPath);
    temporaryFile << "This is only a test file.\n";
    temporaryFile.close();

    bool invalidTimeResult = engine.trim(
        temporaryInputPath,
        "output.mp4",
        5.0,
        2.0
    );

    std::filesystem::remove(temporaryInputPath);

    if (invalidTimeResult)
    {
        std::cout << "Test failed: trim should reject end time <= start time.\n";
        return 1;
    }

    std::cout << "All TrimEngine tests passed.\n";
    return 0;
}
