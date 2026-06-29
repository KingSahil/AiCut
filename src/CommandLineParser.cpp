#include "CommandLineParser.h"

#include <cstdlib>
#include <set>
#include <map>
#include <sstream>

namespace
{
    bool parseDouble(const std::string& text, double& value)
    {
        char* endPointer = nullptr;
        value = std::strtod(text.c_str(), &endPointer);

        return endPointer != text.c_str() && *endPointer == '\0';
    }

    bool collectOptions(
        const std::vector<std::string>& arguments,
        std::map<std::string, std::string>& options,
        std::string& errorMessage
    )
    {
        for (std::size_t index = 2; index < arguments.size(); index += 2)
        {
            const std::string& flag = arguments[index];

            if (flag.rfind("--", 0) != 0)
            {
                errorMessage = "Expected a flag like --input, but got: " + flag;
                return false;
            }

            if (index + 1 >= arguments.size())
            {
                errorMessage = "Missing value for " + flag + ".";
                return false;
            }

            options[flag] = arguments[index + 1];
        }

        return true;
    }

    bool requireOption(
        const std::map<std::string, std::string>& options,
        const std::string& flag,
        std::string& value,
        std::string& errorMessage
    )
    {
        auto option = options.find(flag);

        if (option == options.end())
        {
            errorMessage = "Missing required option " + flag + ".";
            return false;
        }

        value = option->second;
        return true;
    }

    bool rejectUnknownOptions(
        const std::map<std::string, std::string>& options,
        const std::set<std::string>& allowedOptions,
        std::string& errorMessage
    )
    {
        for (const auto& option : options)
        {
            if (allowedOptions.find(option.first) == allowedOptions.end())
            {
                errorMessage = "Unknown option " + option.first + ".";
                return false;
            }
        }

        return true;
    }
}

ParsedCommand parseCommandLine(const std::vector<std::string>& arguments)
{
    ParsedCommand parsed;

    if (arguments.size() < 2)
    {
        parsed.errorMessage = "Missing command.";
        return parsed;
    }

    const std::string& commandName = arguments[1];

    if (commandName == "--help" || commandName == "-h" || commandName == "help")
    {
        parsed.type = CommandType::Help;
        parsed.isValid = true;
        return parsed;
    }

    std::map<std::string, std::string> options;

    if (!collectOptions(arguments, options, parsed.errorMessage))
    {
        return parsed;
    }

    if (commandName == "trim")
    {
        parsed.type = CommandType::Trim;

        if (!rejectUnknownOptions(options, {"--input", "--output", "--start", "--end"}, parsed.errorMessage))
        {
            return parsed;
        }

        std::string startText;
        std::string endText;

        if (!requireOption(options, "--input", parsed.inputPath, parsed.errorMessage)) return parsed;
        if (!requireOption(options, "--output", parsed.outputPath, parsed.errorMessage)) return parsed;
        if (!requireOption(options, "--start", startText, parsed.errorMessage)) return parsed;
        if (!requireOption(options, "--end", endText, parsed.errorMessage)) return parsed;

        if (!parseDouble(startText, parsed.startSeconds))
        {
            parsed.errorMessage = "--start must be a number.";
            return parsed;
        }

        if (!parseDouble(endText, parsed.endSeconds))
        {
            parsed.errorMessage = "--end must be a number.";
            return parsed;
        }

        parsed.isValid = true;
        return parsed;
    }

    if (commandName == "add-song")
    {
        parsed.type = CommandType::AddSong;

        if (!rejectUnknownOptions(options, {"--video", "--song", "--output", "--music-volume"}, parsed.errorMessage))
        {
            return parsed;
        }

        if (!requireOption(options, "--video", parsed.videoPath, parsed.errorMessage)) return parsed;
        if (!requireOption(options, "--song", parsed.songPath, parsed.errorMessage)) return parsed;
        if (!requireOption(options, "--output", parsed.outputPath, parsed.errorMessage)) return parsed;

        auto volumeOption = options.find("--music-volume");

        if (volumeOption != options.end())
        {
            if (!parseDouble(volumeOption->second, parsed.musicVolume))
            {
                parsed.errorMessage = "--music-volume must be a number from 0.0 to 1.0.";
                return parsed;
            }
        }

        if (parsed.musicVolume < 0.0 || parsed.musicVolume > 1.0)
        {
            parsed.errorMessage = "--music-volume must be from 0.0 to 1.0.";
            return parsed;
        }

        parsed.isValid = true;
        return parsed;
    }

    parsed.errorMessage = "Unknown command: " + commandName + ".";
    return parsed;
}

std::string getUsageText()
{
    std::ostringstream usage;

    usage << "Usage:\n";
    usage << "  AIVideoEditor trim --input <video> --output <video> --start <seconds> --end <seconds>\n";
    usage << "  AIVideoEditor add-song --video <video> --song <audio> --output <video> [--music-volume <0.0-1.0>]\n";
    usage << "  AIVideoEditor --help\n";

    return usage.str();
}
