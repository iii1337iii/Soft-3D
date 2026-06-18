#include "Rendered.hpp"

namespace view_mode
{
    void rendered(const sf::Image& texture, const vec4& worldNormal,
                  const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2,
                  const Fragment& frag)
    {
        // InvZ = 1/Z
        float invZ0 = 1.0f / vertex0.projected.w;
        float invZ1 = 1.0f / vertex1.projected.w;
        float invZ2 = 1.0f / vertex2.projected.w;

        float interpolatedInvZ = frag.alpha * invZ0 + frag.beta * invZ1 + frag.gamma * invZ2;

        float u = (frag.alpha * (vertex0.texture.u * invZ0) + frag.beta * (vertex1.texture.u * invZ1) +
            frag.gamma * (vertex2.texture.u * invZ2)) / interpolatedInvZ;

        float v = (frag.alpha * (vertex0.texture.v * invZ0) + frag.beta * (vertex1.texture.v * invZ1) +
            frag.gamma * (vertex2.texture.v * invZ2)) / interpolatedInvZ;

        u = std::clamp(u, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        sf::Color texColor;

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
        {
            texColor = sf::Color(100, 100, 100, 255);
        }
        else
        {
            unsigned int texX = static_cast<unsigned int>(u * (texture.getSize().x - 1));
            unsigned int texY = static_cast<unsigned int>((1.0f - v) * (texture.getSize().y - 1));

            texColor = texture.getPixel(texX, texY);
        }



        // --- World Light Sources ---
        float totalLightR = 0.1f;
        float totalLightG = 0.1f;
        float totalLightB = 0.1f;

        // World space pixel interpolation
        float pWorldX = (frag.alpha * (vertex0.world.x * invZ0) + frag.beta * (vertex1.world.x * invZ1) +
            frag.gamma * (vertex2.world.x * invZ2)) / interpolatedInvZ;

        float pWorldY = (frag.alpha * (vertex0.world.y * invZ0) + frag.beta * (vertex1.world.y * invZ1) +
            frag.gamma * (vertex2.world.y * invZ2)) / interpolatedInvZ;

        float pWorldZ = (frag.alpha * (vertex0.world.z * invZ0) + frag.beta * (vertex1.world.z * invZ1) +
            frag.gamma * (vertex2.world.z * invZ2)) / interpolatedInvZ;

        // Pixel World Position
        vec4 pixelWorldPos(pWorldX, pWorldY, pWorldZ, 1.0f);


        for (auto& light : light_sources)
        {
            if (light.is_deleted || !light.visible) { continue; }

            vec4 lightDir = light.position - pixelWorldPos;

            // Distance between pixel and light source
            float distance = std::sqrt(
                lightDir.x * lightDir.x +
                lightDir.y * lightDir.y +
                lightDir.z * lightDir.z);

            // Light fading
            float kc = 1.0f;
            float kl = 4.5f / light.radius;
            float kq = 75.0f / (light.radius * light.radius);

            float attenuation = 1.0f / (kc + kl * distance + kq * distance * distance);

            if (distance > light.radius) { attenuation = 0.0f; }
            if (attenuation > 0.0f)
            {
                float dot = worldNormal.dot(lightDir.normalize());

                if (dot > 0.0f)
                {
                    float intensity = dot * attenuation;

                    totalLightR += light.color.r * intensity;
                    totalLightG += light.color.g * intensity;
                    totalLightB += light.color.b * intensity;
                }
            }
        }

        // Texture and lighting mix
        sf::Uint8 finalR = std::clamp(static_cast<int>(texColor.r * (totalLightR / 255.0f)), 0, 255);
        sf::Uint8 finalG = std::clamp(static_cast<int>(texColor.g * (totalLightG / 255.0f)), 0, 255);
        sf::Uint8 finalB = std::clamp(static_cast<int>(texColor.b * (totalLightB / 255.0f)), 0, 255);

        setPixel(frag.x, frag.y, finalR, finalG, finalB);
    }
}