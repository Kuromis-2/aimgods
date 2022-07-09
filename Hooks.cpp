#include "framework.h"
#include "GameFunctions.h"
#include "dllmain.h"
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
    
    void hProcessEvent(UFT::UObject* Object, UFT::UFunction* Function, void* Params)
    {
        if (GetAsyncKeyState(VK_CAPITAL) & (1 << 16)|| logfunctions)
        {
            Funcs::LogEvent(Function->GetFullName().c_str());
            
        } 
        if (mustspectatebypass && CompareGameFunction(Function,"Function Engine.GameModeBase.MustSpectate"))
        {
            std::cout << "BLOCKED" << std::endl;
            return;
        }
        return rProcessEvent(Object, Function, Params);
    }





    void HookFunctions() {
        // Getting the function pointers to req exit and process event by scanning the games memory 
        rRequestExit = (tRequestExit)Funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x48\x83\xEC\x28\x84\xC9\x74\x07"), "xxxxxxxx");
        rProcessEvent = (tProcessEvent)Funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\xF0\x00\x00\x00\x00"), "xxxxxxxxxxxxxxxx????");
        
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(LPVOID&)rRequestExit, (PVOID)hRequestExit);
        DetourAttach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent);
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
        DetourDetach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent);
        DetourTransactionCommit();
    }
}
