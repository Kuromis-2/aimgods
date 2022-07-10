#include "DebugTools.h"
#include "framework.h"
#include "GameFunctions.h"

namespace Hooks {

    // Typedefing the function types
    typedef void(*tProcessEvent) (UFT::UObject*, UFT::UFunction*, void*);
    typedef void(*tRequestExit) (bool);

    // Function pointers for exiting the game and processing events that we get from the games memory in dll main
    tRequestExit rRequestExit = nullptr;
    tProcessEvent rProcessEvent = nullptr;
	
    void hRequestExit(bool Force) {
        return;
    }

    void DebugParameter(void* Parameter, int amountofbytes) {
        //print the amount of bytes located at the parameter
        for (int i = 0; i < amountofbytes; i++) {
            printf("%02X ", ((char*)Parameter)[i]);
        }
    }

    auto logFilter = {"Water", "CameraShake"};
    void hProcessEvent(UFT::UObject* Object, UFT::UFunction* Function, void* Params)
    {
        if (DebugTools::bLogEvents || GetAsyncKeyState(VK_CAPITAL) & (1 << 16))
        {
            auto objectName = DebugTools::bLogFullObjectNames ? Object->GetFullName() : Object->GetName();
            auto functionName = DebugTools::bLogFullFunctionNames ? Function->GetFullName() : Function->GetName();
            auto logString = objectName + "->" + functionName + "();";

            // If logString contains any of the logFilter strings then don't log it
            bool bShouldLog = true;
            for (auto& filter : logFilter)
            {
                if (logString.find(filter) != std::string::npos)
                {
                    bShouldLog = false;
                    break;
                }
            }

            if(bShouldLog || !DebugTools::bLogFilter)
            {
                Funcs::LogEvent(logString);
            }
        }
        return rProcessEvent(Object, Function, Params);
    }

    void HookFunctions() {
        // Getting the function pointers to req exit and process event by scanning the games memory
        #if VERSION == SHIPPING 
        rRequestExit = (tRequestExit)Funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x48\x83\xEC\x28\x84\xC9\x74\x07"), "xxxxxxxx");
        #elif VERSION == NO_SHIPPING
        rRequestExit = (tRequestExit)Funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x48\x83\xEC\x38\x80\x3D\x00\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x0F\xB6\xD9"), "xxxxxx?????xxxx?xxx");
        #endif
        COMMENT_IF_NO_SHIPPING rProcessEvent = (tProcessEvent)Funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\xF0\x00\x00\x00\x00"), "xxxxxxxxxxxxxxxx????");
        
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(LPVOID&)rRequestExit, (PVOID)hRequestExit);
        COMMENT_IF_NO_SHIPPING DetourAttach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent);
        DetourTransactionCommit();
        
        
        printf("%p %s\n", Hooks::rRequestExit, "FGenericPlatformMisc::RequestExit");
        printf("%p %s\n", Hooks::rProcessEvent, "UObject::ProcessEvent");
        Funcs::LogEvent("urmom");
    }

    void UnhookFunctions() {
        // Getting the function pointers to req exit and process event by scanning the games memory 
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(LPVOID&)rRequestExit, (PVOID)hRequestExit);
        COMMENT_IF_NO_SHIPPING DetourDetach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent);
        DetourTransactionCommit();
    }
}
