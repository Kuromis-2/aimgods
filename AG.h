#pragma once

class AG
{
public:
	static UFT::ABP_AGCharacter_C* Target;
	static UFT::APlayerController* GetPC();
	static UFT::AAGPlayerController* GetAGPC();
	static UFT::ABP_AGPlayerController_C* GetBPAAGPC();
	static UFT::UWorld* GetWorld();
	static UFT::UGameInstance* GetGameInstance();
	static UFT::UAGGameInstance* GetUAGGameInstance();
	static UFT::UBP_AGGameInstance_C* GetUBP_UAGGameInstance();
	static UFT::UObject* GetUObject();
	static void LockOnClosestTarget();
	static void Begin();
	
};