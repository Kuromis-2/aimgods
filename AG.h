#pragma once

class AG
{
public:
	static UFT::FLevelCollection* GetLevelCollection();
	static UFT::UAvoidanceManager* GetAvoidanceManager();
	static UFT::UAGCustomGameSubsystem* GetUAGCustomGameSubsystem();
	static UFT::UGameLiftClientUtils* GetGameLiftClientUtils();
	static UFT::ABP_AGCharacter_C* Target;
	static UFT::APlayerController* GetPC();
	static UFT::AAGPlayerController* GetAGPC();
	static UFT::ABP_AGPlayerController_C* GetBPAAGPC();
	static UFT::UWorld* GetWorld();
	static UFT::UGameInstance* GetGameInstance();
	static UFT::UAGGameInstance* GetUAGGameInstance();
	static UFT::UBP_AGGameInstance_C* GetUBP_UAGGameInstance();
	static UFT::UObject* GetUObject();
	static UFT::AActor* GetAActor();
	static UFT::AInfo* GetAInfo();
	static UFT::ULevel* GetUlevel();
	static UFT::AGameStateBase* GetAGameStateBase();
	static UFT::AGameState* GetAGameState();
	static UFT::AGameModeBase* GetAGameModeBase();
	static UFT::AGameMode* GetAGameMode();
	static UFT::UAGGameliftSubsystem* GetUAGGameliftSubsystem();
	static UFT::UWB_CheatManager_C* GetUWB_CheatManager();
	static UFT::UCheatManager* GetCheatManager();
	static UFT::UClass* GetCheatClass();
	static UFT::APawn* GetAPawn();
	static void LockOnClosestTarget();
	static void Begin();
	
};