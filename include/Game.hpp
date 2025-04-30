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

    bool collision(const std::vector<kn::math::Vec2>& body,
                         const std::unordered_map<std::string, std::vector<std::vector<kn::math::Vec2>>>& cpolygons,
                         const std::vector<std::string>& chunks);
private:
    Scene environment;



    PolygonManager walls;
    PolygonManager xbounds;
    PolygonManager ybounds;

    PolygonManager dmg;
    kn::math::Vec2 check;
    PolygonManager checks;
    PolygonManager door;

    kn::math::Vec2 mtv;

    Player player;

    Coolcube c1;

};
