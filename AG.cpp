#include "framework.h"

UFT::ABP_AGCharacter_C* AG::Target = nullptr;


UFT::APlayerController* AG::GetPC()
{
	UFT::UGameInstance* const GameInstance = GetGameInstance();
	if (GameInstance && GameInstance->LocalPlayers[0]) 
		return GameInstance->LocalPlayers[0]->PlayerController;
	return nullptr;
}
UFT::UGameLiftClientUtils* AG::GetGameLiftClientUtils()
{
	static auto ptr = UFT::UObject::FindClass("Class AimGods.GameLiftClientUtils");
	auto ptr2 = reinterpret_cast<UFT::UGameLiftClientUtils*>(reinterpret_cast<unsigned char*>(ptr));
	return ptr2;
}
UFT::AActor* AG::GetAActor()
{
	UFT::UWorld* const World = GetWorld();
	if(World)
		return World->LevelSequenceActors[0];
}

UFT::UCheatManager* AG::GetCheatManager()
{
	UFT::APlayerController* const PC = GetPC();
	if (PC) return PC->CheatManager;
	return nullptr;
}
UFT::APawn* AG::GetAPawn()
{
	UFT::APlayerController* const PC = GetPC();
	if (PC) return PC->AcknowledgedPawn;
	return nullptr;
}
UFT::UBP_AGGameInstance_C* AG::GetUBP_UAGGameInstance()
{
	UFT::UAGGameInstance* const UAGGameInstance = GetUAGGameInstance();
	if (UAGGameInstance) return (UFT::UBP_AGGameInstance_C*)UAGGameInstance;
	return nullptr;
}
UFT::UAGGameInstance* AG::GetUAGGameInstance() {
	UFT::UGameInstance* const GameInstance = GetGameInstance();
	if (GameInstance) return (UFT::UAGGameInstance*)GameInstance;
	return nullptr;
}
UFT::AAGPlayerController* AG::GetAGPC()
{
	UFT::APlayerController* const PC = GetPC();
	if (PC) return (UFT::AAGPlayerController*)PC;
	return nullptr;
}
UFT::AGameModeBase* AG::GetAGameModeBase()
{
	UFT::UWorld* const World = GetWorld();
	if (World) return World->AuthorityGameMode;
	return nullptr;
}
UFT::AGameMode* AG::GetAGameMode()
{
	UFT::AGameModeBase* const Base = GetAGameModeBase();
	if (Base) return (UFT::AGameMode*)Base;
	return nullptr;
}
UFT::AGameStateBase* AG::GetAGameStateBase()
{
	UFT::UWorld* const World = GetWorld();
	if (World) return World->GameState;
	return nullptr;
}
UFT::AGameState* AG::GetAGameState()
{
	UFT::AGameStateBase* const StateBase = GetAGameStateBase();
	if (StateBase) return (UFT::AGameState*)StateBase;
	return nullptr;
}

//UFT::AActor* AG::GetAActor()
//{
//	UFT::UWorld* const World = GetWorld();
//	if (World) return World->LevelSequenceActors[1];
//	return nullptr;
//}

UFT::ABP_AGPlayerController_C* AG::GetBPAAGPC()
{
	UFT::APlayerController* const PC = GetPC();
	if (PC) return (UFT::ABP_AGPlayerController_C*)PC;
	return nullptr;
}
UFT::UAGCustomGameSubsystem* AG::GetUAGCustomGameSubsystem()
{
	UFT::UAGGameInstance* const GameInstance = GetUAGGameInstance();
	if (GameInstance) return GameInstance->CustomGameSubsystem;
	return nullptr;
}
UFT::UAGGameliftSubsystem* AG::GetUAGGameliftSubsystem()
{
	UFT::UAGGameInstance* const GameInstance = GetUAGGameInstance();
	if (GameInstance) return GameInstance->GameliftSubsystem;
	return nullptr;
}
UFT::ULevel* AG::GetUlevel()
{
	UFT::UWorld* const World = GetWorld();
	if (World) return World->PersistentLevel;
	return nullptr;
}
UFT::UWorld* AG::GetWorld()
{
	return *reinterpret_cast<UFT::UWorld**>(reinterpret_cast<unsigned char*>(GetModuleHandleW(nullptr)) + 0x38EAC38);  //old: 0x38E9B78
}

UFT::UGameInstance* AG::GetGameInstance()
{
	UFT::UWorld* const World = GetWorld();
	if (World) return World->OwningGameInstance;
	return nullptr;
}

void AG::Begin()
{
	if (!GetBPAAGPC() || !GetBPAAGPC()->K2_GetPawn())
		return;
	
}