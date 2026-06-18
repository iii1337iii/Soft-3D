#include "Main_Cycle.hpp"


std::vector<sf::Uint8> frameBuffer(sizeX * sizeY * 4, 0);
std::vector<float> depthBuffer(sizeX * sizeY, 1.0f);
int cam::FOV = 90;


void render_cycle()
{
    sf::RenderWindow window({ sizeX, sizeY }, "Soft 3D", sf::Style::Default);
    sf::Image icon;
    if (icon.loadFromFile("data/icon.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    window.setVerticalSyncEnabled(true);


    ImGui::SFML::Init(window);
    ImGuiStyle& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(12, 12);
    style.ItemSpacing = ImVec2(50, 8);
    ImGui::GetIO().FontGlobalScale = 2.0f; 


    sf::Texture displayTexture;
    displayTexture.create(sizeX, sizeY);
    sf::Sprite displaySprite;
    displaySprite.setTexture(displayTexture, true);
    sf::Clock deltaClock;


    mat4 projMatrix = cam::set(cam::FOV, sizeX, sizeY);
    std::vector<vec4> worldPoints;
    std::vector<vec4> projectedPoints;


    std::vector<Tile> screenTiles;
    auto updateTiles = [&]()
    {
        screenTiles.clear();

        for (unsigned int y = 0; y < sizeY; y += TILE_SIZE) 
        {
            for (unsigned int x = 0; x < sizeX; x += TILE_SIZE) 
            {
                screenTiles.push_back(
                {
                    static_cast<int>(x),
                    static_cast<int>(y),
                    static_cast<int>(std::min(x + TILE_SIZE - 1, sizeX - 1)),
                    static_cast<int>(std::min(y + TILE_SIZE - 1, sizeY - 1))
                });
            }
        }
    };
    updateTiles();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            // --- Keybinds ---
            if (active_object_index != -1)
            {
                object_transform(event, objects[active_object_index]);
                viewport_control(event, objects[active_object_index]);
            }
            cam::FOV_control(event, projMatrix);


            if (event.type == sf::Event::Closed) { window.close(); }


            else if (event.type == sf::Event::Resized) 
            { 
                unsigned int newW = std::max(1u, window.getSize().x);
                unsigned int newH = std::max(1u, window.getSize().y);

                projMatrix = cam::set(cam::FOV, newW, newH);

                displayTexture.create(newW, newH);
                displaySprite.setTexture(displayTexture, true);

                frameBuffer.resize(newW * newH * 4, 0);
                depthBuffer.resize(newW * newH, 1.0f);

                sizeX = newW;
                sizeY = newH;

                updateTiles();
            }
        }
        if (CURRENT_TILE_SIZE != TILE_SIZE) { updateTiles(); }



        // --- Frame Math ---
        std::fill(frameBuffer.begin(), frameBuffer.end(), 0);
        std::fill(depthBuffer.begin(), depthBuffer.end(), 1.0f);

        std::vector<RenderTriangle> frameTriangles;
        frameTriangles.reserve(100000);


        for (auto& obj : objects)
        {
            if (obj.is_deleted || !obj.visible) { continue; }

            worldPoints.resize(obj.vertices.size());
            projectedPoints.resize(obj.vertices.size());

            // Scale * Rotation * Translation
            mat4 scale_matrix = mat4::scale(obj.scl_x, obj.scl_y, obj.scl_z);

            mat4 rot_x = mat4::rotationX(obj.rot_x);
            mat4 rot_y = mat4::rotationY(obj.rot_y);
            mat4 rot_z = mat4::rotationZ(obj.rot_z);
            mat4 rotation_matrix = rot_z.multiply(rot_y).multiply(rot_x);

            mat4 move_matrix = mat4::translation(obj.mov_x, obj.mov_y, obj.mov_z);


            mat4 final_matrix = move_matrix.multiply(rotation_matrix).multiply(scale_matrix);


            // Apply for each vertex
            for (size_t i = 0; i < obj.vertices.size(); ++i)
            {
                vec4 world = final_matrix.multiply(obj.vertices[i]);
                worldPoints[i] = world;
                vec4 clip = projMatrix.multiply(world);


                vec4 ndc;
                if (clip.w <= 0.0001f)
                {
                    projectedPoints[i] = { -10000.0f, -10000.0f, -10000.0f, -1.0f };
                    continue;
                }
                ndc.x = clip.x / clip.w;
                ndc.y = clip.y / clip.w;
                ndc.z = clip.z / clip.w;


                float screenX = (ndc.x + 1.0f) * 0.5f * sizeX;
                float screenY = (1.0f - ndc.y) * 0.5f * sizeY;

                projectedPoints[i] = { screenX, screenY, ndc.z, clip.w };
            }

            // --- Draw ---
            screen_render(obj, projectedPoints, worldPoints, frameTriangles);
        }

        if (current_render_mode != render_mode::wireframe)
        {
            std::for_each(std::execution::par, screenTiles.begin(), screenTiles.end(), [&](const Tile& tile)
            {
                for (const auto& tri : frameTriangles)
                {
                    drawTriangle(tri.v0, tri.v1, tri.v2, *(tri.texture), tri.worldNormal, tile);
                }
            });
        }
        else
        {
            for (const auto& tri : frameTriangles) 
            {
                view_mode::wireframe(tri.v0, tri.v1, tri.v2);
            }
        }



        sf::View view(sf::FloatRect(0.0f, 0.0f, static_cast<float>(sizeX), static_cast<float>(sizeY)));
        window.setView(view);
        window.clear(background);


        displayTexture.update(frameBuffer.data());
        window.draw(displaySprite);
        if (!save_screenshot_path.empty())
        {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);

            sf::Image screenshot = texture.copyToImage();
            screenshot.saveToFile(save_screenshot_path);

            save_screenshot_path.clear();
        }


        ImGui::SFML::Update(window, deltaClock.restart());
        draw_GUI(window, projMatrix);
        ImGui::SFML::Render(window);


        window.display();
    }

    ImGui::SFML::Shutdown();
}