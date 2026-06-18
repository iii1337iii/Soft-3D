#include "Lighting.hpp"

void gui_menu::light()
{
    if (ImGui::BeginMenu("Lighting"))
    {
        ImGui::Text("Light Sources:");
        ImGui::BeginChild("LightList", ImVec2(0, 100), true);
        for (size_t i = 0; i < light_sources.size(); ++i)
        {
            if (light_sources[i].is_deleted) { continue; }

            ImGui::PushID(static_cast<int>(i));
            char label[32];
            snprintf(label, sizeof(label), "Source [%zu]", i);

            if (ImGui::Selectable(label, active_light_index == static_cast<int>(i)))
            {
                active_light_index = static_cast<int>(i);
            }
            ImGui::PopID();
        }
        if (ImGui::Button("Add"))
        {
            int deleted_source_index = -1;
            for (int i{ 0 }; i < static_cast<int>(light_sources.size()); ++i)
            {
                if (light_sources[i].is_deleted) { deleted_source_index = i; break; }
            }

            if (deleted_source_index != -1)
            {
                light_source& source = light_sources[deleted_source_index];
                source.reset_transforms();
                source.is_deleted = false;
                active_light_index = deleted_source_index;
            }
            else
            {
                light_source source;
                source.reset_transforms();
                light_sources.push_back(source);
                active_light_index = static_cast<int>(light_sources.size()) - 1;
            }
        }
        ImGui::EndChild();
        ImGui::Separator();


        if (active_light_index >= 0 && active_light_index < light_sources.size())
        {
            light_source& active_light = light_sources[active_light_index];

            if (ImGui::Button("Delete Source"))
            {
                active_light.delete_source();

                active_light_index = -1;
            }
            ImGui::SameLine();
            ImGui::Checkbox("Show", &active_light.visible);

            ImGui::Text("Position");
            ImGui::DragFloat("X", &active_light.position.x, 0.1f, -100.0f, 100.0f);
            ImGui::DragFloat("Y", &active_light.position.y, 0.1f, -100.0f, 100.0f);
            ImGui::DragFloat("Z", &active_light.position.z, 0.1f, -100.0f, 100.0f);

            ImGui::Text("Radius");
            ImGui::DragFloat("R", &active_light.radius, 0.1f, 0.0f, 500.0f);

            ImGui::Text("Color");
            float light_color[3] =
            {
                active_light.color.r / 255.0f,
                active_light.color.g / 255.0f,
                active_light.color.b / 255.0f
            };

            if (ImGui::ColorEdit3("Color", light_color))
            {
                active_light.color.r = static_cast<uint8_t>(light_color[0] * 255);
                active_light.color.g = static_cast<uint8_t>(light_color[1] * 255);
                active_light.color.b = static_cast<uint8_t>(light_color[2] * 255);
            }

            if (ImGui::Button("Reset Transforms")) { active_light.reset_transforms(); }
        }
        else
        {
            ImGui::Text("No sources selected");
        }

        ImGui::EndMenu();
    }
}