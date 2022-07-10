#include <functional>
#include <map>
#include <string>
#include "framework.h"
#include "DebugTools.h"

#define GetOrReturn(VARIABLE_NAME, FUNCTION)    \
    auto VARIABLE_NAME = FUNCTION;              \
    if(VARIABLE_NAME == nullptr) {              \
        printf("VARIABLE_NAME is null\n");      \
        return;                                 \
    }                                                 

namespace DebugTools {

    // Settings
    bool bLogEvents = false;
    bool bLogFilter = true;
    bool bLogFullObjectNames = false;
    bool bLogFullFunctionNames = false;
    
    auto commands = GenerateCommands();
    
    std::map<std::string, std::function<void()>> GenerateCommands()
    {
        return {
                    {
                        "Colosseum", []()
                        {
                            if (AG::GetAGPC())
                            {
                                auto levelString = Funcs::ToFString("colosseum_p");
                                AG::GetAGPC()->SwitchLevel(levelString);
                            }
                        }
                    },
                    {
                        "ServerAddToReadyToSpawnList", []()
                        {
                            GetOrReturn(gameMode, AG::GetAAGGameMode())
                            GetOrReturn(localPlayer, AG::GetAGPC())
                            
                            localPlayer->bReadyToSpawn = true; localPlayer->ServerAddToReadyToSpawnList(AG::GetPC());
                            localPlayer->bIsPlaying = true; localPlayer->ServerSetIsPlaying(true);
                            localPlayer->ClientShowRespawnScreen(1);
                            
                            const UFT::FName EnteringMap = UFT::FName(TEXT("EnteringMap"));
                            const UFT::FName WaitingToStart = UFT::FName(TEXT("WaitingToStart"));
                            const UFT::FName InProgress = UFT::FName(TEXT("InProgress"));
                            const UFT::FName WaitingPostMatch = UFT::FName(TEXT("WaitingPostMatch"));
                            const UFT::FName LeavingMap = UFT::FName(TEXT("LeavingMap"));
                            const UFT::FName Aborted = UFT::FName(TEXT("Aborted"));
                            
                            auto ready = gameMode->ReadyToStartMatch();
                            printf("ReadyToStartMatch: %d\n", ready);
                            gameMode->MatchState = EnteringMap;
                            gameMode->StartPlay();
                            
                        }
                    },
                    {
                        "Print Seperator Line", []()
                        {
                            std::cout << "-----------------------------------------------------------" << std::endl;
                        }
                    }
        };
    }

    void CommandHandler(std::string command)
    {
        // Is the command in the map?
        if (commands.find(command) != commands.end())
        {
            // Run the command
            commands[command]();
        }
    }
    
    std::map<std::string, std::function<void()>> GetCommands()
    {
        return commands;
    }
}
