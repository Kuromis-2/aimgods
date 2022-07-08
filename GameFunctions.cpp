#include "framework.h"

bool CompareGameFunction(UFT::UFunction* Function, const char* FunctionName) {
	return strcmp(Function->GetFullName().c_str(), FunctionName) == 0;
}