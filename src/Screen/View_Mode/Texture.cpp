#include "Texture.hpp"

namespace view_mode
{
	void texture(const sf::Image& texture,
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

        // --- UV texel ---
        if (texture.getSize().x == 0 || texture.getSize().y == 0)
        {
            texColor = sf::Color(255, 0, 255, 255);
        }
        else
        {
            unsigned int texX = static_cast<unsigned int>(u * (texture.getSize().x - 1));
            unsigned int texY = static_cast<unsigned int>((1.0f - v) * (texture.getSize().y - 1));
            texColor = texture.getPixel(texX, texY);
        }

        setPixel(frag.x, frag.y, texColor.r, texColor.g, texColor.b);
	}
}