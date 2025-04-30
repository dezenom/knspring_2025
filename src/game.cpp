#include "Game.hpp"


Game::Game(const std::string& env):environment({0,0},env),
walls("res/data/saves/polygons/walls.json"),xbounds("res/data/saves/polygons/xbounds.json"),ybounds("res/data/saves/polygons/ybounds.json"),dmg("res/data/saves/polygons/dmg.json"),
checks("res/data/saves/polygons/checks.json"),door("res/data/saves/polygons/door.json"),
player("res/images/animations/player.png",{300,900},{24,16}),c1(&player){
    setBinds();
    walls.clean();
    xbounds.clean();
    ybounds.clean();

    dmg.clean();
    checks.clean();
    door.clean();
}

void Game::render(){
        kn::window::clear({40,40,40,255});
    environment.render(player.getRect().x);
    player.render();
    c1.render();
    // checks.render();
        kn::window::flip();
}
void Game::update(){
    // checks.update();
    mtv = {0,0};
    player.update();
    c1.update();

    for(const auto& chunk:player.chunks){
        if(walls.chunked.find(chunk) != walls.chunked.end()){
            for(const auto& polygon:walls.chunked[chunk]){
                if(utils::SATCollision(player.getBody(),polygon,mtv)){
                    player.getRect().x -= mtv.x;
                    player.getRect().y -= mtv.y;
                    player.getBody() = utils::getVertices(player.getRect());
                }
            }
        }
    } //doesnt work weirdly
    if(mtv.y>0 and player.getGravityVector().y > 0){
        player.getGravityVector().y = 0;
        player.onground = true;
    }

    if(collision(player.getBody(),checks.chunked,player.chunks)){
        check = {player.getRect().x,player.getRect().y};
    }
    if(collision(player.getBody(),dmg.chunked,player.chunks)){
        player.getRect().x = check.x;player.getRect().y = check.y;
    }

    bool xfreeze = collision(player.getBody(),xbounds.chunked,player.chunks);
    bool yfreeze = collision(player.getBody(),ybounds.chunked,player.chunks);

    if (!xfreeze)
        kn::camera.x = player.getRect().center().x - screendimensions.x/2;
    if(!yfreeze)
        kn::camera.y = player.getRect().center().y - screendimensions.y/2;


}

bool Game::collision(const std::vector<kn::math::Vec2>& body,
                     const std::unordered_map<std::string, std::vector<std::vector<kn::math::Vec2>>>& cpolygons,
                     const std::vector<std::string>& chunks)
{
    for (const auto& chunk : chunks) {
        auto it = cpolygons.find(chunk);
        if (it != cpolygons.end()) {
            for (const auto& polygon : it->second) {
                if (utils::SATCollision(body, polygon, mtv)) {
                    return true;
                }
            }
        }
    }
    return false; // No collision found
}
