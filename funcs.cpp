#include <fstream>

#include "framework.h"
namespace Funcs
{
    std::mutex m;
    std::vector<std::pair<std::string, std::chrono::high_resolution_clock::time_point>> Events{};
  
    void LogEvent(std::string Name, bool PrintToConsole, bool SaveToLog)
    {
        if (!SaveToLog && !PrintToConsole) return;

        m.lock();
        static FILE* fp;
        if (!fp) {
            std::wstring logpath = L"log_aimgods.txt";
            _wfopen_s(&fp, logpath.c_str(), L"a");
        }

        auto it = std::find_if(Events.begin(), Events.end(),
            [&Name](const std::pair<std::string, std::chrono::high_resolution_clock::time_point>& element) {
            return element.first.compare(Name.c_str()) == 0;
        });

        if (it == Events.end())
        {
            Events.push_back(std::make_pair(Name.c_str(), std::chrono::high_resolution_clock::now()));
            if (SaveToLog && fp) fprintf(fp, "%s\n", Name.c_str());
            if (PrintToConsole) printf("%s\n", Name.c_str());
        }

        auto _it = std::remove_if(Events.begin(), Events.end(),
            [](const std::pair<std::string, std::chrono::high_resolution_clock::time_point>& element) {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - element.second).count() > 1000;
        });

        Events.erase(_it, Events.end());
        m.unlock();
    }

    uintptr_t FindPattern(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask)
    {
        size_t pos = 0;
        auto maskLength = std::strlen(mask) - 1;
        auto startAdress = start;
        for (auto it = startAdress; it < startAdress + length; ++it)
        {
            if (*reinterpret_cast<unsigned char*>(it) == pattern[pos] || mask[pos] == '?')
            {
                if (mask[pos + 1] == '\0')
                {
                    return it - maskLength;
                }
                pos++;
            }
            else
            {
                pos = 0;
            }
        }
        return -1;
    }

    uintptr_t FindPattern(HMODULE module, const unsigned char* pattern, const char* mask)
    {
        MODULEINFO info = { };
        GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(MODULEINFO));
        return FindPattern(reinterpret_cast<uintptr_t>(module), info.SizeOfImage, pattern, mask);
    }

    std::string utf8_encode(const std::wstring& wstr)
    {
        //return std::string(wstr.begin(), wstr.end());
        if (wstr.empty()) return std::string();
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
        std::string strTo(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
        return strTo;
    }

    std::wstring utf8_decode(const std::string& str)
    {
        //return std::wstring(str.begin(), str.end());
        if (str.empty()) return std::wstring();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring wstrTo(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
        return wstrTo;
    }
}