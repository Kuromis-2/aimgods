#include "DebugMenu.h"

#include "DebugTools.h"
#include "imgui/imgui.h"

namespace DebugMenu
{
    void DrawDebugMenu()
    {
        ImGui::Text("Hello, world");

        ImGui::Separator();
        ImGui::Text("Logging Settings");
        ImGui::Checkbox("Log Events", &DebugTools::bLogEvents);
        ImGui::Checkbox("Use Log Filter", &DebugTools::bLogFilter);
        ImGui::Checkbox("Log Full Object Names", &DebugTools::bLogFullObjectNames);
        ImGui::Checkbox("Log Full Function Names", &DebugTools::bLogFullFunctionNames);
        
        for (auto& it : DebugTools::GetCommands())
        {
            if (ImGui::Button(it.first.c_str()))
            {
                DebugTools::CommandHandler(it.first);
            }
        }
    }
};