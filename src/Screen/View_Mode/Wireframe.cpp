#include "Wireframe.hpp"

namespace view_mode
{
    void wireframe(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2)
    {
        // --- Bounding Box ---
        int minX = std::max(0, static_cast<int>(std::min(
                            { vertex0.projected.x, vertex1.projected.x, vertex2.projected.x })));

        int maxX = std::min(static_cast<int>(sizeX - 1), static_cast<int>(std::max(
                            { vertex0.projected.x, vertex1.projected.x, vertex2.projected.x })));

        int minY = std::max(0, static_cast<int>(std::min(
                            { vertex0.projected.y, vertex1.projected.y, vertex2.projected.y })));

        int maxY = std::min(static_cast<int>(sizeY - 1), static_cast<int>(std::max(
                            { vertex0.projected.y, vertex1.projected.y, vertex2.projected.y })));

        if (minX > maxX || minY > maxY) { return; }


        // Current triangle area
        float area = (vertex1.projected.x - vertex0.projected.x) * (vertex2.projected.y - vertex0.projected.y) -
                     (vertex1.projected.y - vertex0.projected.y) * (vertex2.projected.x - vertex0.projected.x);
        if (std::abs(area) < 0.00001f) { return; }


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


                // Only if pixel inside the triangle
                if ((weight0 >= 0 && weight1 >= 0 && weight2 >= 0) ||
                    (weight0 <= 0 && weight1 <= 0 && weight2 <= 0))
                {
                    float alpha = weight1 / area;
                    float beta = weight2 / area;
                    float gamma = weight0 / area;

                    // Weight change per pixel step (dx and dy)
                    float dAlpha_dx = (vertex1.projected.y - vertex2.projected.y) / area;
                    float dBeta_dx = (vertex2.projected.y - vertex0.projected.y) / area;
                    float dGamma_dx = (vertex0.projected.y - vertex1.projected.y) / area;

                    float dAlpha_dy = (vertex2.projected.x - vertex1.projected.x) / area;
                    float dBeta_dy = (vertex0.projected.x - vertex2.projected.x) / area;
                    float dGamma_dy = (vertex1.projected.x - vertex0.projected.x) / area;

                    // Distance between pixel and each edge
                    float dist_alpha = std::abs(alpha) / std::sqrt(dAlpha_dx * dAlpha_dx + dAlpha_dy * dAlpha_dy);
                    float dist_beta = std::abs(beta) / std::sqrt(dBeta_dx * dBeta_dx + dBeta_dy * dBeta_dy);
                    float dist_gamma = std::abs(gamma) / std::sqrt(dGamma_dx * dGamma_dx + dGamma_dy * dGamma_dy);


                    if (dist_alpha < 1.0f || dist_beta < 1.0f || dist_gamma < 1.0f)
                    {
                        setPixel(x, y, 0, 0, 0); 
                    }
                }
            }
        }
    }
}