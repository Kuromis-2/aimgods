#pragma once

namespace funcs
{
    void LogEvent(std::string Name, bool PrintToConsole, bool SaveToLog);
    uintptr_t FindPattern(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask);
    uintptr_t FindPattern(HMODULE module, const unsigned char* pattern, const char* mask);
}