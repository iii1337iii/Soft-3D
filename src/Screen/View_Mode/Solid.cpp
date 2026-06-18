#include "Solid.hpp"

static vec4 solid_mode_world_light = { 0.0f, 1000000.0f, 0.0f, 1.0f };

namespace view_mode
{
    void solid(const vec4& worldNormal,
        const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2,
        const Fragment& frag)
    {
        // InvZ = 1/Z
        float invZ0 = 1.0f / vertex0.projected.z;
        float invZ1 = 1.0f / vertex1.projected.z;
        float invZ2 = 1.0f / vertex2.projected.z;

        float interpolatedInvZ = frag.alpha * invZ0 + frag.beta * invZ1 + frag.gamma * invZ2;


        sf::Color solid_color = { 100, 100, 100 };
        float totalLight = 70.0f;


        // World space pixel interpolation
        float pWorldX = (frag.alpha * (vertex0.world.x * invZ0) + frag.beta * (vertex1.world.x * invZ1) +
            frag.gamma * (vertex2.world.x * invZ2)) / interpolatedInvZ;

        float pWorldY = (frag.alpha * (vertex0.world.y * invZ0) + frag.beta * (vertex1.world.y * invZ1) +
            frag.gamma * (vertex2.world.y * invZ2)) / interpolatedInvZ;

        float pWorldZ = (frag.alpha * (vertex0.world.z * invZ0) + frag.beta * (vertex1.world.z * invZ1) +
            frag.gamma * (vertex2.world.z * invZ2)) / interpolatedInvZ;

        // Pixel World Position
        vec4 pixelWorldPos(pWorldX, pWorldY, pWorldZ, 1.0f);




        vec4 lightDir = solid_mode_world_light - pixelWorldPos;

        // Light fading
        float dot = worldNormal.dot(lightDir.normalize());

        if (dot > 0.0f)
        {
            float intensity = dot;

            totalLight += 255 * intensity;
        }

        // Texture and lighting mix
        sf::Uint8 finalColor = std::clamp(static_cast<int>(solid_color.r * (totalLight / 255.0f)), 0, 255);

        setPixel(frag.x, frag.y, finalColor, finalColor, finalColor);
    }
}