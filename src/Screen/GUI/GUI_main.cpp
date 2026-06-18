#include "GUI_main.hpp"


void draw_GUI(sf::Window& window, mat4& projMatrix)
{
    if (ImGui::BeginMainMenuBar())
    {
        gui_menu::file(window);
        gui_menu::view_mode();
        gui_menu::back();
        gui_menu::camera(projMatrix);
        gui_menu::edit();
        gui_menu::light();
        

        ImGui::EndMainMenuBar();
    }
}