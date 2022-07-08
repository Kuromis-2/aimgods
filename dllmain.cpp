#include "framework.h"
#include "includes.h"
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

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("ImGui Window");
    

    
    
    ImGui::Text("Hello, world");

    //create imgui textbox for new command
	std::string command = "Placeholer";
    ImGui::Text("Enter Command");
	static char str0[128] = "Hello, world!";
	ImGui::InputText("HELLO",str0, IM_ARRAYSIZE(str0));
	ImGui::SameLine();
    ImGui::Checkbox("Disable Mustspectate", &mustspectatebypass);
	if (ImGui::Button("Send"))
	{
		std::string str(str0);
		CommandHandler(str);
	}
			
	

    
    

    ImGui::End();

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
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
    
}
DWORD WINAPI Logging(LPVOID lpReserved)
{
    /*AllocConsole();
    FILE* file = nullptr;
    freopen_s(&file,"CONIN$", "r", stdin);
    freopen_s(&file, "CONOUT$", "w", stdout);

    ShowWindow(GetConsoleWindow(), SW_SHOW);*/
    Hooks::HookFunctions();
    return TRUE;
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