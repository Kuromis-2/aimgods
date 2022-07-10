#pragma once

namespace Funcs
{
    void LogEvent(std::string Name, bool PrintToConsole = true, bool SaveToLog = true);
    uintptr_t FindPattern(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask);
    uintptr_t FindPattern(HMODULE module, const unsigned char* pattern, const char* mask);
    std::string utf8_encode(const std::wstring& wstr);
    std::wstring utf8_decode(const std::string& str);
    UFT::FString ToFString(std::string str);
}
