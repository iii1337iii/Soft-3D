#include "Background.hpp"

void gui_menu::back()
{
    if (ImGui::BeginMenu("Background"))
    {
        float bgColor[3] =
        {
            background.r / 255.0f,
            background.g / 255.0f,
            background.b / 255.0f
        };

        if (ImGui::ColorEdit3("Color", bgColor))
        {
            background.r = static_cast<uint8_t>(bgColor[0] * 255);
            background.g = static_cast<uint8_t>(bgColor[1] * 255);
            background.b = static_cast<uint8_t>(bgColor[2] * 255);
        }

        ImGui::EndMenu();
    }
}