#include "Edit.hpp"

void gui_menu::edit()
{
    if (ImGui::BeginMenu("Edit"))
    {
        ImGui::Text("Scene Objects:");
        ImGui::BeginChild("ObjectList", ImVec2(0, 100), true);
        for (size_t i = 0; i < objects.size(); ++i)
        {
            if (objects[i].is_deleted) { continue; }


            ImGui::PushID(static_cast<int>(i));
            char label[32];
            snprintf(label, sizeof(label), objects[i].name.c_str(), i);

            if (ImGui::Selectable(label, active_object_index == static_cast<int>(i)))
            {
                active_object_index = static_cast<int>(i);
            }
            ImGui::PopID();
        }
        if (ImGui::Button("Add"))
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
        ImGui::EndChild();
        ImGui::Separator();


        if (active_object_index >= 0 && active_object_index < objects.size())
        {
            Mesh& active_obj = objects[active_object_index];

            if (ImGui::Button("Delete Object"))
            {
                active_obj.delete_object();
                active_obj.delete_texture();

                active_object_index = -1;
            }
            ImGui::SameLine();
            ImGui::Checkbox("Show", &active_obj.visible);

            ImGui::Text("Move");
            ImGui::DragFloat("Xm", &active_obj.mov_x, 0.1f, -100.0f, 100.0f);
            ImGui::DragFloat("Ym", &active_obj.mov_y, 0.1f, -100.0f, 100.0f);
            ImGui::DragFloat("Zm", &active_obj.mov_z, 0.1f, -100.0f, 100.0f);

            ImGui::Text("Rotate");
            ImGui::DragFloat("Xr", &active_obj.rot_x, 1.0f, -360.0f, 360.0f);
            ImGui::DragFloat("Yr", &active_obj.rot_y, 1.0f, -360.0f, 360.0f);
            ImGui::DragFloat("Zr", &active_obj.rot_z, 1.0f, -360.0f, 360.0f);

            ImGui::Text("Scale");
            ImGui::DragFloat("Xs", &active_obj.scl_x, 0.1f, 0.1f, 100.0f);
            ImGui::DragFloat("Ys", &active_obj.scl_y, 0.1f, 0.1f, 100.0f);
            ImGui::DragFloat("Zs", &active_obj.scl_z, 0.1f, 0.1f, 100.0f);

            if (ImGui::Button("Reset Transforms")) { active_obj.reset_transforms(); }


            ImGui::Separator();
            ImGui::Text("Texture");
            if (ImGui::Button("Import (.png/.jpg)"))
            {
                auto tex_dialog = pfd::open_file(
                    "Import",
                    "",
                    { "Image Files (.png, .jpg, .jpeg)", "*.png *.jpg *.jpeg" }
                );

                if (!tex_dialog.result().empty())
                {
                    objects[active_object_index].texture_path = tex_dialog.result()[0];
                    objects[active_object_index].load_texture();
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Clear")) { objects[active_object_index].delete_texture(); }
        }
        else
        {
            ImGui::Text("No object selected");
        }

        ImGui::EndMenu();
    }
}