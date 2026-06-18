#pragma once

#include <cmath>

struct vec4
{
	float x, y, z, w;

    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}



	float length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	// [-1.0 ; +1.0]
	vec4 normalize() const
	{
		float len = length();
		if (len > 0.0f)
		{
			return { x / len, y / len, z / len, w };
		}
		return { 0.0f, 0.0f, 0.0f, w };
	}



	// Scalar
	float dot(const vec4& other) const
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	// Vector
	vec4 cross(const vec4& other) const
	{
		return
		{
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x,
			w
		};
	}



	vec4 operator-(const vec4& other) const { return { x - other.x, y - other.y, z - other.z, 1.0f }; }
	vec4 operator+(const vec4& other) const { return { x + other.x, y + other.y, z + other.z, 1.0f }; }
	vec4 operator*(const vec4& other) const { return { x * other.x, y * other.y, z * other.z, 1.0f }; }
};