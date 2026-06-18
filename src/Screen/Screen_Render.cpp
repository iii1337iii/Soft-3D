#include "Screen_Render.hpp"



void screen_render(Mesh& object, 
				   const std::vector<vec4>& projectedPoints, 
				   const std::vector<vec4>& worldPoints,
				   std::vector<RenderTriangle>& out_triangles)
{
	for (size_t i{ 0 }; i < object.triangles.size(); i += 1)
	{
		size_t idx0 = object.triangles[i].v1;
		size_t idx1 = object.triangles[i].v2;
		size_t idx2 = object.triangles[i].v3;

		Vertex vertex0, vertex1, vertex2;

		// --- Near Plane Clipping ---
		if (projectedPoints[idx0].w <= 0.0001f ||
			projectedPoints[idx1].w <= 0.0001f ||
			projectedPoints[idx2].w <= 0.0001f)
		{
			continue;
		}

		// --- Backface Culling ---
		vertex0.world = worldPoints[idx0];
		vertex1.world = worldPoints[idx1];
		vertex2.world = worldPoints[idx2];

		vec4 edge1 = 
		{ 
			vertex1.world.x - vertex0.world.x, 
			vertex1.world.y - vertex0.world.y, 
			vertex1.world.z - vertex0.world.z, 
		    0.0f 
		};
		vec4 edge2 = 
		{ 
			vertex2.world.x - vertex0.world.x, 
			vertex2.world.y - vertex0.world.y, 
			vertex2.world.z - vertex0.world.z, 
			0.0f 
		};

		vec4 normal = edge1.cross(edge2).normalize();
		vec4 view = vertex0.world;

		if (normal.dot(view) >= 0.0f && current_render_mode != render_mode::wireframe) { continue; }


		vertex0.projected = projectedPoints[idx0];
		vertex1.projected = projectedPoints[idx1];
		vertex2.projected = projectedPoints[idx2];

		vertex0.texture = object.vertex_textures[object.triangles[i].vt1];
		vertex1.texture = object.vertex_textures[object.triangles[i].vt2];
		vertex2.texture = object.vertex_textures[object.triangles[i].vt3];

		out_triangles.push_back({ vertex0, vertex1, vertex2, normal, &object.texture });
	}
}