#include "View_Mode.hpp"

void gui_menu::view_mode()
{
    if (ImGui::BeginMenu("View Mode"))
    {
        if (ImGui::MenuItem("Wireframe")) { current_render_mode = render_mode::wireframe; }
        if (ImGui::MenuItem("Solid")) { current_render_mode = render_mode::solid; }
        if (ImGui::MenuItem("Textured")) { current_render_mode = render_mode::textured; }
        if (ImGui::MenuItem("Rendered")) { current_render_mode = render_mode::rendered; }
        ImGui::EndMenu();
    }
}