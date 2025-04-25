#include "Game.hpp"


Game::Game(const std::string& bg, const std::string& fg):background({0,-800},bg),foreground({0,-800},fg),
walls("res/data/saves/polygons/walls.json"),xbounds("res/data/saves/polygons/xbounds.json"),ybounds("res/data/saves/polygons/ybounds.json"),
player("res/images/animations/player.png",{0,0},{16,16}),body(utils::getVertices(player.getRect())),
screendimensions(640,320){
    setBinds();
}

void Game::render(){
        kn::window::clear({40,40,40,255});
    background.render();
    player.render();
    foreground.render();
    walls.render();
    kn::window::flip();
}
void Game::update(){
    walls.update();
    mtv = {0,0};
    player.update();
    body = utils::getVertices(player.getRect());
    for(const auto& polygon:walls.polygons){
        if(utils::SATCollision(body,polygon,mtv)){
            player.getRect().x -= mtv.x;
            player.getRect().y -= mtv.y;
        }
    }

    bool xfreeze = false;
    for(const auto& polygon:xbounds.polygons){
        if(utils::SATCollision(body,polygon,mtv)){
            xfreeze = true;
        }
        if(xfreeze)break;
    }
    bool yfreeze = false;
    for(const auto& polygon:ybounds.polygons){
        if(utils::SATCollision(body,polygon,mtv)){
            yfreeze = true;
        }
        if(yfreeze)break;
    }

    if (!xfreeze)
        kn::camera.x = player.getRect().center().x - screendimensions.x/2;
    if(!yfreeze)
        kn::camera.y = player.getRect().center().y - screendimensions.y/2;
}
