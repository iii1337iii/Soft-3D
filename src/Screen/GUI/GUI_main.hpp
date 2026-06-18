#pragma once

#include <SFML/Graphics.hpp>
#include "../Main_Cycle.hpp"
#include "../../config.hpp"
#include "imgui.h"
#include "imgui-sfml.h"
#include "portable-file-dialogs.h"

#include "Menu_Bar/File.hpp"
#include "Menu_Bar/View_Mode.hpp"
#include "Menu_Bar/Background.hpp"
#include "Menu_Bar/Camera.hpp"
#include "Menu_Bar/Edit.hpp"
#include "Menu_Bar/Lighting.hpp"

void draw_GUI(sf::Window& window, mat4& projMatrix);