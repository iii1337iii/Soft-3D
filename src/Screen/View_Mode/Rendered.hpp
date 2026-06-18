#pragma once

#include "../Draw_Triangles.hpp"
#include "../Data/Render_Data.hpp"


namespace view_mode
{
    void rendered(const sf::Image& texture, const vec4& worldNormal,
                  const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2,
                  const Fragment& frag);
}