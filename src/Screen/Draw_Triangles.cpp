#include "Draw_Triangles.hpp"

void setPixel(unsigned int x, unsigned int y, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) { return; }

    int index = (y * sizeX + x) * 4;
    frameBuffer[index] = r;
    frameBuffer[index + 1] = g;
    frameBuffer[index + 2] = b;
    frameBuffer[index + 3] = 255;
}


// --- Barycentric Rasterization ---
void drawTriangle(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2,
                  const sf::Image& texture, const vec4& worldNormal, const Tile& tile)
{
    // --- Bounding Box ---
    int minX = std::max(tile.minX, static_cast<int>(std::min({ vertex0.projected.x, vertex1.projected.x, vertex2.projected.x })));
    int maxX = std::min(tile.maxX, static_cast<int>(std::max({ vertex0.projected.x, vertex1.projected.x, vertex2.projected.x })));
    int minY = std::max(tile.minY, static_cast<int>(std::min({ vertex0.projected.y, vertex1.projected.y, vertex2.projected.y })));
    int maxY = std::min(tile.maxY, static_cast<int>(std::max({ vertex0.projected.y, vertex1.projected.y, vertex2.projected.y })));

    if (minX > maxX || minY > maxY) { return; }


    // Current triangle area
    float area = (vertex1.projected.x - vertex0.projected.x) * (vertex2.projected.y - vertex0.projected.y) - 
                 (vertex1.projected.y - vertex0.projected.y) * (vertex2.projected.x - vertex0.projected.x);
    float invArea = 1.0f / area;
    if (std::abs(area) < 0.00001f) { return; }


    // Current triangle world normal
    vec4 edge1 = { vertex1.world.x - vertex0.world.x, 
                   vertex1.world.y - vertex0.world.y, 
                   vertex1.world.z - vertex0.world.z, 
                   0.0f };
    vec4 edge2 = { vertex2.world.x - vertex0.world.x, 
                   vertex2.world.y - vertex0.world.y, 
                   vertex2.world.z - vertex0.world.z, 
                   0.0f };


    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float weight0 = (vertex1.projected.x - vertex0.projected.x) * (y - vertex0.projected.y) - 
                            (vertex1.projected.y - vertex0.projected.y) * (x - vertex0.projected.x);

            float weight1 = (vertex2.projected.x - vertex1.projected.x) * (y - vertex1.projected.y) - 
                            (vertex2.projected.y - vertex1.projected.y) * (x - vertex1.projected.x);

            float weight2 = (vertex0.projected.x - vertex2.projected.x) * (y - vertex2.projected.y) - 
                            (vertex0.projected.y - vertex2.projected.y) * (x - vertex2.projected.x);

            if ((weight0 >= 0 && weight1 >= 0 && weight2 >= 0) || 
                (weight0 <= 0 && weight1 <= 0 && weight2 <= 0))
            {
                // Normalize area
                // Same as (weight / area), just for faster calculation
                float alpha = weight1 * invArea;
                float beta = weight2 * invArea;
                float gamma = weight0 * invArea;

                // Z depth for pixel in tirangle
                float pixelZ = alpha * vertex0.projected.z + 
                               beta * vertex1.projected.z + 
                               gamma * vertex2.projected.z;

                int depthIndex = y * sizeX + x;

                // if current pixel.z less than other.z
                if (pixelZ < depthBuffer[depthIndex])
                {
                    depthBuffer[depthIndex] = pixelZ;

                    Fragment frag{ alpha, beta, gamma, x, y };

                    if (current_render_mode == render_mode::solid)
                    {
                        view_mode::solid(worldNormal, vertex0, vertex1, vertex2, frag);
                    }

                    else if (current_render_mode == render_mode::textured)
                    {
                        view_mode::texture(texture, vertex0, vertex1, vertex2, frag);
                    }

                    else if (current_render_mode == render_mode::rendered)
                    {
                        view_mode::rendered(texture, worldNormal, vertex0, vertex1, vertex2, frag);
                    }
                }
            }
        }
    }
}