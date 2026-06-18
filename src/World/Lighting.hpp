#pragma once

#include <SFML/Graphics.hpp>
#include "../Math/vec4.hpp"

struct light_source
{
	bool is_deleted{ false };
	bool visible{ true };

	vec4 position;
	float radius;
	sf::Color color;

	void reset_transforms()
	{
		position = { 0.0f, 0.0f, 0.0f, 1.0f };
		radius = 5.0f;
		color = { 255, 255, 255 };
	}

	void delete_source()
	{
		position = { 0.0f, 0.0f, 0.0f, 1.0f };
		radius = 0.0f;
		color = { 0, 0, 0 };
		is_deleted = true;
	}
};

inline std::vector<light_source> light_sources;
inline int active_light_index = -1;