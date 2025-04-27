#pragma once

#include <kn/KrakenEngine.hpp>

#include "Scene.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "Player.hpp"
#include "keybinds.hpp"
#include "PolygonManager.hpp"

class Game
{
public:
    Game(const std::string& env);

    void render();
    void update();

private:
    Scene environment;



    PolygonManager walls;
    PolygonManager xbounds;
    PolygonManager ybounds;
    kn::math::Vec2 mtv;

    Player player;

    Coolcube c1;

};
