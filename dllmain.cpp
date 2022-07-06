#include "framework.h"

typedef void(*tProcessEvent)(UFT::UObject*, UFT::UFunction*, void*);
typedef void(*tRequestExit)(bool);

tRequestExit rRequestExit = nullptr;
tProcessEvent rProcessEvent = nullptr;

void hProcessEvent(UFT::UObject* Object, UFT::UFunction* Function, void* Params)
{
    funcs::LogEvent("OBJECT: " + (std::string)Object->GetFullName(), true, true);
    funcs::LogEvent("FUNCTION: " + (std::string)Function->GetFullName(), true, true);
	return rProcessEvent(Object, Function, Params);
}

void hRequestExit(bool Force)
{

	return;
}
static bool example = false;
static int example_int = 10;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
        AllocConsole();
        FILE* file = nullptr;
        freopen_s(&file, "CONOUT$", "w", stdout);
        ShowWindow(GetConsoleWindow(), SW_SHOW);

        rRequestExit = (tRequestExit)funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x48\x83\xEC\x28\x84\xC9\x74\x07"), "xxxxxxxx");
        rProcessEvent = (tProcessEvent)funcs::FindPattern(GetModuleHandleW(nullptr), reinterpret_cast<const unsigned char*>("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\xF0\x00\x00\x00\x00"), "xxxxxxxxxxxxxxxx????");

        UFT::InitSdk();

        

        printf("%p %s\n", UFT::UObject::GObjects, "GUObjectArray");
        printf("%p %s\n", UFT::FName::GNames , "GNames");
		printf("%p %s\n", rRequestExit, "FGenericPlatformMisc::RequestExit");
        printf("%p %s\n", rProcessEvent, "UObject::ProcessEvent");
        
        
		if (DetourTransactionBegin() != NO_ERROR ||
			DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
			DetourAttach(&(LPVOID&)rRequestExit, (PVOID)hRequestExit) != NO_ERROR ||
            DetourAttach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent) != NO_ERROR ||
			DetourTransactionCommit() != NO_ERROR)
			return FALSE;
		return TRUE;
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
        if (DetourTransactionBegin() != NO_ERROR ||
            DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
            DetourDetach(&(LPVOID&)rRequestExit, (PVOID)hRequestExit) != NO_ERROR ||
            DetourDetach(&(LPVOID&)rProcessEvent, (PVOID)hProcessEvent) != NO_ERROR ||
            DetourTransactionCommit() != NO_ERROR)
            return FALSE;
        return TRUE;
	}
	return TRUE;
}