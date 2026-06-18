#pragma once

#include "vec4.hpp"
#include "../config.hpp"

struct mat4
{
    float m[4][4] = { 0 };

    static mat4 init()
    {
        mat4 matrix;
        matrix.m[0][0] = 1.0f;
        matrix.m[1][1] = 1.0f;
        matrix.m[2][2] = 1.0f;
        matrix.m[3][3] = 1.0f;
        return matrix;
    }



    vec4 multiply(const vec4& v) const
    {
        return
        {
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
            m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
        };
    }

    mat4 multiply(const mat4& other) const
    {
        mat4 res;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res.m[i][j] =
                    m[i][0] * other.m[0][j] +
                    m[i][1] * other.m[1][j] +
                    m[i][2] * other.m[2][j] +
                    m[i][3] * other.m[3][j];
            }
        }
        return res;
    }



    static mat4 translation(float tx, float ty, float tz)
    {
        mat4 res = init();
        res.m[0][3] = tx;
        res.m[1][3] = ty;
        res.m[2][3] = tz;
        return res;
    }



    static mat4 rotationX(float angleRad)
    {
        angleRad *= (PI / 180);
        mat4 res = init();
        res.m[1][1] = std::cos(angleRad);
        res.m[1][2] = -std::sin(angleRad);
        res.m[2][1] = std::sin(angleRad);
        res.m[2][2] = std::cos(angleRad);
        return res;
    }

    static mat4 rotationY(float angleRad)
    {
        angleRad *= (PI / 180);
        mat4 res = init();
        res.m[0][0] = std::cos(angleRad);
        res.m[0][2] = std::sin(angleRad);
        res.m[2][0] = -std::sin(angleRad);
        res.m[2][2] = std::cos(angleRad);
        return res;
    }

    static mat4 rotationZ(float angleRad)
    {
        angleRad *= (PI / 180);
        mat4 res = init();
        res.m[0][0] = std::cos(angleRad);
        res.m[0][1] = -std::sin(angleRad);
        res.m[1][0] = std::sin(angleRad);
        res.m[1][1] = std::cos(angleRad);
        return res;
    }



    static mat4 scale(float sx, float sy, float sz)
    {
        mat4 res = init();
        res.m[0][0] = sx;
        res.m[1][1] = sy;
        res.m[2][2] = sz;
        return res;
    }
};