#pragma once

#include <SFML/Graphics.hpp>
#include "../Math/vec4.hpp"
#include "../Math/mat4x4.hpp"
#include "../config.hpp"

struct cam
{
    static int FOV;

    static mat4 perspective(const float fov, const float aspect, const float zNear, const float zFar)
    {
        mat4 res;

        float tanHalfFov = std::tan(fov / 2.0f);

        res.m[0][0] = 1.0f / (aspect * tanHalfFov);             // X_world to X_screen
        res.m[1][1] = 1.0f / tanHalfFov;                        // Y_world to Y_screen

        res.m[2][2] = (zFar + zNear) / (zFar - zNear);          // A
        res.m[2][3] = -(2.0f * zFar * zNear) / (zFar - zNear);  // B

        res.m[3][2] = 1.0f;                                     // Z direction (+1/-1)

        return res;
    }


    static mat4 set(const unsigned short fov_degrees, const int new_sizeX, const int new_sizeY)
    {
        float fov_radians = fov_degrees * (PI / 180.0f); // degrees to radians
        float aspect = static_cast<float>(new_sizeX) / static_cast<float>(new_sizeY);
        mat4 projMatrix = cam::perspective(fov_radians, aspect, 0.1f, 100.0f);
        return projMatrix;
    }


    static void FOV_control(const sf::Event& event, mat4& projMatrix)
    {
        if (event.type == sf::Event::MouseWheelScrolled &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        {
            if (event.mouseWheelScroll.delta > 0 && cam::FOV < 179)
            {
                ++cam::FOV;
            }
            else if (event.mouseWheelScroll.delta < 0 && cam::FOV > 1)
            {
                --cam::FOV;
            }

            projMatrix = cam::set(cam::FOV, sizeX, sizeY);
        }
    }
};