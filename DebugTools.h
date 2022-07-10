#pragma once

#include <functional>
#include <map>
#include <string>

namespace DebugTools
{
    std::map<std::string, std::function<void()>> GenerateCommands();
    void CommandHandler(std::string command);
    std::map<std::string, std::function<void()>> GetCommands();

    // Settings
    extern bool bLogEvents;
    extern bool bLogFilter;
    extern bool bLogFullObjectNames;
    extern bool bLogFullFunctionNames;
}
