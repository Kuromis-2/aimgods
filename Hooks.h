#pragma once

namespace Hooks
{
	void hRequestExit(bool Force);
	void hProcessEvent(UFT::UObject* Object, UFT::UFunction* Function, void* Params);
	void HookFunctions(); 
	void UnhookFunctions();
};

