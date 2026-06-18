#pragma once

#include <thread>
#include "Main_Cycle.hpp"
#include "Draw_Triangles.hpp"
#include "View_Mode/Wireframe.hpp"
#include "Data/Render_Data.hpp"

void screen_render(Mesh& object, 
				   const std::vector<vec4> &projectedPoints, 
				   const std::vector<vec4> &worldPoints,
	               std::vector<RenderTriangle>& out_triangles);