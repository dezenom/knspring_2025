#pragma once

#include <kn/KrakenEngine.hpp>

#include "Scene.hpp"
#include "utils.hpp"
#include "Player.hpp"
#include "keybinds.hpp"
#include "PolygonManager.hpp"

class Game
{
public:
    Game(const std::string& bg, const std::string& fg);

    void render();
    void update();

private:
    Scene background;
    Scene foreground;



    PolygonManager walls;
    PolygonManager xbounds;
    PolygonManager ybounds;
    kn::math::Vec2 mtv;

    Player player;
    std::vector<kn::math::Vec2> body;
    kn::math::Vec2 screendimensions;

};
