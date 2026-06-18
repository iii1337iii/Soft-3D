#pragma once
#include "Main_Cycle.hpp"
#include "Data/Render_Data.hpp"
#include "../Object/Mesh_Data.hpp"
#include "../World/Lighting.hpp"
#include "View_Mode/Solid.hpp"
#include "View_Mode/Texture.hpp"
#include "View_Mode/Rendered.hpp"


void setPixel(unsigned int x, unsigned int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);

void drawTriangle(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2, 
				  const sf::Image& texture, const vec4& worldNormal, const Tile& tile);