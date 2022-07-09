#include "framework.h"
#include "includes.h"
#include <map>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void(*tProcessEvent)(UFT::UObject*, UFT::UFunction*, void*);
typedef void(*tRequestExit)(bool);
tRequestExit rRequestExit = nullptr;
tProcessEvent rProcessEvent = nullptr;
void CommandHandler(std::string command);
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
bool mustspectatebypass = false;
bool logfunctions = false;
void Summon(std::wstring);
DWORD WINAPI Logging(LPVOID lpReserved);
void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}




bool init = !true;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!init)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;
        }

        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }
    static char str0[128] = "input text";
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("DEBUG WINDOW");
    ImGui::Text("Enter Command:");
    ImGui::SameLine();
    if (ImGui::InputText("", str0, IM_ARRAYSIZE(str0), 32))
    {
        std::string str(str0);
        CommandHandler(str);
    }
    if (ImGui::Button("Execute"))
    {
        std::string str(str0);
        CommandHandler(str);
    }
    ImGui::Checkbox("Block Mustspectate", &mustspectatebypass);

    ImGui::Checkbox("Log Functions", &logfunctions);
    //create imgui textbox for new command
    ImGui::End();
    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}
void Summon(std::wstring)
{
    if(AG::GetCheatManager())
    {
	    
    }
}
DWORD WINAPI MainThread(LPVOID lpReserved)
{
    
    bool init_hook = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            kiero::bind(8, (void**)&oPresent, hkPresent);
            init_hook = true;
            std::cout << "GUI Initialized" << std::endl;
        }
    } while (!init_hook);
    return TRUE;
}

void CommandHandler(std::string command)
{
    if(command == "OpenShop")
    {
        if(AG::GetBPAAGPC())
            AG::GetBPAAGPC()->Open_Shop_UI();
    }
    if (command == "CloseShop")
    {
        if (AG::GetBPAAGPC())
            AG::GetBPAAGPC()->Close_Shop_UI();
    }
    else if(command=="SpawnDefaultController")
    {
	    if(AG::GetAPawn())
	    {
		    AG::GetAPawn()->SpawnDefaultController();
	    }
    }
    else if (command == "ReceivePossessed")
    {
        if (AG::GetAPawn())
        {
            AG::GetAPawn()->ReceivePossessed(AG::GetPC());
        }
    }
    else if(command=="StartCustom")
    {
        
        if(AG::GetUAGGameliftSubsystem())
        {
            if(AG::GetUAGGameliftSubsystem())
            {
                AG::GetUAGGameliftSubsystem()->StartCustomGame();
            }
        }
        
    }
    else if(command=="ShowRespawnScreen")
    {
	    if(AG::GetAGPC)
	    {
            AG::GetAGPC()->ShowRespawnScreen(10000);
	    }
    }
    else if(command=="StartMatch2")
    {
        if(AG::GetAGameModeBase())
        {
            AG::GetAGameModeBase()->FindPlayerStart(AG::GetPC(),AG::GetUAGGameInstance()->Username);
            std::cout << "Found PlayerStart" << std::endl;
            AG::GetAGameModeBase()->ChoosePlayerStart(AG::GetPC());
            std::cout << "Chose PlayerStart" << std::endl;
            AG::GetAGameModeBase()->GetDefaultPawnClassForController(AG::GetPC());
            std::cout << "Got DefaultPawnClassForController" << std::endl;
            std::cout << "InitializeHUDForPlayer" << std::endl;
            //AG::GetAGameModeBase()->SpawnDefaultPawnFor(AG::GetPC(), AG::GetAActor());
            std::cout << "SpawnDefaultPawnFor" << std::endl;
            AG::GetAGameModeBase()->HandleStartingNewPlayer(AG::GetPC());
            std::cout << "HandleStartingNewPlayer" << std::endl;
            AG::GetAGameModeBase()->StartPlay();
            std::cout << "StartPlay" << std::endl;
            
        }
    }
    else if(command=="ActivateCheats")
    {
	    if(AG::GetPC())
	    {
            AG::GetPC()->EnableCheats();
	    }
    }
    else if(command=="OpenSocket")
    {
	    if(AG::GetWebSocketManager())
	    {
		    AG::GetWebSocketManager()->OpenConnection();
	    }
    }
    else if(command=="CheatMenu")
    {
	    if(AG::GetUWBCheatManager())
	    {
            AG::GetUWBCheatManager()->Construct();
	    }
    }
    else if(command=="UpdateInMatchStatus")
    {
	    if(AG::GetWebSocketManager())
	    {
		    AG::GetWebSocketManager()->UpdateInMatchStatus(true);
	    }
    }
    else if(command=="LoadGame")
    {
	    if(AG::GetBPAAGPC())
	    {
            AG::GetBPAAGPC()->AddCheatManagerWidget();
	    }
    }
    else if(command=="KillingSpree")
    {
	    if(AG::GetBPAAGPC())
	    {
		    AG::GetBPAAGPC()->ShowKillingSpreeMessage();
	    }
    }
    else if(command=="SaveGame")
    {
	    if(AG::GetUAGGameInstance())
	    {
		    AG::GetUAGGameInstance()->SaveGame();
	    }
    }
    else if(command=="RestartPlayer")
    {
        if(AG::GetAGameModeBase())
		{
			AG::GetAGameModeBase()->RestartPlayer(AG::GetPC());
		}
    }
    else if (command == "RestartGame")
    {
        if (AG::GetAGameMode())
        {
	        AG::GetAGameMode()->RestartGame();
        }
    }
    else if (command == "Spawn")
    {
		
    }
    else if(command=="minions")
    {
	    if(AG::GetAAGGameMode())
	    {
            AG::GetAAGGameMode()->SpawnMinions();
	    }
    }
}
bool initLog = true;
DWORD WINAPI Logging(LPVOID lpReserved)
{
    if(initLog)
    {
        AllocConsole();
        FILE* file = nullptr;
        freopen_s(&file, "CONIN$", "r", stdin);
        freopen_s(&file, "CONOUT$", "w", stdout);

        ShowWindow(GetConsoleWindow(), SW_SHOW);
        Hooks::HookFunctions();
        initLog = false;
        return TRUE;
    }
    else
    {
        AllocConsole();
        FILE* file = nullptr;
        freopen_s(&file, "CONIN$", "r", stdin);
        freopen_s(&file, "CONOUT$", "w", stdout);

        ShowWindow(GetConsoleWindow(), SW_SHOW);
    }
    
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
        UFT::InitSdk();
        
        CreateThread(0, 0, Logging, hModule, 0, 0);
        CreateThread(0, 0, MainThread, hModule, 0, nullptr);
        
		return TRUE;
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
        Hooks::UnhookFunctions();
        return TRUE;
	}
	return TRUE;
}