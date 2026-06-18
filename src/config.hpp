#pragma once

#include <cmath>
#include <numbers>


enum render_mode
{
	wireframe,
	solid,
	textured,
	rendered
};
inline render_mode current_render_mode = render_mode::solid;



inline int TILE_SIZE = 512;
inline int CURRENT_TILE_SIZE = TILE_SIZE;

inline unsigned int sizeX = 1200;
inline unsigned int sizeY = 720;

inline std::string save_screenshot_path = "";



constexpr float PI = std::numbers::pi_v<float>;