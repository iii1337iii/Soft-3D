#include "Camera.hpp"

void gui_menu::camera(mat4& projMatrix)
{
    if (ImGui::BeginMenu("Camera"))
    {
        if (ImGui::SliderInt("FOV", &cam::FOV, 1, 179)) { projMatrix = cam::set(cam::FOV, sizeX, sizeY); }
        ImGui::EndMenu();
    }
}