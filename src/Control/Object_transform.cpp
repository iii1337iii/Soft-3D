#include "Object_transform.hpp"


action action_mode::current = action::view;
axis action_mode::direction = axis::none;


static void set_axis(const sf::Event& event, const action act)
{
    switch(event.key.code)
    {
        case sf::Keyboard::X: action_mode::direction = axis::x; break;
        case sf::Keyboard::Y: action_mode::direction = axis::y; break;
        case sf::Keyboard::Z: action_mode::direction = axis::z; break;
    }
}



static void move_object(const sf::Event& event, Mesh& object)
{
    set_axis(event, action::move);

    if (event.type == sf::Event::MouseWheelScrolled &&
        event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            switch (action_mode::direction)
            {
                case axis::x: object.mov_x += 0.1f; break;
                case axis::y: object.mov_y += 0.1f; break;
                case axis::z: object.mov_z += 0.1f; break;
            }
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            switch (action_mode::direction)
            {
                case axis::x: object.mov_x -= 0.1f; break;
                case axis::y: object.mov_y -= 0.1f; break;
                case axis::z: object.mov_z -= 0.1f; break;
            }
        }
    }
}



static void rotate_object(const sf::Event& event, Mesh& object)
{
    set_axis(event, action::rotate);

    if (event.type == sf::Event::MouseWheelScrolled &&
        event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            switch (action_mode::direction)
            {
            case axis::x: object.rot_x += 5.0f; break;
            case axis::y: object.rot_y += 5.0f; break;
            case axis::z: object.rot_z += 5.0f; break;
            }
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            switch (action_mode::direction)
            {
            case axis::x: object.rot_x -= 5.0f; break;
            case axis::y: object.rot_y -= 5.0f; break;
            case axis::z: object.rot_z -= 5.0f; break;
            }
        }
    }
}



static void scale_object(const sf::Event& event, Mesh& object)
{
    set_axis(event, action::scale);

    if (event.type == sf::Event::MouseWheelScrolled &&
        event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            switch (action_mode::direction)
            {
            case axis::x: object.scl_x += 0.1f; break;
            case axis::y: object.scl_y += 0.1f; break;
            case axis::z: object.scl_z += 0.1f; break;
            case axis::none: object.scl_x += 0.1f;  object.scl_y += 0.1f;  object.scl_z += 0.1f; break;
            }
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            switch (action_mode::direction)
            {
            case axis::x: object.scl_x -= 0.1f; break;
            case axis::y: object.scl_y -= 0.1f; break;
            case axis::z: object.scl_z -= 0.1f; break;
            case axis::none: object.scl_x -= 0.1f;  object.scl_y -= 0.1f;  object.scl_z -= 0.1f; break;
            }
        }
    }
}



void object_transform(const sf::Event& event, Mesh& object)
{
    switch (event.key.code)
    {
        case sf::Keyboard::M: action_mode::current = action::move; break;
        case sf::Keyboard::R: action_mode::current = action::rotate; break;
        case sf::Keyboard::S: action_mode::current = action::scale; break;
    }
    if (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left)
    { 
        action_mode::current = action::view; 
        action_mode::direction = axis::none;
    }



    switch (action_mode::current)
    {
        case action::view: break;
        case action::move: move_object(event, object); break;
        case action::rotate: rotate_object(event, object); break;
        case action::scale: scale_object(event, object); break;
    }
}