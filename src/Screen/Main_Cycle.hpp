#pragma once

#include <SFML/Graphics.hpp>
#include <execution>
#include "../config.hpp"
#include "../Math/vec4.hpp"
#include "../Math/mat4x4.hpp"
#include "../World/Camera.hpp"
#include "../Object/Mesh_Data.hpp"
#include "../Control/Object_transform.hpp"
#include "../Control/View_Control.hpp"
#include "Data/Render_Data.hpp"
#include "GUI/GUI_main.hpp"
#include "Screen_Render.hpp"
#include "imgui.h"
#include "imgui-sfml.h"

void render_cycle();

extern std::vector<sf::Uint8> frameBuffer;
extern std::vector<float> depthBuffer;
inline sf::Color background{150, 150, 150};