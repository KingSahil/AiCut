#include "TrimEngine.h"

#include <iostream>
#include <string>

int main()
{
    std::string inputPath;
    std::string outputPath;
    double startSeconds = 0.0;
    double endSeconds = 0.0;

    std::cout << "Lossless AI Video Editor - Phase 1\n\n";

    std::cout << "Enter input video path: ";
    std::getline(std::cin, inputPath);

    std::cout << "Enter output video path: ";
    std::getline(std::cin, outputPath);

    std::cout << "Enter start time in seconds: ";
    std::cin >> startSeconds;

    std::cout << "Enter end time in seconds: ";
    std::cin >> endSeconds;

    TrimEngine engine;

    bool success = engine.trim(
        inputPath,
        outputPath,
        startSeconds,
        endSeconds
    );

    if (success)
    {
        return 0;
    }

    return 1;
}
