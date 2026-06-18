#pragma once

#include "../../Math/vec4.hpp"
#include "../../Object/Mesh_Data.hpp"

struct Fragment
{
    int x, y;
    float alpha, beta, gamma;

    Fragment(float _alpha, float _beta, float _gamma, int _x, int _y) :
        alpha(_alpha), beta(_beta), gamma(_gamma), x(_x), y(_y) {}
};


struct Vertex
{
    vec4 projected;
    vec4 world;
    uv texture;
};


struct Tile
{
    int minX, minY, maxX, maxY;
};


struct RenderTriangle
{
    Vertex v0, v1, v2;
    vec4 worldNormal;
    const sf::Image* texture;
};