#pragma once
class AG
{
public:
    static UFT::AAGGameMode* GetAAGGameMode();
    static UFT::UGameplayTaskOwnerInterface* GetTaskOwner();
    static UFT::UGameplayTask* GetGamePlayTask();
    static UFT::UGameplayTask_SpawnActor* GetSpawn();
    static UFT::ACharacter* GetACharacter();
    static UFT::UWebSocketManager* GetWebSocketManager();
    static UFT::FLevelCollection* GetLevelCollection();
    static UFT::UAvoidanceManager* GetAvoidanceManager();
    static UFT::UAGCustomGameSubsystem* GetUAGCustomGameSubsystem();
    static UFT::UGameLiftClientUtils* GetGameLiftClientUtils();
    static UFT::ABP_AGCharacter_C* Target;
    static UFT::APlayerController* GetPC();
    static UFT::AAGPlayerController* GetAGPC();
    static UFT::UWB_CheatManager_C* GetUWBCheatManager();
    static UFT::ABP_AGPlayerController_C* GetBPAAGPC();
    static UFT::UWorld* GetWorld();
    static UFT::UGameInstance* GetGameInstance();
    static UFT::UAGGameInstance* GetUAGGameInstance();
    static UFT::UBP_AGGameInstance_C* GetUBP_UAGGameInstance();
    static UFT::UObject* GetUObject();
    static UFT::AActor* GetAActor();
    static UFT::AActor** GetAActor2();
    static UFT::AInfo* GetAInfo();
    static UFT::ULevel* GetUlevel();
    static UFT::AGameStateBase* GetAGameStateBase();
    static UFT::AGameState* GetAGameState();
    static UFT::AGameModeBase* GetAGameModeBase();
    static UFT::AGameMode* GetAGameMode();
    static UFT::UAGGameliftSubsystem* GetUAGGameliftSubsystem();
    static UFT::UCheatManager* GetCheatManager();
    static UFT::UClass* GetCheatClass();
    static UFT::APawn* GetAPawn();
    static UFT::AAGCharacterBase* GetAAGCharacterBase();
    static UFT::AAGCharacter* GetAAGCharacter();
};
