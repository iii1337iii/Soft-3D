#include "View_Control.hpp"


void viewport_control(const sf::Event& event, Mesh& object)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Num1: current_render_mode = render_mode::wireframe; break;
            case sf::Keyboard::Num2: current_render_mode = render_mode::solid; break;
            case sf::Keyboard::Num3: current_render_mode = render_mode::textured; break;
            case sf::Keyboard::Num4: current_render_mode = render_mode::rendered; break;
        }
    }
}