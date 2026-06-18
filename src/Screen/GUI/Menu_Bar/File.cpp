#include "File.hpp"

void gui_menu::file(sf::Window& window)
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::BeginMenu("Import"))
        {
            if (ImGui::MenuItem(".obj"))
            {
                auto obj_dialog = pfd::open_file(
                    "Import",
                    "",
                    { "Wavefront OBJ Files (.obj)", "*.obj" }
                );

                if (!obj_dialog.result().empty())
                {
                    int deleted_object_index = -1;
                    for (int i{ 0 }; i < static_cast<int>(objects.size()); ++i)
                    {
                        if (objects[i].is_deleted) { deleted_object_index = i; break; }
                    }
                    if (deleted_object_index != -1)
                    {
                        Mesh& object = objects[deleted_object_index];
                        object.obj_path = obj_dialog.result()[0];
                        object.import_from_obj();

                        active_object_index = deleted_object_index;
                    }
                    else
                    {
                        Mesh new_mesh;
                        new_mesh.obj_path = obj_dialog.result()[0];
                        new_mesh.import_from_obj();

                        objects.push_back(new_mesh);
                        active_object_index = static_cast<int>(objects.size()) - 1;
                    }
                }
            }

            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::Text("Tile Size");
            ImGui::DragInt("pixels", &TILE_SIZE, 128, 128, 1024);

            if (ImGui::Button("128")) { TILE_SIZE = 128; }
            ImGui::SameLine();
            if (ImGui::Button("512")) { TILE_SIZE = 512; }
            ImGui::SameLine();
            if (ImGui::Button("1024")) { TILE_SIZE = 1024; }

            ImGui::SameLine();
            if (ImGui::Button("-"))
            {
                TILE_SIZE -= 128;
                if (TILE_SIZE < 128) { TILE_SIZE = 128; }
            }
            ImGui::SameLine();
            if (ImGui::Button("+"))
            {
                TILE_SIZE += 128;
                if (TILE_SIZE > 1024) { TILE_SIZE = 1024; }
            }

            ImGui::Text("Decreasing the 'Tile Size'");
            ImGui::Text("value increases CPU load");

            ImGui::EndMenu();
        }


        if (ImGui::MenuItem("Save as"))
        {
            auto save_dialog = pfd::save_file(
                "Save Rendered Image",
                "render.png",
                { "PNG Image (.png)", "*.png" },
                pfd::opt::none
            );

            std::string result_path = save_dialog.result();

            if (!save_dialog.result().empty())
            {
                if (result_path.length() < 4 ||
                    result_path.compare(result_path.length() - 4, 4, ".png") != 0)
                {
                    result_path += ".png";
                }

                save_screenshot_path = result_path;
            }
        }


        ImGui::Separator();
        ImGui::Text("1.0.0");
        ImGui::Separator();

        if (ImGui::MenuItem("Clear Scene"))
        {
            for (auto& obj : objects)
            {
                obj.delete_object();
                obj.delete_texture();
            }
            active_object_index = -1;

            for (auto& source : light_sources)
            {
                source.delete_source();
            }
            active_light_index = -1;
        }

        if (ImGui::MenuItem("Quit")) { window.close(); }

        ImGui::EndMenu();
    }
}