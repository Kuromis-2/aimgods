#include "framework.h"

UFT::ABP_AGCharacter_C* AG::Target = nullptr;


UFT::APlayerController* AG::GetPC()
{
    UFT::UGameInstance* const GameInstance = GetGameInstance();
    if (GameInstance && GameInstance->LocalPlayers[0])
        return GameInstance->LocalPlayers[0]->PlayerController;
    return nullptr;
}

UFT::UWebSocketManager* AG::GetWebSocketManager()
{
    UFT::UAGGameInstance* const GameInstance = GetUAGGameInstance();
    if (GameInstance)
        return GameInstance->Socket;
    return nullptr;
}

UFT::AAGGameMode* AG::GetAAGGameMode()
{
    UFT::AGameMode* const GameMode = GetAGameMode();
    if (GameMode) return static_cast<UFT::AAGGameMode*>(GameMode);
    return nullptr;
}

UFT::UWB_CheatManager_C* AG::GetUWBCheatManager()
{
    UFT::ABP_AGPlayerController_C* const PC = GetBPAAGPC();
    if (PC) return PC->CheatManagerWidget;
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
    if (World)
        return World->LevelSequenceActors[0];
}

UFT::AActor** AG::GetAActor2()
{
    UFT::UWorld* const World = GetWorld();
    if (World)
    {
        auto ptr = World->LevelSequenceActors[0];
        auto ptr2 = &ptr;
        return ptr2;
    }
}

UFT::UCheatManager* AG::GetCheatManager()
{
    UFT::APlayerController* const PC = GetPC();
    if (PC) return PC->CheatManager;
    return nullptr;
}

UFT::AAGCharacter* AG::GetAAGCharacter()
{
    UFT::AAGCharacterBase* const ACB = GetAAGCharacterBase();
    if (ACB) return static_cast<UFT::AAGCharacter*>(ACB);
    return nullptr;
}

UFT::ACharacter* AG::GetACharacter()
{
    UFT::APawn* const Pawn = GetAPawn();
    if (Pawn)return static_cast<UFT::ACharacter*>(Pawn);
    return nullptr;
}

UFT::AAGCharacterBase* AG::GetAAGCharacterBase()
{
    UFT::ACharacter* const AC = GetACharacter();
    if (AC) return static_cast<UFT::AAGCharacterBase*>(AC);
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
    if (UAGGameInstance) return static_cast<UFT::UBP_AGGameInstance_C*>(UAGGameInstance);
    return nullptr;
}

UFT::UAGGameInstance* AG::GetUAGGameInstance()
{
    UFT::UGameInstance* const GameInstance = GetGameInstance();
    if (GameInstance) return static_cast<UFT::UAGGameInstance*>(GameInstance);
    return nullptr;
}

UFT::AAGPlayerController* AG::GetAGPC()
{
    UFT::APlayerController* const PC = GetPC();
    if (PC) return static_cast<UFT::AAGPlayerController*>(PC);
    return nullptr;
}

UFT::FLevelCollection* AG::GetLevelCollection()
{
    UFT::UWorld* const World = GetWorld();
    if (World) return &World->LevelCollections[0];
    return nullptr;
}

UFT::UAvoidanceManager* AG::GetAvoidanceManager()
{
    UFT::UWorld* const World = GetWorld();
    if (World) return World->AvoidanceManager;
    return nullptr;
}

UFT::AGameModeBase* AG::GetAGameModeBase()
{
    UFT::UWorld* const World = GetWorld();
    if (World) return World->AuthorityGameMode;
    return nullptr;
}

UFT::UGameplayTaskOwnerInterface* AG::GetTaskOwner()
{
    static auto ptr = UFT::UObject::FindClass("Class GameplayTasks.GameplayTaskOwnerInterface");
    std::cout << "Found Pointer to UGamePlayTaskOwnerInterface at";
    std::cout << ptr;
    return (UFT::UGameplayTaskOwnerInterface*)ptr;
}

UFT::UGameplayTask* AG::GetGamePlayTask()
{
    static auto ptr = UFT::UObject::FindClass("Class GameplayTasks.GameplayTask");
    std::cout << "Found Pointer to UGamePlayTask at";
    std::cout << ptr;
    return (UFT::UGameplayTask*)ptr;
}

UFT::UGameplayTask_SpawnActor* AG::GetSpawn()
{
    UFT::UGameplayTask* const Task = GetGamePlayTask();
    std::cout << "Try casting to SpawnActor" << std::endl;
    if (Task)
    {
        auto ptr = static_cast<UFT::UGameplayTask_SpawnActor*>(Task);
        std::cout << "Casted UGamePlayTask to SpawnActor";
        std::cout << ptr << std::endl;
    }
    return nullptr;
}

UFT::AGameMode* AG::GetAGameMode()
{
    UFT::AGameModeBase* const Base = GetAGameModeBase();
    if (Base) return static_cast<UFT::AGameMode*>(Base);
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
    if (StateBase) return static_cast<UFT::AGameState*>(StateBase);
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
    if (PC) return static_cast<UFT::ABP_AGPlayerController_C*>(PC);
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
    return *reinterpret_cast<UFT::UWorld**>(reinterpret_cast<unsigned char*>(GetModuleHandleW(nullptr)) + 0x38EAC38);
    //old: 0x38E9B78
}

UFT::UGameInstance* AG::GetGameInstance()
{
    UFT::UWorld* const World = GetWorld();
    if (World) return World->OwningGameInstance;
    return nullptr;
}
