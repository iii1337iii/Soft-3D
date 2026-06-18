#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <filesystem>
#include <vector>
#include "../Math/vec4.hpp"


struct uv
{
    float u, v;
};


struct triangle
{
    size_t v1, v2, v3;       // vertex idx
    size_t vt1, vt2, vt3;    // vertex texture idx
    size_t vn1, vn2, vn3;    // vertex normal idx
};



struct Mesh
{
    bool is_deleted{ false };
    bool visible{ true };

    std::string name;

    float mov_x{}, mov_y{}, mov_z{};
    float rot_x{}, rot_y{}, rot_z{};
    float scl_x{}, scl_y{}, scl_z{};

    std::vector<vec4> vertices{};
    std::vector<uv> vertex_textures{};
    std::vector<vec4> vertex_normals{};
    std::vector<triangle> triangles{};


    sf::Image texture;
    void load_texture() { texture.loadFromFile(texture_path); }
    void delete_texture() { texture = sf::Image(); }

    std::string obj_path;
    std::string texture_path;

    void import_from_obj();

    void delete_object();


    void reset_transforms()
    {
        mov_x = mov_y = mov_z = 0.0f;
        rot_x = rot_y = rot_z = 0.0f;
        scl_x = scl_y = scl_z = 1.0f;
    }
};


inline std::vector<Mesh> objects;
inline int active_object_index = -1;