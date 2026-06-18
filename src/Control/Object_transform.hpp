#pragma once

#include <SFML/Graphics.hpp>
#include "../Object/Mesh_Data.hpp"

void object_transform(const sf::Event& event, Mesh& object);



enum action
{
	view,
	move,
	rotate,
	scale
};

enum axis
{
	none,
	x,
	y,
	z
};


struct action_mode
{
	static action current;
	static axis direction;
};