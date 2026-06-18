#include "Mesh_Data.hpp"


void Mesh::delete_object()
{
    vertices.clear();
    vertex_normals.clear();
    vertex_textures.clear();
    triangles.clear();

    mov_x = mov_y = 0.0f;
    mov_z = 4.0f;
    rot_x = rot_y = rot_z = 0.0f;
    scl_x = scl_y = scl_z = 1.0f;

    name = "null";
    is_deleted = true;
}


void Mesh::import_from_obj()
{
    delete_object();

	std::ifstream data(obj_path);

    std::string line;

    while (std::getline(data, line)) 
    {
        if (line.empty()) { continue; }

        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;


        if (prefix == "o")
        {
            std::string object_name;
            if (ss >> object_name)
            {
                name = object_name;
            }
        }


        else if (prefix == "v") 
        {
            vec4 v;
            if (ss >> v.x >> v.y >> v.z) 
            {
                v.w = 1.0f;
                vertices.push_back(v);
            }
        }


        else if (prefix == "vn")
        {
            vec4 vn;
            if (ss >> vn.x >> vn.y >> vn.z)
            {
                vn.w = 1.0f;
                vertex_normals.push_back(vn);
            }
        }


        else if (prefix == "vt")
        {
            uv UV;
            if (ss >> UV.u >> UV.v)
            {
                vertex_textures.push_back(UV);
            }
        }


        else if (prefix == "f")
        {
            std::string token;

            struct VertexIndices 
            { 
                size_t v, vt, vn; 
            };
            std::vector<VertexIndices> face_indices;

            while (ss >> token)
            {
                size_t v, t, n;
                
                if (sscanf_s(token.c_str(), "%zu/%zu/%zu", &v, &t, &n) == 3) 
                {
                    face_indices.push_back({ v - 1, t - 1, n - 1 });
                }
                else if (sscanf_s(token.c_str(), "%zu//%zu", &v, &n) == 2) 
                {
                    face_indices.push_back({ v - 1, 0, n - 1 });
                }
            }

            if (face_indices.size() >= 3)
            {
                triangle tri;
                for (size_t i = 1; i < face_indices.size() - 1; ++i)
                {
                    tri.v1 = face_indices[0].v;
                    tri.v2 = face_indices[i].v;
                    tri.v3 = face_indices[i + 1].v;

                    tri.vt1 = face_indices[0].vt;
                    tri.vt2 = face_indices[i].vt;
                    tri.vt3 = face_indices[i + 1].vt;

                    tri.vn1 = face_indices[0].vn;
                    tri.vn2 = face_indices[i].vn;
                    tri.vn3 = face_indices[i + 1].vn;

                    triangles.push_back(tri);
                }
            }
        }
    }

    if (vertex_textures.empty()) 
    {
        vertex_textures.push_back({ 0.0f, 0.0f });

        for (auto& tri : triangles)
        {
            tri.vt1 = 0;
            tri.vt2 = 0;
            tri.vt3 = 0;
        }
    }

    is_deleted = false;
	data.close();
}